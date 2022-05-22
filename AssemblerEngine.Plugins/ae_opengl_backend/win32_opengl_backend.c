#include "wgl.h"
#include "opengl_renderer.h"
#include "opengl_shader.h"

#include <apis/opengl_backend.h>
#include <apis/api_registry.h>
#include <apis/renderer.h>
#include <apis/shader.h>
#include <apis/window.h>
#include <core/core.h>
#include <core/os.h>
#include <math/vec3.h>
#include "glad/glad.h"

#include <stdio.h>
#include <assert.h>



typedef void* opengl_fn;

struct ae_opengl_backend
{
	HGLRC					render_context;
	PIXELFORMATDESCRIPTOR	pixel_format_desc;
	int						pixel_format_id;
};

struct ae_native_window
{
#ifdef _WIN32
	HWND	handle;
	HDC		device;
#endif // _WIN32
};

static HMODULE					 opengl_instance = NULL;
static struct ae_opengl_backend* render_backend = NULL;
static struct ae_window_api*	 ae_window_api = NULL;

void opengl_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	const char* src_str;
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		src_str = "API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		src_str = "WINDOW SYSTEM";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		src_str = "SHADER COMPILER";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		src_str = "THIRD PARTY";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		src_str = "APPLICATION";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		src_str = "OTHER";
		break;
	}

	const char* type_str;
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		type_str = "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		type_str = "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		type_str = "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		type_str = "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		type_str = "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_MARKER:
		type_str = "MARKER";
		break;
	case GL_DEBUG_TYPE_OTHER:
		type_str = "OTHER";
		break;
	}

	const char* severity_str;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		severity_str = "NOTIFICATION";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		severity_str = "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		severity_str = "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		severity_str = "HIGH";
		break;
	}

	printf("%s, %s, %s, %i: %s \n", src_str, type_str, severity_str, id, message);
}

static opengl_fn opengl_backend_get_opengl_proc_address(const char* name)
{
	void* proc = (void*)wglGetProcAddress(name);

	if (!proc)
		proc = (void*)GetProcAddress(opengl_instance, name);

	return proc;
}


static LRESULT CALLBACK dummy_window_procedure(HWND window, UINT message, WPARAM param_w, LPARAM param_l)
{
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(window, message, param_w, param_l);
}

static void ae_opengl_backend_set_debug_callback(ae_renderer_opengl_debug_callback_fn callback)
{
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(callback, NULL);
}

static struct ae_opengl_backend* opengl_get_or_create(struct ae_window* window)
{
	assert(ae_window_api);

	if (render_backend)
		return render_backend;

	struct ae_native_window* native_window = ae_window_api->get_native_window(window);

	// create dummy window
	HINSTANCE dummy_instance = NULL;
	WNDCLASSEX dummy_class = { 0 };
	PIXELFORMATDESCRIPTOR dummy_pixel_desc = { 0 };

	dummy_instance = GetModuleHandle(NULL);

	if (!dummy_instance)
		return NULL;

	dummy_class.cbSize = sizeof(dummy_class);
	dummy_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	dummy_class.lpfnWndProc = dummy_window_procedure;
	dummy_class.hInstance = dummy_instance;
	dummy_class.hCursor = LoadCursor(NULL, IDC_CROSS);
	dummy_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	dummy_class.lpszClassName = TEXT("dummy");
	dummy_class.cbWndExtra = sizeof(window);

	RegisterClassEx(&dummy_class);

	HWND dummy_window = CreateWindow(
		TEXT("dummy"),
		TEXT("DummyWindow"),
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0, 0,
		1, 1,
		NULL,
		NULL,
		dummy_instance,
		NULL);

	HDC dummy_device_context = GetDC(dummy_window);

	dummy_pixel_desc.nSize = sizeof(dummy_pixel_desc);
	dummy_pixel_desc.nVersion = 1;
	dummy_pixel_desc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	dummy_pixel_desc.iPixelType = PFD_TYPE_RGBA;
	dummy_pixel_desc.cColorBits = 32;
	dummy_pixel_desc.cAlphaBits = 8;
	dummy_pixel_desc.cDepthBits = 24;

	int dummy_pixel_format_id = ChoosePixelFormat(dummy_device_context, &dummy_pixel_desc);
	SetPixelFormat(dummy_device_context, dummy_pixel_format_id, &dummy_pixel_desc);

	HGLRC dummy_render_context = wglCreateContext(dummy_device_context);

	if (!wglMakeCurrent(dummy_device_context, dummy_render_context))
		return NULL;

	opengl_instance = LoadLibrary(TEXT("opengl32.dll"));

	PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB = opengl_backend_get_opengl_proc_address("wglGetExtensionsStringARB");
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = opengl_backend_get_opengl_proc_address("wglChoosePixelFormatARB");
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = opengl_backend_get_opengl_proc_address("wglCreateContextAttribsARB");

	const int pixelAttribs[] = {
		WGL_DRAW_TO_WINDOW_ARB, 1,
		WGL_SUPPORT_OPENGL_ARB, 1,
		WGL_DOUBLE_BUFFER_ARB, 1,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_SAMPLES_ARB, 4,
		0
	};

	if (!(render_backend = malloc(sizeof(*render_backend))))
		return NULL;

	memset(&render_backend->pixel_format_desc, 0, sizeof(render_backend->pixel_format_desc));

	UINT num_formats;
	if (!wglChoosePixelFormatARB(dummy_device_context, pixelAttribs, NULL, 1, &render_backend->pixel_format_id, &num_formats))
		return NULL;

	wglMakeCurrent(dummy_device_context, NULL);
	wglDeleteContext(dummy_render_context);
	ReleaseDC(dummy_window, dummy_device_context);
	DestroyWindow(dummy_window);

	DescribePixelFormat(native_window->device, render_backend->pixel_format_id, sizeof(render_backend->pixel_format_desc), &render_backend->pixel_format_desc);
	SetPixelFormat(native_window->device, render_backend->pixel_format_id, &render_backend->pixel_format_desc);

	const int major_min = 4, minor_min = 6;
	int  contextAttribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	render_backend->render_context = wglCreateContextAttribsARB(native_window->device, 0, contextAttribs);
	wglMakeCurrent(native_window->device, render_backend->render_context);

	gladLoadGLLoader(opengl_backend_get_opengl_proc_address);

	ae_opengl_backend_set_debug_callback(opengl_message_callback);

	return render_backend;
}

static void opengl_backend_destroy(struct ae_opengl_backend* backend)
{

}

static void opengl_backend_set_window(struct ae_opengl_backend* backend, struct ae_window* window)
{
	HDC device = ae_window_api->get_native_window(window)->device;

	if (!GetPixelFormat(device))
	{
		DescribePixelFormat(device, backend->pixel_format_id, sizeof(backend->pixel_format_desc), &backend->pixel_format_desc);
		SetPixelFormat(device, backend->pixel_format_id, &backend->pixel_format_desc);
	}

	if (!wglMakeCurrent(device, backend->render_context))
	{
		DWORD error = GetLastError();
		LPSTR message = NULL;

		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&message, 0, NULL);

		printf(message);

		LocalFree(message);
	}
	
	glViewport(0, 0, window->size[0], window->size[1]);
}

static struct ae_opengl_backend* ae_opengl_backend_get()
{
	return render_backend;
}

static const struct ae_opengl_backend_api opengl_backend_api =
{
	.get = ae_opengl_backend_get,
	.get_or_create = opengl_get_or_create,
	.destroy = opengl_backend_destroy,
	.set_window = opengl_backend_set_window
};

static const struct ae_shader_api shader_api =
{
	.create = ae_shader_create,
	.create_basic = ae_shader_create_basic
};

static const struct ae_renderer_api render_api =
{
	.render_batch_create = ae_render_batch_create,
	.render_batch_destroy = ae_render_batch_destroy,
	.render_scene_start = ae_render_scene_start,
	.render_batch_start = ae_render_batch_start,
	.render_batch_end = ae_render_batch_end,
	.render_batch_draw = ae_render_batch_draw,
	.render_batch_draw_textured = ae_render_batch_draw_textured
};

AE_DLL_EXPORT plugin_load(struct ae_api_registry_api* registry, bool reload)
{
	ae_window_api = ae_get_api(registry, ae_window_api);

	ae_set_api(registry, ae_opengl_backend_api, &opengl_backend_api);
	ae_set_api(registry, ae_renderer_api, &render_api);
	ae_set_api(registry, ae_shader_api, &shader_api);
}

AE_DLL_EXPORT plugin_unload(struct ae_api_registry_api* registry)
{

}
