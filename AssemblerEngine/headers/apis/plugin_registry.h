#pragma once

#include <stdint.h>
#include <stdbool.h>

struct ae_api_registry_api;
struct ae_plugin_registry_o;
struct ae_plugin_registry_api;

typedef void (*ae_plugin_load_fn)(struct ae_api_registry_api* registry, bool reload);
typedef void (*ae_plugin_unload_fn)(struct ae_api_registry_api* registry);

typedef uint32_t(*ae_plugin_registry_load_fn)(struct ae_plugin_registry_api* self, const char* path);
typedef void (*ae_plugin_registry_unload_fn)(struct ae_plugin_registry_api* self, uint32_t id);
typedef void (*ae_plugin_registry_reload_fn)(struct ae_plugin_registry_api* self, uint32_t id);

struct ae_plugin_registry_api
{
	struct ae_plugin_registry_o*	registry;

	ae_plugin_registry_load_fn		load;
	ae_plugin_registry_unload_fn	unload;
	ae_plugin_registry_reload_fn	reload;
};