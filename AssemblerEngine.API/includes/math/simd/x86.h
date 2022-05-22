/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ae_simd_x86_h
#define ae_simd_x86_h
#include "intrin.h"
#ifdef AE_SIMD_x86

#ifdef AE_ALL_UNALIGNED
#  define aem_load(p)      _mm_loadu_ps(p)
#  define aem_store(p, a)  _mm_storeu_ps(p, a)
#else
#  define aem_load(p)      _mm_load_ps(p)
#  define aem_store(p, a)  _mm_store_ps(p, a)
#endif

#define aem_set1(x) _mm_set1_ps(x)
#define aem_128     __m128

#ifdef AE_USE_INT_DOMAIN
#  define aem_shuff1(xmm, z, y, x, w)                                        \
     _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(xmm),                \
                                        _MM_SHUFFLE(z, y, x, w)))
#else
#  define aem_shuff1(xmm, z, y, x, w)                                        \
       _mm_shuffle_ps(xmm, xmm, _MM_SHUFFLE(z, y, x, w))
#endif

#define aem_splat(x, lane) aem_shuff1(x, lane, lane, lane, lane)

#define aem_splat_x(x) aem_splat(x, 0)
#define aem_splat_y(x) aem_splat(x, 1)
#define aem_splat_z(x) aem_splat(x, 2)
#define aem_splat_w(x) aem_splat(x, 3)

/* aem_shuff1x() is DEPRECATED!, use aem_splat() */
#define aem_shuff1x(xmm, x) aem_shuff1(xmm, x, x, x, x)

#define aem_shuff2(a, b, z0, y0, x0, w0, z1, y1, x1, w1)                     \
     aem_shuff1(_mm_shuffle_ps(a, b, _MM_SHUFFLE(z0, y0, x0, w0)),           \
                 z1, y1, x1, w1)

#ifdef __AVX__
#  ifdef AE_ALL_UNALIGNED
#    define aem_load256(p)      _mm256_loadu_ps(p)
#    define aem_store256(p, a)  _mm256_storeu_ps(p, a)
#  else
#    define aem_load256(p)      _mm256_load_ps(p)
#    define aem_store256(p, a)  _mm256_store_ps(p, a)
#  endif
#endif

static inline
__m128
aem_abs(__m128 x) {
  return _mm_andnot_ps(_mm_set1_ps(-0.0f), x);
}

static inline
__m128
aem_vhadd(__m128 v) {
  __m128 x0;
  x0 = _mm_add_ps(v,  aem_shuff1(v, 0, 1, 2, 3));
  x0 = _mm_add_ps(x0, aem_shuff1(x0, 1, 0, 0, 1));
  return x0;
}

static inline
__m128
aem_vhadds(__m128 v) {
#if defined(__SSE3__)
  __m128 shuf, sums;
  shuf = _mm_movehdup_ps(v);
  sums = _mm_add_ps(v, shuf);
  shuf = _mm_movehl_ps(shuf, sums);
  sums = _mm_add_ss(sums, shuf);
  return sums;
#else
  __m128 shuf, sums;
  shuf = aem_shuff1(v, 2, 3, 0, 1);
  sums = _mm_add_ps(v, shuf);
  shuf = _mm_movehl_ps(shuf, sums);
  sums = _mm_add_ss(sums, shuf);
  return sums;
#endif
}

static inline
float
aem_hadd(__m128 v) {
  return _mm_cvtss_f32(aem_vhadds(v));
}

static inline
__m128
aem_vhmin(__m128 v) {
  __m128 x0, x1, x2;
  x0 = _mm_movehl_ps(v, v);     /* [2, 3, 2, 3] */
  x1 = _mm_min_ps(x0, v);       /* [0|2, 1|3, 2|2, 3|3] */
  x2 = aem_splat(x1, 1);       /* [1|3, 1|3, 1|3, 1|3] */
  return _mm_min_ss(x1, x2);
}

static inline
float
aem_hmin(__m128 v) {
  return _mm_cvtss_f32(aem_vhmin(v));
}

static inline
__m128
aem_vhmax(__m128 v) {
  __m128 x0, x1, x2;
  x0 = _mm_movehl_ps(v, v);     /* [2, 3, 2, 3] */
  x1 = _mm_max_ps(x0, v);       /* [0|2, 1|3, 2|2, 3|3] */
  x2 = aem_splat(x1, 1);       /* [1|3, 1|3, 1|3, 1|3] */
  return _mm_max_ss(x1, x2);
}

static inline
float
aem_hmax(__m128 v) {
  return _mm_cvtss_f32(aem_vhmax(v));
}

static inline
__m128
aem_vdots(__m128 a, __m128 b) {
#if (defined(__SSE4_1__) || defined(__SSE4_2__)) && defined(AE_SSE4_DOT)
  return _mm_dp_ps(a, b, 0xFF);
#elif defined(__SSE3__) && defined(AE_SSE3_DOT)
  __m128 x0, x1;
  x0 = _mm_mul_ps(a, b);
  x1 = _mm_hadd_ps(x0, x0);
  return _mm_hadd_ps(x1, x1);
#else
  return aem_vhadds(_mm_mul_ps(a, b));
#endif
}

static inline
__m128
aem_vdot(__m128 a, __m128 b) {
#if (defined(__SSE4_1__) || defined(__SSE4_2__)) && defined(AE_SSE4_DOT)
  return _mm_dp_ps(a, b, 0xFF);
#elif defined(__SSE3__) && defined(AE_SSE3_DOT)
  __m128 x0, x1;
  x0 = _mm_mul_ps(a, b);
  x1 = _mm_hadd_ps(x0, x0);
  return _mm_hadd_ps(x1, x1);
#else
  __m128 x0;
  x0 = _mm_mul_ps(a, b);
  x0 = _mm_add_ps(x0, aem_shuff1(x0, 1, 0, 3, 2));
  return _mm_add_ps(x0, aem_shuff1(x0, 0, 1, 0, 1));
#endif
}

static inline
float
aem_dot(__m128 a, __m128 b) {
  return _mm_cvtss_f32(aem_vdots(a, b));
}

static inline
float
aem_norm(__m128 a) {
  return _mm_cvtss_f32(_mm_sqrt_ss(aem_vhadds(_mm_mul_ps(a, a))));
}

static inline
float
aem_norm2(__m128 a) {
  return _mm_cvtss_f32(aem_vhadds(_mm_mul_ps(a, a)));
}

static inline
float
aem_norm_one(__m128 a) {
  return _mm_cvtss_f32(aem_vhadds(aem_abs(a)));
}

static inline
float
aem_norm_inf(__m128 a) {
  return _mm_cvtss_f32(aem_vhmax(aem_abs(a)));
}

static inline
__m128
aem_load3(float v[3]) {
  __m128i xy;
  __m128  z;

  xy = _mm_loadl_epi64(AE_CASTPTR_ASSUME_ALIGNED(v, const __m128i));
  z  = _mm_load_ss(&v[2]);

  return _mm_movelh_ps(_mm_castsi128_ps(xy), z);
}

static inline
void
aem_store3(float v[3], __m128 vx) {
  _mm_storel_pi(AE_CASTPTR_ASSUME_ALIGNED(v, __m64), vx);
  _mm_store_ss(&v[2], aem_shuff1(vx, 2, 2, 2, 2));
}

static inline
__m128
aem_div(__m128 a, __m128 b) {
  return _mm_div_ps(a, b);
}

/* enable FMA macro for MSVC? */
#if defined(_MSC_VER) && !defined(__FMA__) && defined(__AVX2__)
#  define __FMA__ 1
#endif

static inline
__m128
aem_fmadd(__m128 a, __m128 b, __m128 c) {
#ifdef __FMA__
  return _mm_fmadd_ps(a, b, c);
#else
  return _mm_add_ps(c, _mm_mul_ps(a, b));
#endif
}

static inline
__m128
aem_fnmadd(__m128 a, __m128 b, __m128 c) {
#ifdef __FMA__
  return _mm_fnmadd_ps(a, b, c);
#else
  return _mm_sub_ps(c, _mm_mul_ps(a, b));
#endif
}

static inline
__m128
aem_fmsub(__m128 a, __m128 b, __m128 c) {
#ifdef __FMA__
  return _mm_fmsub_ps(a, b, c);
#else
  return _mm_sub_ps(_mm_mul_ps(a, b), c);
#endif
}

static inline
__m128
aem_fnmsub(__m128 a, __m128 b, __m128 c) {
#ifdef __FMA__
  return _mm_fnmsub_ps(a, b, c);
#else
  return _mm_xor_ps(_mm_add_ps(_mm_mul_ps(a, b), c), _mm_set1_ps(-0.0f));
#endif
}

#if defined(__AVX__)
static inline
__m256
aem256_fmadd(__m256 a, __m256 b, __m256 c) {
#ifdef __FMA__
  return _mm256_fmadd_ps(a, b, c);
#else
  return _mm256_add_ps(c, _mm256_mul_ps(a, b));
#endif
}

static inline
__m256
aem256_fnmadd(__m256 a, __m256 b, __m256 c) {
#ifdef __FMA__
  return _mm256_fnmadd_ps(a, b, c);
#else
  return _mm256_sub_ps(c, _mm256_mul_ps(a, b));
#endif
}

static inline
__m256
aem256_fmsub(__m256 a, __m256 b, __m256 c) {
#ifdef __FMA__
  return _mm256_fmsub_ps(a, b, c);
#else
  return _mm256_sub_ps(_mm256_mul_ps(a, b), c);
#endif
}

static inline
__m256
aem256_fnmsub(__m256 a, __m256 b, __m256 c) {
#ifdef __FMA__
  return _mm256_fmsub_ps(a, b, c);
#else
  return _mm256_xor_ps(_mm256_sub_ps(_mm256_mul_ps(a, b), c),
                       _mm256_set1_ps(-0.0f));
#endif
}
#endif

#endif
#endif /* ae_simd_x86_h */
