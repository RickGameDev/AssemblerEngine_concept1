/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*
 Functions:
   AE_INLINE mat4s aes_translate(mat4s m, vec3s v);
   AE_INLINE mat4s aes_translate_x(mat4s m, float x);
   AE_INLINE mat4s aes_translate_y(mat4s m, float y);
   AE_INLINE mat4s aes_translate_z(mat4s m, float z);
   AE_INLINE mat4s aes_translate_make(vec3s v);
   AE_INLINE mat4s aes_scale_to(mat4s m, vec3s v);
   AE_INLINE mat4s aes_scale_make(vec3s v);
   AE_INLINE mat4s aes_scale(mat4s m, vec3s v);
   AE_INLINE mat4s aes_scale_uni(mat4s m, float s);
   AE_INLINE mat4s aes_rotate_x(mat4s m, float angle);
   AE_INLINE mat4s aes_rotate_y(mat4s m, float angle);
   AE_INLINE mat4s aes_rotate_z(mat4s m, float angle);
   AE_INLINE mat4s aes_rotate_make(float angle, vec3s axis);
   AE_INLINE mat4s aes_rotate(mat4s m, float angle, vec3s axis);
   AE_INLINE mat4s aes_rotate_at(mat4s m, vec3s pivot, float angle, vec3s axis);
   AE_INLINE mat4s aes_rotate_atm(mat4s m, vec3s pivot, float angle, vec3s axis);
   AE_INLINE vec3s aes_decompose_scalev(mat4s m);
   AE_INLINE bool  aes_uniscaled(mat4s m);
   AE_INLINE void  aes_decompose_rs(mat4s m, mat4s * r, vec3s * s);
   AE_INLINE void  aes_decompose(mat4s m, vec4s t, mat4s * r, vec3s * s);
 */

#ifndef aes_affines_h
#define aes_affines_h

#include "../common.h"
#include "../types-struct.h"
#include "../affine.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

/*!
 * @brief translate existing transform matrix by v vector
 *        and stores result in same matrix
 *
 * @param[in]       m   affine transfrom
 * @param[in]       v   translate vector [x, y, z]
 * @returns             affine transfrom
 */
AE_INLINE
mat4s
aes_translate(mat4s m, vec3s v) {
  ae_translate(m.raw, v.raw);
  return m;
}

/*!
 * @brief translate existing transform matrix by x factor
 *
 * @param[in]       m   affine transfrom
 * @param[in]       x   x factor
 * @returns             affine transfrom
 */
AE_INLINE
mat4s
aes_translate_x(mat4s m, float x) {
  ae_translate_x(m.raw, x);
  return m;
}

/*!
 * @brief translate existing transform matrix by y factor
 *
 * @param[in]       m   affine transfrom
 * @param[in]       y   y factor
 * @returns             affine transfrom
 */
AE_INLINE
mat4s
aes_translate_y(mat4s m, float y) {
  ae_translate_y(m.raw, y);
  return m;
}

/*!
 * @brief translate existing transform matrix by z factor
 *
 * @param[in]       m   affine transfrom
 * @param[in]       z   z factor
 * @returns             affine transfrom
 */
AE_INLINE
mat4s
aes_translate_z(mat4s m, float z) {
  ae_translate_z(m.raw, z);
  return m;
}

/*!
 * @brief creates NEW translate transform matrix by v vector
 *
 * @param[in]   v   translate vector [x, y, z]
 * @returns         affine transfrom
 */
AE_INLINE
mat4s
aes_translate_make(vec3s v) {
  mat4s m;
  ae_translate_make(m.raw, v.raw);
  return m;
}

/*!
 * @brief creates NEW scale matrix by v vector
 *
 * @param[in]   v  scale vector [x, y, z]
 * @returns affine transfrom
 */
AE_INLINE
mat4s
aes_scale_make(vec3s v) {
  mat4s m;
  ae_scale_make(m.raw, v.raw);
  return m;
}

/*!
 * @brief scales existing transform matrix by v vector
 *        and stores result in same matrix
 *
 * @param[in]    m   affine transfrom
 * @param[in]    v   scale vector [x, y, z]
 * @returns          affine transfrom
 */
AE_INLINE
mat4s
aes_scale(mat4s m, vec3s v) {
  mat4s r;
  ae_scale_to(m.raw, v.raw, r.raw);
  return r;
}

/*!
 * @brief applies uniform scale to existing transform matrix v = [s, s, s]
 *        and stores result in same matrix
 *
 * @param[in]    m   affine transfrom
 * @param[in]    s   scale factor
 * @returns          affine transfrom
 */
AE_INLINE
mat4s
aes_scale_uni(mat4s m, float s) {
  ae_scale_uni(m.raw, s);
  return m;
}

/*!
 * @brief rotate existing transform matrix around X axis by angle
 *        and store result in dest
 *
 * @param[in]   m       affine transfrom
 * @param[in]   angle   angle (radians)
 * @returns             rotated matrix
 */
AE_INLINE
mat4s
aes_rotate_x(mat4s m, float angle) {
  mat4s r;
  ae_rotate_x(m.raw, angle, r.raw);
  return r;
}

/*!
 * @brief rotate existing transform matrix around Y axis by angle
 *        and store result in dest
 *
 * @param[in]   m       affine transfrom
 * @param[in]   angle   angle (radians)
 * @returns             rotated matrix
 */
AE_INLINE
mat4s
aes_rotate_y(mat4s m, float angle) {
  mat4s r;
  ae_rotate_y(m.raw, angle, r.raw);
  return r;
}

/*!
 * @brief rotate existing transform matrix around Z axis by angle
 *        and store result in dest
 *
 * @param[in]   m       affine transfrom
 * @param[in]   angle   angle (radians)
 * @returns             rotated matrix
 */
AE_INLINE
mat4s
aes_rotate_z(mat4s m, float angle) {
  mat4s r;
  ae_rotate_z(m.raw, angle, r.raw);
  return r;
}

/*!
 * @brief creates NEW rotation matrix by angle and axis
 *
 * axis will be normalized so you don't need to normalize it
 *
 * @param[in]  angle  angle (radians)
 * @param[in]  axis   axis
 * @returns           affine transfrom
 */
AE_INLINE
mat4s
aes_rotate_make(float angle, vec3s axis) {
  mat4s m;
  ae_rotate_make(m.raw, angle, axis.raw);
  return m;
}

/*!
 * @brief rotate existing transform matrix around given axis by angle
 *
 * @param[in]       m       affine transfrom
 * @param[in]       angle   angle (radians)
 * @param[in]       axis    axis
 * @returns                 affine transfrom
 */
AE_INLINE
mat4s
aes_rotate(mat4s m, float angle, vec3s axis) {
  ae_rotate(m.raw, angle, axis.raw);
  return m;
}

/*!
 * @brief rotate existing transform
 *        around given axis by angle at given pivot point (rotation center)
 *
 * @param[in]       m       affine transfrom
 * @param[in]       pivot   rotation center
 * @param[in]       angle   angle (radians)
 * @param[in]       axis    axis
 * @returns                 affine transfrom
 */
AE_INLINE
mat4s
aes_rotate_at(mat4s m, vec3s pivot, float angle, vec3s axis) {
  ae_rotate_at(m.raw, pivot.raw, angle, axis.raw);
  return m;
}

/*!
 * @brief creates NEW rotation matrix by angle and axis at given point
 *
 * this creates rotation matrix, it assumes you don't have a matrix
 *
 * this should work faster than ae_rotate_at because it reduces
 * one ae_translate.
 *
 * @param[in]  m      affine transfrom
 * @param[in]  pivot  rotation center
 * @param[in]  angle  angle (radians)
 * @param[in]  axis   axis
 * @returns           affine transfrom
 */
AE_INLINE
mat4s
aes_rotate_atm(mat4s m, vec3s pivot, float angle, vec3s axis) {
  ae_rotate_atm(m.raw, pivot.raw, angle, axis.raw);
  return m;
}

/*!
 * @brief decompose scale vector
 *
 * @param[in]  m  affine transform
 * @returns       scale vector (Sx, Sy, Sz)
 */
AE_INLINE
vec3s
aes_decompose_scalev(mat4s m) {
  vec3s r;
  ae_decompose_scalev(m.raw, r.raw);
  return r;
}

/*!
 * @brief returns true if matrix is uniform scaled. This is helpful for
 *        creating normal matrix.
 *
 * @param[in] m m
 *
 * @return boolean
 */
AE_INLINE
bool
aes_uniscaled(mat4s m) {
  return ae_uniscaled(m.raw);
}

/*!
 * @brief decompose rotation matrix (mat4) and scale vector [Sx, Sy, Sz]
 *        DON'T pass projected matrix here
 *
 * @param[in]  m affine transform
 * @param[out] r rotation matrix
 * @param[out] s scale matrix
 */
AE_INLINE
void
aes_decompose_rs(mat4s m, mat4s * __restrict r, vec3s * __restrict s) {
  ae_decompose_rs(m.raw, r->raw, s->raw);
}

/*!
 * @brief decompose affine transform, TODO: extract shear factors.
 *        DON'T pass projected matrix here
 *
 * @param[in]  m affine transfrom
 * @param[out] t translation vector
 * @param[out] r rotation matrix (mat4)
 * @param[out] s scaling vector [X, Y, Z]
 */
AE_INLINE
void
aes_decompose(mat4s m, vec4s * __restrict t, mat4s * __restrict r, vec3s * __restrict s) {
  ae_decompose(m.raw, t->raw, r->raw, s->raw);
}

#endif /* aes_affines_h */
