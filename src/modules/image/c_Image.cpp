#include "c_Image.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "common/Data.h"
#include "modules/love_c/runtime_c.h"

#include "Image.h"

using namespace love;
using namespace love::image;

#define instance() (Module::getInstance<Image>(Module::M_IMAGE))


LoveC_Bool love_image_newImageData(int w, int h, LoveC_Graphics_PixelFormat format, LoveC_ImageDataRef* outImageData, char** outError) {
  auto format_ = static_cast<PixelFormat>(format);

  ImageData* t = nullptr;

  try {
    t = instance()->newImageData(w, h, format_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outImageData = wrap<LoveC_ImageDataRef>(t);

  return true;
}

LoveC_Bool love_image_newImageData__Data(LoveC_DataRef data, LoveC_ImageDataRef* outImageData, char** outError) {
  auto data_ = unwrap<Data>(data);

  ImageData* t = nullptr;

  try {
    t = instance()->newImageData(data_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outImageData = wrap<LoveC_ImageDataRef>(t);

  return true;
}

LoveC_Bool love_image_newCompressedData(LoveC_DataRef data, LoveC_CompressedDataRef* outCompressedData, char** outError) {
  auto data_ = unwrap<Data>(data);

  CompressedImageData *t = nullptr;

  try {
    t = instance()->newCompressedData(data_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outCompressedData = wrap<LoveC_CompressedDataRef>(t);

  return true;
}

LoveC_Bool love_image_isCompressed(LoveC_DataRef data) {
  auto data_ = unwrap<Data>(data);

  return instance()->isCompressed(data_);
}

LoveC_Bool love_image_newCubeFaces(LoveC_ImageDataRef imageData, LoveC_ImageDataRef** outFaces, LoveC_Int64* outSize, char** outError) {
  auto imageData_ = unwrap<ImageData>(imageData);

  std::vector<StrongRef<ImageData>> faces;

  try {
    faces = instance()->newCubeFaces(imageData_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  int i;
  for (i = 0; faces[i]; i++) {
    *outFaces[i] = wrap<LoveC_ImageDataRef>(faces[i].get());
  }

  return true;
}


LoveC_Bool love_image_registerModule(char** outError) {
  Image *instance = instance();
  if (instance == nullptr) {
    try {
      instance = new image::Image();
    } catch (const std::exception &e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  WrappedModule w;
  w.module = instance;
  w.name = "image";
  w.type = &Image::type;
  w.functions = nullptr;
  w.types = nullptr;

  return love_c::register_module(w, outError);
}
