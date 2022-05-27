#pragma once

typedef void library;
typedef void function;

struct ae_os_shared_lib_api
{
    library*    (*load_library)(const char* name);
    void        (*close_library)(library* library);
    function*   (*load_function)(library* library, const char* name);
};