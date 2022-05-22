/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef aes_spheres_h
#define aes_spheres_h

#include "../common.h"
#include "../types-struct.h"
#include "../sphere.h"
#include "mat4.h"

/*
  Sphere Representation in ae: [center.x, center.y, center.z, radii]

  You could use this representation or you can convert it to vec4 before call
  any function
 */

/*!
 * @brief helper for getting sphere radius
 *
 * @param[in]   s  sphere
 *
 * @return returns radii
 */
AE_INLINE
float
aes_sphere_radii(vec4s s) {
  return ae_sphere_radii(s.raw);
}

/*!
 * @brief apply transform to sphere, it is just wrapper for ae_mat4_mulv3
 *
 * @param[in]  s    sphere
 * @param[in]  m    transform matrix
 * @returns         transformed sphere
 */
AE_INLINE
vec4s
aes_sphere_transform(vec4s s, mat4s m) {
  vec4s r;
  ae_sphere_transform(s.raw, m.raw, r.raw);
  return r;
}

/*!
 * @brief merges two spheres and creates a new one
 *
 * two sphere must be in same space, for instance if one in world space then
 * the other must be in world space too, not in local space.
 *
 * @param[in]  s1   sphere 1
 * @param[in]  s2   sphere 2
 * returns          merged/extended sphere
 */
AE_INLINE
vec4s
aes_sphere_merge(vec4s s1, vec4s s2) {
  vec4s r;
  ae_sphere_merge(s1.raw, s2.raw, r.raw);
  return r;
}

/*!
 * @brief check if two sphere intersects
 *
 * @param[in]   s1  sphere
 * @param[in]   s2  other sphere
 */
AE_INLINE
bool
aes_sphere_sphere(vec4s s1, vec4s s2) {
  return ae_sphere_sphere(s1.raw, s2.raw);
}

/*!
 * @brief check if sphere intersects with point
 *
 * @param[in]   s      sphere
 * @param[in]   point  point
 */
AE_INLINE
bool
aes_sphere_point(vec4s s, vec3s point) {
  return ae_sphere_point(s.raw, point.raw);
}

#endif /* aes_spheres_h */
