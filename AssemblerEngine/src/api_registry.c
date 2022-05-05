#include "AssemblerEngine/api_registry.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

//struct hash_node
//{
//	struct hash_node* next;
//	uint32_t key_hash;
//	void* value;
//	char key[1];
//};
//
//struct hash_table
//{
//	struct hash_node** buckets;
//	uint32_t size;
//	uint32_t count;
//	uint32_t mask;
//	uint32_t max_chain;
//};

struct ae_api_registry_o
{
	struct ae_hashmap apis;
	struct ae_hashmap interfaces;
};

// fnva1 hash
//static uint32_t hash_string(const char* str, uint32_t length)
//{
//	unsigned char* p = (unsigned char*)str;
//	unsigned long int h = 2166136261UL;
//	unsigned long int i;
//
//	for (i = 0; i < length; i++)
//		h = (h ^ 16777619) * p[i];
//
//	return h;
//}
//
//static struct hash_node* hash_table_find(struct hash_table* table, const char* key, uint32_t hash, uint32_t key_length)
//{
//	struct hash_node* node = NULL;
//
//	for (node = table->buckets[hash & table->mask]; node != NULL; node = node->next)
//	{
//		if (node->key_hash == hash &&
//			strncmp(node->key, key, key_length) == 0 &&
//			node->key[key_length] == '\0')
//			break;
//	}
//
//	return node;
//}
//
//static void hash_table_resize(struct hash_table* table)
//{
//	struct hash_node** buckets = table->buckets;
//
//	uint32_t new_size = 2 * table->size;
//	uint32_t new_mask = new_size - 1;
//
//	if (!(table->buckets = malloc(sizeof(*table->buckets) * new_size)))
//		return;
//
//	memset(table->buckets, 0, sizeof(*table->buckets) * new_size);
//
//	uint32_t i = 0;
//
//	for (; i < table->size; i++)
//	{
//		struct hash_node* node = buckets[i];
//		while (node != NULL)
//		{
//			struct hash_node* next = node->next;
//			node->next = table->buckets[node->key_hash & new_mask];
//			table->buckets[node->key_hash & new_mask] = node;
//			node = next;
//		}
//	}
//
//	free(buckets);
//	
//	table->size = new_size;
//	table->mask = new_mask;
//}

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

	return self;
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