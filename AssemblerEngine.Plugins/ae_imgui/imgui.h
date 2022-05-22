#pragma once

#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <core/vector.h>

// forward declarations
struct ae_window;
struct ae_imgui_viewport;
struct ae_imgui_context;
struct vector_vec4;
struct vector_vec2;
struct vector_float;
struct vector_uint;
struct vector_window;

// functions
void ae_imgui_start_viewport(const char* name);
void ae_imgui_end_viewport();

void ae_imgui_styles_push_size(vec2 size);
void ae_imgui_styles_pop_size();
void ae_imgui_styles_push_padding(vec4 padding);
void ae_imgui_styles_pop_padding();
void ae_imgui_styles_push_margin(vec4 margin);
void ae_imgui_styles_pop_margin();
void ae_imgui_styles_push_background_color(vec4 color);
void ae_imgui_styles_pop_background_color();


// declarations
struct ae_imgui_viewport
{
	uint32_t	window_id;
	vec2		position;
	vec2		size;
};

enum ae_imgui_elements
{
	AE_IMGUI_VIEWPORT,
	AE_IMGUI_ALL_ELEMENTS
};

VECTOR_DEFINE_NAME(struct ae_window*, window)
VECTOR_DEFINE_NAME(struct ae_imgui_viewport, viewport)
VECTOR_DEFINE_NAME(float*, vec4)
VECTOR_DEFINE_NAME(float*, vec2)
VECTOR_DEFINE_NAME(float, float)
VECTOR_DEFINE_NAME(uint32_t, uint)

struct ae_imgui_context
{
	struct vector_window	window_stack;
	struct vector_viewport	viewport_stack;
	struct vector_vec4		background_color_stack;
	struct vector_vec4		border_color_stack;
	struct vector_vec4		font_color_stack;
	struct vector_vec4		padding_stack;
	struct vector_vec4		margin_stack;
	struct vector_vec4		border_width_stack;
	struct vector_vec4		border_radius_stack;
	struct vector_vec2		size_stack;
	struct vector_float		font_size_stack;
	struct vector_float		font_weigth_stack;
	struct vector_uint		texture_stack;
	struct vector_uint		text_flags_stack;

	uint32_t				current_viewport_index;
	uint32_t				current_window_index;
};


extern struct ae_imgui_context context;
