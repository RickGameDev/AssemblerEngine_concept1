#include "AssemblerEngine/plugin_registry.h"
#include "AssemblerEngine/api_registry.h"
#include <apis/plugin_registry.h>
#include <core/core.h>
#include "filesystem.h"
#include "hashmap.h"

#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#elif defined __linux
#include <linux/limits.h>
#include <dlfcn.h>
#endif

#ifdef _WIN32
#define LIBRARY_TYPE HMODULE
#elif defined __linux
#define LIBRARY_TYPE void*
#endif

#if defined _WIN32
#define LOAD_LIBRARY(path) LoadLibrary(path)
#elif defined __linux
#define LOAD_LIBRARY(path) dlopen(path, RTLD_NOW)
#endif

#if defined _WIN32
#define UNLOAD_LIBRARY FreeLibrary
#elif defined __linux
#define UNLOAD_LIBRARY_FUNCTION dlclose
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

struct ae_plugin
{
	ae_plugin_load_fn load;
	ae_plugin_unload_fn unload;
	LIBRARY_TYPE library;
	char path[AE_PATH_MAX_LENGTH];
	char tmp_path[AE_PATH_MAX_LENGTH];
};

struct ae_plugin_registry
{
	struct ae_hashmap plugins;
};

static void ae_plugin_load(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, const char* dir, const char* name);

struct ae_plugin_registry* ae_plugin_registry_new()
{
	struct ae_plugin_registry* self = malloc(sizeof(*self));

	if (!self)
	{
		return NULL;
	}

	ae_hashmap_init(&self->plugins);

	return self;
}

void ae_plugin_registry_free(struct ae_plugin_registry* registry)
{
	ae_hashmap_free(&registry->plugins);
	free(registry);
}

void ae_plugin_registry_load(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, const char* dir)
{
	// validate path
	struct ae_path path = { .length = 0 };
	ae_path_init(&path, dir);

	struct ae_filesystem_it it;
	ae_filesystem_it_init(&it, &path);

	char name[AE_FILENAME_MAX_LENGTH];

	if (ae_filesystem_it_is_dir(&it))
	{
		while (ae_filesystem_it_next(&it))
		{
			const char* ext = ae_filesystem_it_get_extension(&it);
			if (strcmp(ext, LIBRARY_EXTENSION) == 0)
			{
				ae_filesystem_it_get_name(&it, name, AE_FILENAME_MAX_LENGTH);
				ae_filesystem_it_get_full_path(&it, &path);
				ae_plugin_load(registry, api_registry, path.path, name);
			}
		}
	}
	else if (strcmp(ae_filesystem_it_get_extension(&it), LIBRARY_EXTENSION) == 0)
	{
		ae_filesystem_it_get_name(&it, name, AE_FILENAME_MAX_LENGTH);
		ae_filesystem_it_get_full_path(&it, &path);
		ae_plugin_load(registry, api_registry, path.path, name);
	}
}

void ae_plugin_registry_unload(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, uint32_t index)
{
	AE_UNREFERENCED_PARAMETER(registry);
	AE_UNREFERENCED_PARAMETER(api_registry);
	AE_UNREFERENCED_PARAMETER(index);
}

void ae_plugin_registry_reload(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, uint32_t index)
{
	AE_UNREFERENCED_PARAMETER(registry);
	AE_UNREFERENCED_PARAMETER(api_registry);
	AE_UNREFERENCED_PARAMETER(index);
}

static void ae_plugin_load(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, const char* dir, const char* name)
{
	LIBRARY_TYPE library = NULL;

	library = LOAD_LIBRARY(dir);

	if (library)
	{
		ae_plugin_load_fn load_fn = (ae_plugin_load_fn)LOAD_FUNCTION(library, "plugin_load");
		ae_plugin_unload_fn unload_fn = (ae_plugin_unload_fn)LOAD_FUNCTION(library, "plugin_unload");

		if (!load_fn || !unload_fn)
		{
			UNLOAD_LIBRARY(library);
			return;
		}

		struct ae_plugin plugin = {
			.library = library,
			.load = load_fn,
			.unload = unload_fn
		};

		memcpy_s(plugin.path, AE_PATH_MAX_LENGTH, dir, strlen(dir) + 1);

		ae_hashmap_insert(&registry->plugins, name, &plugin, sizeof(plugin));

		plugin.load(api_registry, false);
	}
}