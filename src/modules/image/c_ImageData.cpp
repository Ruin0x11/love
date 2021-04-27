#include "c_ImageData.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "ImageData.h"

using namespace love;
using namespace love::image;


LoveC_Graphics_PixelFormat love_image_ImageData_getFormat(LoveC_ImageDataRef ref) {
  auto format = unwrap<ImageData>(ref)->getFormat();
  return static_cast<LoveC_Graphics_PixelFormat>();
}

int love_image_ImageData_getWidth(LoveC_ImageDataRef ref) {
  return unwrap<ImageData>(ref)->getWidth();
}

int love_image_ImageData_getHeight(LoveC_ImageDataRef ref) {
  return unwrap<ImageData>(ref)->getHeight();
}

LoveC_Bool love_image_ImageData_getPixel(LoveC_ImageDataRef ref, int x, int y, LoveC_Colorf* outColor, char** outError) {
  auto imageData = unwrap<ImageData>(ref);
  auto color_ = unwrap<Colorf>(outColor);

  try {
    imageData->getPixel(x, y, *color_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_image_ImageData_setPixel(LoveC_ImageDataRef ref, int x, int y, const LoveC_Colorf* color, char** outError) {
  auto imageData = unwrap<ImageData>(ref);
  auto color_ = unwrap<const Colorf>(outColor);

  try {
    imageData->setPixel(x, y, *color_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_image_ImageData_paste(LoveC_ImageDataRef ref, LoveC_ImageDataRef src, int dx, int dy, int sx, int sy, int sw, int sh) {
  auto imageData = unwrap<ImageData>(ref);
  auto src_ = unwrap<ImageData>(src);

  ref->paste(imageData, dx, dy, sx, sy, sw, sh);
}

void love_image_ImageData_encode(LoveC_ImageDataRef ref, LoveC_ImageData_EncodedFormat format, const char* filename, LoveC_Bool hasfilename, LoveC_FileDataRef* outFileData) {
  auto imageData = unwrap<ImageData>(ref);
  auto format_ = static_cast<FormatHandler::EncodedFormat>(format);

  love::filesystem::FileData *filedata = nullptr;

  try {
    filedata = imageData->encode(format, filename, hasfilename);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}
