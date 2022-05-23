#pragma once

#include <apis/api_registry.h>

struct ae_api_registry* ae_api_registry_new();
void ae_api_registry_free(struct ae_api_registry* registry);

void ae_api_registry_set_api(struct ae_api_registry* registry, const char* type, const void* api, const uint32_t size);
void* ae_api_registry_get_api(struct ae_api_registry* registry, const char* type, const uint32_t size);
void ae_api_registry_remove_api(struct ae_api_registry* registry, const char* type);