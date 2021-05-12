#include "c_Canvas.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Canvas.h"

using namespace love;
using namespace love::graphics;


int LoveC_Canvas_getMSAA(LoveC_CanvasRef ref) {
  return unwrap<Canvas>(ref)->getMSAA();
}

LoveC_Bool LoveC_Canvas_newImageData(LoveC_CanvasRef ref, int slice, int mipmap, LoveC_Rect* rect, LoveC_Image_ImageDataRef* outImageData, char** outError) {
  auto canvas = unwrap<Canvas>(ref);
  auto image_ = Module::getInstance<image::Image>(Module::M_IMAGE);
  auto rect_ = unwrap<Rect>(rect);

  love::image::ImageData* img = nullptr;

  try {
    img = canvas->newImageData(image_, slice, mipmap, *rect_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outImageData = wrap<LoveC_Image_ImageDataRef>(img);

  return true;
}

LoveC_Bool LoveC_Canvas_generateMipmaps(LoveC_CanvasRef ref, char** outError) {
  try {
    unwrap<Canvas>(ref)->generateMipmaps();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Canvas_MipmapMode LoveC_Canvas_getMipmapMode(LoveC_CanvasRef ref) {
  auto mode = unwrap<Canvas>(ref)->getMipmapMode();
  return static_cast<LoveC_Canvas_MipmapMode>(mode);
}
