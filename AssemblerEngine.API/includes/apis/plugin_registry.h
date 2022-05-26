/*****************************************************************//**
 * @file   plugin_registry.h
 * @ingroup group_api
 * @brief  Plugin registry API
 * 
 * @author RickNijhuis
 * @date   May 2022
 *********************************************************************/

 /**
 *@addtogroup group_api
 * @{
 */

#pragma once

#include "core/types.h"

struct ae_api_registry_api;
struct ae_plugin_registry;
struct ae_plugin_registry_api;

typedef void (*ae_plugin_load_fn)(struct ae_api_registry_api* registry, bool reload);
typedef void (*ae_plugin_unload_fn)(struct ae_api_registry_api* registry);

struct ae_plugin_registry_api
{
	struct ae_plugin_registry*	registry;

	void (*load)(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, const char* path);
	void (*unload)(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, uint32_t id);
	void (*reload)(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, uint32_t id);
};

/**@}*/
