#include "AssemblerEngine/ae_filesystem_internal.h"

#include <apis/ae_filesystem.h>
#include <core/os.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct ae_os_filesystem_it
{
    HANDLE              handle;
    WIN32_FIND_DATAW    data;
    wchar_t*            base_path;
    uint32_t            base_path_size;
};

struct ae_os_filesystem_it* ae_os_filesystem_it_create(const char* path)
{
    struct ae_os_filesystem_it* it = malloc(sizeof(*it));

    if (!it)
        return NULL;

    it->base_path_size = MultiByteToWideChar(CP_UTF8, 0, path, -1, NULL, 0);
    it->handle = NULL;

    // reserve +3 for appending if path is dir
    it->base_path = malloc(sizeof(*it->base_path) * ((size_t)it->base_path_size + 3));

    if (!it->base_path)
    {
        free(it);
        return NULL;
    }

    if (it->base_path_size == 0)
    {
        it->base_path_size = 1;
        it->base_path[0] = L'.';
        it->base_path[1] = L'\0';
    }
    else
    {
        MultiByteToWideChar(CP_UTF8, 0, path, -1, it->base_path, it->base_path_size);
    }

    if (it->base_path[it->base_path_size - 1] == AE_PATH_SEPERATOR)
        it->base_path[it->base_path_size - 1] = L'\0';

    const wchar_t* dot = wcsrchr(it->base_path, L'.');

    if (!dot || dot == it->base_path)
    {
        wcscat_s(it->base_path, (rsize_t)it->base_path_size + 3, L"\\*");

        it->handle = FindFirstFileW(it->base_path, &it->data);

        it->base_path[it->base_path_size - 1] = L'\0';
    }
    else
    {
        it->handle = FindFirstFileW(it->base_path, &it->data);
    }

    if (it->handle == INVALID_HANDLE_VALUE)
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
        FindClose(it->handle);

    free(it->base_path);
    free(it);
}

bool ae_os_filesystem_it_next(struct ae_os_filesystem_it* it)
{
    assert(it);

    if (it->handle == INVALID_HANDLE_VALUE)
        return false;

    return FindNextFileW(it->handle, &it->data);
}

uint32_t ae_os_filesystem_it_get_full_path(struct ae_os_filesystem_it* it, char* dest, uint32_t size)
{
    assert(it);

    uint32_t path_size = (uint32_t)WideCharToMultiByte(CP_UTF8, 0, it->base_path, -1, NULL, 0, NULL, NULL);
    uint32_t name_size = (uint32_t)WideCharToMultiByte(CP_UTF8, 0, it->data.cFileName, -1, NULL, 0, NULL, NULL);

    if (dest == NULL)
        return path_size + name_size + 1;

    if (path_size + name_size > size)
        return 0;

    uint32_t write_size = (uint32_t)WideCharToMultiByte(CP_UTF8, 0, it->base_path, -1, dest, (int32_t)(size > path_size ? path_size : size), NULL, NULL);

    dest[write_size - 1] = AE_PATH_SEPERATOR;

    write_size += WideCharToMultiByte(CP_UTF8, 0, it->data.cFileName, -1, &dest[path_size], (int32_t)(name_size), NULL, NULL);

    return write_size;
}

bool ae_os_filesystem_it_is_dir(struct ae_os_filesystem_it* it)
{
    assert(it);

    return it->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

uint32_t ae_os_filesystem_it_get_name(struct ae_os_filesystem_it* it, char* buffer, uint32_t size)
{
    assert(it);

    wchar_t* dot = wcsrchr(it->data.cFileName, L'.');

    uint32_t name_size = (uint32_t)WideCharToMultiByte(CP_UTF8, 0, it->data.cFileName, -1, NULL, 0, NULL, NULL);

    if (dot)
        name_size = (uint32_t)(dot - it->data.cFileName);

    if (name_size > size)
        return 0;

    WideCharToMultiByte(CP_UTF8, 0, it->data.cFileName, -1, buffer, (int32_t)(name_size > size ? size : name_size), NULL, NULL);

    buffer[name_size] = '\0';

    return name_size;
}

uint32_t ae_os_filesystem_it_get_name_with_ext(struct ae_os_filesystem_it* it, char* buffer, uint32_t size)
{
    assert(it);

    uint32_t name_size = (uint32_t)WideCharToMultiByte(CP_UTF8, 0, it->data.cFileName, -1, NULL, 0, NULL, NULL);

    if (name_size > size)
        return 0;

    return WideCharToMultiByte(CP_UTF8, 0, it->data.cFileName, -1, buffer, (int32_t)(name_size > size ? size : name_size), NULL, NULL);
}

uint32_t ae_os_filesystem_it_get_extension(struct ae_os_filesystem_it* it, char* buffer, uint32_t size)
{
    assert(it);

    wchar_t* dot = wcsrchr(it->data.cFileName, L'.');

    uint32_t ext_size = (uint32_t)WideCharToMultiByte(CP_UTF8, 0, dot + 1, -1, NULL, 0, NULL, NULL);

    if (ext_size > size)
        return 0;

    WideCharToMultiByte(CP_UTF8, 0, dot + 1, -1, buffer, (int32_t)(ext_size > size ? size : ext_size), NULL, NULL);

    buffer[ext_size] = '\0';

    return ext_size;
}

size_t ae_os_filesystem_it_get_size(struct ae_os_filesystem_it* it)
{
    assert(it);

    LARGE_INTEGER file_size = { 0 };
    file_size.LowPart = it->data.nFileSizeLow;
    file_size.HighPart = it->data.nFileSizeHigh;

    return (size_t)file_size.QuadPart;
}