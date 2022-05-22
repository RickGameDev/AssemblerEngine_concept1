#pragma once

// - naming conventions
// ae:	namespace
// o:	object/instance
// i:	interface
// api: plugin api

#include "core/types.h"

/// <summary>
/// opaque api_registry instance ptr
/// </summary>
struct ae_api_registry;
struct ae_api_registry_api;

/// <summary>
/// api for the api_registry
/// </summary>
struct ae_api_registry_api
{
	/// <summary>
	/// opaque api_registry instance ptr
	/// </summary>
	struct ae_api_registry*				registry;

	/// <summary>
	/// adds api interface to the registry
	/// </summary>
	/// <param name="name">name of the api to add</param>
	/// <param name="interface">instance of the api to add</param>
	/// <returns>void* pointing to the interface if succeeded, else NULL</returns>
	void		(*set_api)(struct ae_api_registry* registry, const char* type, void* api, uint32_t size);

	/// <summary>
	/// removes api interface from the registry
	/// </summary>
	/// <param name="name">name of the api to remove</param>
	/// <returns>void* pointing to the interface that is removed from the registry, else NULL if not exists</returns>
	void*		(*remove_api)(struct ae_api_registry* registry, const char* type);

	/// <summary>
	/// gets the interface from the registry by name
	/// </summary>
	/// <param name="name">name of the api to get from the registry</param>
	/// <returns>void* pointing to the interface if succeeded, else NULL</returns>
	void*		(*get_api)(struct ae_api_registry* registry, const char* type, uint32_t size);
	uint32_t	(*get_api_count)(struct ae_api_registry* registry, const char* type);

	void*		(*add_object)(struct ae_api_registry* registry, const char* type, void* object, uint32_t size);
	void*		(*remove_object)(struct ae_api_registry* registry, const char* type);
	void*		(*get_object)(struct ae_api_registry* registry, const char* type);
	uint32_t	(*get_object_count)(struct ae_api_registry* registry, const char* type);
};

#define ae_get_api(reg, TYPE) reg->get_api(reg->registry, #TYPE, sizeof(struct TYPE))
#define ae_set_api(reg, TYPE, INTERF) reg->set_api(reg->registry, #TYPE, INTERF, sizeof(*INTERF))