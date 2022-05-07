#pragma once

// - naming conventions
// ae:	namespace
// o:	object/instance
// i:	interface
// api: plugin api

#include <stdint.h>

/// <summary>
/// opaque api_registry instance ptr
/// </summary>
struct ae_api_registry_o;
struct ae_api_registry_api;

typedef void (*ae_api_registry_set_api_fn)(struct ae_api_registry_api* self, const char* type, void* api, uint32_t size);
typedef void* (*ae_api_registry_remove_api_fn)(struct ae_api_registry_api* self, const char* type);
typedef void* (*ae_api_registry_get_api_fn)(struct ae_api_registry_api* self, const char* type, uint32_t size);
typedef uint32_t(*ae_api_registry_get_api_count_fn)(struct ae_api_registry_api* self, const char* type);

typedef void* (*ae_api_registry_add_object_fn)(struct ae_api_registry_api* self, const char* type, void* object, uint32_t size);
typedef void* (*ae_api_registry_remove_object_fn)(struct ae_api_registry_api* self, const char* type);
typedef void* (*ae_api_registry_get_object_fn)(struct ae_api_registry_api* self, const char* type);
typedef uint32_t (*ae_api_registry_get_object_count_fn)(struct ae_api_registry_api* self, const char* type);

/// <summary>
/// api for the api_registry
/// </summary>
struct ae_api_registry_api
{
	/// <summary>
	/// opaque api_registry instance ptr
	/// </summary>
	struct ae_api_registry_o*			registry;

	/// <summary>
	/// adds api interface to the registry
	/// </summary>
	/// <param name="name">name of the api to add</param>
	/// <param name="interface">instance of the api to add</param>
	/// <returns>void* pointing to the interface if succeeded, else NULL</returns>
	ae_api_registry_set_api_fn			set_api;

	/// <summary>
	/// removes api interface from the registry
	/// </summary>
	/// <param name="name">name of the api to remove</param>
	/// <returns>void* pointing to the interface that is removed from the registry, else NULL if not exists</returns>
	ae_api_registry_remove_api_fn		remove_api;

	/// <summary>
	/// gets the interface from the registry by name
	/// </summary>
	/// <param name="name">name of the api to get from the registry</param>
	/// <returns>void* pointing to the interface if succeeded, else NULL</returns>
	ae_api_registry_get_api_fn			get_api;
	ae_api_registry_get_api_count_fn	get_api_count;

	ae_api_registry_add_object_fn		add_object;
	ae_api_registry_remove_object_fn	remove_object;
	ae_api_registry_get_object_fn		get_object;
	ae_api_registry_get_object_count_fn get_object_count;
};

#define ae_get_api(reg, TYPE) reg->get_api(reg, #TYPE, sizeof(struct TYPE))
#define ae_set_api(reg, TYPE, INTERF) reg->set_api(reg, #TYPE, &INTERF, sizeof(struct TYPE))