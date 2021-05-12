#include "c_Image.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Image.h"

using namespace love;
using namespace love::graphics;


LoveC_Graphics_Image_SlicesRef love_Graphics_Image_Slices_construct(LoveC_Texture_TextureType type) {
  auto type_ = static_cast<TextureType>(type);

  auto slices = new Image::Slices(type_);
  return wrap<LoveC_Graphics_Image_SlicesRef>(slices);
}

void love_Graphics_Image_Slices_delete(LoveC_Graphics_Image_SlicesRef ref) {
  auto slices = unwrap<Image::Slices>(ref);
  delete slices;
}

void love_Graphics_Image_Slices_clear(LoveC_Graphics_Image_SlicesRef ref) {
  unwrap<Image::Slices>(ref)->clear();
}

void love_Graphics_Image_Slices_set(LoveC_Graphics_Image_SlicesRef ref, int slice, int mipmap, LoveC_Image_ImageDataBaseRef image) {
  auto slices = unwrap<Image::Slices>(ref);
  auto image_ = unwrap<image::ImageDataBase>(image);

  slices->set(slice, mipmap, image_);
}

LoveC_Image_ImageDataBaseRef love_Graphics_Image_Slices_get(LoveC_Graphics_Image_SlicesRef ref, int slice, int mipmap) {
  auto slices = unwrap<Image::Slices>(ref);

  auto image = slices->get(slice, mipmap);
  return wrap<LoveC_Image_ImageDataBaseRef>(image);
}

void love_Graphics_Image_Slices_add(LoveC_Graphics_Image_SlicesRef ref, LoveC_Image_CompressedImageDataRef cImageData, int startslice, int startmip, LoveC_Bool addallslices, LoveC_Bool addallmips) {
  auto slices = unwrap<Image::Slices>(ref);
  auto cImageData_ = unwrap<image::CompressedImageData>(cImageData);

  slices->add(cImageData_, startslice, startmip, addallslices, addallmips);
}

int love_Graphics_Image_Slices_getSliceCount(LoveC_Graphics_Image_SlicesRef ref) {
  return unwrap<Image::Slices>(ref)->getSliceCount();
}

int love_Graphics_Image_Slices_getMipmapCount(LoveC_Graphics_Image_SlicesRef ref) {
  return unwrap<Image::Slices>(ref)->getMipmapCount();
}

LoveC_Graphics_Image_MipmapsType love_Graphics_Image_Slices_validate(LoveC_Graphics_Image_SlicesRef ref) {
  auto type = unwrap<Image::Slices>(ref)->validate();
  return static_cast<LoveC_Graphics_Image_MipmapsType>(type);
}

LoveC_Texture_TextureType love_Graphics_Image_Slices_getTextureType(LoveC_Graphics_Image_SlicesRef ref) {
  auto type = unwrap<Image::Slices>(ref)->getTextureType();
  return static_cast<LoveC_Texture_TextureType>(type);
}


float love_Graphics_Image_getWidth(LoveC_Graphics_ImageRef ref) {
  return unwrap<Image>(ref)->getWidth();
}

float love_Graphics_Image_getHeight(LoveC_Graphics_ImageRef ref) {
  return unwrap<Image>(ref)->getHeight();
}
