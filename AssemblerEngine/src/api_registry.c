#include "AssemblerEngine/api_registry.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

struct ae_api_registry_o
{
	struct ae_hashmap apis;
	struct ae_hashmap interfaces;
};

struct ae_api_registry_api* ae_api_registry_new()
{
	struct ae_api_registry_api* self = NULL;

	if (!(self = malloc(sizeof(*self))))
	{
		return NULL;
	}

	self->registry = NULL;

	if (!(self->registry = malloc(sizeof(*self->registry))))
	{
		free(self);
		return NULL;
	}

	ae_hashmap_init(&self->registry->apis);

	if (!self->registry->apis.buckets)
	{
		free(self->registry);
		free(self);
		return NULL;
	}

	ae_hashmap_init(&self->registry->interfaces);

	if (!self->registry->interfaces.buckets)
	{
		ae_hashmap_free(&self->registry->apis);
		free(self->registry);
		free(self);
		return NULL;
	}

	self->get_api = ae_api_registry_get_api;
	self->set_api = ae_api_registry_set_api;
	self->remove_api = ae_api_registry_remove_api;

	return self;
}

void ae_api_registry_free(struct ae_api_registry_api* self)
{
	if (self)
	{
		ae_hashmap_free(&self->registry->apis);
		ae_hashmap_free(&self->registry->interfaces);
		free(self->registry);
		free(self);
	}
}

void ae_api_registry_set_api(struct ae_api_registry_api* self, const char* type, void* api, const uint32_t size)
{
	ae_hashmap_insert(&self->registry->apis, type, api, size);
}

void* ae_api_registry_get_api(struct ae_api_registry_api* self, const char* type, uint32_t size)
{
	ae_hashmap_get_or_reserve(&self->registry->apis, type, size);
}

void* ae_api_registry_remove_api(struct ae_api_registry_api* self, const char* type)
{
	ae_hashmap_remove(&self->registry->apis, type);
}