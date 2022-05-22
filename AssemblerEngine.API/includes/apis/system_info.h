#pragma once

#include "core/types.h"

struct ae_system_info;

struct ae_system_info_api
{
	struct ae_system_info*	system_info;
	size_t					(*get_page_size)(struct ae_system_info* system_info);
};