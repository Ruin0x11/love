#ifndef LOVE_GRAPHICS_C_IMAGE_H
#define LOVE_GRAPHICS_C_IMAGE_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_ImageHandle;
typedef struct LoveC_ImageHandle* LoveC_ImageRef;

typedef struct LoveC_Image_Settings {
  LoveC_Bool mipmaps;
  LoveC_Bool linear;
  float dpiScale;
} LoveC_Image_Settings;


LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_IMAGE_H
