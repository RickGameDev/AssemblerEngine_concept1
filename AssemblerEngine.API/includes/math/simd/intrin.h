/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ae_intrin_h
#define ae_intrin_h

#if defined( _MSC_VER )
#  if (defined(_M_AMD64) || defined(_M_X64)) || _M_IX86_FP == 2
#    ifndef __SSE2__
#      define __SSE2__
#    endif
#  elif _M_IX86_FP == 1
#    ifndef __SSE__
#      define __SSE__
#    endif
#  endif
/* do not use alignment for older visual studio versions */
#  if _MSC_VER < 1913     /* Visual Studio 2017 version 15.6 */
#    define AE_ALL_UNALIGNED
#  endif
#endif

#if defined( __SSE__ ) || defined( __SSE2__ )
#  include <xmmintrin.h>
#  include <emmintrin.h>
#  define AE_SSE_FP 1
#  ifndef AE_SIMD_x86
#    define AE_SIMD_x86
#  endif
#endif

#if defined(__SSE3__)
#  include <x86intrin.h>
#  ifndef AE_SIMD_x86
#    define AE_SIMD_x86
#  endif
#endif

#if defined(__SSE4_1__)
#  include <smmintrin.h>
#  ifndef AE_SIMD_x86
#    define AE_SIMD_x86
#  endif
#endif

#if defined(__SSE4_2__)
#  include <nmmintrin.h>
#  ifndef AE_SIMD_x86
#    define AE_SIMD_x86
#  endif
#endif

#ifdef __AVX__
#  include <immintrin.h>
#  define AE_AVX_FP 1
#  ifndef AE_SIMD_x86
#    define AE_SIMD_x86
#  endif
#endif

/* ARM Neon */
#if defined(__ARM_NEON)
#  include <arm_neon.h>
#  if defined(__ARM_NEON_FP)
#    define AE_NEON_FP 1
#    ifndef AE_SIMD_ARM
#      define AE_SIMD_ARM
#    endif
#  endif
#endif

#if defined(AE_SIMD_x86) || defined(AE_NEON_FP)
#  ifndef AE_SIMD
#    define AE_SIMD
#  endif
#endif

#if defined(AE_SIMD_x86)
#  include "x86.h"
#endif

#if defined(AE_SIMD_ARM)
#  include "arm.h"
#endif

#endif /* ae_intrin_h */
