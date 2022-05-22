/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef aes_boxs_h
#define aes_boxs_h

#include "../common.h"
#include "../types-struct.h"
#include "../box.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

/*!
 * @brief apply transform to Axis-Aligned Bounding Box
 *
 * @param[in]  box  bounding box
 * @param[in]  m    transform matrix
 * @param[out] dest transformed bounding box
 */
AE_INLINE
void
aes_aabb_transform(vec3s box[2], mat4s m, vec3s dest[2]) {
  vec3 rawBox[2];
  vec3 rawDest[2];

  aes_vec3_unpack(rawBox, box, 2);
  ae_aabb_transform(rawBox, m.raw, rawDest);
  aes_vec3_pack(dest, rawDest, 2);
}

/*!
 * @brief merges two AABB bounding box and creates new one
 *
 * two box must be in same space, if one of box is in different space then
 * you should consider to convert it's space by ae_box_space
 *
 * @param[in]  box1 bounding box 1
 * @param[in]  box2 bounding box 2
 * @param[out] dest merged bounding box
 */
AE_INLINE
void
aes_aabb_merge(vec3s box1[2], vec3s box2[2], vec3s dest[2]) {
  vec3 rawBox1[2];
  vec3 rawBox2[2];
  vec3 rawDest[2];

  aes_vec3_unpack(rawBox1, box1, 2);
  aes_vec3_unpack(rawBox2, box2, 2);
  ae_aabb_merge(rawBox1, rawBox2, rawDest);
  aes_vec3_pack(dest, rawDest, 2);
}

/*!
 * @brief crops a bounding box with another one.
 *
 * this could be useful for gettng a bbox which fits with view frustum and
 * object bounding boxes. In this case you crop view frustum box with objects
 * box
 *
 * @param[in]  box     bounding box 1
 * @param[in]  cropBox crop box
 * @param[out] dest    cropped bounding box
 */
AE_INLINE
void
aes_aabb_crop(vec3s box[2], vec3s cropBox[2], vec3s dest[2]) {
  vec3 rawBox[2];
  vec3 rawCropBox[2];
  vec3 rawDest[2];

  aes_vec3_unpack(rawBox, box, 2);
  aes_vec3_unpack(rawCropBox, cropBox, 2);
  ae_aabb_crop(rawBox, rawCropBox, rawDest);
  aes_vec3_pack(dest, rawDest, 2);
}

/*!
 * @brief crops a bounding box with another one.
 *
 * this could be useful for gettng a bbox which fits with view frustum and
 * object bounding boxes. In this case you crop view frustum box with objects
 * box
 *
 * @param[in]  box      bounding box
 * @param[in]  cropBox  crop box
 * @param[in]  clampBox miniumum box
 * @param[out] dest     cropped bounding box
 */
AE_INLINE
void
aes_aabb_crop_until(vec3s box[2],
                     vec3s cropBox[2],
                     vec3s clampBox[2],
                     vec3s dest[2]) {
  aes_aabb_crop(box, cropBox, dest);
  aes_aabb_merge(clampBox, dest, dest);
}

/*!
 * @brief check if AABB intersects with frustum planes
 *
 * this could be useful for frustum culling using AABB.
 *
 * OPTIMIZATION HINT:
 *  if planes order is similar to LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR
 *  then this method should run even faster because it would only use two
 *  planes if object is not inside the two planes
 *  fortunately ae extracts planes as this order! just pass what you got!
 *
 * @param[in]  box     bounding box
 * @param[in]  planes  frustum planes
 */
AE_INLINE
bool
aes_aabb_frustum(vec3s box[2], vec4s planes[6]) {
  vec3 rawBox[2];
  vec4 rawPlanes[6];

  aes_vec3_unpack(rawBox, box, 2);
  aes_vec4_unpack(rawPlanes, planes, 6);
  return ae_aabb_frustum(rawBox, rawPlanes);
}

/*!
 * @brief invalidate AABB min and max values
 *
 * @param[in, out]  box bounding box
 */
AE_INLINE
void
aes_aabb_invalidate(vec3s box[2]) {
  box[0] = aes_vec3_broadcast(FLT_MAX);
  box[1] = aes_vec3_broadcast(-FLT_MAX);
}

/*!
 * @brief check if AABB is valid or not
 *
 * @param[in]  box bounding box
 */
AE_INLINE
bool
aes_aabb_isvalid(vec3s box[2]) {
  vec3 rawBox[2];
  aes_vec3_unpack(rawBox, box, 2);
  return ae_aabb_isvalid(rawBox);
}

/*!
 * @brief distance between of min and max
 *
 * @param[in]  box bounding box
 */
AE_INLINE
float
aes_aabb_size(vec3s box[2]) {
  return ae_vec3_distance(box[0].raw, box[1].raw);
}

/*!
 * @brief radius of sphere which surrounds AABB
 *
 * @param[in]  box bounding box
 */
AE_INLINE
float
aes_aabb_radius(vec3s box[2]) {
  return aes_aabb_size(box) * 0.5f;
}

/*!
 * @brief computes center point of AABB
 *
 * @param[in]   box  bounding box
 * @returns center of bounding box
 */
AE_INLINE
vec3s
aes_aabb_center(vec3s box[2]) {
  return aes_vec3_center(box[0], box[1]);
}

/*!
 * @brief check if two AABB intersects
 *
 * @param[in]   box    bounding box
 * @param[in]   other  other bounding box
 */
AE_INLINE
bool
aes_aabb_aabb(vec3s box[2], vec3s other[2]) {
  vec3 rawBox[2];
  vec3 rawOther[2];

  aes_vec3_unpack(rawBox, box, 2);
  aes_vec3_unpack(rawOther, other, 2);
  return ae_aabb_aabb(rawBox, rawOther);
}

/*!
 * @brief check if AABB intersects with sphere
 *
 * https://github.com/erich666/GraphicsGems/blob/master/gems/BoxSphere.c
 * Solid Box - Solid Sphere test.
 *
 * @param[in]   box    solid bounding box
 * @param[in]   s      solid sphere
 */
AE_INLINE
bool
aes_aabb_sphere(vec3s box[2], vec4s s) {
  vec3 rawBox[2];

  aes_vec3_unpack(rawBox, box, 2);
  return ae_aabb_sphere(rawBox, s.raw);
}

/*!
 * @brief check if point is inside of AABB
 *
 * @param[in]   box    bounding box
 * @param[in]   point  point
 */
AE_INLINE
bool
aes_aabb_point(vec3s box[2], vec3s point) {
  vec3 rawBox[2];

  aes_vec3_unpack(rawBox, box, 2);
  return ae_aabb_point(rawBox, point.raw);
}

/*!
 * @brief check if AABB contains other AABB
 *
 * @param[in]   box    bounding box
 * @param[in]   other  other bounding box
 */
AE_INLINE
bool
aes_aabb_contains(vec3s box[2], vec3s other[2]) {
  vec3 rawBox[2];
  vec3 rawOther[2];

  aes_vec3_unpack(rawBox, box, 2);
  aes_vec3_unpack(rawOther, other, 2);
  return ae_aabb_contains(rawBox, rawOther);
}

#endif /* aes_boxs_h */
