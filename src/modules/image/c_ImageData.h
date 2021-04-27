#ifndef LOVE_IMAGE_C_IMAGEDATA_H
#define LOVE_IMAGE_C_IMAGEDATA_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/filesystem/c_FileData.h"
#include "modules/graphics/c_PixelFormat.h"
#include "modules/image/c_CompressedData.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_ImageDataHandle;
typedef struct LoveC_ImageDataHandle* LoveC_ImageDataRef;

typedef enum LoveC_ImageData_EncodedFormat
  {
    ENCODED_TGA,
    ENCODED_PNG,
    ENCODED_MAX_ENUM
  } LoveC_ImageData_EncodedFormat;

LOVE_EXPORT LoveC_Graphics_PixelFormat love_image_ImageData_getFormat(LoveC_ImageDataRef ref);
LOVE_EXPORT int love_image_ImageData_getWidth(LoveC_ImageDataRef ref);
LOVE_EXPORT int love_image_ImageData_getHeight(LoveC_ImageDataRef ref);
LOVE_EXPORT LoveC_Bool love_image_ImageData_getPixel(LoveC_ImageDataRef ref, int x, int y, LoveC_Colorf* outColor, char** outError);
LOVE_EXPORT LoveC_Bool love_image_ImageData_setPixel(LoveC_ImageDataRef ref, int x, int y, const LoveC_Colorf* color, char** outError);
LOVE_EXPORT void love_image_ImageData_paste(LoveC_ImageDataRef ref, LoveC_ImageDataRef src, int dx, int dy, int sx, int sy, int sw, int sh);
LOVE_EXPORT LoveC_Bool love_image_ImageData_encode(LoveC_ImageDataRef ref, LoveC_ImageData_EncodedFormat format, const char* filename, LoveC_Bool hasfilename, LoveC_FileDataRef* outFileData, char** outError);


LOVE_C_EXTERN_C_END

#endif // LOVE_IMAGE_C_IMAGEDATA_H
