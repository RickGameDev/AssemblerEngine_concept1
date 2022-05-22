/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ae_sphere_h
#define ae_sphere_h

#include "common.h"
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
ae_sphere_radii(vec4 s) {
  return s[3];
}

/*!
 * @brief apply transform to sphere, it is just wrapper for ae_mat4_mulv3
 *
 * @param[in]  s    sphere
 * @param[in]  m    transform matrix
 * @param[out] dest transformed sphere
 */
AE_INLINE
void
ae_sphere_transform(vec4 s, mat4 m, vec4 dest) {
  ae_mat4_mulv3(m, s, 1.0f, dest);
  dest[3] = s[3];
}

/*!
 * @brief merges two spheres and creates a new one
 *
 * two sphere must be in same space, for instance if one in world space then
 * the other must be in world space too, not in local space.
 *
 * @param[in]  s1   sphere 1
 * @param[in]  s2   sphere 2
 * @param[out] dest merged/extended sphere
 */
AE_INLINE
void
ae_sphere_merge(vec4 s1, vec4 s2, vec4 dest) {
  float dist, radii;

  dist  = ae_vec3_distance(s1, s2);
  radii = dist + s1[3] + s2[3];

  radii = ae_max(radii, s1[3]);
  radii = ae_max(radii, s2[3]);

  ae_vec3_center(s1, s2, dest);
  dest[3] = radii;
}

/*!
 * @brief check if two sphere intersects
 *
 * @param[in]   s1  sphere
 * @param[in]   s2  other sphere
 */
AE_INLINE
bool
ae_sphere_sphere(vec4 s1, vec4 s2) {
  return ae_vec3_distance2(s1, s2) <= ae_pow2(s1[3] + s2[3]);
}

/*!
 * @brief check if sphere intersects with point
 *
 * @param[in]   s      sphere
 * @param[in]   point  point
 */
AE_INLINE
bool
ae_sphere_point(vec4 s, vec3 point) {
  float rr;
  rr = s[3] * s[3];
  return ae_vec3_distance2(point, s) <= rr;
}

#endif /* ae_sphere_h */
