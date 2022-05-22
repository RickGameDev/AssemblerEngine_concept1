/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef aes_planes_h
#define aes_planes_h

#include "../common.h"
#include "../types-struct.h"
#include "../plane.h"
#include "vec4.h"

/*
 Plane equation:  Ax + By + Cz + D = 0;

 It stored in vec4 as [A, B, C, D]. (A, B, C) is normal and D is distance
*/

/*
 Functions:
   AE_INLINE vec4s aes_plane_normalize(vec4s plane);
 */

/*!
 * @brief normalizes a plane
 *
 * @param[in] plane plane to normalize
 * @returns         normalized plane
 */
AE_INLINE
vec4s
aes_plane_normalize(vec4s plane) {
  ae_plane_normalize(plane.raw);
  return plane;
}

#endif /* aes_planes_h */
