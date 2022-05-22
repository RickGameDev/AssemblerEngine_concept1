/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ae_common_h
#define ae_common_h

#ifndef _USE_MATH_DEFINES
#  define _USE_MATH_DEFINES       /* for windows */
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#  define _CRT_SECURE_NO_WARNINGS /* for windows */
#endif

#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>

#if defined(_MSC_VER)
#  ifdef AE_STATIC
#    define AE_EXPORT
#  elif defined(AE_EXPORTS)
#    define AE_EXPORT __declspec(dllexport)
#  else
#    define AE_EXPORT __declspec(dllimport)
#  endif
#  define AE_INLINE __forceinline
#else
#  define AE_EXPORT __attribute__((visibility("default")))
#  define AE_INLINE static inline __attribute((always_inline))
#endif

#define GLM_SHUFFLE4(z, y, x, w) (((z) << 6) | ((y) << 4) | ((x) << 2) | (w))
#define GLM_SHUFFLE3(z, y, x)    (((z) << 4) | ((y) << 2) | (x))

#include "types.h"
#include "simd/intrin.h"

#ifndef AE_USE_DEFAULT_EPSILON
#  ifndef GLM_FLT_EPSILON
#    define GLM_FLT_EPSILON 1e-6
#  endif
#else
#  define GLM_FLT_EPSILON FLT_EPSILON
#endif

/*
 * Clip control: define GLM_FORCE_DEPTH_ZERO_TO_ONE before including
 * AE to use a clip space between 0 to 1.
 * Coordinate system: define GLM_FORCE_LEFT_HANDED before including
 * AE to use the left handed coordinate system by default.
 */

#define AE_CLIP_CONTROL_ZO_BIT (1 << 0) /* ZERO_TO_ONE */
#define AE_CLIP_CONTROL_NO_BIT (1 << 1) /* NEGATIVE_ONE_TO_ONE */
#define AE_CLIP_CONTROL_LH_BIT (1 << 2) /* LEFT_HANDED, For DirectX, Metal, Vulkan */
#define AE_CLIP_CONTROL_RH_BIT (1 << 3) /* RIGHT_HANDED, For OpenGL, default in GLM */

#define AE_CLIP_CONTROL_LH_ZO (AE_CLIP_CONTROL_LH_BIT | AE_CLIP_CONTROL_ZO_BIT)
#define AE_CLIP_CONTROL_LH_NO (AE_CLIP_CONTROL_LH_BIT | AE_CLIP_CONTROL_NO_BIT)
#define AE_CLIP_CONTROL_RH_ZO (AE_CLIP_CONTROL_RH_BIT | AE_CLIP_CONTROL_ZO_BIT)
#define AE_CLIP_CONTROL_RH_NO (AE_CLIP_CONTROL_RH_BIT | AE_CLIP_CONTROL_NO_BIT)

#ifdef AE_FORCE_DEPTH_ZERO_TO_ONE
#  ifdef AE_FORCE_LEFT_HANDED
#    define AE_CONFIG_CLIP_CONTROL AE_CLIP_CONTROL_LH_ZO
#  else
#    define AE_CONFIG_CLIP_CONTROL AE_CLIP_CONTROL_RH_ZO
#  endif
#else
#  ifdef AE_FORCE_LEFT_HANDED
#    define AE_CONFIG_CLIP_CONTROL AE_CLIP_CONTROL_LH_NO
#  else
#    define AE_CONFIG_CLIP_CONTROL AE_CLIP_CONTROL_RH_NO
#  endif
#endif

#endif /* ae_common_h */
