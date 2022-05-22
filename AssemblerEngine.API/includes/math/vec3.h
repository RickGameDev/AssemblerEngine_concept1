/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*
 Macros:
   GLM_VEC3_ONE_INIT
   GLM_VEC3_ZERO_INIT
   GLM_VEC3_ONE
   GLM_VEC3_ZERO
   GLM_YUP
   GLM_ZUP
   GLM_XUP

 Functions:
   AE_INLINE void  ae_vec3(vec4 v4, vec3 dest);
   AE_INLINE void  ae_vec3_copy(vec3 a, vec3 dest);
   AE_INLINE void  ae_vec3_zero(vec3 v);
   AE_INLINE void  ae_vec3_one(vec3 v);
   AE_INLINE float ae_vec3_dot(vec3 a, vec3 b);
   AE_INLINE float ae_vec3_norm2(vec3 v);
   AE_INLINE float ae_vec3_norm(vec3 v);
   AE_INLINE float ae_vec3_norm_one(vec3 v);
   AE_INLINE float ae_vec3_norm_inf(vec3 v);
   AE_INLINE void  ae_vec3_add(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_adds(vec3 a, float s, vec3 dest);
   AE_INLINE void  ae_vec3_sub(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_subs(vec3 a, float s, vec3 dest);
   AE_INLINE void  ae_vec3_mul(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_scale(vec3 v, float s, vec3 dest);
   AE_INLINE void  ae_vec3_scale_as(vec3 v, float s, vec3 dest);
   AE_INLINE void  ae_vec3_div(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_divs(vec3 a, float s, vec3 dest);
   AE_INLINE void  ae_vec3_addadd(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_subadd(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_muladd(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_muladds(vec3 a, float s, vec3 dest);
   AE_INLINE void  ae_vec3_maxadd(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_minadd(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_flipsign(vec3 v);
   AE_INLINE void  ae_vec3_flipsign_to(vec3 v, vec3 dest);
   AE_INLINE void  ae_vec3_negate_to(vec3 v, vec3 dest);
   AE_INLINE void  ae_vec3_negate(vec3 v);
   AE_INLINE void  ae_vec3_inv(vec3 v);
   AE_INLINE void  ae_vec3_inv_to(vec3 v, vec3 dest);
   AE_INLINE void  ae_vec3_normalize(vec3 v);
   AE_INLINE void  ae_vec3_normalize_to(vec3 v, vec3 dest);
   AE_INLINE void  ae_vec3_cross(vec3 a, vec3 b, vec3 d);
   AE_INLINE void  ae_vec3_crossn(vec3 a, vec3 b, vec3 dest);
   AE_INLINE float ae_vec3_angle(vec3 a, vec3 b);
   AE_INLINE void  ae_vec3_rotate(vec3 v, float angle, vec3 axis);
   AE_INLINE void  ae_vec3_rotate_m4(mat4 m, vec3 v, vec3 dest);
   AE_INLINE void  ae_vec3_rotate_m3(mat3 m, vec3 v, vec3 dest);
   AE_INLINE void  ae_vec3_proj(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_center(vec3 a, vec3 b, vec3 dest);
   AE_INLINE float ae_vec3_distance(vec3 a, vec3 b);
   AE_INLINE float ae_vec3_distance2(vec3 a, vec3 b);
   AE_INLINE void  ae_vec3_maxv(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_minv(vec3 a, vec3 b, vec3 dest);
   AE_INLINE void  ae_vec3_ortho(vec3 v, vec3 dest);
   AE_INLINE void  ae_vec3_clamp(vec3 v, float minVal, float maxVal);
   AE_INLINE void  ae_vec3_lerp(vec3 from, vec3 to, float t, vec3 dest);
   AE_INLINE void  ae_vec3_lerpc(vec3 from, vec3 to, float t, vec3 dest);
   AE_INLINE void  ae_vec3_mix(vec3 from, vec3 to, float t, vec3 dest);
   AE_INLINE void  ae_vec3_mixc(vec3 from, vec3 to, float t, vec3 dest);
   AE_INLINE void  ae_vec3_step_uni(float edge, vec3 x, vec3 dest);
   AE_INLINE void  ae_vec3_step(vec3 edge, vec3 x, vec3 dest);
   AE_INLINE void  ae_vec3_smoothstep_uni(float edge0, float edge1, vec3 x, vec3 dest);
   AE_INLINE void  ae_vec3_smoothstep(vec3 edge0, vec3 edge1, vec3 x, vec3 dest);
   AE_INLINE void  ae_vec3_smoothinterp(vec3 from, vec3 to, float t, vec3 dest);
   AE_INLINE void  ae_vec3_smoothinterpc(vec3 from, vec3 to, float t, vec3 dest);
   AE_INLINE void  ae_vec3_swizzle(vec3 v, int mask, vec3 dest);

 Convenient:
   AE_INLINE void  ae_cross(vec3 a, vec3 b, vec3 d);
   AE_INLINE float ae_dot(vec3 a, vec3 b);
   AE_INLINE void  ae_normalize(vec3 v);
   AE_INLINE void  ae_normalize_to(vec3 v, vec3 dest);

 DEPRECATED:
   ae_vec3_dup
   ae_vec3_flipsign
   ae_vec3_flipsign_to
   ae_vec3_inv
   ae_vec3_inv_to
   ae_vec3_mulv
 */

#ifndef ae_vec3_h
#define ae_vec3_h

#include "common.h"
#include "vec4.h"
#include "vec3-ext.h"
#include "util.h"

/* DEPRECATED! use _copy, _ucopy versions */
#define ae_vec3_dup(v, dest)         ae_vec3_copy(v, dest)
#define ae_vec3_flipsign(v)          ae_vec3_negate(v)
#define ae_vec3_flipsign_to(v, dest) ae_vec3_negate_to(v, dest)
#define ae_vec3_inv(v)               ae_vec3_negate(v)
#define ae_vec3_inv_to(v, dest)      ae_vec3_negate_to(v, dest)
#define ae_vec3_mulv(a, b, d)        ae_vec3_mul(a, b, d)

#define GLM_VEC3_ONE_INIT   {1.0f, 1.0f, 1.0f}
#define GLM_VEC3_ZERO_INIT  {0.0f, 0.0f, 0.0f}

#define GLM_VEC3_ONE  ((vec3)GLM_VEC3_ONE_INIT)
#define GLM_VEC3_ZERO ((vec3)GLM_VEC3_ZERO_INIT)

#define GLM_YUP       ((vec3){0.0f,  1.0f,  0.0f})
#define GLM_ZUP       ((vec3){0.0f,  0.0f,  1.0f})
#define GLM_XUP       ((vec3){1.0f,  0.0f,  0.0f})
#define GLM_FORWARD   ((vec3){0.0f,  0.0f, -1.0f})

#define GLM_XXX GLM_SHUFFLE3(0, 0, 0)
#define GLM_YYY GLM_SHUFFLE3(1, 1, 1)
#define GLM_ZZZ GLM_SHUFFLE3(2, 2, 2)
#define GLM_ZYX GLM_SHUFFLE3(0, 1, 2)

/*!
 * @brief init vec3 using vec4
 *
 * @param[in]  v4   vector4
 * @param[out] dest destination
 */
AE_INLINE
void
ae_vec3(vec4 v4, vec3 dest) {
  dest[0] = v4[0];
  dest[1] = v4[1];
  dest[2] = v4[2];
}

/*!
 * @brief copy all members of [a] to [dest]
 *
 * @param[in]  a    source
 * @param[out] dest destination
 */
AE_INLINE
void
ae_vec3_copy(vec3 a, vec3 dest) {
  dest[0] = a[0];
  dest[1] = a[1];
  dest[2] = a[2];
}

/*!
 * @brief make vector zero
 *
 * @param[in, out]  v vector
 */
AE_INLINE
void
ae_vec3_zero(vec3 v) {
  v[0] = v[1] = v[2] = 0.0f;
}

/*!
 * @brief make vector one
 *
 * @param[in, out]  v vector
 */
AE_INLINE
void
ae_vec3_one(vec3 v) {
  v[0] = v[1] = v[2] = 1.0f;
}

/*!
 * @brief vec3 dot product
 *
 * @param[in] a vector1
 * @param[in] b vector2
 *
 * @return dot product
 */
AE_INLINE
float
ae_vec3_dot(vec3 a, vec3 b) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/*!
 * @brief norm * norm (magnitude) of vec
 *
 * we can use this func instead of calling norm * norm, because it would call
 * sqrtf fuction twice but with this func we can avoid func call, maybe this is
 * not good name for this func
 *
 * @param[in] v vector
 *
 * @return norm * norm
 */
AE_INLINE
float
ae_vec3_norm2(vec3 v) {
  return ae_vec3_dot(v, v);
}

/*!
 * @brief euclidean norm (magnitude), also called L2 norm
 *        this will give magnitude of vector in euclidean space
 *
 * @param[in] v vector
 *
 * @return norm
 */
AE_INLINE
float
ae_vec3_norm(vec3 v) {
  return sqrtf(ae_vec3_norm2(v));
}

/*!
 * @brief L1 norm of vec3
 * Also known as Manhattan Distance or Taxicab norm.
 * L1 Norm is the sum of the magnitudes of the vectors in a space.
 * It is calculated as the sum of the absolute values of the vector components.
 * In this norm, all the components of the vector are weighted equally.
 *
 * This computes:
 * R = |v[0]| + |v[1]| + |v[2]|
 *
 * @param[in] v vector
 *
 * @return L1 norm
 */
AE_INLINE
float
ae_vec3_norm_one(vec3 v) {
  vec3 t;
  ae_vec3_abs(v, t);
  return ae_vec3_hadd(t);
}

/*!
 * @brief infinity norm of vec3
 * Also known as Maximum norm.
 * Infinity Norm is the largest magnitude among each element of a vector.
 * It is calculated as the maximum of the absolute values of the vector components.
 *
 * This computes:
 * inf norm = max(|v[0]|, |v[1]|, |v[2]|)
 *
 * @param[in] v vector
 *
 * @return infinity norm
 */
AE_INLINE
float
ae_vec3_norm_inf(vec3 v) {
  vec3 t;
  ae_vec3_abs(v, t);
  return ae_vec3_max(t);
}

/*!
 * @brief add a vector to b vector store result in dest
 *
 * @param[in]  a    vector1
 * @param[in]  b    vector2
 * @param[out] dest destination vector
 */
AE_INLINE
void
ae_vec3_add(vec3 a, vec3 b, vec3 dest) {
  dest[0] = a[0] + b[0];
  dest[1] = a[1] + b[1];
  dest[2] = a[2] + b[2];
}

/*!
 * @brief add scalar to v vector store result in dest (d = v + s)
 *
 * @param[in]  v    vector
 * @param[in]  s    scalar
 * @param[out] dest destination vector
 */
AE_INLINE
void
ae_vec3_adds(vec3 v, float s, vec3 dest) {
  dest[0] = v[0] + s;
  dest[1] = v[1] + s;
  dest[2] = v[2] + s;
}

/*!
 * @brief subtract b vector from a vector store result in dest
 *
 * @param[in]  a    vector1
 * @param[in]  b    vector2
 * @param[out] dest destination vector
 */
AE_INLINE
void
ae_vec3_sub(vec3 a, vec3 b, vec3 dest) {
  dest[0] = a[0] - b[0];
  dest[1] = a[1] - b[1];
  dest[2] = a[2] - b[2];
}

/*!
 * @brief subtract scalar from v vector store result in dest (d = v - s)
 *
 * @param[in]  v    vector
 * @param[in]  s    scalar
 * @param[out] dest destination vector
 */
AE_INLINE
void
ae_vec3_subs(vec3 v, float s, vec3 dest) {
  dest[0] = v[0] - s;
  dest[1] = v[1] - s;
  dest[2] = v[2] - s;
}

/*!
 * @brief multiply two vector (component-wise multiplication)
 *
 * @param a    vector1
 * @param b    vector2
 * @param dest v3 = (a[0] * b[0], a[1] * b[1], a[2] * b[2])
 */
AE_INLINE
void
ae_vec3_mul(vec3 a, vec3 b, vec3 dest) {
  dest[0] = a[0] * b[0];
  dest[1] = a[1] * b[1];
  dest[2] = a[2] * b[2];
}

/*!
 * @brief multiply/scale vec3 vector with scalar: result = v * s
 *
 * @param[in]  v    vector
 * @param[in]  s    scalar
 * @param[out] dest destination vector
 */
AE_INLINE
void
ae_vec3_scale(vec3 v, float s, vec3 dest) {
  dest[0] = v[0] * s;
  dest[1] = v[1] * s;
  dest[2] = v[2] * s;
}

/*!
 * @brief make vec3 vector scale as specified: result = unit(v) * s
 *
 * @param[in]  v    vector
 * @param[in]  s    scalar
 * @param[out] dest destination vector
 */
AE_INLINE
void
ae_vec3_scale_as(vec3 v, float s, vec3 dest) {
  float norm;
  norm = ae_vec3_norm(v);

  if (norm == 0.0f) {
    ae_vec3_zero(dest);
    return;
  }

  ae_vec3_scale(v, s / norm, dest);
}

/*!
 * @brief div vector with another component-wise division: d = a / b
 *
 * @param[in]  a    vector 1
 * @param[in]  b    vector 2
 * @param[out] dest result = (a[0]/b[0], a[1]/b[1], a[2]/b[2])
 */
AE_INLINE
void
ae_vec3_div(vec3 a, vec3 b, vec3 dest) {
  dest[0] = a[0] / b[0];
  dest[1] = a[1] / b[1];
  dest[2] = a[2] / b[2];
}

/*!
 * @brief div vector with scalar: d = v / s
 *
 * @param[in]  v    vector
 * @param[in]  s    scalar
 * @param[out] dest result = (a[0]/s, a[1]/s, a[2]/s)
 */
AE_INLINE
void
ae_vec3_divs(vec3 v, float s, vec3 dest) {
  dest[0] = v[0] / s;
  dest[1] = v[1] / s;
  dest[2] = v[2] / s;
}

/*!
 * @brief add two vectors and add result to sum
 *
 * it applies += operator so dest must be initialized
 *
 * @param[in]  a    vector 1
 * @param[in]  b    vector 2
 * @param[out] dest dest += (a + b)
 */
AE_INLINE
void
ae_vec3_addadd(vec3 a, vec3 b, vec3 dest) {
  dest[0] += a[0] + b[0];
  dest[1] += a[1] + b[1];
  dest[2] += a[2] + b[2];
}

/*!
 * @brief sub two vectors and add result to dest
 *
 * it applies += operator so dest must be initialized
 *
 * @param[in]  a    vector 1
 * @param[in]  b    vector 2
 * @param[out] dest dest += (a + b)
 */
AE_INLINE
void
ae_vec3_subadd(vec3 a, vec3 b, vec3 dest) {
  dest[0] += a[0] - b[0];
  dest[1] += a[1] - b[1];
  dest[2] += a[2] - b[2];
}

/*!
 * @brief mul two vectors and add result to dest
 *
 * it applies += operator so dest must be initialized
 *
 * @param[in]  a    vector 1
 * @param[in]  b    vector 2
 * @param[out] dest dest += (a * b)
 */
AE_INLINE
void
ae_vec3_muladd(vec3 a, vec3 b, vec3 dest) {
  dest[0] += a[0] * b[0];
  dest[1] += a[1] * b[1];
  dest[2] += a[2] * b[2];
}

/*!
 * @brief mul vector with scalar and add result to sum
 *
 * it applies += operator so dest must be initialized
 *
 * @param[in]  a    vector
 * @param[in]  s    scalar
 * @param[out] dest dest += (a * b)
 */
AE_INLINE
void
ae_vec3_muladds(vec3 a, float s, vec3 dest) {
  dest[0] += a[0] * s;
  dest[1] += a[1] * s;
  dest[2] += a[2] * s;
}

/*!
 * @brief add max of two vector to result/dest
 *
 * it applies += operator so dest must be initialized
 *
 * @param[in]  a    vector 1
 * @param[in]  b    vector 2
 * @param[out] dest dest += max(a, b)
 */
AE_INLINE
void
ae_vec3_maxadd(vec3 a, vec3 b, vec3 dest) {
  dest[0] += ae_max(a[0], b[0]);
  dest[1] += ae_max(a[1], b[1]);
  dest[2] += ae_max(a[2], b[2]);
}

/*!
 * @brief add min of two vector to result/dest
 *
 * it applies += operator so dest must be initialized
 *
 * @param[in]  a    vector 1
 * @param[in]  b    vector 2
 * @param[out] dest dest += min(a, b)
 */
AE_INLINE
void
ae_vec3_minadd(vec3 a, vec3 b, vec3 dest) {
  dest[0] += ae_min(a[0], b[0]);
  dest[1] += ae_min(a[1], b[1]);
  dest[2] += ae_min(a[2], b[2]);
}

/*!
 * @brief negate vector components and store result in dest
 *
 * @param[in]   v     vector
 * @param[out]  dest  result vector
 */
AE_INLINE
void
ae_vec3_negate_to(vec3 v, vec3 dest) {
  dest[0] = -v[0];
  dest[1] = -v[1];
  dest[2] = -v[2];
}

/*!
 * @brief negate vector components
 *
 * @param[in, out]  v  vector
 */
AE_INLINE
void
ae_vec3_negate(vec3 v) {
  ae_vec3_negate_to(v, v);
}

/*!
 * @brief normalize vec3 and store result in same vec
 *
 * @param[in, out] v vector
 */
AE_INLINE
void
ae_vec3_normalize(vec3 v) {
  float norm;

  norm = ae_vec3_norm(v);

  if (norm == 0.0f) {
    v[0] = v[1] = v[2] = 0.0f;
    return;
  }

  ae_vec3_scale(v, 1.0f / norm, v);
}

/*!
 * @brief normalize vec3 to dest
 *
 * @param[in]  v    source
 * @param[out] dest destination
 */
AE_INLINE
void
ae_vec3_normalize_to(vec3 v, vec3 dest) {
  float norm;

  norm = ae_vec3_norm(v);

  if (norm == 0.0f) {
    ae_vec3_zero(dest);
    return;
  }

  ae_vec3_scale(v, 1.0f / norm, dest);
}

/*!
 * @brief cross product of two vector (RH)
 *
 * @param[in]  a    vector 1
 * @param[in]  b    vector 2
 * @param[out] dest destination
 */
AE_INLINE
void
ae_vec3_cross(vec3 a, vec3 b, vec3 dest) {
  vec3 c;
  /* (u2.v3 - u3.v2, u3.v1 - u1.v3, u1.v2 - u2.v1) */
  c[0] = a[1] * b[2] - a[2] * b[1];
  c[1] = a[2] * b[0] - a[0] * b[2];
  c[2] = a[0] * b[1] - a[1] * b[0];
  ae_vec3_copy(c, dest);
}

/*!
 * @brief cross product of two vector (RH) and normalize the result
 *
 * @param[in]  a    vector 1
 * @param[in]  b    vector 2
 * @param[out] dest destination
 */
AE_INLINE
void
ae_vec3_crossn(vec3 a, vec3 b, vec3 dest) {
  ae_vec3_cross(a, b, dest);
  ae_vec3_normalize(dest);
}

/*!
 * @brief angle betwen two vector
 *
 * @param[in] a  vector1
 * @param[in] b  vector2
 *
 * @return angle as radians
 */
AE_INLINE
float
ae_vec3_angle(vec3 a, vec3 b) {
  float norm, dot;

  /* maybe compiler generate approximation instruction (rcp) */
  norm = 1.0f / (ae_vec3_norm(a) * ae_vec3_norm(b));
  dot  = ae_vec3_dot(a, b) * norm;

  if (dot > 1.0f)
    return 0.0f;
  else if (dot < -1.0f)
    return AE_PI;

  return acosf(dot);
}

/*!
 * @brief rotate vec3 around axis by angle using Rodrigues' rotation formula
 *
 * @param[in, out] v     vector
 * @param[in]      axis  axis vector (must be unit vector)
 * @param[in]      angle angle by radians
 */
AE_INLINE
void
ae_vec3_rotate(vec3 v, float angle, vec3 axis) {
  vec3   v1, v2, k;
  float  c, s;

  c = cosf(angle);
  s = sinf(angle);

  ae_vec3_normalize_to(axis, k);

  /* Right Hand, Rodrigues' rotation formula:
        v = v*cos(t) + (kxv)sin(t) + k*(k.v)(1 - cos(t))
   */
  ae_vec3_scale(v, c, v1);

  ae_vec3_cross(k, v, v2);
  ae_vec3_scale(v2, s, v2);

  ae_vec3_add(v1, v2, v1);

  ae_vec3_scale(k, ae_vec3_dot(k, v) * (1.0f - c), v2);
  ae_vec3_add(v1, v2, v);
}

/*!
 * @brief apply rotation matrix to vector
 *
 *  matrix format should be (no perspective):
 *   a  b  c  x
 *   e  f  g  y
 *   i  j  k  z
 *   0  0  0  w
 *
 * @param[in]  m    affine matrix or rot matrix
 * @param[in]  v    vector
 * @param[out] dest rotated vector
 */
AE_INLINE
void
ae_vec3_rotate_m4(mat4 m, vec3 v, vec3 dest) {
  vec4 x, y, z, res;

  ae_vec4_normalize_to(m[0], x);
  ae_vec4_normalize_to(m[1], y);
  ae_vec4_normalize_to(m[2], z);

  ae_vec4_scale(x,   v[0], res);
  ae_vec4_muladds(y, v[1], res);
  ae_vec4_muladds(z, v[2], res);

  ae_vec3(res, dest);
}

/*!
 * @brief apply rotation matrix to vector
 *
 * @param[in]  m    affine matrix or rot matrix
 * @param[in]  v    vector
 * @param[out] dest rotated vector
 */
AE_INLINE
void
ae_vec3_rotate_m3(mat3 m, vec3 v, vec3 dest) {
  vec4 res, x, y, z;

  ae_vec4(m[0], 0.0f, x);
  ae_vec4(m[1], 0.0f, y);
  ae_vec4(m[2], 0.0f, z);

  ae_vec4_normalize(x);
  ae_vec4_normalize(y);
  ae_vec4_normalize(z);

  ae_vec4_scale(x,   v[0], res);
  ae_vec4_muladds(y, v[1], res);
  ae_vec4_muladds(z, v[2], res);

  ae_vec3(res, dest);
}

/*!
 * @brief project a vector onto b vector
 *
 * @param[in]  a    vector1
 * @param[in]  b    vector2
 * @param[out] dest projected vector
 */
AE_INLINE
void
ae_vec3_proj(vec3 a, vec3 b, vec3 dest) {
  ae_vec3_scale(b,
                 ae_vec3_dot(a, b) / ae_vec3_norm2(b),
                 dest);
}

/**
 * @brief find center point of two vector
 *
 * @param[in]  a    vector1
 * @param[in]  b    vector2
 * @param[out] dest center point
 */
AE_INLINE
void
ae_vec3_center(vec3 a, vec3 b, vec3 dest) {
  ae_vec3_add(a, b, dest);
  ae_vec3_scale(dest, 0.5f, dest);
}

/**
 * @brief squared distance between two vectors
 *
 * @param[in] a vector1
 * @param[in] b vector2
 * @return returns squared distance (distance * distance)
 */
AE_INLINE
float
ae_vec3_distance2(vec3 a, vec3 b) {
  return ae_pow2(a[0] - b[0])
       + ae_pow2(a[1] - b[1])
       + ae_pow2(a[2] - b[2]);
}

/**
 * @brief distance between two vectors
 *
 * @param[in] a vector1
 * @param[in] b vector2
 * @return returns distance
 */
AE_INLINE
float
ae_vec3_distance(vec3 a, vec3 b) {
  return sqrtf(ae_vec3_distance2(a, b));
}

/*!
 * @brief max values of vectors
 *
 * @param[in]  a    vector1
 * @param[in]  b    vector2
 * @param[out] dest destination
 */
AE_INLINE
void
ae_vec3_maxv(vec3 a, vec3 b, vec3 dest) {
  dest[0] = ae_max(a[0], b[0]);
  dest[1] = ae_max(a[1], b[1]);
  dest[2] = ae_max(a[2], b[2]);
}

/*!
 * @brief min values of vectors
 *
 * @param[in]  a    vector1
 * @param[in]  b    vector2
 * @param[out] dest destination
 */
AE_INLINE
void
ae_vec3_minv(vec3 a, vec3 b, vec3 dest) {
  dest[0] = ae_min(a[0], b[0]);
  dest[1] = ae_min(a[1], b[1]);
  dest[2] = ae_min(a[2], b[2]);
}

/*!
 * @brief possible orthogonal/perpendicular vector
 *
 * @param[in]  v    vector
 * @param[out] dest orthogonal/perpendicular vector
 */
AE_INLINE
void
ae_vec3_ortho(vec3 v, vec3 dest) {
  float ignore;
  float f      = modff(fabsf(v[0]) + 0.5f, &ignore);
  vec3  result = {-v[1], v[0] - f * v[2], f * v[1]};
  ae_vec3_copy(result, dest);
}

/*!
 * @brief clamp vector's individual members between min and max values
 *
 * @param[in, out]  v      vector
 * @param[in]       minVal minimum value
 * @param[in]       maxVal maximum value
 */
AE_INLINE
void
ae_vec3_clamp(vec3 v, float minVal, float maxVal) {
  v[0] = ae_clamp(v[0], minVal, maxVal);
  v[1] = ae_clamp(v[1], minVal, maxVal);
  v[2] = ae_clamp(v[2], minVal, maxVal);
}

/*!
 * @brief linear interpolation between two vectors
 *
 * formula:  from + s * (to - from)
 *
 * @param[in]   from from value
 * @param[in]   to   to value
 * @param[in]   t    interpolant (amount)
 * @param[out]  dest destination
 */
AE_INLINE
void
ae_vec3_lerp(vec3 from, vec3 to, float t, vec3 dest) {
  vec3 s, v;

  /* from + s * (to - from) */
  ae_vec3_broadcast(t, s);
  ae_vec3_sub(to, from, v);
  ae_vec3_mul(s, v, v);
  ae_vec3_add(from, v, dest);
}

/*!
 * @brief linear interpolation between two vectors (clamped)
 *
 * formula:  from + s * (to - from)
 *
 * @param[in]   from from value
 * @param[in]   to   to value
 * @param[in]   t    interpolant (amount) clamped between 0 and 1
 * @param[out]  dest destination
 */
AE_INLINE
void
ae_vec3_lerpc(vec3 from, vec3 to, float t, vec3 dest) {
  ae_vec3_lerp(from, to, ae_clamp_zo(t), dest);
}

/*!
 * @brief linear interpolation between two vectors
 *
 * formula:  from + s * (to - from)
 *
 * @param[in]   from from value
 * @param[in]   to   to value
 * @param[in]   t    interpolant (amount)
 * @param[out]  dest destination
 */
AE_INLINE
void
ae_vec3_mix(vec3 from, vec3 to, float t, vec3 dest) {
  ae_vec3_lerp(from, to, t, dest);
}

/*!
 * @brief linear interpolation between two vectors (clamped)
 *
 * formula:  from + s * (to - from)
 *
 * @param[in]   from from value
 * @param[in]   to   to value
 * @param[in]   t    interpolant (amount) clamped between 0 and 1
 * @param[out]  dest destination
 */
AE_INLINE
void
ae_vec3_mixc(vec3 from, vec3 to, float t, vec3 dest) {
  ae_vec3_lerpc(from, to, t, dest);
}

/*!
 * @brief threshold function (unidimensional)
 *
 * @param[in]   edge    threshold
 * @param[in]   x       value to test against threshold
 * @param[out]  dest    destination
 */
AE_INLINE
void
ae_vec3_step_uni(float edge, vec3 x, vec3 dest) {
  dest[0] = ae_step(edge, x[0]);
  dest[1] = ae_step(edge, x[1]);
  dest[2] = ae_step(edge, x[2]);
}

/*!
 * @brief threshold function
 *
 * @param[in]   edge    threshold
 * @param[in]   x       value to test against threshold
 * @param[out]  dest    destination
 */
AE_INLINE
void
ae_vec3_step(vec3 edge, vec3 x, vec3 dest) {
  dest[0] = ae_step(edge[0], x[0]);
  dest[1] = ae_step(edge[1], x[1]);
  dest[2] = ae_step(edge[2], x[2]);
}

/*!
 * @brief threshold function with a smooth transition (unidimensional)
 *
 * @param[in]   edge0   low threshold
 * @param[in]   edge1   high threshold
 * @param[in]   x       value to test against threshold
 * @param[out]  dest    destination
 */
AE_INLINE
void
ae_vec3_smoothstep_uni(float edge0, float edge1, vec3 x, vec3 dest) {
  dest[0] = ae_smoothstep(edge0, edge1, x[0]);
  dest[1] = ae_smoothstep(edge0, edge1, x[1]);
  dest[2] = ae_smoothstep(edge0, edge1, x[2]);
}

/*!
 * @brief threshold function with a smooth transition
 *
 * @param[in]   edge0   low threshold
 * @param[in]   edge1   high threshold
 * @param[in]   x       value to test against threshold
 * @param[out]  dest    destination
 */
AE_INLINE
void
ae_vec3_smoothstep(vec3 edge0, vec3 edge1, vec3 x, vec3 dest) {
  dest[0] = ae_smoothstep(edge0[0], edge1[0], x[0]);
  dest[1] = ae_smoothstep(edge0[1], edge1[1], x[1]);
  dest[2] = ae_smoothstep(edge0[2], edge1[2], x[2]);
}

/*!
 * @brief smooth Hermite interpolation between two vectors
 *
 * formula:  from + s * (to - from)
 *
 * @param[in]   from from value
 * @param[in]   to   to value
 * @param[in]   t    interpolant (amount)
 * @param[out]  dest destination
 */
AE_INLINE
void
ae_vec3_smoothinterp(vec3 from, vec3 to, float t, vec3 dest) {
  vec3 s, v;
    
  /* from + s * (to - from) */
  ae_vec3_broadcast(ae_smooth(t), s);
  ae_vec3_sub(to, from, v);
  ae_vec3_mul(s, v, v);
  ae_vec3_add(from, v, dest);
}

/*!
 * @brief smooth Hermite interpolation between two vectors (clamped)
 *
 * formula:  from + s * (to - from)
 *
 * @param[in]   from from value
 * @param[in]   to   to value
 * @param[in]   t    interpolant (amount) clamped between 0 and 1
 * @param[out]  dest destination
 */
AE_INLINE
void
ae_vec3_smoothinterpc(vec3 from, vec3 to, float t, vec3 dest) {
  ae_vec3_smoothinterp(from, to, ae_clamp_zo(t), dest);
}

/*!
 * @brief swizzle vector components
 *
 * you can use existin masks e.g. GLM_XXX, GLM_ZYX
 *
 * @param[in]  v    source
 * @param[in]  mask mask
 * @param[out] dest destination
 */
AE_INLINE
void
ae_vec3_swizzle(vec3 v, int mask, vec3 dest) {
  vec3 t;

  t[0] = v[(mask & (3 << 0))];
  t[1] = v[(mask & (3 << 2)) >> 2];
  t[2] = v[(mask & (3 << 4)) >> 4];

  ae_vec3_copy(t, dest);
}

/*!
 * @brief vec3 cross product
 *
 * this is just convenient wrapper
 *
 * @param[in]  a source 1
 * @param[in]  b source 2
 * @param[out] d destination
 */
AE_INLINE
void
ae_cross(vec3 a, vec3 b, vec3 d) {
  ae_vec3_cross(a, b, d);
}

/*!
 * @brief vec3 dot product
 *
 * this is just convenient wrapper
 *
 * @param[in] a vector1
 * @param[in] b vector2
 *
 * @return dot product
 */
AE_INLINE
float
ae_dot(vec3 a, vec3 b) {
  return ae_vec3_dot(a, b);
}

/*!
 * @brief normalize vec3 and store result in same vec
 *
 * this is just convenient wrapper
 *
 * @param[in, out] v vector
 */
AE_INLINE
void
ae_normalize(vec3 v) {
  ae_vec3_normalize(v);
}

/*!
 * @brief normalize vec3 to dest
 *
 * this is just convenient wrapper
 *
 * @param[in]  v    source
 * @param[out] dest destination
 */
AE_INLINE
void
ae_normalize_to(vec3 v, vec3 dest) {
  ae_vec3_normalize_to(v, dest);
}

#endif /* ae_vec3_h */
