//#include <AssemblerEngine/api_registry.h>
//#include <AssemblerEngine/plugin_registry.h>
//#include <AssemblerEngine/ae_filesystem_internal.h>

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

//static const struct ae_create_window_params main_window_params =
//{
//	.title = "test",
//	.position_x = 0,
//	.position_y = 0,
//	.height = 720,
//	.width = 1280,
//	.flags = AE_WINDOW_DECORATED | AE_WINDOW_VISIBLE
//};

//char debug[255];

//int main()
//{
//	// create api register
//	struct ae_api_registry_api* api_registry_api = &(struct ae_api_registry_api)
//	{
//		.registry = ae_api_registry_new(),
//		.get_api = ae_api_registry_get_api,
//		.set_api = ae_api_registry_set_api,
//		.remove_api = ae_api_registry_remove_api
//	};
//
//	ae_set_api(api_registry_api, ae_api_registry_api, api_registry_api);
//
//	// register core plugins
//	struct ae_plugin_registry_api* plugin_registry_api = ae_get_api(api_registry_api, ae_plugin_registry_api);
//	plugin_registry_api->registry = ae_plugin_registry_new();
//	plugin_registry_api->load = ae_plugin_registry_load;
//	plugin_registry_api->reload = ae_plugin_registry_reload;
//	plugin_registry_api->unload = ae_plugin_registry_unload;
//
//	// register other plugins
//	plugin_registry_api->load(plugin_registry_api->registry, api_registry_api, "./");
//
//	// get other plugins
//	struct ae_logging_api* ae_logging_api = ae_get_api(api_registry_api, ae_logging_api);
//	struct ae_window_api* ae_window_api = ae_get_api(api_registry_api, ae_window_api);
//	struct ae_opengl_backend_api* ae_render_backend_api = ae_get_api(api_registry_api, ae_opengl_backend_api);
//	//struct ae_renderer_api* ae_renderer_api = ae_get_api(api_registry_api, ae_renderer_api);
//	//struct ae_shader_api* ae_shader_api = ae_get_api(api_registry_api, ae_shader_api);
//	//struct ae_camera_api* ae_camera_api = ae_get_api(api_registry_api, ae_camera_api);
//	struct ae_imgui_api* ae_imgui_api = ae_get_api(api_registry_api, ae_imgui_api);
//
//	//// initialize apis
//	ae_logging_api->get_or_create_main_logger(LEVEL_INFO);
//	struct ae_window* window = ae_window_api->get_or_create(&main_window_params);
//	ae_render_backend_api->get_or_create(window);
//	//struct ae_camera* camera = ae_camera_api->create_orthographic((vec3)
//	//{
//	//	0, 0, 0
//	//}, 1280.0f / 720.0f, 0.0f, 1000.0f, 0.0f, 1000.0f, 0.0f, 1.0f);
//	//struct ae_shader* shader = ae_shader_api->create_basic(debug, 255, default_vertex, default_fragment);
//	//struct ae_render_batch* batch = ae_renderer_api->render_batch_create(shader, 1024);
//
//	ae_log_info("Starting AssemblerEngine...");
//
//	bool running = true;
//
//	ae_imgui_api->init(window);
//
//	while (running)
//	{
//		ae_imgui_api->styles_push_size((vec2){1280.0f, 720.0f });
//		ae_imgui_api->styles_push_background_color((vec4){ 1.0f, 0.0f, 0.0f, 1.0f });
//
//		ae_imgui_api->start_viewport("test");
//
//		ae_imgui_api->styles_pop_size();
//		ae_imgui_api->styles_pop_background_color();
//
//		ae_imgui_api->end_viewport();
//
//		running = ae_window_api->update(window);
//	}
//
//	ae_log_info("Shuttingdown AssemblerEngine...");
//}

int main()
{
	//struct ae_os_filesystem_it* it = ae_os_filesystem_it_create(".");

	//char path[512];
	//char name[512];
	//char nameext[512];
	//char ext[512];
	//while (ae_os_filesystem_it_next(it))
	//{
	//	ae_os_filesystem_it_get_full_path(it, path, 512);
	//	ae_os_filesystem_it_get_name(it, name, 512);
	//	ae_os_filesystem_it_get_name_with_ext(it, nameext, 512);
	//	ae_os_filesystem_it_get_extension(it, ext, 512);
	//	printf("path: %s \n", path);
	//	printf("name: %s \n", name);
	//	printf("nameext: %s \n", nameext);
	//	printf("ext: %s \n\n", ext);
	//}

	//(void)it;

}
