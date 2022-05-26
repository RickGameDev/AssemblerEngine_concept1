#pragma once

#include <stdint.h>
#include <stddef.h>

struct ae_hash_node
{
	struct ae_hash_node* next;
	uint32_t key_hash;
	void* value;
	char key[1];
};

struct ae_hashmap
{
	struct ae_hash_node** buckets;
	uint32_t size;
	uint32_t count;
	uint32_t mask;
	uint32_t max_chain;
};

void	ae_hashmap_init(struct ae_hashmap* map);
void	ae_hashmap_insert(struct ae_hashmap* map, const char* key, const void* value, const uint32_t size);
void*	ae_hashmap_get_or_reserve(struct ae_hashmap* map, const char* key, const uint32_t size);
void	ae_hashmap_remove(struct ae_hashmap* map, const char* key);
void	ae_hashmap_free(struct ae_hashmap* map);