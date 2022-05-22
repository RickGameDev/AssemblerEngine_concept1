/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*
 Functions:
   AE_INLINE void  ae_vec2_fill(vec2 v, float val)
   AE_INLINE bool  ae_vec2_eq(vec2 v, float val);
   AE_INLINE bool  ae_vec2_eq_eps(vec2 v, float val);
   AE_INLINE bool  ae_vec2_eq_all(vec2 v);
   AE_INLINE bool  ae_vec2_eqv(vec2 a, vec2 b);
   AE_INLINE bool  ae_vec2_eqv_eps(vec2 a, vec2 b);
   AE_INLINE float ae_vec2_max(vec2 v);
   AE_INLINE float ae_vec2_min(vec2 v);
   AE_INLINE bool  ae_vec2_isnan(vec2 v);
   AE_INLINE bool  ae_vec2_isinf(vec2 v);
   AE_INLINE bool  ae_vec2_isvalid(vec2 v);
   AE_INLINE void  ae_vec2_sign(vec2 v, vec2 dest);
   AE_INLINE void  ae_vec2_sqrt(vec2 v, vec2 dest);
 */

#ifndef ae_vec2_ext_h
#define ae_vec2_ext_h

#include "common.h"
#include "util.h"

/*!
 * @brief fill a vector with specified value
 *
 * @param[out] v   dest
 * @param[in]  val value
 */
AE_INLINE
void
ae_vec2_fill(vec2 v, float val) {
  v[0] = v[1] = val;
}

/*!
 * @brief check if vector is equal to value (without epsilon)
 *
 * @param[in] v   vector
 * @param[in] val value
 */
AE_INLINE
bool
ae_vec2_eq(vec2 v, float val) {
  return v[0] == val && v[0] == v[1];
}

/*!
 * @brief check if vector is equal to value (with epsilon)
 *
 * @param[in] v   vector
 * @param[in] val value
 */
AE_INLINE
bool
ae_vec2_eq_eps(vec2 v, float val) {
  return fabsf(v[0] - val) <= GLM_FLT_EPSILON
         && fabsf(v[1] - val) <= GLM_FLT_EPSILON;
}

/*!
 * @brief check if vectors members are equal (without epsilon)
 *
 * @param[in] v   vector
 */
AE_INLINE
bool
ae_vec2_eq_all(vec2 v) {
  return ae_vec2_eq_eps(v, v[0]);
}

/*!
 * @brief check if vector is equal to another (without epsilon)
 *
 * @param[in] a vector
 * @param[in] b vector
 */
AE_INLINE
bool
ae_vec2_eqv(vec2 a, vec2 b) {
  return a[0] == b[0] && a[1] == b[1];
}

/*!
 * @brief check if vector is equal to another (with epsilon)
 *
 * @param[in] a vector
 * @param[in] b vector
 */
AE_INLINE
bool
ae_vec2_eqv_eps(vec2 a, vec2 b) {
  return fabsf(a[0] - b[0]) <= GLM_FLT_EPSILON
         && fabsf(a[1] - b[1]) <= GLM_FLT_EPSILON;
}

/*!
 * @brief max value of vector
 *
 * @param[in] v vector
 */
AE_INLINE
float
ae_vec2_max(vec2 v) {
  return ae_max(v[0], v[1]);
}

/*!
 * @brief min value of vector
 *
 * @param[in] v vector
 */
AE_INLINE
float
ae_vec2_min(vec2 v) {
  return ae_min(v[0], v[1]);
}

/*!
 * @brief check if all items are NaN (not a number)
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
AE_INLINE
bool
ae_vec2_isnan(vec2 v) {
  return isnan(v[0]) || isnan(v[1]);
}

/*!
 * @brief check if all items are INFINITY
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
AE_INLINE
bool
ae_vec2_isinf(vec2 v) {
  return isinf(v[0]) || isinf(v[1]);
}

/*!
 * @brief check if all items are valid number
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
AE_INLINE
bool
ae_vec2_isvalid(vec2 v) {
  return !ae_vec2_isnan(v) && !ae_vec2_isinf(v);
}

/*!
 * @brief get sign of 32 bit float as +1, -1, 0
 *
 * Important: It returns 0 for zero/NaN input
 *
 * @param v vector
 */
AE_INLINE
void
ae_vec2_sign(vec2 v, vec2 dest) {
  dest[0] = ae_signf(v[0]);
  dest[1] = ae_signf(v[1]);
}

/*!
 * @brief square root of each vector item
 *
 * @param[in]  v    vector
 * @param[out] dest destination vector
 */
AE_INLINE
void
ae_vec2_sqrt(vec2 v, vec2 dest) {
  dest[0] = sqrtf(v[0]);
  dest[1] = sqrtf(v[1]);
}

#endif /* ae_vec2_ext_h */
