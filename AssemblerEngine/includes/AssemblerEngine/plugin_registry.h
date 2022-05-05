#pragma once

#include "AssemblerEngine/plugin_registry_api.h"

struct ae_plugin_registry_api* ae_plugin_registry_new();
void ae_plugin_registry_free(struct ae_plugin_registry_api* self);

void ae_plugin_registry_load(struct ae_plugin_registry_api* self, const char* path);
void ae_plugin_registry_unload(struct ae_plugin_registry_api* self, uint32_t id);
void ae_plugin_registry_reload(struct ae_plugin_registry_api* self, uint32_t id);

extern struct ae_plugin_registry_api* ae_global_plugin_registry_api;