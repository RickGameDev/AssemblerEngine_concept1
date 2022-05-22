#pragma once

#include "core/types.h"

struct ae_camera
{
	mat4 view;
	mat4 projection;
	mat4 view_projection;
};

struct ae_camera_api
{
	struct ae_camera*	(*create_orthographic)(vec3 position, const float aspect_ratio, const float left, const float right, const float bottom, const float top, const float near, const float far);
	void				(*destroy)(struct ae_camera* camera);
	const float*		(*get_view_projection)(struct ae_camera* const camera);
};