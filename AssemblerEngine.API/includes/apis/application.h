/*****************************************************************//**
 * @file   application.h
 * @ingroup group_api
 * @brief  Generic API to manage the application
 
 * @author RickNijhuis
 * @date   May 2022
 *********************************************************************/

 /**
 *@addtogroup group_api
 * @{
 */

#pragma once

#include "core/types.h"

struct ae_application;
struct ae_window;

/**
* @brief Application API containing function pointers to manage the application
*/
struct ae_application_api
{
	/**
	 * @todo to be implemented
	 */
	struct ae_application*	(*get)();

	/**
	 * @todo to be implemented
	 */
	struct ae_application*	(*create)(int argc, char** argv);

	/**
	 * @todo to be implemented
	 */
	void					(*exit)(struct ae_application* application);

	/**
	 * @todo to be implemented
	 */
	bool  					(*update)(struct ae_application* application);

	/**
	 * @todo to be implemented
	 */
	struct ae_window*		(*get_window)(struct ae_application* application);

	/**
	 * @todo to be implemented
	 */
	struct ae_window*		(*create_child_window)(struct ae_application* application);
};

/**@}*/
