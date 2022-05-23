
#include <apis/window.h>
#include <apis/api_registry.h>
#include <core/core.h>
#include <core/os.h>
#include <core/types.h>

#include <windows.h>

struct ae_native_window
{
#ifdef _WIN32
	HWND	handle;
	HDC		device;
#endif // _WIN32
};

static struct ae_window* main_window = NULL;
static bool close = true;

static LRESULT CALLBACK main_window_callback(HWND window, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		close = false;
	}

	return DefWindowProcA(window, msg, wparam, lparam);
}

static LRESULT CALLBACK child_window_callback(HWND window, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(window);
		return 0;
	case WM_NCHITTEST:
	{
		LRESULT hit = DefWindowProc(window, msg, wparam, lparam);
		if (hit == HTCLIENT)
			hit = HTCAPTION;
		return hit;
	};
	}

	return DefWindowProcA(window, msg, wparam, lparam);
}

static DWORD ae_window_get_style(const enum ae_window_flags flags)
{
	DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	style |= WS_SYSMENU | WS_MINIMIZEBOX;

	if (flags & AE_WINDOW_DECORATED)
	{
		style |= WS_CAPTION;

		if (flags & AE_WINDOW_RESIZABLE)
			style |= WS_MAXIMIZEBOX | WS_THICKFRAME;
	}
	else
		style |= WS_POPUP;

	return style;
}

static DWORD ae_window_get_style_ex(const enum ae_window_flags flags)
{
	DWORD style = WS_EX_APPWINDOW;

	if (flags & AE_WINDOW_HOVERED)
		style |= WS_EX_TOPMOST;

	return style;
}

static struct ae_window* ae_window_create(struct ae_window* parent, struct ae_create_window_params* params)
{
	struct ae_window* window = malloc(sizeof(*window));

	if (!window)
		return NULL;

	window->native_handle = malloc(sizeof(*window->native_handle));

	if (!window->native_handle)
	{
		free(window);
		return NULL;
	}

	HMODULE instance = NULL;

	instance = GetModuleHandle(NULL);

	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = parent ? child_window_callback : main_window_callback;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = parent ? "ae_window_main" : "ae_window";
	wcex.hIconSm = NULL;

	if (!RegisterClassEx(&wcex))
	{
		return NULL;
	};

	window->native_handle->handle = CreateWindowExA(
		ae_window_get_style_ex(params->flags),
		wcex.lpszClassName,
		params->title,
		ae_window_get_style(params->flags),
		params->position_x,
		params->position_y,
		params->width - params->position_x,
		params->height - params->position_y,
		parent ? parent->native_handle->handle : NULL,
		0,
		instance,
		0);

	window->native_handle->device = GetDC(window->native_handle->handle);
	window->size[0] = (float)params->width;
	window->size[1] = (float)params->height;
	window->position[0] = (float)params->position_x;
	window->position[1] = (float)params->position_y;
	window->flags = params->flags;

	if (params->flags & AE_WINDOW_VISIBLE)
		ShowWindow(window->native_handle->handle, true);

	if (params->flags & AE_WINDOW_FOCUSED && (params->flags & AE_WINDOW_MAXIMIZED) == 0)
		SetFocus(window->native_handle->handle);

	return window;
}

static struct ae_window* ae_window_get_main_window()
{
	return main_window;
}

static struct ae_window* ae_window_get_or_create_main_window(struct ae_create_window_params* params)
{
	if (main_window)
		return main_window;

	main_window = ae_window_create(NULL, params);

	return main_window;
}

static void ae_window_show(struct ae_window* window, const bool show)
{
	if (show)
		ShowWindow(window->native_handle->handle, SW_SHOW);
	else
		ShowWindow(window->native_handle->handle, SW_HIDE);
}

static struct ae_native_window* ae_window_get_native_window(struct ae_window* window)
{
	return window->native_handle;
}

static bool ae_window_update(struct ae_window* window)
{
	struct ae_native_window* native_window = ae_window_get_native_window(window);
	SwapBuffers(native_window->device);

	MSG msg;
	while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
	{
		switch (msg.message)
		{
		case WM_INPUT:
			return true;
		default:
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	return close;
}

static void ae_window_destroy(struct ae_window* window)
{
	DestroyWindow(window->native_handle->handle);
}

static struct ae_window* ae_window_create_child(struct ae_window* parent, struct ae_create_window_params* params)
{
	return ae_window_create(parent, params);
}

static const struct ae_window_api window_api =
{
	.get_window = ae_window_get_main_window,
	.get_or_create = ae_window_get_or_create_main_window,
	.create_child = ae_window_create_child,
	.destroy = ae_window_destroy,
	.update = ae_window_update,
	.show = ae_window_show,
	.get_native_window = ae_window_get_native_window
};

AE_DLL_EXPORT void plugin_load(struct ae_api_registry_api* registry, bool reload)
{
	AE_UNREFERENCED_PARAMETER(reload);
	ae_set_api(registry, ae_window_api, &window_api);
}

AE_DLL_EXPORT void plugin_unload(struct ae_api_registry_api* registry)
{
	AE_UNREFERENCED_PARAMETER(registry);
}
