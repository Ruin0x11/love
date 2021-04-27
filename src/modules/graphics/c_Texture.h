#ifndef LOVE_GRAPHICS_C_TEXTURE_H
#define LOVE_GRAPHICS_C_TEXTURE_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_TextureHandle;
typedef struct LoveC_TextureHandle* LoveC_TextureRef;

typedef enum LoveC_Graphics_TextureType
  {
    TEXTURE_2D,
    TEXTURE_VOLUME,
    TEXTURE_2D_ARRAY,
    TEXTURE_CUBE,
    TEXTURE_MAX_ENUM
  } LoveC_Texture_TextureType;

typedef enum LoveC_Texture_WrapMode
  {
    WRAP_CLAMP,
    WRAP_CLAMP_ZERO,
    WRAP_REPEAT,
    WRAP_MIRRORED_REPEAT,
    WRAP_MAX_ENUM
  } LoveC_Texture_WrapMode;

typedef enum LoveC_Texture_FilterMode
  {
    FILTER_NONE,
    FILTER_LINEAR,
    FILTER_NEAREST,
    FILTER_MAX_ENUM
  } LoveC_Texture_FilterMode;

typedef struct LoveC_Texture_Filter
{
  LoveC_Texture_FilterMode min;
  LoveC_Texture_FilterMode mag;
  LoveC_Texture_FilterMode mipmap;
  float anisotropy;
} LoveC_Texture_Filter;

typedef struct LoveC_Texture_Wrap
{
  LoveC_Texture_WrapMode s;
  LoveC_Texture_WrapMode t;
  LoveC_Texture_WrapMode r;
} LoveC_Texture_Wrap;


LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_TEXTURE_H
