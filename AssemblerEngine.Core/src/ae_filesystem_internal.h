#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef AE_PATH_SEPERATOR
#define AE_PATH_SEPERATOR '/'
#endif // !RG_

typedef void handle;

struct ae_os_filesystem_it
{
    handle*     handle;
    char*       base_path;
    uint32_t    base_path_size;
};

struct ae_os_filesystem_it*     ae_os_filesystem_it_create(const char* path);
//void                            ae_os_filesystem_it_destroy(struct ae_os_filesystem_it* it);
//bool						    ae_os_filesystem_it_next(struct ae_os_filesystem_it* it);
//void						    ae_os_filesystem_it_get_full_path(struct ae_os_filesystem_it* it, char* dest, size_t size);
//bool						    ae_os_filesystem_it_is_dir(struct ae_os_filesystem_it* it);
//void						    ae_os_filesystem_it_get_name(struct ae_os_filesystem_it* it, char* buffer, uint32_t size);
//void						    ae_os_filesystem_it_get_name_with_ext(struct ae_os_filesystem_it* it, char* buffer, uint32_t size);
//char*                           ae_os_filesystem_it_get_extension(struct ae_os_filesystem_it* it);
//size_t                          ae_os_filesystem_it_get_size(struct ae_os_filesystem_it* it);
//
//void                            ae_os_filesystem_rename(const char* old_path, const char* new_path);
//void                            ae_os_filesystem_copy(const char* path, const char* dest);
//
//struct ae_os_filesystem_api*    ae_os_filesystem_api_init();