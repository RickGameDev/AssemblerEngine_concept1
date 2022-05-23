#include "hashmap.h"

#include <core/core.h>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// private functions
static uint32_t				ae_hash_string(const char* str, uint32_t length);
static struct ae_hash_node* ae_hashmap_find(struct ae_hashmap* map, const char* key, uint32_t hash, uint32_t key_length);
static void					ae_hashmap_resize(struct ae_hashmap* map);
static bool					make_executable(void* ptr, size_t size);

void ae_hashmap_init(struct ae_hashmap* map)
{
	uint32_t start_size = 16, i;

	struct ae_hash_node** buckets = NULL;

	buckets = malloc(sizeof(*buckets) * start_size);

	if (!buckets)
		return;

	for (i = 0; i < start_size; i++)
		buckets[i] = NULL;

	map->buckets = buckets;
	map->size = start_size;
	map->count = 0;
	map->mask = start_size - 1;
	map->max_chain = 0;
}

void ae_hashmap_insert(struct ae_hashmap* map, const char* key, void* value, const uint32_t size)
{
	uint32_t key_length = (uint32_t)strlen(key);
	uint32_t hash = ae_hash_string(key, key_length);
	uint32_t index = hash & map->mask;

	struct ae_hash_node* node = ae_hashmap_find(map, key, hash, key_length);

	if (node)
	{
		memcpy(node->value, value, size);

		return;
	}

	if (map->count >= 3 * map->size)
		ae_hashmap_resize(map);

	node = malloc(sizeof(*node) + key_length);

	if (!node)
		return;

	node->value = malloc(size);

	if (!node->value)
	{
		free(node);
		return;
	}

	memcpy(node->value, value, size);
	memcpy(node->key, key, (size_t)key_length + 1);

	if (!make_executable(node->value, size))
		return;

	node->key_hash = hash;
	node->next = map->buckets[index];
	map->buckets[index] = node;
	map->count++;
}

void* ae_hashmap_get_or_reserve(struct ae_hashmap* map, const char* key, const uint32_t size)
{
	uint32_t key_length = (uint32_t)strlen(key);
	uint32_t hash = ae_hash_string(key, key_length);
	uint32_t index = hash & map->mask;

	struct ae_hash_node* node = ae_hashmap_find(map, key, hash, key_length);

	if (node)
		return node->value;

	if (map->count >= 3 * map->size)
		ae_hashmap_resize(map);

	node = malloc(sizeof(*node) + key_length + 1);
	if (!node)
		return NULL;

	node->value = malloc(size);

	if (!node->value)
	{
		free(node);
		return NULL;
	}

	memset(node->value, 0, size);
	memcpy(node->key, key, (size_t)key_length + 1);

	if (!make_executable(node->value, size))
		return NULL;

	node->key_hash = hash;
	node->next = map->buckets[index];
	map->buckets[index] = node;
	map->count++;

	return node->value;
}

void ae_hashmap_remove(struct ae_hashmap* map, const char* key)
{
	AE_UNREFERENCED_PARAMETER(map);
	AE_UNREFERENCED_PARAMETER(key);
}

void ae_hashmap_free(struct ae_hashmap* map)
{
	free(map->buckets);
}

// fnva1 hash
static uint32_t ae_hash_string(const char* str, uint32_t length)
{
	unsigned char* p = (unsigned char*)str;
	unsigned long int h = 2166136261UL;
	unsigned long int i;

	for (i = 0; i < length; i++)
		h = (h ^ 16777619) * p[i];

	return h;
}

static struct ae_hash_node* ae_hashmap_find(struct ae_hashmap* map, const char* key, uint32_t hash, uint32_t key_length)
{
	struct ae_hash_node* node = NULL;

	for (node = map->buckets[hash & map->mask]; node != NULL; node = node->next)
	{
		if (node->key_hash == hash &&
			strncmp(node->key, key, key_length) == 0 &&
			node->key[key_length] == '\0')
			break;
	}

	return node;
}

static void ae_hashmap_resize(struct ae_hashmap* map)
{
	struct ae_hash_node** buckets = map->buckets;

	uint32_t new_size = 2 * map->size;
	uint32_t new_mask = new_size - 1;

	map->buckets = malloc(sizeof(*map->buckets) * new_size);

	if (!map->buckets)
		return;

	memset(map->buckets, 0, sizeof(*map->buckets) * new_size);

	uint32_t i = 0;

	for (; i < map->size; i++)
	{
		struct ae_hash_node* node = buckets[i];
		while (node != NULL)
		{
			struct ae_hash_node* next = node->next;
			node->next = map->buckets[node->key_hash & new_mask];
			map->buckets[node->key_hash & new_mask] = node;
			node = next;
		}
	}

	free(buckets);

	map->size = new_size;
	map->mask = new_mask;
}

static bool make_executable(void* ptr, size_t size)
{
#ifdef _WIN32
	long unsigned int out_protect;
	if (!VirtualProtect(ptr, size, PAGE_EXECUTE_READWRITE, &out_protect))
		return false;
#endif
	return true;
}
