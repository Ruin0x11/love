#ifndef LOVE_GRAPHICS_C_CANVAS_H
#define LOVE_GRAPHICS_C_CANVAS_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "c_PixelFormat.h"
#include "c_Texture.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_CanvasHandle;
typedef struct LoveC_CanvasHandle* LoveC_CanvasRef;

typedef enum LoveC_Canvas_MipmapMode
  {
    MIPMAPS_NONE,
    MIPMAPS_MANUAL,
    MIPMAPS_AUTO,
    MIPMAPS_MAX_ENUM
  } LoveC_Canvas_MipmapMode;

typedef struct LoveC_Canvas_Settings {
  int width;
  int height;
  int layers; // depth for 3D textures
  LoveC_Canvas_MipmapMode mipmaps;
  LoveC_Graphics_PixelFormat format;
  LoveC_Texture_TextureType type;
  float dpiScale;
  int msaa;
  LoveC_OptionalBool readable;
} LoveC_Canvas_Settings;


LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_CANVAS_H
