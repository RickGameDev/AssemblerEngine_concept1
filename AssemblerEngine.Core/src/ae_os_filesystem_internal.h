#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef AE_PATH_SEPERATOR
#define AE_PATH_SEPERATOR '/'
#endif // !AE_PATH_SEPERATOR

typedef void handle;
typedef void data;

struct ae_os_filesystem_it;

struct ae_os_filesystem_it*     ae_os_filesystem_it_create(const char* path);
void                            ae_os_filesystem_it_destroy(struct ae_os_filesystem_it* it);
bool						    ae_os_filesystem_it_next(struct ae_os_filesystem_it* it);
uint32_t						ae_os_filesystem_it_get_full_path(struct ae_os_filesystem_it* it, char* dest, uint32_t size);
bool						    ae_os_filesystem_it_is_dir(struct ae_os_filesystem_it* it);
uint32_t						ae_os_filesystem_it_get_name(struct ae_os_filesystem_it* it, char* dest, uint32_t size);
uint32_t						ae_os_filesystem_it_get_name_with_ext(struct ae_os_filesystem_it* it, char* buffer, uint32_t size);
uint32_t                        ae_os_filesystem_it_get_extension(struct ae_os_filesystem_it* it, char* dest, uint32_t size);
size_t                          ae_os_filesystem_it_get_size(struct ae_os_filesystem_it* it);