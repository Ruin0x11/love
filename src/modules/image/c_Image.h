#ifndef LOVE_IMAGE_C_IMAGE_H
#define LOVE_IMAGE_C_IMAGE_H

#include "c_ImageData.h"
#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Module.h"
#include "modules/love_c/c_Data.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_ImageHandle;
typedef struct LoveC_ImageHandle* LoveC_ImageRef;

LOVE_EXPORT LoveC_ImageRef love_image_getInstance();

LOVE_EXPORT LoveC_Bool love_image_newImageData(LoveC_ImageRef ref, int w, int h, LoveC_Graphics_PixelFormat format, LoveC_ImageDataRef* outImageData, char** outError);
LOVE_EXPORT LoveC_Bool love_image_newImageData__Data(LoveC_ImageRef ref, LoveC_DataRef data, LoveC_ImageDataRef* outImageData, char** outError);
LOVE_EXPORT LoveC_Bool love_image_newCompressedData(LoveC_ImageRef ref, LoveC_DataRef data, LoveC_CompressedDataRef* outCompressedData, char** outError);
LOVE_EXPORT LoveC_Bool love_image_isCompressed(LoveC_ImageRef ref, LoveC_DataRef data);
LOVE_EXPORT LoveC_Bool love_image_newCubeFaces(LoveC_ImageRef ref, LoveC_ImageDataRef imageData, LoveC_ImageDataRef** outFaces, LoveC_Int64* outSize, char** outError);

LOVE_EXPORT LoveC_Bool love_image_registerModule(char** outError);


LOVE_C_EXTERN_C_END

#endif // LOVE_IMAGE_C_IMAGE_H
