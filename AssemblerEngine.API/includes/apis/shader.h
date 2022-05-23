#pragma once

#include <core/types.h>

struct ae_shader
{
	bool enable_depth_test;
	bool enable_blending;
	int32_t blend_source;
	int32_t blend_destination;
	int32_t id;
};

struct ae_shader_api
{
	struct ae_shader*	(*create)(char* debug_output, int32_t debug_output_size, char** stage_sources, int32_t* stage_sizes, int32_t* stage_types, int32_t stage_count);
	struct ae_shader*	(*create_basic)(char* debug_output, int32_t debug_output_size, const char* vertex_shader, const char* fragment_shader);
	void				(*set_view_projection)(mat4 view_projection);
	void				(*set_blending)(struct ae_shader* shader, bool enable, uint32_t source, uint32_t destination);
	void				(*set_depth_test)(struct ae_shader* shader, bool enable);
};