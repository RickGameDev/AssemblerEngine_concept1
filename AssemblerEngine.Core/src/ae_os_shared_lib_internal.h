#pragma once

typedef void library;
typedef void function;

library*    ae_os_shared_lib_load_library(const char* name);
void        ae_os_shared_lib_close_library(library* library);
function*   ae_os_shared_lib_load_function(library* library, const char* name);