#pragma once

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif defined UNIX
#include <sys/stat.h>
#endif // WIN32

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// default max path linux
#ifndef AE_PATH_MAX_LENGTH
#define AE_PATH_MAX_LENGTH 4096
#endif // !RG_PATH_MAX_LENGTH

// default max path linux
#ifndef AE_FILENAME_MAX_LENGTH
#define AE_FILENAME_MAX_LENGTH 256
#endif // !RG_FILENAME_MAX_LENGTH

#ifndef AE_PATH_SEPERATOR
#define AE_PATH_SEPERATOR '/'
#endif // !RG_PATH_SEPERATOR

struct ae_path
{
	uint32_t length;
	char path[AE_PATH_MAX_LENGTH];
};

struct ae_filesystem_it
{
#ifdef _WIN32
	HANDLE handle;
	WIN32_FIND_DATAA data;
#endif // WIN32
	struct ae_path path;
};

void ae_path_init(struct ae_path* path, char* root);
void ae_path_append(struct ae_path* path, struct ae_path* path_to_append);

struct ae_filesystem_it* ae_filesystem_it_new(struct ae_path* path);
bool ae_filesystem_it_init(struct ae_filesystem_it* it, struct ae_path* path);
void ae_filesystem_it_free(struct ae_filesystem_it* it);
bool ae_filesystem_it_next(struct ae_filesystem_it* it);

void ae_filesystem_it_get_full_path(struct ae_filesystem_it* it, struct ae_path* path);
const bool ae_filesystem_it_is_dir(struct ae_filesystem_it* it);
const char* ae_filesystem_it_get_name(struct ae_filesystem_it* it);
const char* ae_filesystem_it_get_extension(struct ae_filesystem_it* it);
const size_t ae_filesystem_it_get_size(struct ae_filesystem_it* it);