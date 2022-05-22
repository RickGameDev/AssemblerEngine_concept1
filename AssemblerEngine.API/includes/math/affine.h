/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

 /*
  Functions:
	AE_INLINE void ae_translate_to(mat4 m, vec3 v, mat4 dest);
	AE_INLINE void ae_translate(mat4 m, vec3 v);
	AE_INLINE void ae_translate_x(mat4 m, float to);
	AE_INLINE void ae_translate_y(mat4 m, float to);
	AE_INLINE void ae_translate_z(mat4 m, float to);
	AE_INLINE void ae_translate_make(mat4 m, vec3 v);
	AE_INLINE void ae_scale_to(mat4 m, vec3 v, mat4 dest);
	AE_INLINE void ae_scale_make(mat4 m, vec3 v);
	AE_INLINE void ae_scale(mat4 m, vec3 v);
	AE_INLINE void ae_scale_uni(mat4 m, float s);
	AE_INLINE void ae_rotate_x(mat4 m, float angle, mat4 dest);
	AE_INLINE void ae_rotate_y(mat4 m, float angle, mat4 dest);
	AE_INLINE void ae_rotate_z(mat4 m, float angle, mat4 dest);
	AE_INLINE void ae_rotate_make(mat4 m, float angle, vec3 axis);
	AE_INLINE void ae_rotate(mat4 m, float angle, vec3 axis);
	AE_INLINE void ae_rotate_at(mat4 m, vec3 pivot, float angle, vec3 axis);
	AE_INLINE void ae_rotate_atm(mat4 m, vec3 pivot, float angle, vec3 axis);
	AE_INLINE void ae_decompose_scalev(mat4 m, vec3 s);
	AE_INLINE bool ae_uniscaled(mat4 m);
	AE_INLINE void ae_decompose_rs(mat4 m, mat4 r, vec3 s);
	AE_INLINE void ae_decompose(mat4 m, vec4 t, mat4 r, vec3 s);
  */

#ifndef ae_affine_h
#define ae_affine_h

#include "common.h"
#include "util.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "affine-mat.h"

  /*!
   * @brief translate existing transform matrix by v vector
   *        and stores result in same matrix
   *
   * @param[in, out]  m  affine transfrom
   * @param[in]       v  translate vector [x, y, z]
   */
AE_INLINE
void
ae_translate(mat4 m, vec3 v)
{
#if defined(AE_SIMD)
	aem_128 m0, m1, m2, m3;

	m0 = aem_load(m[0]);
	m1 = aem_load(m[1]);
	m2 = aem_load(m[2]);
	m3 = aem_load(m[3]);

	aem_store(m[3],
		aem_fmadd(m0, aem_set1(v[0]),
			aem_fmadd(m1, aem_set1(v[1]),
				aem_fmadd(m2, aem_set1(v[2]), m3))));
#else
	ae_vec4_muladds(m[0], v[0], m[3]);
	ae_vec4_muladds(m[1], v[1], m[3]);
	ae_vec4_muladds(m[2], v[2], m[3]);
#endif
}

/*!
 * @brief translate existing transform matrix by v vector
 *        and store result in dest
 *
 * source matrix will remain same
 *
 * @param[in]  m    affine transfrom
 * @param[in]  v    translate vector [x, y, z]
 * @param[out] dest translated matrix
 */
AE_INLINE
void
ae_translate_to(mat4 m, vec3 v, mat4 dest)
{
	ae_mat4_copy(m, dest);
	ae_translate(dest, v);
}

/*!
 * @brief translate existing transform matrix by x factor
 *
 * @param[in, out]  m  affine transfrom
 * @param[in]       x  x factor
 */
AE_INLINE
void
ae_translate_x(mat4 m, float x)
{
#if defined(AE_SIMD)
	aem_store(m[3], aem_fmadd(aem_load(m[0]), aem_set1(x), aem_load(m[3])));
#else
	vec4 v1;
	ae_vec4_scale(m[0], x, v1);
	ae_vec4_add(v1, m[3], m[3]);
#endif
}

/*!
 * @brief translate existing transform matrix by y factor
 *
 * @param[in, out]  m  affine transfrom
 * @param[in]       y  y factor
 */
AE_INLINE
void
ae_translate_y(mat4 m, float y)
{
#if defined(AE_SIMD)
	aem_store(m[3], aem_fmadd(aem_load(m[1]), aem_set1(y), aem_load(m[3])));
#else
	vec4 v1;
	ae_vec4_scale(m[1], y, v1);
	ae_vec4_add(v1, m[3], m[3]);
#endif
}

/*!
 * @brief translate existing transform matrix by z factor
 *
 * @param[in, out]  m  affine transfrom
 * @param[in]       z  z factor
 */
AE_INLINE
void
ae_translate_z(mat4 m, float z)
{
#if defined(AE_SIMD)
	aem_store(m[3], aem_fmadd(aem_load(m[2]), aem_set1(z), aem_load(m[3])));
#else
	vec4 v1;
	ae_vec4_scale(m[2], z, v1);
	ae_vec4_add(v1, m[3], m[3]);
#endif
}

/*!
 * @brief creates NEW translate transform matrix by v vector
 *
 * @param[out]  m  affine transfrom
 * @param[in]   v  translate vector [x, y, z]
 */
AE_INLINE
void
ae_translate_make(mat4 m, vec3 v)
{
	ae_mat4_identity(m);
	ae_vec3_copy(v, m[3]);
}

/*!
 * @brief scale existing transform matrix by v vector
 *        and store result in dest
 *
 * @param[in]  m    affine transfrom
 * @param[in]  v    scale vector [x, y, z]
 * @param[out] dest scaled matrix
 */
AE_INLINE
void
ae_scale_to(mat4 m, vec3 v, mat4 dest)
{
	ae_vec4_scale(m[0], v[0], dest[0]);
	ae_vec4_scale(m[1], v[1], dest[1]);
	ae_vec4_scale(m[2], v[2], dest[2]);

	ae_vec4_copy(m[3], dest[3]);
}

/*!
 * @brief creates NEW scale matrix by v vector
 *
 * @param[out]  m  affine transfrom
 * @param[in]   v  scale vector [x, y, z]
 */
AE_INLINE
void
ae_scale_make(mat4 m, vec3 v)
{
	ae_mat4_identity(m);
	m[0][0] = v[0];
	m[1][1] = v[1];
	m[2][2] = v[2];
}

/*!
 * @brief scales existing transform matrix by v vector
 *        and stores result in same matrix
 *
 * @param[in, out]  m  affine transfrom
 * @param[in]       v  scale vector [x, y, z]
 */
AE_INLINE
void
ae_scale(mat4 m, vec3 v)
{
	ae_scale_to(m, v, m);
}

/*!
 * @brief applies uniform scale to existing transform matrix v = [s, s, s]
 *        and stores result in same matrix
 *
 * @param[in, out]  m  affine transfrom
 * @param[in]       s  scale factor
 */
AE_INLINE
void
ae_scale_uni(mat4 m, float s)
{
	AE_ALIGN(8) vec3 v = { s, s, s };
	ae_scale_to(m, v, m);
}

/*!
 * @brief rotate existing transform matrix around X axis by angle
 *        and store result in dest
 *
 * @param[in]   m      affine transfrom
 * @param[in]   angle  angle (radians)
 * @param[out]  dest   rotated matrix
 */
AE_INLINE
void
ae_rotate_x(mat4 m, float angle, mat4 dest)
{
	AE_ALIGN_MAT mat4 t = GLM_MAT4_IDENTITY_INIT;
	float c, s;

	c = cosf(angle);
	s = sinf(angle);

	t[1][1] = c;
	t[1][2] = s;
	t[2][1] = -s;
	t[2][2] = c;

	ae_mul_rot(m, t, dest);
}

/*!
 * @brief rotate existing transform matrix around Y axis by angle
 *        and store result in dest
 *
 * @param[in]   m      affine transfrom
 * @param[in]   angle  angle (radians)
 * @param[out]  dest   rotated matrix
 */
AE_INLINE
void
ae_rotate_y(mat4 m, float angle, mat4 dest)
{
	AE_ALIGN_MAT mat4 t = GLM_MAT4_IDENTITY_INIT;
	float c, s;

	c = cosf(angle);
	s = sinf(angle);

	t[0][0] = c;
	t[0][2] = -s;
	t[2][0] = s;
	t[2][2] = c;

	ae_mul_rot(m, t, dest);
}

/*!
 * @brief rotate existing transform matrix around Z axis by angle
 *        and store result in dest
 *
 * @param[in]   m      affine transfrom
 * @param[in]   angle  angle (radians)
 * @param[out]  dest   rotated matrix
 */
AE_INLINE
void
ae_rotate_z(mat4 m, float angle, mat4 dest)
{
	AE_ALIGN_MAT mat4 t = GLM_MAT4_IDENTITY_INIT;
	float c, s;

	c = cosf(angle);
	s = sinf(angle);

	t[0][0] = c;
	t[0][1] = s;
	t[1][0] = -s;
	t[1][1] = c;

	ae_mul_rot(m, t, dest);
}

/*!
 * @brief creates NEW rotation matrix by angle and axis
 *
 * axis will be normalized so you don't need to normalize it
 *
 * @param[out] m     affine transfrom
 * @param[in]  angle angle (radians)
 * @param[in]  axis  axis
 */
AE_INLINE
void
ae_rotate_make(mat4 m, float angle, vec3 axis)
{
	AE_ALIGN(8) vec3 axisn, v, vs;
	float c;

	c = cosf(angle);

	ae_vec3_normalize_to(axis, axisn);
	ae_vec3_scale(axisn, 1.0f - c, v);
	ae_vec3_scale(axisn, sinf(angle), vs);

	ae_vec3_scale(axisn, v[0], m[0]);
	ae_vec3_scale(axisn, v[1], m[1]);
	ae_vec3_scale(axisn, v[2], m[2]);

	m[0][0] += c;       m[1][0] -= vs[2];   m[2][0] += vs[1];
	m[0][1] += vs[2];   m[1][1] += c;       m[2][1] -= vs[0];
	m[0][2] -= vs[1];   m[1][2] += vs[0];   m[2][2] += c;

	m[0][3] = m[1][3] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

/*!
 * @brief rotate existing transform matrix around given axis by angle
 *
 * @param[in, out]  m      affine transfrom
 * @param[in]       angle  angle (radians)
 * @param[in]       axis   axis
 */
AE_INLINE
void
ae_rotate(mat4 m, float angle, vec3 axis)
{
	AE_ALIGN_MAT mat4 rot;
	ae_rotate_make(rot, angle, axis);
	ae_mul_rot(m, rot, m);
}

/*!
 * @brief rotate existing transform
 *        around given axis by angle at given pivot point (rotation center)
 *
 * @param[in, out]  m      affine transfrom
 * @param[in]       pivot  rotation center
 * @param[in]       angle  angle (radians)
 * @param[in]       axis   axis
 */
AE_INLINE
void
ae_rotate_at(mat4 m, vec3 pivot, float angle, vec3 axis)
{
	AE_ALIGN(8) vec3 pivotInv;

	ae_vec3_negate_to(pivot, pivotInv);

	ae_translate(m, pivot);
	ae_rotate(m, angle, axis);
	ae_translate(m, pivotInv);
}

/*!
 * @brief creates NEW rotation matrix by angle and axis at given point
 *
 * this creates rotation matrix, it assumes you don't have a matrix
 *
 * this should work faster than ae_rotate_at because it reduces
 * one ae_translate.
 *
 * @param[out] m      affine transfrom
 * @param[in]  pivot  rotation center
 * @param[in]  angle  angle (radians)
 * @param[in]  axis   axis
 */
AE_INLINE
void
ae_rotate_atm(mat4 m, vec3 pivot, float angle, vec3 axis)
{
	AE_ALIGN(8) vec3 pivotInv;

	ae_vec3_negate_to(pivot, pivotInv);

	ae_translate_make(m, pivot);
	ae_rotate(m, angle, axis);
	ae_translate(m, pivotInv);
}

/*!
 * @brief decompose scale vector
 *
 * @param[in]  m  affine transform
 * @param[out] s  scale vector (Sx, Sy, Sz)
 */
AE_INLINE
void
ae_decompose_scalev(mat4 m, vec3 s)
{
	s[0] = ae_vec3_norm(m[0]);
	s[1] = ae_vec3_norm(m[1]);
	s[2] = ae_vec3_norm(m[2]);
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
ae_uniscaled(mat4 m)
{
	AE_ALIGN(8) vec3 s;
	ae_decompose_scalev(m, s);
	return ae_vec3_eq_all(s);
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
ae_decompose_rs(mat4 m, mat4 r, vec3 s)
{
	AE_ALIGN(16) vec4 t = { 0.0f, 0.0f, 0.0f, 1.0f };
	AE_ALIGN(8)  vec3 v;

	ae_vec4_copy(m[0], r[0]);
	ae_vec4_copy(m[1], r[1]);
	ae_vec4_copy(m[2], r[2]);
	ae_vec4_copy(t, r[3]);

	s[0] = ae_vec3_norm(m[0]);
	s[1] = ae_vec3_norm(m[1]);
	s[2] = ae_vec3_norm(m[2]);

	ae_vec4_scale(r[0], 1.0f / s[0], r[0]);
	ae_vec4_scale(r[1], 1.0f / s[1], r[1]);
	ae_vec4_scale(r[2], 1.0f / s[2], r[2]);

	/* Note from Apple Open Source (assume that the matrix is orthonormal):
	   check for a coordinate system flip.  If the determinant
	   is -1, then negate the matrix and the scaling factors. */
	ae_vec3_cross(m[0], m[1], v);
	if (ae_vec3_dot(v, m[2]) < 0.0f)
	{
		ae_vec4_negate(r[0]);
		ae_vec4_negate(r[1]);
		ae_vec4_negate(r[2]);
		ae_vec3_negate(s);
	}
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
ae_decompose(mat4 m, vec4 t, mat4 r, vec3 s)
{
	ae_vec4_copy(m[3], t);
	ae_decompose_rs(m, r, s);
}

#endif /* ae_affine_h */
