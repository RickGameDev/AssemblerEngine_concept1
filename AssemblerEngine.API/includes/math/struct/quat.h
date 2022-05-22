/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*
 Macros:
   GLMS_QUAT_IDENTITY_INIT
   GLMS_QUAT_IDENTITY

 Functions:
   AE_INLINE versors aes_quat_identity(void)
   AE_INLINE void    aes_quat_identity_array(versor *q, size_t count)
   AE_INLINE versors aes_quat_init(float x, float y, float z, float w)
   AE_INLINE versors aes_quatv(float angle, vec3s axis)
   AE_INLINE versors aes_quat(float angle, float x, float y, float z)
   AE_INLINE versors aes_quat_from_vecs(vec3s a, vec3s b)
   AE_INLINE float   aes_quat_norm(versors q)
   AE_INLINE versors aes_quat_normalize(versors q)
   AE_INLINE float   aes_quat_dot(versors p, versors q)
   AE_INLINE versors aes_quat_conjugate(versors q)
   AE_INLINE versors aes_quat_inv(versors q)
   AE_INLINE versors aes_quat_add(versors p, versors q)
   AE_INLINE versors aes_quat_sub(versors p, versors q)
   AE_INLINE vec3s   aes_quat_imagn(versors q)
   AE_INLINE float   aes_quat_imaglen(versors q)
   AE_INLINE float   aes_quat_angle(versors q)
   AE_INLINE vec3s   aes_quat_axis(versors q)
   AE_INLINE versors aes_quat_mul(versors p, versors q)
   AE_INLINE mat4s   aes_quat_mat4(versors q)
   AE_INLINE mat4s   aes_quat_mat4t(versors q)
   AE_INLINE mat3s   aes_quat_mat3(versors q)
   AE_INLINE mat3s   aes_quat_mat3t(versors q)
   AE_INLINE versors aes_quat_lerp(versors from, versors to, float t)
   AE_INLINE versors aes_quat_lerpc(versors from, versors to, float t)
   AE_INLINE versors aes_quat_nlerp(versors from, versors to, float t)
   AE_INLINE versors aes_quat_slerp(versors from, versors to, float t)
   AE_INLINE mat4s.  aes_quat_look(vec3s eye, versors ori)
   AE_INLINE versors aes_quat_for(vec3s dir, vec3s fwd, vec3s up)
   AE_INLINE versors aes_quat_forp(vec3s from, vec3s to, vec3s fwd, vec3s up)
   AE_INLINE vec3s   aes_quat_rotatev(versors q, vec3s v)
   AE_INLINE mat4s   aes_quat_rotate(mat4s m, versors q)
   AE_INLINE mat4s   aes_quat_rotate_at(mat4s m, versors q, vec3s pivot)
   AE_INLINE mat4s   aes_quat_rotate_atm(versors q, vec3s pivot)
 */

#ifndef aes_quat_h
#define aes_quat_h

#include "../common.h"
#include "../types-struct.h"
#include "../plane.h"
#include "../quat.h"

/*
 * IMPORTANT:
 * ----------------------------------------------------------------------------
 * ae stores quat as [x, y, z, w] since v0.3.6
 *
 * it was [w, x, y, z] before v0.3.6 it has been changed to [x, y, z, w]
 * with v0.3.6 version.
 * ----------------------------------------------------------------------------
 */

#define GLMS_QUAT_IDENTITY_INIT  {GLM_QUAT_IDENTITY_INIT}
#define GLMS_QUAT_IDENTITY       ((versors)GLMS_QUAT_IDENTITY_INIT)

/*!
 * @brief makes given quat to identity
 *
 * @returns identity quaternion
 */
AE_INLINE
versors
aes_quat_identity(void) {
  versors dest;
  ae_quat_identity(dest.raw);
  return dest;
}

/*!
 * @brief make given quaternion array's each element identity quaternion
 *
 * @param[in, out]  q     quat array (must be aligned (16)
 *                        if alignment is not disabled)
 *
 * @param[in]       count count of quaternions
 */
AE_INLINE
void
aes_quat_identity_array(versors * __restrict q, size_t count) {
  AE_ALIGN(16) versor v = GLM_QUAT_IDENTITY_INIT;
  size_t i;

  for (i = 0; i < count; i++) {
    ae_vec4_copy(v, q[i].raw);
  }
}

/*!
 * @brief inits quaterion with raw values
 *
 * @param[in]   x     x
 * @param[in]   y     y
 * @param[in]   z     z
 * @param[in]   w     w (real part)
 * @returns quaternion
 */
AE_INLINE
versors
aes_quat_init(float x, float y, float z, float w) {
  versors dest;
  ae_quat_init(dest.raw, x, y, z, w);
  return dest;
}

/*!
 * @brief creates NEW quaternion with axis vector
 *
 * @param[in]   angle angle (radians)
 * @param[in]   axis  axis
 * @returns quaternion
 */
AE_INLINE
versors
aes_quatv(float angle, vec3s axis) {
  versors dest;
  ae_quatv(dest.raw, angle, axis.raw);
  return dest;
}

/*!
 * @brief creates NEW quaternion with individual axis components
 *
 * @param[in]   angle angle (radians)
 * @param[in]   x     axis.x
 * @param[in]   y     axis.y
 * @param[in]   z     axis.z
 * @returns quaternion
 */
AE_INLINE
versors
aes_quat(float angle, float x, float y, float z) {
  versors dest;
  ae_quat(dest.raw, angle, x, y, z);
  return dest;
}

/*!
 * @brief compute quaternion rotating vector A to vector B
 *
 * @param[in]   a     vec3 (must have unit length)
 * @param[in]   b     vec3 (must have unit length)
 * @returns     quaternion (of unit length)
 */
AE_INLINE
versors
aes_quat_from_vecs(vec3s a, vec3s b) {
  versors dest;
  ae_quat_from_vecs(a.raw, b.raw, dest.raw);
  return dest;
}

/*!
 * @brief returns norm (magnitude) of quaternion
 *
 * @param[in]  q  quaternion
 */
AE_INLINE
float
aes_quat_norm(versors q) {
  return ae_quat_norm(q.raw);
}

/*!
 * @brief normalize quaternion
 *
 * @param[in]  q  quaternion
 * @returns    quaternion
 */
AE_INLINE
versors
aes_quat_normalize(versors q) {
  versors dest;
  ae_quat_normalize_to(q.raw, dest.raw);
  return dest;
}

/*!
 * @brief dot product of two quaternion
 *
 * @param[in]  p  quaternion 1
 * @param[in]  q  quaternion 2
 * @returns    dot product
 */
AE_INLINE
float
aes_quat_dot(versors p, versors q) {
  return ae_quat_dot(p.raw, q.raw);
}

/*!
 * @brief conjugate of quaternion
 *
 * @param[in]   q     quaternion
 * @returns    conjugate
 */
AE_INLINE
versors
aes_quat_conjugate(versors q) {
  versors dest;
  ae_quat_conjugate(q.raw, dest.raw);
  return dest;
}

/*!
 * @brief inverse of non-zero quaternion
 *
 * @param[in]  q    quaternion
 * @returns    inverse quaternion
 */
AE_INLINE
versors
aes_quat_inv(versors q) {
  versors dest;
  ae_quat_inv(q.raw, dest.raw);
  return dest;
}

/*!
 * @brief add (componentwise) two quaternions and store result in dest
 *
 * @param[in]   p    quaternion 1
 * @param[in]   q    quaternion 2
 * @returns result quaternion
 */
AE_INLINE
versors
aes_quat_add(versors p, versors q) {
  versors dest;
  ae_quat_add(p.raw, q.raw, dest.raw);
  return dest;
}

/*!
 * @brief subtract (componentwise) two quaternions and store result in dest
 *
 * @param[in]   p    quaternion 1
 * @param[in]   q    quaternion 2
 * @returns result quaternion
 */
AE_INLINE
versors
aes_quat_sub(versors p, versors q) {
  versors dest;
  ae_quat_sub(p.raw, q.raw, dest.raw);
  return dest;
}

/*!
 * @brief returns normalized imaginary part of quaternion
 *
 * @param[in]   q    quaternion
 */
AE_INLINE
vec3s
aes_quat_imagn(versors q) {
  vec3s dest;
  ae_normalize_to(q.raw, dest.raw);
  return dest;
}

/*!
 * @brief returns length of imaginary part of quaternion
 *
 * @param[in]   q    quaternion
 */
AE_INLINE
float
aes_quat_imaglen(versors q) {
  return ae_quat_imaglen(q.raw);
}

/*!
 * @brief returns angle of quaternion
 *
 * @param[in]   q    quaternion
 */
AE_INLINE
float
aes_quat_angle(versors q) {
  return ae_quat_angle(q.raw);
}

/*!
 * @brief axis of quaternion
 *
 * @param[in]   q    quaternion
 * @returns axis of quaternion
 */
AE_INLINE
vec3s
aes_quat_axis(versors q) {
  vec3s dest;
  ae_quat_axis(q.raw, dest.raw);
  return dest;
}

/*!
 * @brief multiplies two quaternion and stores result in dest
 *        this is also called Hamilton Product
 *
 * According to WikiPedia:
 * The product of two rotation quaternions [clarification needed] will be
 * equivalent to the rotation q followed by the rotation p
 *
 * @param[in]   p     quaternion 1
 * @param[in]   q     quaternion 2
 * @returns  result quaternion
 */
AE_INLINE
versors
aes_quat_mul(versors p, versors q) {
  versors dest;
  ae_quat_mul(p.raw, q.raw, dest.raw);
  return dest;
}

/*!
 * @brief convert quaternion to mat4
 *
 * @param[in]   q     quaternion
 * @returns  result matrix
 */
AE_INLINE
mat4s
aes_quat_mat4(versors q) {
  mat4s dest;
  ae_quat_mat4(q.raw, dest.raw);
  return dest;
}

/*!
 * @brief convert quaternion to mat4 (transposed)
 *
 * @param[in]   q     quaternion
 * @returns  result matrix as transposed
 */
AE_INLINE
mat4s
aes_quat_mat4t(versors q) {
  mat4s dest;
  ae_quat_mat4t(q.raw, dest.raw);
  return dest;
}

/*!
 * @brief convert quaternion to mat3
 *
 * @param[in]   q     quaternion
 * @returns  result matrix
 */
AE_INLINE
mat3s
aes_quat_mat3(versors q) {
  mat3s dest;
  ae_quat_mat3(q.raw, dest.raw);
  return dest;
}

/*!
 * @brief convert quaternion to mat3 (transposed)
 *
 * @param[in]   q     quaternion
 * @returns  result matrix
 */
AE_INLINE
mat3s
aes_quat_mat3t(versors q) {
  mat3s dest;
  ae_quat_mat3t(q.raw, dest.raw);
  return dest;
}

/*!
 * @brief interpolates between two quaternions
 *        using linear interpolation (LERP)
 *
 * @param[in]   from  from
 * @param[in]   to    to
 * @param[in]   t     interpolant (amount)
 * @returns  result quaternion
 */
AE_INLINE
versors
aes_quat_lerp(versors from, versors to, float t) {
  versors dest;
  ae_quat_lerp(from.raw, to.raw, t, dest.raw);
  return dest;
}

/*!
 * @brief interpolates between two quaternions
 *        using linear interpolation (LERP)
 *
 * @param[in]   from  from
 * @param[in]   to    to
 * @param[in]   t     interpolant (amount) clamped between 0 and 1
 * @returns  result quaternion
 */
AE_INLINE
versors
aes_quat_lerpc(versors from, versors to, float t) {
  versors dest;
  ae_quat_lerpc(from.raw, to.raw, t, dest.raw);
  return dest;
}

/*!
 * @brief interpolates between two quaternions
 *        taking the shortest rotation path using
 *        normalized linear interpolation (NLERP)
 *
 * @param[in]   from  from
 * @param[in]   to    to
 * @param[in]   t     interpolant (amount)
 * @returns result quaternion
 */
AE_INLINE
versors
aes_quat_nlerp(versors from, versors to, float t) {
  versors dest;
  ae_quat_nlerp(from.raw, to.raw, t, dest.raw);
  return dest;
}

/*!
 * @brief interpolates between two quaternions
 *        using spherical linear interpolation (SLERP)
 *
 * @param[in]   from  from
 * @param[in]   to    to
 * @param[in]   t     amout
 * @returns result quaternion
 */
AE_INLINE
versors
aes_quat_slerp(versors from, versors to, float t) {
  versors dest;
  ae_quat_slerp(from.raw, to.raw, t, dest.raw);
  return dest;
}

/*!
 * @brief creates view matrix using quaternion as camera orientation
 *
 * @param[in]   eye   eye
 * @param[in]   ori   orientation in world space as quaternion
 * @returns  view matrix
 */
AE_INLINE
mat4s
aes_quat_look(vec3s eye, versors ori) {
  mat4s dest;
  ae_quat_look(eye.raw, ori.raw, dest.raw);
  return dest;
}

/*!
 * @brief creates look rotation quaternion
 *
 * @param[in]   dir   direction to look
 * @param[in]   up    up vector
 * @returns  destination quaternion
 */
AE_INLINE
versors
aes_quat_for(vec3s dir, vec3s up) {
  versors dest;
  ae_quat_for(dir.raw, up.raw, dest.raw);
  return dest;
}

/*!
 * @brief creates look rotation quaternion using source and
 *        destination positions p suffix stands for position
 *
 * @param[in]   from  source point
 * @param[in]   to    destination point
 * @param[in]   up    up vector
 * @returns  destination quaternion
 */
AE_INLINE
versors
aes_quat_forp(vec3s from, vec3s to, vec3s up) {
  versors dest;
  ae_quat_forp(from.raw, to.raw, up.raw, dest.raw);
  return dest;
}

/*!
 * @brief rotate vector using using quaternion
 *
 * @param[in]   q     quaternion
 * @param[in]   v     vector to rotate
 * @returns  rotated vector
 */
AE_INLINE
vec3s
aes_quat_rotatev(versors q, vec3s v) {
  vec3s dest;
  ae_quat_rotatev(q.raw, v.raw, dest.raw);
  return dest;
}

/*!
 * @brief rotate existing transform matrix using quaternion
 *
 * @param[in]   m     existing transform matrix
 * @param[in]   q     quaternion
 * @returns  rotated matrix/transform
 */
AE_INLINE
mat4s
aes_quat_rotate(mat4s m, versors q) {
  ae_quat_rotate(m.raw, q.raw, m.raw);
  return m;
}

/*!
 * @brief rotate existing transform matrix using quaternion at pivot point
 *
 * @param[in, out]   m     existing transform matrix
 * @param[in]        q     quaternion
 * @returns pivot
 */
AE_INLINE
mat4s
aes_quat_rotate_at(mat4s m, versors q, vec3s pivot) {
  ae_quat_rotate_at(m.raw, q.raw, pivot.raw);
  return m;
}

/*!
 * @brief rotate NEW transform matrix using quaternion at pivot point
 *
 * this creates rotation matrix, it assumes you don't have a matrix
 *
 * this should work faster than ae_quat_rotate_at because it reduces
 * one ae_translate.
 *
 * @param[in]   q     quaternion
 * @returns pivot
 */
AE_INLINE
mat4s
aes_quat_rotate_atm(versors q, vec3s pivot) {
  mat4s dest;
  ae_quat_rotate_atm(dest.raw, q.raw, pivot.raw);
  return dest;
}

#endif /* aes_quat_h */
