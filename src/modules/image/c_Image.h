#ifndef LOVE_IMAGE_C_IMAGE_H
#define LOVE_IMAGE_C_IMAGE_H

#include "c_ImageData.h"
#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Module.h"
#include "modules/love_c/c_Data.h"

LOVE_C_EXTERN_C_BEGIN

LOVE_EXPORT LoveC_Bool love_image_newImageData(int w, int h, LoveC_Graphics_PixelFormat format, LoveC_Image_ImageDataRef* outImageData, char** outError);
LOVE_EXPORT LoveC_Bool love_image_newImageData__Data(LoveC_DataRef data, LoveC_Image_ImageDataRef* outImageData, char** outError);
LOVE_EXPORT LoveC_Bool love_image_newCompressedData(LoveC_DataRef data, LoveC_CompressedDataRef* outCompressedData, char** outError);
LOVE_EXPORT LoveC_Bool love_image_isCompressed(LoveC_DataRef data);
LOVE_EXPORT LoveC_Bool love_image_newCubeFaces(LoveC_Image_ImageDataRef imageData, LoveC_Image_ImageDataRef** outFaces, LoveC_Int64* outSize, char** outError);

LOVE_EXPORT LoveC_Bool love_image_registerModule(char** outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_IMAGE_C_IMAGE_H
