#pragma once

#include "AssemblerEngine/api_registry_api.h"

struct ae_api_registry_api* ae_api_registry_new();
void ae_api_registry_free(struct ae_api_registry_api* self);
void ae_api_registry_set_api(struct ae_api_registry_api* self, const char* type, void* api, const uint32_t size);
void* ae_api_registry_get_api(struct ae_api_registry_api* self, const char* type, const uint32_t size);
void* ae_api_registry_remove_api(struct ae_api_registry_api* self, const char* type);

void* ae_api_registry_add_object(struct ae_api_registry_api* self, const char* type, void* object, uint32_t size);
void* ae_api_registry_get_object(struct ae_api_registry_api* self, const char* type);
void* ae_api_registry_remove_object(struct ae_api_registry_api* self, const char* type);

extern struct ae_api_registry_api* ae_global_api_registry_api;