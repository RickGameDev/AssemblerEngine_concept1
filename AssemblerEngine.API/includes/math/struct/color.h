/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef aes_colors_h
#define aes_colors_h

#include "../common.h"
#include "../types-struct.h"
#include "../color.h"
#include "vec3.h"

/*!
 * @brief averages the color channels into one value
 *
 * @param[in]  rgb RGB color
 */
AE_INLINE
float
aes_luminance(vec3s rgb) {
  return ae_luminance(rgb.raw);
}

#endif /* aes_colors_h */
