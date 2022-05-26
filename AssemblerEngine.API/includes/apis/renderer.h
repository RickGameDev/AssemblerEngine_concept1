/*****************************************************************//**
 * @file   renderer.h
 * @ingroup group_api
 * @brief Render API using one of the registered rendering backends
 * 
 * @author RickNijhuis
 * @date   May 2022
 *********************************************************************/

 /**
 *@addtogroup group_api
 * @{
 */

#pragma once

#include "core/types.h"

struct ae_render_batch;
struct ae_camera;
struct ae_shader;

struct ae_draw_params
{
	vec4 color;
	vec3 position;
	vec2 size;
	struct ae_camera* camera;
};

struct ae_textured_draw_params
{
	vec4 color;
	vec3 position;
	vec2 size;
	vec2 texture_coordinates[4];
	struct ae_camera* camera;
	uint32_t texture;
};

struct ae_renderer_api
{
	struct ae_render_batch* (*render_batch_create)(struct ae_shader* const shader, const uint32_t max_quad_count);
	void					(*render_batch_destroy)(struct ae_render_batch* batch);
	void					(*render_scene_start)(const struct ae_camera* camera);
	void					(*render_batch_start)(const struct ae_render_batch* batch);
	void					(*render_batch_end)(struct ae_render_batch* batch);
	void					(*render_batch_draw)(struct ae_render_batch* batch, struct ae_draw_params* const params);
	void					(*render_batch_draw_textured)(struct ae_render_batch* batch, struct ae_textured_draw_params* const params);
};

/**@}*/
