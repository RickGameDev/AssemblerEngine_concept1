#pragma once

#include <core/types.h>

struct ae_shader;

void ae_shader_set_view_projection(mat4 view_projection);
void ae_shader_set_blending(struct ae_shader* shader, bool enable, uint32_t source, uint32_t destination);
void ae_shader_set_depth_test(struct ae_shader* shader, bool enable);
void ae_shader_set_current_shader(struct ae_shader* shader);

struct ae_shader* ae_shader_create(
	char* debug_output,
	int32_t debug_output_size,
	char** stage_sources,
	int32_t* stage_sizes,
	int32_t* stage_types,
	int32_t stage_count);

struct ae_shader* ae_shader_create_basic(
	char* debug_output,
	int32_t debug_output_size,
	char* vertex_shader,
	char* fragment_shader);