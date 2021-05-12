#ifndef LOVE_GRAPHICS_C_IMAGE_H
#define LOVE_GRAPHICS_C_IMAGE_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "c_Texture.h"
#include "image/c_ImageDataBase.h"
#include "image/c_CompressedImageData.h"

LOVE_C_EXTERN_C_BEGIN

LOVE_C_DEFINE_OPAQUE_TYPE(Graphics_Image);
LOVE_C_DEFINE_OPAQUE_TYPE(Graphics_Image_Slices);

typedef enum LoveC_Graphics_Image_MipmapsType {
  IMAGE_MIPMAPS_NONE,
  IMAGE_MIPMAPS_DATA,
  IMAGE_MIPMAPS_GENERATED,
} LoveC_Graphics_Image_MipmapsType;

typedef struct LoveC_Graphics_Image_Settings {
  LoveC_Bool mipmaps;
  LoveC_Bool linear;
  float dpiScale;
} LoveC_Graphics_Image_Settings;

LOVE_EXPORT LoveC_Graphics_Image_SlicesRef love_Graphics_Image_Slices_construct(LoveC_Texture_TextureType type);
LOVE_EXPORT void love_Graphics_Image_Slices_delete(LoveC_Graphics_Image_SlicesRef ref);
LOVE_EXPORT void love_Graphics_Image_Slices_clear(LoveC_Graphics_Image_SlicesRef ref);
LOVE_EXPORT void love_Graphics_Image_Slices_set(LoveC_Graphics_Image_SlicesRef ref, int slice, int mipmap, LoveC_Image_ImageDataBaseRef image);
LOVE_EXPORT LoveC_Image_ImageDataBaseRef love_Graphics_Image_Slices_get(LoveC_Graphics_Image_SlicesRef ref, int slice, int mipmap);
LOVE_EXPORT void love_Graphics_Image_Slices_add(LoveC_Graphics_Image_SlicesRef ref, LoveC_Image_CompressedImageDataRef cImageData, int startslice, int startmip, LoveC_Bool addallslices, LoveC_Bool addallmips);
LOVE_EXPORT int love_Graphics_Image_Slices_getSliceCount(LoveC_Graphics_Image_SlicesRef ref);
LOVE_EXPORT int love_Graphics_Image_Slices_getMipmapCount(LoveC_Graphics_Image_SlicesRef ref);
LOVE_EXPORT LoveC_Graphics_Image_MipmapsType love_Graphics_Image_Slices_validate(LoveC_Graphics_Image_SlicesRef ref);
LOVE_EXPORT LoveC_Texture_TextureType love_Graphics_Image_Slices_getTextureType(LoveC_Graphics_Image_SlicesRef ref);

LOVE_EXPORT float love_Graphics_Image_getWidth(LoveC_Graphics_ImageRef ref);
LOVE_EXPORT float love_Graphics_Image_getHeight(LoveC_Graphics_ImageRef ref);

LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_IMAGE_H
