#include "ae_os_filesystem_internal.h"
#include "ae_os_shared_lib_internal.h"

#include <apis/ae_os_filesystem.h>
#include <apis/ae_os_shared_lib.h>

#include <assert.h>

static struct ae_os_filesystem_api filesystem_api;
static struct ae_os_shared_lib_api shared_lib_api;

struct ae_api_registry_api* ae_engine_init()
{
    filesystem_api = (struct ae_os_filesystem_api)
    {
        .filesystem_it_create = ae_os_filesystem_it_create,
        .filesystem_it_destroy = ae_os_filesystem_it_destroy,
        .filesystem_it_next = ae_os_filesystem_it_next,
        .filesystem_it_get_full_path = ae_os_filesystem_it_get_full_path,
        .filesystem_it_is_dir = ae_os_filesystem_it_is_dir,
        .filesystem_it_get_name = ae_os_filesystem_it_get_name,
        .filesystem_it_get_name_with_ext = ae_os_filesystem_it_get_name_with_ext,
        .filesystem_it_get_extension = ae_os_filesystem_it_get_extension,
        .filesystem_it_get_size = ae_os_filesystem_it_get_size
    };

    shared_lib_api = (struct ae_os_shared_lib_api)
    {
        .load_library = ae_os_shared_lib_load_library,
        .close_library = ae_os_shared_lib_close_library,
        .load_function = ae_os_shared_lib_load_function
    };

    return NULL;
}

void ae_engine_shutdown(struct ae_api_registry_api* registry)
{
    assert(registry);
}