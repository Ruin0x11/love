#include "c_Font.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Font.h"
#include "modules/filesystem/FileData.h"

#include "freetype/Font.h"

using namespace love;
using namespace love::font;

#define instance() (Module::getInstance<Font>(Module::M_FONT))


LoveC_Bool love_font_newRasterizer(LoveC_FileDataRef fileData, LoveC_Font_RasterizerRef* outRasterizer, char** outError) {
  auto fileData_ = unwrap<filesystem::FileData>(fileData);

  Rasterizer* t = nullptr;

  try {
    t = instance()->newRasterizer(fileData_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outRasterizer = wrap<LoveC_Font_RasterizerRef>(t);

  return true;
}

LoveC_Bool love_font_newTrueTypeRasterizer(LoveC_FileDataRef fileData, int size, float dpiscale, LoveC_Font_TrueTypeRasterizer_Hinting hinting, LoveC_Font_RasterizerRef* outRasterizer, char** outError) {
  auto fileData_ = unwrap<filesystem::FileData>(fileData);
  auto hinting_ = static_cast<TrueTypeRasterizer::Hinting>(hinting);

  Rasterizer* t = nullptr;

  try {
    t = instance()->newTrueTypeRasterizer(fileData_, size, dpiscale, hinting_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outRasterizer = wrap<LoveC_Font_RasterizerRef>(t);

  return true;
}

LoveC_Bool love_font_newBMFontRasterizer(LoveC_FileDataRef fileData, LoveC_ImageDataRef** images, float dpiscale, LoveC_Font_RasterizerRef* outRasterizer, char** outError) {
  auto fileData_ = unwrap<filesystem::FileData>(fileData);
  std::vector<image::ImageData *> images_;

  for (int i = 0; images[i]; i++) {
    images_.push_back(unwrap<image::ImageData>(images[i]));
  }

  Rasterizer* t = nullptr;

  try {
    t = instance()->newBMFontRasterizer(fileData_, images_, dpiscale);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outRasterizer = wrap<LoveC_Font_RasterizerRef>(t);

  return true;
}

LoveC_Bool love_font_newImageRasterizer(LoveC_ImageDataRef imageData, const char* glyphs, int extraspacing, float dpiscale, LoveC_Font_RasterizerRef* outRasterizer, char** outError) {
  auto imageData_ = unwrap<image::ImageData>(imageData);

  Rasterizer* t = nullptr;

  try {
    t = instance()->newImageRasterizer(imageData_, glyphs, extraspacing, dpiscale);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outRasterizer = wrap<LoveC_Font_RasterizerRef>(t);

  return true;
}

LoveC_Bool love_font_newGlyphData(LoveC_Font_RasterizerRef rasterizer, LoveC_UInt32 codepoint, LoveC_Font_GlyphDataRef* outGlyphData, char** outError) {
  auto rasterizer_ = unwrap<Rasterizer>(rasterizer);

  GlyphData* t = nullptr;

  try {
    t = instance()->newGlyphData(rasterizer_, codepoint);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outGlyphData = wrap<LoveC_Font_GlyphDataRef>(t);

  return true;
}

LoveC_Bool love_font_registerModule(char** outError) {
  Font *instance = instance();
  if (instance == nullptr) {
    try {
      instance = new freetype::Font();
    } catch (const std::exception &e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  WrappedModule w;
  w.module = instance;
  w.name = "font";
  w.type = &Font::type;
  w.functions = nullptr;
  w.types = nullptr;

  return love_c::register_module(w, outError);
}
