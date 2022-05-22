#pragma once

#include "core/types.h"

enum ae_window_flags
{
	AE_WINDOW_FOCUSED =	(1 << 0),
	AE_WINDOW_ICONIFIED = (1 << 1),
	AE_WINDOW_MAXIMIZED = (1 << 2),
	AE_WINDOW_HOVERED =	(1 << 3),
	AE_WINDOW_VISIBLE =	(1 << 4),
	AE_WINDOW_RESIZABLE = (1 << 5),
	AE_WINDOW_DECORATED = (1 << 6)
};

struct ae_create_window_params
{
	enum ae_window_flags	flags;
	uint32_t				width;
	uint32_t				height;
	uint32_t				position_x;
	uint32_t				position_y;
	char*					title;
};

struct ae_window
{
	uint32_t					id;
	uint32_t					parent_id;
	uint32_t					flags;
	vec2						position;
	vec2						size;
	char*						title;
	struct ae_native_window*	native_handle;
};

struct ae_window_api
{
	struct ae_window*			(*get_window)();
	struct ae_window*			(*get_or_create)();
	void						(*destroy)(struct ae_window* window);
	struct ae_window*			(*create_child)(struct ae_window* parent, struct ae_create_window_params* params);
	bool						(*update)(struct ae_window* window);
	void						(*show)(struct ae_window* window);
	struct ae_native_window*	(*get_native_window)(struct ae_window* window);
};