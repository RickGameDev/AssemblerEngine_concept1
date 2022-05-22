#include "AssemblerEngine/system_info.h"

#include <core/os.h>

struct ae_system_info {
	size_t page_size;
};

static struct ae_system_info system_info = {
	.page_size = 0
};

struct ae_system_info* ae_system_info_init()
{
	if (!system_info.page_size)
	{
		SYSTEM_INFO info = { 0 };

		GetSystemInfo(&info);

		system_info.page_size = info.dwPageSize;
	}

	return &system_info;
}

const size_t ae_system_info_get_page_size(const struct ae_system_info* const system_info)
{
	return system_info->page_size;
}