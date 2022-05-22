/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ae_quat_neon_h
#define ae_quat_neon_h
#if defined(__ARM_NEON_FP)

#include "../../common.h"
#include "../intrin.h"

AE_INLINE
void
ae_quat_mul_neon(versor p, versor q, versor dest) {
  /*
   + (a1 b2 + b1 a2 + c1 d2 − d1 c2)i
   + (a1 c2 − b1 d2 + c1 a2 + d1 b2)j
   + (a1 d2 + b1 c2 − c1 b2 + d1 a2)k
     a1 a2 − b1 b2 − c1 c2 − d1 d2
   */

  aem_128 xp, xq, xqr, r, x, y, z, s2, s3;
  aem_128 s1 = {-0.f, 0.f, 0.f, -0.f};
  float32x2_t   qh, ql;
  
  xp  = aem_load(p); /* 3 2 1 0 */
  xq  = aem_load(q);

  r   = vmulq_f32(aem_splat_w(xp), xq);
  x   = aem_splat_x(xp);
  y   = aem_splat_y(xp);
  z   = aem_splat_z(xp);

  ql  = vget_high_f32(s1);
  s3  = vcombine_f32(ql, ql);
  s2  = vzipq_f32(s3, s3).val[0];

  xqr = vrev64q_f32(xq);
  qh  = vget_high_f32(xqr);
  ql  = vget_low_f32(xqr);

  r = aem_fmadd(aem_xor(x, s3), vcombine_f32(qh, ql), r);
  
  r = aem_fmadd(aem_xor(y, s2), vcombine_f32(vget_high_f32(xq),
                                               vget_low_f32(xq)), r);
  
  r = aem_fmadd(aem_xor(z, s1), vcombine_f32(ql, qh), r);

  aem_store(dest, r);
}

#endif
#endif /* ae_quat_neon_h */
