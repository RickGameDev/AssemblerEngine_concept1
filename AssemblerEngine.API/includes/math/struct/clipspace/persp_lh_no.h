/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), htt../opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*
 Functions:
   AE_INLINE mat4s aes_frustum_lh_no(float left,    float right,
                                        float bottom,  float top,
                                        float nearZ,   float farZ)
   AE_INLINE mat4s aes_perspective_lh_no(float fovy,
                                            float aspect,
                                            float nearZ,
                                            float farZ)
   AE_INLINE void  aes_persp_move_far_lh_no(mat4s proj, float deltaFar)
   AE_INLINE mat4s aes_perspective_default_lh_no(float aspect)
   AE_INLINE void  aes_perspective_resize_lh_no(mat4s proj, float aspect)
   AE_INLINE void  aes_persp_decomp_lh_no(mat4s  proj,
                                             float *nearv, float *farv,
                                             float *top,   float *bottom,
                                             float *left,  float *right)
   AE_INLINE void  aes_persp_decompv_lh_no(mat4s proj, float dest[6])
   AE_INLINE void  aes_persp_decomp_x_lh_no(mat4s proj, float *left, float *right)
   AE_INLINE void  aes_persp_decomp_y_lh_no(mat4s proj, float *top, float *bottom)
   AE_INLINE void  aes_persp_decomp_z_lh_no(mat4s proj, float *nearv, float *farv)
   AE_INLINE void  aes_persp_decomp_far_lh_no(mat4s proj, float *farZ)
   AE_INLINE void  aes_persp_decomp_near_lh_no(mat4s proj, float *nearZ)
   AE_INLINE float aes_persp_fovy_lh_no(mat4s proj)
   AE_INLINE float aes_persp_aspect_lh_no(mat4s proj)
   AE_INLINE vec4s aes_persp_sizes_lh_no(mat4s proj, float fovy)
 */

#ifndef aes_persp_lh_no_h
#define aes_persp_lh_no_h

#include "../../common.h"
#include "../../types-struct.h"
#include "../../plane.h"
#include "../../cam.h"

/*!
 * @brief set up perspective peprojection matrix
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  left    viewport.left
 * @param[in]  right   viewport.right
 * @param[in]  bottom  viewport.bottom
 * @param[in]  top     viewport.top
 * @param[in]  nearZ   near clipping plane
 * @param[in]  farZ    far clipping plane
 * @returns    result matrix
 */
AE_INLINE
mat4s
aes_frustum_lh_no(float left,   float right,
                   float bottom, float top,
                   float nearZ,  float farZ) {
  mat4s dest;
  ae_frustum_lh_no(left, right, bottom, top, nearZ, farZ, dest.raw);
  return dest;
}

/*!
 * @brief set up perspective projection matrix
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  fovy    field of view angle
 * @param[in]  aspect  aspect ratio ( width / height )
 * @param[in]  nearZ   near clipping plane
 * @param[in]  farZ    far clipping planes
 * @returns    result matrix
 */
AE_INLINE
mat4s
aes_perspective_lh_no(float fovy, float aspect, float nearZ, float farZ) {
  mat4s dest;
  ae_perspective_lh_no(fovy, aspect, nearZ, farZ, dest.raw);
  return dest;
}

/*!
 * @brief extend perspective projection matrix's far distance
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * NOTE: if you dodn't want to create new matrix then use array api on struct.raw
 *       like aes_persp_move_far_lh_no(prooj.raw, deltaFar) to avoid create new mat4
 *       each time
 *       
 * this function does not guarantee far >= near, be aware of that!
 *
 * @param[in, out] proj      projection matrix to extend
 * @param[in]      deltaFar  distance from existing far (negative to shink)
 */
AE_INLINE
mat4s
aes_persp_move_far_lh_no(mat4s proj, float deltaFar) {
  mat4s dest;
  dest = proj;
  ae_persp_move_far_lh_no(dest.raw, deltaFar);
  return dest;
}

/*!
 * @brief set up perspective projection matrix with default near/far
 *        and angle values with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  aspect aspect ratio ( width / height )
 * @returns    result matrix
 */
AE_INLINE
mat4s
aes_perspective_default_lh_no(float aspect) {
  mat4s dest;
  ae_perspective_default_lh_no(aspect, dest.raw);
  return dest;
}

/*!
 * @brief resize perspective matrix by aspect ratio ( width / height )
 *        this makes very easy to resize proj matrix when window /viewport
 *        reized with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * NOTE: if you dodn't want to create new matrix then use array api on struct.raw
 *       like ae_perspective_resize_lh_no(proj.raw, aspect) to avoid create new mat4
 *       each time
 *       
 * @param[in, out] proj   perspective projection matrix
 * @param[in]      aspect aspect ratio ( width / height )
 */
AE_INLINE
mat4s
aes_perspective_resize_lh_no(mat4s proj, float aspect) {
  mat4s dest;
  dest = proj;
  ae_perspective_resize_lh_no(aspect, dest.raw);
  return dest;
}

/*!
 * @brief decomposes frustum values of perspective projection.
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  proj    perspective projection matrix
 * @param[out] nearZ   near
 * @param[out] farZ    far
 * @param[out] top     top
 * @param[out] bottom  bottom
 * @param[out] left    left
 * @param[out] right   right
 */
AE_INLINE
void
aes_persp_decomp_lh_no(mat4s proj,
                        float * __restrict nearZ, float * __restrict farZ,
                        float * __restrict top,   float * __restrict bottom,
                        float * __restrict left,  float * __restrict right) {
  ae_persp_decomp_lh_no(proj.raw, nearZ, farZ, top, bottom, left, right);
}

/*!
 * @brief decomposes frustum values of perspective projection.
 *        this makes easy to get all values at once
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  proj   perspective projection matrix
 * @param[out] dest   array
 */
AE_INLINE
void
aes_persp_decompv_lh_no(mat4s proj, float dest[6]) {
  ae_persp_decompv_lh_no(proj.raw, dest);
}

/*!
 * @brief decomposes left and right values of perspective projection
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *        x stands for x axis (left / right axis)
 *
 * @param[in]  proj  perspective projection matrix
 * @param[out] left  left
 * @param[out] right right
 */
AE_INLINE
void
aes_persp_decomp_x_lh_no(mat4s proj,
                          float * __restrict left,
                          float * __restrict right) {
  ae_persp_decomp_x_lh_no(proj.raw, left, right);
}

/*!
 * @brief decomposes top and bottom values of perspective projection
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *        y stands for y axis (top / botom axis)
 *
 * @param[in]  proj   perspective projection matrix
 * @param[out] top    top
 * @param[out] bottom bottom
 */
AE_INLINE
void
aes_persp_decomp_y_lh_no(mat4s proj,
                          float * __restrict top,
                          float * __restrict bottom) {
  ae_persp_decomp_y_lh_no(proj.raw, top, bottom);
}

/*!
 * @brief decomposes near and far values of perspective projection
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *        z stands for z axis (near / far axis)
 *
 * @param[in]  proj    perspective projection matrix
 * @param[out] nearZ   near
 * @param[out] farZ    far
 */
AE_INLINE
void
aes_persp_decomp_z_lh_no(mat4s proj,
                          float * __restrict nearZ,
                          float * __restrict farZ) {
  ae_persp_decomp_z_lh_no(proj.raw, nearZ, farZ);
}

/*!
 * @brief decomposes far value of perspective projection
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  proj   perspective projection matrix
 * @param[out] farZ   far
 */
AE_INLINE
void
aes_persp_decomp_far_lh_no(mat4s proj, float * __restrict farZ) {
  ae_persp_decomp_far_lh_no(proj.raw, farZ);
}

/*!
 * @brief decomposes near value of perspective projection
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  proj  perspective projection matrix
 * @param[out] nearZ near
 */
AE_INLINE
void
aes_persp_decomp_near_lh_no(mat4s proj, float * __restrict nearZ) {
  ae_persp_decomp_near_lh_no(proj.raw, nearZ);
}

/*!
 * @brief returns field of view angle along the Y-axis (in radians)
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * if you need to degrees, use ae_deg to convert it or use this:
 * fovy_deg = ae_deg(ae_persp_fovy(projMatrix))
 *
 * @param[in] proj perspective projection matrix
 */
AE_INLINE
float
aes_persp_fovy_lh_no(mat4s proj) {
  return ae_persp_fovy_lh_no(proj.raw);
}

/*!
 * @brief returns aspect ratio of perspective projection
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in] proj perspective projection matrix
 */
AE_INLINE
float
aes_persp_aspect_lh_no(mat4s proj) {
  return ae_persp_aspect_lh_no(proj.raw);
}

/*!
 * @brief returns sizes of near and far planes of perspective projection
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  proj perspective projection matrix
 * @param[in]  fovy fovy (see brief)
 * @returns    sizes as vector, sizes order: [Wnear, Hnear, Wfar, Hfar]
 */
AE_INLINE
vec4s
aes_persp_sizes_lh_no(mat4s proj, float fovy) {
  vec4s dest;
  ae_persp_sizes_lh_no(proj.raw, fovy, dest.raw);
  return dest;
}

#endif /* aes_persp_lh_no_h */
