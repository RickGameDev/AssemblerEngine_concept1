/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ae_simd_arm_h
#define ae_simd_arm_h
#include "intrin.h"
#ifdef AE_SIMD_ARM

#if defined(_M_ARM64) || defined(_M_HYBRID_X86_ARM64) || defined(_M_ARM64EC) || defined(__aarch64__)
# define AE_ARM64 1
#endif

#define aem_load(p)      vld1q_f32(p)
#define aem_store(p, a)  vst1q_f32(p, a)

#define aem_set1(x) vdupq_n_f32(x)
#define aem_128     float32x4_t

#define aem_splat_x(x) vdupq_lane_f32(vget_low_f32(x),  0)
#define aem_splat_y(x) vdupq_lane_f32(vget_low_f32(x),  1)
#define aem_splat_z(x) vdupq_lane_f32(vget_high_f32(x), 0)
#define aem_splat_w(x) vdupq_lane_f32(vget_high_f32(x), 1)

#define aem_xor(a, b)                                                        \
  vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(a),                   \
                                  vreinterpretq_s32_f32(b)))

#define aem_swplane(v) vextq_f32(v, v, 2)
#define aem_low(x)     vget_low_f32(x)
#define aem_high(x)    vget_high_f32(x)

#define aem_combine_ll(x, y) vcombine_f32(vget_low_f32(x),  vget_low_f32(y))
#define aem_combine_hl(x, y) vcombine_f32(vget_high_f32(x), vget_low_f32(y))
#define aem_combine_lh(x, y) vcombine_f32(vget_low_f32(x),  vget_high_f32(y))
#define aem_combine_hh(x, y) vcombine_f32(vget_high_f32(x), vget_high_f32(y))

static inline
float32x4_t
aem_abs(float32x4_t v) {
  return vabsq_f32(v);
}

static inline
float32x4_t
aem_vhadd(float32x4_t v) {
  return vaddq_f32(vaddq_f32(aem_splat_x(v), aem_splat_y(v)),
                   vaddq_f32(aem_splat_z(v), aem_splat_w(v)));
  /*
   this seems slower:
   v = vaddq_f32(v, vrev64q_f32(v));
   return vaddq_f32(v, vcombine_f32(vget_high_f32(v), vget_low_f32(v)));
   */
}

static inline
float
aem_hadd(float32x4_t v) {
#if AE_ARM64
  return vaddvq_f32(v);
#else
  v = vaddq_f32(v, vrev64q_f32(v));
  v = vaddq_f32(v, vcombine_f32(vget_high_f32(v), vget_low_f32(v)));
  return vgetq_lane_f32(v, 0);
#endif
}

static inline
float
aem_hmin(float32x4_t v) {
  float32x2_t t;
  t = vpmin_f32(vget_low_f32(v), vget_high_f32(v));
  t = vpmin_f32(t, t);
  return vget_lane_f32(t, 0);
}

static inline
float
aem_hmax(float32x4_t v) {
  float32x2_t t;
  t = vpmax_f32(vget_low_f32(v), vget_high_f32(v));
  t = vpmax_f32(t, t);
  return vget_lane_f32(t, 0);
}

static inline
float
aem_dot(float32x4_t a, float32x4_t b) {
  return aem_hadd(vmulq_f32(a, b));
}

static inline
float
aem_norm(float32x4_t a) {
  return sqrtf(aem_dot(a, a));
}

static inline
float
aem_norm2(float32x4_t a) {
  return aem_dot(a, a);
}

static inline
float
aem_norm_one(float32x4_t a) {
  return aem_hadd(aem_abs(a));
}

static inline
float
aem_norm_inf(float32x4_t a) {
  return aem_hmax(aem_abs(a));
}

static inline
float32x4_t
aem_div(float32x4_t a, float32x4_t b) {
#if AE_ARM64
  return vdivq_f32(a, b);
#else
  /* 2 iterations of Newton-Raphson refinement of reciprocal */
  float32x4_t r0, r1;
  r0 = vrecpeq_f32(b);
  r1 = vrecpsq_f32(r0, b);
  r0 = vmulq_f32(r1, r0);
  r1 = vrecpsq_f32(r0, b);
  r0 = vmulq_f32(r1, r0);
  return vmulq_f32(a, r0);
#endif
}

static inline
float32x4_t
aem_fmadd(float32x4_t a, float32x4_t b, float32x4_t c) {
#if AE_ARM64
  return vfmaq_f32(c, a, b); /* why vfmaq_f32 is slower than vmlaq_f32 ??? */
#else
  return vmlaq_f32(c, a, b);
#endif
}

static inline
float32x4_t
aem_fnmadd(float32x4_t a, float32x4_t b, float32x4_t c) {
#if AE_ARM64
  return vfmsq_f32(c, a, b);
#else
  return vmlsq_f32(c, a, b);
#endif
}

static inline
float32x4_t
aem_fmsub(float32x4_t a, float32x4_t b, float32x4_t c) {
#if AE_ARM64
  return vfmsq_f32(c, a, b);
#else
  return vmlsq_f32(c, a, b);
#endif
}

static inline
float32x4_t
aem_fnmsub(float32x4_t a, float32x4_t b, float32x4_t c) {
  return vsubq_f32(vdupq_n_f32(0.0f), aem_fmadd(a, b, c));
}

#endif
#endif /* ae_simd_arm_h */
