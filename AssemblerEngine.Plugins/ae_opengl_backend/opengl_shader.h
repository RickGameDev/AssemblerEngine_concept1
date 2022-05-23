#pragma once

#include <core/types.h>

struct ae_shader;

void ae_shader_set_view_projection(const float* view_projection);
void ae_shader_set_blending(struct ae_shader* shader, bool enable, uint32_t source, uint32_t destination);
void ae_shader_set_depth_test(struct ae_shader* shader, bool enable);
void ae_shader_set_current_shader(struct ae_shader* shader);

struct ae_shader* ae_shader_create(
	char* debug_output,
	const int32_t debug_output_size,
	const char** stage_sources,
	const int32_t* stage_sizes,
	const int32_t* stage_types,
	const int32_t stage_count);

struct ae_shader* ae_shader_create_basic(
	char* debug_output,
	const int32_t debug_output_size,
	const char* vertex_shader,
	const char* fragment_shader);