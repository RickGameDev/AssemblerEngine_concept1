#include "ae_os_shared_lib_internal.h"

#ifdef _WIN32
#include <Windows.h>
#elif defined __linux
#include <linux/limits.h>
#include <dlfcn.h>
typedef void* __attribute__((__may_alias__)) pvoid_may_alias_t;
#endif

#ifdef _WIN32
#define LIBRARY_TYPE HMODULE
#elif defined __linux
#define LIBRARY_TYPE void*
#endif

#if defined _WIN32
#define LOAD_LIBRARY(path) LoadLibraryW(path)
#elif defined __linux
#define LOAD_LIBRARY(path) dlopen(path, RTLD_NOW)
#endif

#if defined _WIN32
#define UNLOAD_LIBRARY FreeLibrary
#elif defined __linux
#define UNLOAD_LIBRARY dlclose
#endif

#if defined _WIN32
#define LOAD_FUNCTION GetProcAddress
#elif defined __linux
#define LOAD_FUNCTION dlsym
#endif

#if defined _WIN32
#define LIBRARY_EXTENSION "dll"
#elif defined __linux
#define LIBRARY_EXTENSION "so"
#endif


library* ae_os_shared_lib_load_library(const char* path)
{
#ifdef _WIN32
    uint32_t size = (uint32_t)MultiByteToWideChar(CP_UTF8, 0, path, -1, NULL, 0);

    wchar_t* buffer = malloc(sizeof(*buffer) * size);

    if (!buffer)
        return NULL;

    size = MultiByteToWideChar(CP_UTF8, 0, path, -1, buffer, size);

    if (!size)
        return NULL;

    LOAD_LIBRARY(buffer);
#endif // _WIN32
    
    return LOAD_LIBRARY(path);
}

void ae_os_shared_lib_close_library(library* library)
{
    UNLOAD_LIBRARY(library);
}

function* ae_os_shared_lib_load_function(library* library, const char* name)
{
#ifdef _WIN32
    return LOAD_FUNCTION(library, name);
#else
    return (pvoid_may_alias_t)LOAD_FUNCTION(library, name);
#endif // _WIN32
}