#include "AssemblerEngine/plugin_registry.h"
#include "AssemblerEngine/api_registry.h"
#include "filesystem.h"

#include <stdlib.h>

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
#define LIBRARY_EXTENSION ".so"
#endif

struct ae_plugin
{
	ae_plugin_load_fn load;
	ae_plugin_unload_fn unload;
	LIBRARY_TYPE module;
	char name[AE_FILENAME_MAX_LENGTH];
	char path[AE_PATH_MAX_LENGTH];
	char tmp_path[AE_PATH_MAX_LENGTH];
};

struct ae_plugin_registry_o
{
	struct ae_plugin* plugins;
	uint32_t size;
	uint32_t count;
};

static void ae_plugin_load(struct ae_plugin_registry_o* registry, const char* dir, const char* name)
{
	LIBRARY_TYPE plugin = NULL;

	plugin = LOAD_LIBRARY(dir);

	if (plugin)
	{
		ae_plugin_load_fn load_fn = (ae_plugin_load_fn)LOAD_FUNCTION(plugin, "plugin_load");
		ae_plugin_unload_fn unload_fn = (ae_plugin_unload_fn)LOAD_FUNCTION(plugin, "plugin_unload");

		if (!load_fn || !unload_fn)
		{
			UNLOAD_LIBRARY(plugin);
			return 0;
		}

		if (registry->size == registry->count)
		{
			struct ae_plugin* tmp = NULL;

			if (!(tmp = realloc(registry->plugins, sizeof(*registry->plugins) * registry->size + 1)))
			{
				UNLOAD_LIBRARY(plugin);
				return 0;
			}

			registry->plugins = tmp;
			registry->size++;
		}

		uint32_t index = registry->count;

		memcpy(registry->plugins[index].path, dir, strlen(dir) + 1);
		memcpy(registry->plugins[index].name, name, strlen(name) + 1);

		registry->plugins[index].load = load_fn;
		registry->plugins[index].unload = unload_fn;
		registry->plugins[index].load(ae_global_api_registry_api, false);
		registry->count++;
	}
}

struct ae_plugin_registry_api* ae_plugin_registry_new()
{
	struct ae_plugin_registry_api* self = NULL;

	if (!(self = malloc(sizeof(*self))))
	{
		return NULL;
	}

	if (!(self->registry = malloc(sizeof(*self->registry))))
	{
		free(self);
		return NULL;
	}

	if (!(self->registry->plugins = malloc(sizeof(*self->registry->plugins))))
	{
		free(self->registry);
		free(self);
		return NULL;
	}

	self->registry->count = 0;
	self->registry->size = 0;

	self->load = ae_plugin_registry_load;
	self->unload = ae_plugin_registry_unload;
	self->reload = ae_plugin_registry_reload;

	return self;
}

void ae_plugin_registry_free(struct ae_plugin_registry_api* self)
{
	for (uint32_t i = 0; i < self->registry->count; ++i)
	{
		UNLOAD_LIBRARY(self->registry->plugins[i].module);
	}

	free(self->registry->plugins);
	free(self->registry);
	free(self);
}

void ae_plugin_registry_load(struct ae_plugin_registry_api* self, const char* dir)
{
	// validate path
	struct ae_path path = { .length = 0 };
	ae_path_init(&path, dir);

	struct ae_filesystem_it it;
	ae_filesystem_it_init(&it, &path);

	if (ae_filesystem_it_is_dir(&it))
	{
		while (ae_filesystem_it_next(&it))
		{
			if (ae_filesystem_it_get_extension(&it) == LIBRARY_EXTENSION)
			{
				ae_filesystem_it_get_full_path(&it, &path);
				ae_plugin_load(self->registry, path.path, ae_filesystem_it_get_name(&it));
			}
		}
	}
	else
	{
		ae_filesystem_it_get_full_path(&it, &path);
		ae_plugin_load(self->registry, path.path, ae_filesystem_it_get_name(&it));
	}
}

void ae_plugin_registry_unload(struct ae_plugin_registry_api* self, uint32_t index)
{

}

void ae_plugin_registry_reload(struct ae_plugin_registry_api* self, uint32_t index)
{

}