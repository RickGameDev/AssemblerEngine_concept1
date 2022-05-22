/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ae_plane_h
#define ae_plane_h

#include "common.h"
#include "vec3.h"
#include "vec4.h"

/*
 Plane equation:  Ax + By + Cz + D = 0;

 It stored in vec4 as [A, B, C, D]. (A, B, C) is normal and D is distance
*/

/*
 Functions:
   AE_INLINE void  ae_plane_normalize(vec4 plane);
 */

/*!
 * @brief normalizes a plane
 *
 * @param[in, out] plane plane to normalize
 */
AE_INLINE
void
ae_plane_normalize(vec4 plane) {
  float norm;
  
  if ((norm = ae_vec3_norm(plane)) == 0.0f) {
    ae_vec4_zero(plane);
    return;
  }
  
  ae_vec4_scale(plane, 1.0f / norm, plane);
}

#endif /* ae_plane_h */
