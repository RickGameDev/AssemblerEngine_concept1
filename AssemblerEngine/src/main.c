#include <AssemblerEngine/api_registry.h>
#include <AssemblerEngine/plugin_registry.h>

#include <core/vector.h>

#include <apis/application.h>
#include <apis/api_registry.h>
#include <apis/camera.h>
#include <apis/logging.h>
#include <apis/plugin_registry.h>
#include <apis/renderer.h>
#include <apis/shader.h>
#include <apis/window.h>
#include <apis/opengl_backend.h>
#include <apis/imgui.h>

static const struct ae_create_window_params main_window_params =
{
	.title = "test",
	.position_x = 0,
	.position_y = 0,
	.height = 720,
	.width = 1280,
	.flags = AE_WINDOW_DECORATED | AE_WINDOW_VISIBLE
};

const char* default_vertex = "\
#version 430\n\
layout(location = 0) in vec4 a_color;\n\
layout(location = 1) in vec3 a_position;\n\
layout(location = 2) in vec2 a_textureCoordinate;\n\
layout(location = 3) in float a_textureUnit;\n\
\n\
layout (std140, binding = 0) uniform ViewProjection \n\
{\n\
mat4 viewProjection;\n\
};\n\
\n\
out vec4 v_color;\n\
out vec2 v_textureCoordinate;\n\
out float v_textureUnit;\n\
\n\
void main()\n\
{\
	v_color = a_color;\n\
	v_textureCoordinate = a_textureCoordinate;\n\
	v_textureUnit = a_textureUnit;\n\
\n\
	gl_Position = viewProjection * vec4(a_position, 1.0);\n\
};";

const char* default_fragment = "\
#version 430\n\
\n\
layout(location = 0) out vec4 o_color;\n\
\n\
uniform sampler2D u_textures[32];\n\
\n\
in vec4 v_color;\n\
in vec2 v_textureCoordinate;\n\
in float v_textureUnit;\n\
\n\
void main()\n\
{\n\
	int index = int(v_textureUnit);\n\
\n\
	// vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_textures[index], v_textureCoordinate).r);\n\
	// o_color = sampled * v_color;\n\
\n\
	o_color = texture(u_textures[index], v_textureCoordinate) * v_color;\n\
};";

char debug[255];

int main()
{
	// create api register
	struct ae_api_registry_api* api_registry_api = &(struct ae_api_registry_api)
	{
		.registry = ae_api_registry_new(),
		.get_api = ae_api_registry_get_api,
		.set_api = ae_api_registry_set_api,
		.remove_api = ae_api_registry_remove_api
	};

	ae_set_api(api_registry_api, ae_api_registry_api, api_registry_api);

	// register core plugins
	struct ae_plugin_registry_api* plugin_registry_api = ae_get_api(api_registry_api, ae_plugin_registry_api);
	plugin_registry_api->registry = ae_plugin_registry_new();
	plugin_registry_api->load = ae_plugin_registry_load;
	plugin_registry_api->reload = ae_plugin_registry_reload;
	plugin_registry_api->unload = ae_plugin_registry_unload;

	// register other plugins
	plugin_registry_api->load(plugin_registry_api->registry, api_registry_api, "./");

	// get other plugins
	struct ae_logging_api* ae_logging_api = ae_get_api(api_registry_api, ae_logging_api);
	struct ae_window_api* ae_window_api = ae_get_api(api_registry_api, ae_window_api);
	struct ae_opengl_backend_api* ae_render_backend_api = ae_get_api(api_registry_api, ae_opengl_backend_api);
	//struct ae_renderer_api* ae_renderer_api = ae_get_api(api_registry_api, ae_renderer_api);
	//struct ae_shader_api* ae_shader_api = ae_get_api(api_registry_api, ae_shader_api);
	//struct ae_camera_api* ae_camera_api = ae_get_api(api_registry_api, ae_camera_api);
	struct ae_imgui_api* ae_imgui_api = ae_get_api(api_registry_api, ae_imgui_api);

	//// initialize apis
	ae_logging_api->get_or_create_main_logger(LEVEL_INFO);
	struct ae_window* window = ae_window_api->get_or_create(&main_window_params);
	ae_render_backend_api->get_or_create(window);
	//struct ae_camera* camera = ae_camera_api->create_orthographic((vec3)
	//{
	//	0, 0, 0
	//}, 1280.0f / 720.0f, 0.0f, 1000.0f, 0.0f, 1000.0f, 0.0f, 1.0f);
	//struct ae_shader* shader = ae_shader_api->create_basic(debug, 255, default_vertex, default_fragment);
	//struct ae_render_batch* batch = ae_renderer_api->render_batch_create(shader, 1024);

	ae_log_info("Starting AssemblerEngine...");

	bool running = true;

	ae_imgui_api->init(window);

	while (running)
	{
		ae_imgui_api->styles_push_size((vec2){1280.0f, 720.0f });
		ae_imgui_api->styles_push_background_color((vec4){ 1.0f, 0.0f, 0.0f, 1.0f });

		ae_imgui_api->start_viewport("test");

		ae_imgui_api->styles_pop_size();
		ae_imgui_api->styles_pop_background_color();

		ae_imgui_api->end_viewport();

		running = ae_window_api->update(window);
	}

	ae_log_info("Shuttingdown AssemblerEngine...");
}