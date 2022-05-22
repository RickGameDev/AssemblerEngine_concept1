/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*!
 * @brief SIMD like functions
 */

/*
 Functions:
   AE_INLINE vec3s aes_vec3_broadcast(float val);
   AE_INLINE vec3s aes_vec3_fill(float val);
   AE_INLINE bool  aes_vec3_eq(vec3s v, float val);
   AE_INLINE bool  aes_vec3_eq_eps(vec3s v, float val);
   AE_INLINE bool  aes_vec3_eq_all(vec3s v);
   AE_INLINE bool  aes_vec3_eqv(vec3s a, vec3s b);
   AE_INLINE bool  aes_vec3_eqv_eps(vec3s a, vec3s b);
   AE_INLINE float aes_vec3_max(vec3s v);
   AE_INLINE float aes_vec3_min(vec3s v);
   AE_INLINE bool  aes_vec3_isnan(vec3s v);
   AE_INLINE bool  aes_vec3_isinf(vec3s v);
   AE_INLINE bool  aes_vec3_isvalid(vec3s v);
   AE_INLINE vec3s aes_vec3_sign(vec3s v);
   AE_INLINE vec3s aes_vec3_abs(vec3s v);
   AE_INLINE vec3s aes_vec3_fract(vec3s v);
   AE_INLINE float aes_vec3_hadd(vec3s v);
   AE_INLINE vec3s aes_vec3_sqrt(vec3s v);
 */

#ifndef aes_vec3s_ext_h
#define aes_vec3s_ext_h

#include "../common.h"
#include "../types-struct.h"
#include "../util.h"
#include "../vec3-ext.h"

/*!
 * @brief fill a vector with specified value
 *
 * @param[in]  val  value
 * @returns         dest
 */
AE_INLINE
vec3s
aes_vec3_broadcast(float val) {
  vec3s r;
  ae_vec3_broadcast(val, r.raw);
  return r;
}

/*!
 * @brief fill a vector with specified value
 *
 * @param[in]  val  value
 * @returns         dest
 */
AE_INLINE
vec3s
aes_vec3_fill(float val) {
  vec3s r;
  ae_vec3_fill(r.raw, val);
  return r;
}

/*!
 * @brief check if vector is equal to value (without epsilon)
 *
 * @param[in] v   vector
 * @param[in] val value
 */
AE_INLINE
bool
aes_vec3_eq(vec3s v, float val) {
  return ae_vec3_eq(v.raw, val);
}

/*!
 * @brief check if vector is equal to value (with epsilon)
 *
 * @param[in] v   vector
 * @param[in] val value
 */
AE_INLINE
bool
aes_vec3_eq_eps(vec3s v, float val) {
  return ae_vec3_eq_eps(v.raw, val);
}

/*!
 * @brief check if vectors members are equal (without epsilon)
 *
 * @param[in] v   vector
 */
AE_INLINE
bool
aes_vec3_eq_all(vec3s v) {
  return ae_vec3_eq_all(v.raw);
}

/*!
 * @brief check if vector is equal to another (without epsilon)
 *
 * @param[in] a vector
 * @param[in] b vector
 */
AE_INLINE
bool
aes_vec3_eqv(vec3s a, vec3s b) {
  return ae_vec3_eqv(a.raw, b.raw);
}

/*!
 * @brief check if vector is equal to another (with epsilon)
 *
 * @param[in] a vector
 * @param[in] b vector
 */
AE_INLINE
bool
aes_vec3_eqv_eps(vec3s a, vec3s b) {
  return ae_vec3_eqv_eps(a.raw, b.raw);
}

/*!
 * @brief max value of vector
 *
 * @param[in] v vector
 */
AE_INLINE
float
aes_vec3_max(vec3s v) {
  return ae_vec3_max(v.raw);
}

/*!
 * @brief min value of vector
 *
 * @param[in] v vector
 */
AE_INLINE
float
aes_vec3_min(vec3s v) {
  return ae_vec3_min(v.raw);
}

/*!
 * @brief check if all items are NaN (not a number)
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
AE_INLINE
bool
aes_vec3_isnan(vec3s v) {
  return ae_vec3_isnan(v.raw);
}

/*!
 * @brief check if all items are INFINITY
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
AE_INLINE
bool
aes_vec3_isinf(vec3s v) {
  return ae_vec3_isinf(v.raw);
}

/*!
 * @brief check if all items are valid number
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
AE_INLINE
bool
aes_vec3_isvalid(vec3s v) {
  return ae_vec3_isvalid(v.raw);
}

/*!
 * @brief get sign of 32 bit float as +1, -1, 0
 *
 * Important: It returns 0 for zero/NaN input
 *
 * @param   v   vector
 * @returns     sign vector
 */
AE_INLINE
vec3s
aes_vec3_sign(vec3s v) {
  vec3s r;
  ae_vec3_sign(v.raw, r.raw);
  return r;
}

/*!
 * @brief absolute value of each vector item
 *
 * @param[in]  v    vector
 * @return          destination vector
 */
AE_INLINE
vec3s
aes_vec3_abs(vec3s v) {
  vec3s r;
  ae_vec3_abs(v.raw, r.raw);
  return r;
}

/*!
 * @brief fractional part of each vector item
 *
 * @param[in]  v    vector
 * @return          dest destination vector
 */
AE_INLINE
vec3s
aes_vec3_fract(vec3s v) {
  vec3s r;
  ae_vec3_fract(v.raw, r.raw);
  return r;
}

/*!
 * @brief vector reduction by summation
 * @warning could overflow
 *
 * @param[in]  v    vector
 * @return     sum of all vector's elements
 */
AE_INLINE
float
aes_vec3_hadd(vec3s v) {
  return ae_vec3_hadd(v.raw);
}

/*!
 * @brief square root of each vector item
 *
 * @param[in]  v    vector
 * @returns         destination vector
 */
AE_INLINE
vec3s
aes_vec3_sqrt(vec3s v) {
  vec3s r;
  ae_vec3_sqrt(v.raw, r.raw);
  return r;
}

#endif /* aes_vec3s_ext_h */
