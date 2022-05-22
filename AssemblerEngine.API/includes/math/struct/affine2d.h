/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*
 Functions:
   AE_INLINE mat3s aes_translate2d(mat3 m, vec2 v)
   AE_INLINE mat3s aes_translate2d_x(mat3s m, float x)
   AE_INLINE mat3s aes_translate2d_y(mat3s m, float y)
   AE_INLINE mat3s aes_translate2d_make(vec2s v)
   AE_INLINE mat3s aes_scale2d_make(vec2s v)
   AE_INLINE mat3s aes_scale2d(mat3s m, vec2s v)
   AE_INLINE mat3s aes_scale2d_uni(mat3s m, float s)
   AE_INLINE mat3s aes_rotate2d_make(float angle)
   AE_INLINE mat3s aes_rotate2d(mat3s m, float angle)
   AE_INLINE mat3s aes_rotate2d_to(mat3s m, float angle)
 */

#ifndef aes_affine2ds_h
#define aes_affine2ds_h

#include "../common.h"
#include "../types-struct.h"
#include "../affine2d.h"
#include "vec3.h"
#include "mat3.h"

/*!
 * @brief translate existing 2d transform matrix by v vector
 *        and stores result in same matrix
 *
 * @param[in] m  affine transfrom
 * @param[in] v  translate vector [x, y]
 * @returns      affine transfrom
 */
AE_INLINE
mat3s
aes_translate2d(mat3s m, vec2s v) {
  ae_translate2d(m.raw, v.raw);
  return m;
}

/*!
 * @brief translate existing 2d transform matrix by x factor
 *
 * @param[in] m  affine transfrom
 * @param[in] x  x factor
 * @returns      affine transfrom
 */
AE_INLINE
mat3s
aes_translate2d_x(mat3s m, float x) {
  ae_translate2d_x(m.raw, x);
  return m;
}

/*!
 * @brief translate existing 2d transform matrix by y factor
 *
 * @param[in] m  affine transfrom
 * @param[in] y  y factor
 * @returns      affine transfrom
 */
AE_INLINE
mat3s
aes_translate2d_y(mat3s m, float y) {
  ae_translate2d_y(m.raw, y);
  return m;
}

/*!
 * @brief creates NEW translate 2d transform matrix by v vector
 *
 * @param[in] v  translate vector [x, y]
 * @returns      affine transfrom
 */
AE_INLINE
mat3s
aes_translate2d_make(vec2s v) {
  mat3s m;
  ae_translate2d_make(m.raw, v.raw);
  return m;
}

/*!
 * @brief creates NEW 2d scale matrix by v vector
 *
 * @param[in]   v  scale vector [x, y]
 * @returns affine transfrom
 */
AE_INLINE
mat3s
aes_scale2d_make(vec2s v) {
  mat3s m;
  ae_scale2d_make(m.raw, v.raw);
  return m;
}

/*!
 * @brief scales existing 2d transform matrix by v vector
 *        and stores result in same matrix
 *
 * @param[in]  m  affine transfrom
 * @param[in]  v  scale vector [x, y, z]
 * @returns       affine transfrom
 */
AE_INLINE
mat3s
aes_scale2d(mat3s m, vec2s v) {
  mat3s r;
  ae_scale2d_to(m.raw, v.raw, r.raw);
  return r;
}

/*!
 * @brief applies uniform scale to existing 2d transform matrix v = [s, s, s]
 *        and stores result in same matrix
 *
 * @param[in] m  affine transfrom
 * @param[in] s  scale factor
 * @returns      affine transfrom
 */
AE_INLINE
mat3s
aes_scale2d_uni(mat3s m, float s) {
  ae_scale2d_uni(m.raw, s);
  return m;
}

/*!
 * @brief creates NEW 2d rotation matrix by angle and axis
 *
 * axis will be normalized so you don't need to normalize it
 *
 * @param[in]  angle  angle (radians)
 * @returns           affine transfrom
 */
AE_INLINE
mat3s
aes_rotate2d_make(float angle) {
  mat3s m;
  ae_rotate2d_make(m.raw, angle);
  return m;
}

/*!
 * @brief rotate existing 2d transform matrix around given axis by angle
 *
 * @param[in] m      affine transfrom
 * @param[in] angle  angle (radians)
 * @returns          affine transfrom
 */
AE_INLINE
mat3s
aes_rotate2d(mat3s m, float angle) {
  ae_rotate2d(m.raw, angle);
  return m;
}

/*!
 * @brief rotate existing 2d transform matrix around given axis by angle
 *
 * @param[in] m      affine transfrom
 * @param[in] angle  angle (radians)
 * @returns          affine transfrom
 */
AE_INLINE
mat3s
aes_rotate2d_to(mat3s m, float angle) {
  ae_rotate2d(m.raw, angle);
  return m;
}

#endif /* aes_affine2ds_h */
