/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*
 Functions:
   AE_INLINE void ae_mat4_print(mat4 matrix, FILE *ostream);
   AE_INLINE void ae_mat3_print(mat3 matrix, FILE *ostream);
   AE_INLINE void ae_vec4_print(vec4 vec, FILE *ostream);
   AE_INLINE void ae_vec3_print(vec3 vec, FILE *ostream);
   AE_INLINE void ae_ivec3_print(ivec3 vec, FILE *ostream);
   AE_INLINE void ae_versor_print(versor vec, FILE *ostream);
 */

#ifndef aes_ios_h
#define aes_ios_h

#include "../common.h"
#include "../io.h"
#include "mat4.h"

#include <stdio.h>
#include <stdlib.h>

AE_INLINE
void
aes_mat4_print(mat4s             matrix,
                FILE * __restrict ostream) {

  ae_mat4_print(matrix.raw, ostream);
}

AE_INLINE
void
aes_mat3_print(mat3s             matrix,
                FILE * __restrict ostream) {
  ae_mat3_print(matrix.raw, ostream);
}

AE_INLINE
void
aes_vec4_print(vec4s             vec,
                FILE * __restrict ostream) {
  ae_vec4_print(vec.raw, ostream);
}

AE_INLINE
void
aes_vec3_print(vec3s             vec,
                FILE * __restrict ostream) {
  ae_vec3_print(vec.raw, ostream);
}

AE_INLINE
void
aes_ivec3_print(ivec3s            vec,
                 FILE * __restrict ostream) {
  ae_ivec3_print(vec.raw, ostream);
}

AE_INLINE
void
aes_versor_print(versors           vec,
                  FILE * __restrict ostream) {
  ae_versor_print(vec.raw, ostream);
}

AE_INLINE
void
aes_aabb_print(vec3s                   bbox[2],
                const char * __restrict tag,
                FILE       * __restrict ostream) {
  vec3 rawBbox[2];

  aes_vec3_unpack(rawBbox, bbox, 2);
  ae_aabb_print(rawBbox, tag, ostream);
}

#endif /* aes_ios_h */
