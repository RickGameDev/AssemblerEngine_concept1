#include "AssemblerEngine/api_registry.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct hash_node
{
	struct hash_node* next;
	uint32_t key_hash;
	void* value;
	char key[1];
};

struct hash_table
{
	struct hash_node** buckets;
	uint32_t size;
	uint32_t count;
	uint32_t mask;
	uint32_t max_chain;
};

struct ae_api_registry_o
{
	struct hash_table apis;
	struct hash_table interfaces;
};

// fnva1 hash
static uint32_t hash_string(const char* str, uint32_t length)
{
	unsigned char* p = (unsigned char*)str;
	unsigned long int h = 2166136261UL;
	unsigned long int i;

	for (i = 0; i < length; i++)
		h = (h ^ 16777619) * p[i];

	return h;
}

static struct hash_node* hash_table_find(struct hash_table* table, const char* key, uint32_t hash, uint32_t key_length)
{
	struct hash_node* node = NULL;

	for (node = table->buckets[hash & table->mask]; node != NULL; node = node->next)
	{
		if (node->key_hash == hash &&
			strncmp(node->key, key, key_length) == 0 &&
			node->key[key_length] == '\0')
			break;
	}

	return node;
}

static void hash_table_resize(struct hash_table* table)
{
	struct hash_node** buckets = table->buckets;

	uint32_t new_size = 2 * table->size;
	uint32_t new_mask = new_size - 1;

	if (!(table->buckets = malloc(sizeof(*table->buckets) * new_size)))
		return;

	memset(table->buckets, 0, sizeof(*table->buckets) * new_size);

	uint32_t i = 0;

	for (; i < table->size; i++)
	{
		struct hash_node* node = buckets[i];
		while (node != NULL)
		{
			struct hash_node* next = node->next;
			node->next = table->buckets[node->key_hash & new_mask];
			table->buckets[node->key_hash & new_mask] = node;
			node = next;
		}
	}

	free(buckets);
	
	table->size = new_size;
	table->mask = new_mask;
}

struct ae_api_registry_api* ae_api_registry_new()
{
	struct ae_api_registry_api* self = NULL;

	if (!(self = malloc(sizeof(*self))))
	{
		return NULL;
	}

	struct ae_api_registry_o* registry = NULL;

	if (!(registry = malloc(sizeof(*registry))))
	{
		free(self);
		return NULL;
	}

	self->registry = registry;

	uint32_t start_size = 16, i;

	struct hash_node** buckets = NULL;

	if (!(buckets = malloc(sizeof(*buckets) * start_size)))
	{
		free(self->registry);
		free(self);
		return NULL;
	}

	for (i = 0; i < start_size; i++)
		buckets[i] = NULL;

	self->registry->apis.buckets = buckets;
	self->registry->apis.size = start_size;
	self->registry->apis.count = 0;
	self->registry->apis.mask = start_size - 1;
	self->registry->apis.max_chain = 0;

	if (!(buckets = malloc(sizeof(*buckets) * start_size)))
	{
		free(self->registry->apis.buckets);
		free(self->registry);
		free(self);
		return NULL;
	}

	for (i = 0; i < start_size; i++)
		buckets[i] = NULL;

	self->registry->interfaces.buckets = buckets;
	self->registry->interfaces.size = start_size;
	self->registry->interfaces.count = 0;
	self->registry->interfaces.mask = start_size - 1;
	self->registry->interfaces.max_chain = 0;

	return self;
}

void ae_api_registry_set_api(struct ae_api_registry_api* self, const char* type, void* api, const uint32_t size)
{
	struct hash_table* table = &self->registry->apis;
	uint32_t key_length = strlen(type);
	uint32_t hash = hash_string(type, key_length);
	uint32_t index = hash & table->mask;

	struct hash_node* node = hash_table_find(table, type, hash, key_length);

	if (node)
	{
		memcpy(node->value, api, size);
		return;
	}

	if (table->count >= 3 * table->size)
		hash_table_resize(table);

	if (!(node = malloc(sizeof(*node) + key_length)))
		return;

	if (!(node->value = malloc(size)))
	{
		free(node);
		return;
	}

	memcpy(node->value, api, size);
	memcpy(node->key, type, (size_t)key_length + 1);

	node->key_hash = hash;
	node->next = table->buckets[index];
	table->buckets[index] = node;
	table->count++;

}

void* ae_api_registry_get_api(struct ae_api_registry_api* self, const char* type, uint32_t size)
{
	struct hash_table* table = &self->registry->apis;
	uint32_t key_length = strlen(type) ;
	uint32_t hash = hash_string(type, key_length);
	uint32_t index = hash & table->mask;

	struct hash_node* node = hash_table_find(table, type, hash, key_length);

	if (node)
		return node;

	if (table->count >= 3 * table->size)
		hash_table_resize(table);

	if (!(node = malloc(sizeof(*node) + key_length)))
		return NULL;

	if (!(node->value = malloc(size)))
	{
		free(node);
		return NULL;
	}
	memset(node->value, 0, size);
	memcpy(node->key, type, (size_t)key_length + 1);

	node->key_hash = hash;
	node->next = table->buckets[index];
	table->buckets[index] = node;
	table->count++;

	return node->value;
}

void* ae_api_registry_remove_api(struct ae_api_registry_api* self, const char* type)
{
	return NULL;
}