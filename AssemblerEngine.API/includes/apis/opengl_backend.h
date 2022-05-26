/*****************************************************************//**
 * @file   opengl_backend.h
 * @ingroup group_api
 * @brief  OpenGL Backend API
 * 
 * @author RickNijhuis
 * @date   May 2022
 *********************************************************************/

 /**
 *@addtogroup group_api
 * @{
 */

#pragma once

struct ae_opengl_backend;
struct ae_camera;
struct ae_window;

typedef void(*ae_renderer_opengl_debug_callback_fn)(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, char const* message, void const* user_param);

struct ae_opengl_backend_api
{
	struct ae_opengl_backend*	(*get)();
	struct ae_opengl_backend*	(*get_or_create)();
	void						(*destroy)(struct ae_opengl_backend* backend);
	void						(*set_window)(struct ae_opengl_backend* backend, struct ae_window* window);
	void						(*set_debug_callback)(ae_renderer_opengl_debug_callback_fn callback);
};

/**@}*/
