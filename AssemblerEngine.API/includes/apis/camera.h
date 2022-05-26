/*****************************************************************//**
 * @file   camera.h
 * @ingroup group_api
 * @brief  Camera API for creating and modifying the camera struct
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

/** @brief camera struct containing matrices needed to create the view projection */
struct ae_camera
{
    /** @brief view matrix */
    mat4 view;
    
    /** @brief projection matrix, orthographic or perspective */
    mat4 projection;
    
    /** @brief view projection matrix, created by multiplying the view and projection matrix. */
    mat4 view_projection;
};

/** @brief camera api, containing function pointers to modify the camera struct */
struct ae_camera_api
{
    /**
    * @brief function ptr to create a new orthographic camera
    * @param [in] position The position to create the camera at in world space
    * @param [in] aspect_ratio The aspect ratio, should be viewport width / viewport height
    * @param [in] left The left coordinate of the frustum
    * @param [in] right The right coordinate of the frustum
    * @param [in] bottom The Bottom coordinate of the frustum
    * @param [in] top The top coordinate of the frustum
    * @param [in] near The near coordinate of the frustum
    * @param [in] far The far coordinate of the frustum
    * @return struct ae_camera ptr
    */
    struct ae_camera* (*create_orthographic)(vec3 position, const float aspect_ratio, const float left, const float right, const float bottom, const float top, const float near, const float far);
    /**
     * @brief destroys allocated camera
     * @param [in] camera The camera to destroy
     */
    void (*destroy)(struct ae_camera* camera);
};

/**@}*/
