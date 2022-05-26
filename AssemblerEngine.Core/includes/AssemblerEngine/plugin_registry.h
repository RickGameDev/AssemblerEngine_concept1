/*****************************************************************//**
 * @file   plugin_registry.h
 * @ingroup group_core
 * @brief  
 * 
 * @author RickNijhuis
 * @date   May 2022
 *********************************************************************/

 /**
 *@addtogroup group_core
 * @{
 */

#pragma once

#include <stdint.h>

struct ae_plugin_registry;
struct ae_api_registry_api;

struct ae_plugin_registry* ae_plugin_registry_new();
void ae_plugin_registry_free(struct ae_plugin_registry* registry);
void ae_plugin_registry_load(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, const char* dir);
void ae_plugin_registry_unload(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, uint32_t index);
void ae_plugin_registry_reload(struct ae_plugin_registry* registry, struct ae_api_registry_api* api_registry, uint32_t index);

/**@}*/
