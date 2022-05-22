#pragma once

struct ae_opengl_backend;
struct ae_camera;
struct ae_window;

typedef void(*ae_renderer_opengl_debug_callback_fn)(uint32_t, uint32_t, uint32_t, uint32_t, int32_t, char);

struct ae_opengl_backend_api
{
	struct ae_opengl_backend*	(*get)();
	struct ae_opengl_backend*	(*get_or_create)(struct ae_window* window);
	void						(*destroy)(struct ae_opengl_backend* backend);
	void						(*set_window)(struct ae_opengl_backend* backend, struct ae_window* window);
	void						(*set_debug_callback)(ae_renderer_opengl_debug_callback_fn callback);
};