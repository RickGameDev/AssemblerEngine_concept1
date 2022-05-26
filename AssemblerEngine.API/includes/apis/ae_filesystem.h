#pragma once

#include <core/types.h>
#include <core/string.h>

typedef void handle;

struct ae_os_filesystem_it;

struct ae_os_filesystem_api
{
    struct ae_os_filesystem_it* (*filesystem_it_create)(const char* path);
    void                        (*filesystem_it_destroy)(struct ae_os_filesystem_it* it);

    bool						(*filesystem_it_next)(struct ae_os_filesystem_it* it);
    void						(*filesystem_it_get_full_path)(struct ae_os_filesystem_it* it, const char* path);
    bool						(*filesystem_it_is_dir)(struct ae_os_filesystem_it* it);
    void						(*filesystem_it_get_name)(struct ae_os_filesystem_it* it, char* buffer, uint32_t size);
    void						(*filesystem_it_get_name_with_ext)(struct ae_os_filesystem_it* it, char* buffer, uint32_t size);
    char*                       (*filesystem_it_get_extension)(struct ae_os_filesystem_it* it);
    size_t						(*filesystem_it_get_size)(struct ae_os_filesystem_it* it);

    void                        (*rename)(const char* old_path, const char* new_path);
    void                        (*copy)(const char* path, const char* dest);
};