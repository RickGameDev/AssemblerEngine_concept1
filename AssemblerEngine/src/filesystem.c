#include "filesystem.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void ae_path_init(struct ae_path* path, char* root)
{
	memset(path->path, '\0', AE_PATH_MAX_LENGTH);
	size_t length = strlen(root);

	if (length >= AE_PATH_MAX_LENGTH)
		return;

	if (length == 0)
	{
		path->length = 1;
		path->path[0] = '.';
		path->path[1] = '\0';
	}
	else
	{
		memcpy(path->path, root, length + 1);
		path->length = length;
	}

	if (path->path[path->length] == AE_PATH_SEPERATOR)
		path->path[path->length] = '\0';
}

void ae_path_append(struct ae_path* path, struct ae_path* path_to_append)
{
	if (path->length + path_to_append->length >= AE_PATH_MAX_LENGTH)
		return;

	if (path_to_append->path[0] != AE_PATH_SEPERATOR)
	{
		path->path[path->length] = AE_PATH_SEPERATOR;
		path->length++;
	}

	memcpy(&path->path[path->length], path_to_append->path, path_to_append->length);

	path->length += path_to_append->length;

	if (path->path[path->length] == AE_PATH_SEPERATOR)
		path->path[path->length] = '\0';
}

struct ae_filesystem_it* ae_filesystem_it_new(struct ae_path* path)
{
	struct ae_filesystem_it* self = NULL;

	if (!(self == malloc(sizeof(*self))))
		return NULL;

	if (!ae_filesystem_it_init(self, path))
		return NULL;

	return self;
}

void ae_filesystem_it_free(struct ae_filesystem_it* it)
{
#ifdef _WIN32
	FindClose(it->handle);
#endif // WIN32
	free(it);
}

bool ae_filesystem_it_init(struct ae_filesystem_it* it, struct ae_path* path)
{
	assert(it);
	assert(path);
	assert(path->length > 0);

	memcpy(&it->path, path, sizeof(*path));

	const char* dot = strrchr(it->path.path, '.');
	if (!dot || dot == it->path.path)
	{
		char tmp_path[AE_PATH_MAX_LENGTH] = { 0 };
		memcpy(tmp_path, path->path, path->length);
		strcat(tmp_path, "\\*");

#ifdef _WIN32
		it->handle = FindFirstFile(tmp_path, &it->data);
#endif
	}
	else
	{
		it->handle = FindFirstFile(path->path, &it->data);
	}
#ifdef _WIN32
	if (it->handle == INVALID_HANDLE_VALUE)
	{
		return false;
	}
#endif // WIN32

	return true;
}

bool ae_filesystem_it_next(struct ae_filesystem_it* it)
{
	if (it == NULL || it->handle == INVALID_HANDLE_VALUE)
		return false;

	if (FindNextFile(it->handle, &it->data))
	{
		return true;
	}

	return false;
}

void ae_filesystem_it_get_name(struct ae_filesystem_it* it, char* buffer, uint32_t size)
{
	if (it == NULL)
		return NULL;

#ifdef WIN32
	char* ext = strrchr(it->data.cFileName, '.');

	size_t str_size = strlen(it->data.cFileName);

	if (ext)
		str_size = (size_t)(ext - it->data.cFileName);

	if (str_size > size)
		str_size = size;

	memcpy(buffer, it->data.cFileName, str_size);
	buffer[str_size + 1] = '\0';
#endif // WIN32
}

void ae_filesystem_it_get_name_with_ext(struct ae_filesystem_it* it, char* buffer, uint32_t size)
{
	if (it == NULL)
		return NULL;

#ifdef WIN32
	size_t str_size = strlen(it->data.cFileName);

	if (str_size > size)
		str_size = size;

	memcpy(buffer, it->data.cFileName, str_size);
	buffer[str_size + 1] = '\0';
#endif // WIN32
}

void ae_filesystem_it_get_full_path(struct ae_filesystem_it* it, struct ae_path* path)
{
	if (it == NULL)
		return NULL;

	ae_path_init(path, it->path.path);

	struct ae_path tmp_path = { .length = 0 };

#ifdef WIN32
	ae_path_init(&tmp_path, it->data.cFileName);
#endif // WIN32
	ae_path_append(path, &tmp_path);
}


const bool ae_filesystem_it_is_dir(struct ae_filesystem_it* it)
{
	if (it == NULL)
		return NULL;

#ifdef _WIN32
	return it->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
#endif // WIN32
}
const char* ae_filesystem_it_get_extension(struct ae_filesystem_it* it)
{
	if (it == NULL)
		return NULL;

#ifdef _WIN32
	return (strrchr(it->data.cFileName, '.')) + 1;
#endif // WIN32
}

const size_t ae_filesystem_it_get_size(struct ae_filesystem_it* it)
{
	if (it == NULL)
		return NULL;

#ifdef _WIN32
	LARGE_INTEGER file_size = { 0 };
	file_size.LowPart = it->data.nFileSizeLow;
	file_size.HighPart = it->data.nFileSizeHigh;

	return (size_t)file_size.QuadPart;
#endif // WIN32
}