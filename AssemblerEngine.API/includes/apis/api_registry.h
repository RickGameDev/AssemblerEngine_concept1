/*****************************************************************//**
 * @file   api_registry.h
 * @ingroup group_api
 * @brief  API registry API responsible for registering, fetching and removing of plugin apis
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

/**@brief opaque registry object containing all registered apis.*/
struct ae_api_registry;

/**@brief typedef for api interface.*/
typedef void ae_interface;

/** @brief ae_api_registry_api containing the actual registry and functions to modify the registry */
struct ae_api_registry_api
{
	/** @brief opaque registry object containing all registered apis */
	struct ae_api_registry*	registry;
	
	/**
	 * @brief Function pointer to add an api to the registry
	 * @param [in] registry The pointer to the registry
	 * @param [in] type The name of the registry api type to set
	 * @param [in] api The pointer of the api containing the function pointers of that api
	 * @param [in] size The size of the registry api type to get
	 */
	void			(*set_api)(struct ae_api_registry* registry, const char* type, const ae_interface* api, const uint32_t size);

	/**
	 * @brief Function pointer to remove an api from the registry
	 * @param [in] registry The pointer to the registry
	 * @param [in] type The name of the registry api type to remove
	 */
	void			(*remove_api)(struct ae_api_registry* registry, const char* type);

	/**
	* @brief Function pointer to get an api from the registry
	* @param [in] registry The pointer to the registry
	* @param [in] type The name of the registry api type to get
	* @param [in] size The size of the registry api type to get
	*/
	ae_interface*	(*get_api)(struct ae_api_registry* registry, const char* type, uint32_t size);

	/**
	 * @todo to be implemented
	 */
	uint32_t		(*get_api_count)(struct ae_api_registry* registry, const char* type);

	/**
	 * @todo to be implemented
	 */
	void*			(*add_object)(struct ae_api_registry* registry, const char* type, const void* object, uint32_t size);

	/**
	 * @todo to be implemented
	 */
	void*			(*remove_object)(struct ae_api_registry* registry, const char* type);

	/**
	 * @todo to be implemented
	 */
	void*			(*get_object)(struct ae_api_registry* registry, const char* type);

	/**
	 * @todo to be implemented
	 */
	uint32_t		(*get_object_count)(struct ae_api_registry* registry, const char* type);
};

/** convenience macro to get an api */
#define ae_get_api(reg, TYPE) reg->get_api(reg->registry, #TYPE, sizeof(struct TYPE))

/** convenience macro to set an api */
#define ae_set_api(reg, TYPE, INTERF) reg->set_api(reg->registry, #TYPE, INTERF, sizeof(*INTERF))

/**@}*/
