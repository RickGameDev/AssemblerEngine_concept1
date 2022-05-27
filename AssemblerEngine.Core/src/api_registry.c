#include "ae_api_registry_internal.h"
#include "ae_hashmap_internal.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct ae_api_registry
{
	struct ae_hashmap apis;
	struct ae_hashmap interfaces;
};

void ae_api_registry_free(struct ae_api_registry* registry)
{
	if (registry)
	{
		ae_hashmap_free(&registry->apis);
		ae_hashmap_free(&registry->interfaces);
		free(registry);
	}
}

void ae_api_registry_set_api(struct ae_api_registry* registry, const char* type, const ae_interface* api, const uint32_t size)
{
	ae_hashmap_insert(&registry->apis, type, api, size);
}

void* ae_api_registry_get_api(struct ae_api_registry* registry, const char* type, const uint32_t size)
{
	return ae_hashmap_get_or_reserve(&registry->apis, type, size);
}

void ae_api_registry_remove_api(struct ae_api_registry* registry, const char* type)
{
	 ae_hashmap_remove(&registry->apis, type);
}

struct ae_api_registry* ae_api_registry_new()
{
	struct ae_api_registry* self = malloc(sizeof(*self));

	if (!self)
	{
		return NULL;
	}

	ae_hashmap_init(&self->apis);

	if (!self->apis.buckets)
	{
		free(self);
		return NULL;
	}

	ae_hashmap_init(&self->interfaces);

	if (!self->interfaces.buckets)
	{
		ae_hashmap_free(&self->apis);
		free(self);
		return NULL;
	}

	return self;
}
