#include "ae_os_filesystem_internal.h"

#define _GNU_SOURCE
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


struct ae_os_filesystem_it
{
    DIR*            handle;
    struct dirent*  data;
    char*           base_path;
    uint32_t        base_path_size;
};

struct ae_os_filesystem_it* ae_os_filesystem_it_create(const char* path)
{
    struct ae_os_filesystem_it* it = malloc(sizeof(*it));

    if (!it)
        return NULL;

    it->base_path_size = (uint32_t)strlen(path) + 1;
    it->base_path = malloc(it->base_path_size);
    
    memcpy(it->base_path, path, it->base_path_size);

    if (!it->base_path)
    {
        free(it);
        return NULL;
    }

    it->handle = opendir(it->base_path);

    if (!it->handle)
    {
        free(it->base_path);
        free(it);
        return NULL;
    }

    it->data = readdir(it->handle);

    if (!it->data)
    {
        free(it->base_path);
        free(it);
        return NULL;
    }

    return it;
}

void ae_os_filesystem_it_destroy(struct ae_os_filesystem_it* it)
{
    if (it->handle)
        closedir(it->handle);

    free(it->base_path);
    free(it);
}

bool ae_os_filesystem_it_next(struct ae_os_filesystem_it* it)
{
    assert(it);
    return (it->data = readdir(it->handle)) != NULL;
}

uint32_t ae_os_filesystem_it_get_full_path(struct ae_os_filesystem_it* it, char* dest, uint32_t size)
{
    uint32_t name_size = (uint32_t)strlen(it->data->d_name) + 1;

    if (it->base_path_size + name_size > size)
        return 0;

    memcpy(dest, it->base_path, it->base_path_size);
    
    dest[it->base_path_size - 1] = AE_PATH_SEPERATOR;

    memcpy(&dest[it->base_path_size], it->data->d_name, name_size);

    return it->base_path_size + name_size;
}

bool ae_os_filesystem_it_is_dir(struct ae_os_filesystem_it* it)
{
    assert(it);

#ifdef _DIRENT_HAVE_D_TYPE
    if (it->data->d_type != DT_UNKNOWN && (it->data->d_type != DT_LNK))
    {
        return it->data->d_type == DT_DIR;
    }
    else
#endif
    {
        struct stat stbuf;

        stat(it->data->d_name, &stbuf);
        return S_ISDIR(stbuf.st_mode);
    }
}

uint32_t ae_os_filesystem_it_get_name(struct ae_os_filesystem_it* it, char* dest, uint32_t size)
{
    assert(it);

    char* dot = strrchr(it->data->d_name, '.');

    uint32_t name_size = (uint32_t)strlen(it->data->d_name) + 1;

    if (dot)
        name_size = (uint32_t)(dot - it->data->d_name);

    if (name_size > size)
        return 0;

    memcpy(dest, it->data->d_name, name_size);

    dest[name_size] = '\0';

    return name_size;
}

uint32_t ae_os_filesystem_it_get_name_with_ext(struct ae_os_filesystem_it* it, char* dest, uint32_t size)
{
    assert(it);

    uint32_t name_size = (uint32_t)strlen(it->data->d_name) + 1;

    if (name_size > size)
        return 0;

    memcpy(dest, it->data->d_name, name_size);

    return name_size;
}

uint32_t ae_os_filesystem_it_get_extension(struct ae_os_filesystem_it* it, char* dest, uint32_t size)
{
    assert(it);
    
    uint32_t ext_size = (uint32_t)strlen(it->data->d_name) + 1;
    char* dot = strrchr(it->data->d_name, '.');

    if (dot)
        ext_size = ext_size - (++dot - it->data->d_name);
    else
        return 0;

    if (ext_size > size)
        return 0;

    memcpy(dest, dot, ext_size);

    dest[ext_size] = '\0';

    return ext_size;
}

size_t ae_os_filesystem_it_get_size(struct ae_os_filesystem_it* it)
{
    struct stat st;
    stat(it->data->d_name, &st);

    return (size_t)st.st_size;
}