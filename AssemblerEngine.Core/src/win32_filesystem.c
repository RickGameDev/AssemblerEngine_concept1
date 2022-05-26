#include "ae_filesystem_internal.h"

#include <apis/ae_filesystem.h>
#include <core/os.h>

#include <stdlib.h>
#include <string.h>

struct ae_os_filesystem_it* ae_os_filesystem_it_create(const char* path)
{
	struct ae_os_filesystem_it* it = malloc(sizeof(*it));

	if (!it)
		return NULL;

	it->base_path_size = (uint32_t)strlen(path);

	// +3 for appending if path is dir
	it->base_path = calloc(it->base_path_size + 3, sizeof(*it->base_path));

	if (!it->base_path)
	{
		free(it);
		return NULL;
	}

	if (it->base_path_size == 0)
	{
		it->base_path_size = 1;
		it->base_path[0] = '.';
		it->base_path[1] = '\0';
	}
	else
	{
		memcpy(it->base_path, path, it->base_path_size);
	}

	if (it->base_path[it->base_path_size - 1] == AE_PATH_SEPERATOR)
		it->base_path[it->base_path_size - 1] = '\0';

	const char* dot = strrchr(it->base_path, '.');

	if (!dot || dot == it->base_path)
	{
		strcat(it->base_path, "\\*");

		it->handle = FindFirstFileW(it->base_path, it->handle);
	}
	else
	{
		wchar_t t;
		it->handle = FindFirstFileW(it->base_path, it->handle);
	}

	if (it->handle == INVALID_HANDLE_VALUE)
	{
		free(it->base_path);
		return NULL;
	}

	return it;
}

//void ae_os_filesystem_it_destroy(struct ae_os_filesystem_it* it)
//{
//
//}
//
//bool ae_os_filesystem_it_next(struct ae_os_filesystem_it* it)
//{
//
//}
//
//void ae_os_filesystem_it_get_full_path(struct ae_os_filesystem_it* it, char* dest, size_t size)
//{
//
//}
//
//bool ae_os_filesystem_it_is_dir(struct ae_os_filesystem_it* it)
//{
//
//}
//
//void ae_os_filesystem_it_get_name(struct ae_os_filesystem_it* it, char* buffer, uint32_t size)
//{
//
//}
//
//void ae_os_filesystem_it_get_name_with_ext(struct ae_os_filesystem_it* it, char* buffer, uint32_t size)
//{
//
//}
//
//char* ae_os_filesystem_it_get_extension(struct ae_os_filesystem_it* it)
//{
//
//}
//
//size_t ae_os_filesystem_it_get_size(struct ae_os_filesystem_it* it)
//{
//
//}
//       
//void ae_os_filesystem_rename(const char* old_path, const char* new_path)
//{
//
//}
//
//void ae_os_filesystem_copy(const char* path, const char* dest)
//{
//
//}
//
//struct ae_os_filesystem_api* ae_os_filesystem_api_init()
//{
//
//}