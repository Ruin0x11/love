#include "c_Rasterizer.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Rasterizer.h"

using namespace love;
using namespace love::font;


float love_font_Rasterizer_getHeight(LoveC_Font_RasterizerRef ref) {
  return unwrap<Rasterizer>(ref)->getHeight();
}

float love_font_Rasterizer_getAdvance(LoveC_Font_RasterizerRef ref) {
  return unwrap<Rasterizer>(ref)->getAdvance();
}

float love_font_Rasterizer_getAscent(LoveC_Font_RasterizerRef ref) {
  return unwrap<Rasterizer>(ref)->getAdvance();
}

float love_font_Rasterizer_getDescent(LoveC_Font_RasterizerRef ref) {
  return unwrap<Rasterizer>(ref)->getDescent();
}

float love_font_Rasterizer_getLineHeight(LoveC_Font_RasterizerRef ref) {
  return unwrap<Rasterizer>(ref)->getDescent();
}

LoveC_Bool love_font_Rasterizer_getGlyphData(LoveC_Font_RasterizerRef ref, LoveC_UInt32 codepoint, LoveC_Font_GlyphDataRef* outGlyphData, char** outError) {
  auto rasterizer = unwrap<Rasterizer>(ref);

  GlyphData* t = nullptr;

  try {
    t = rasterizer->getGlyphData(codepoint);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outGlyphData = wrap<LoveC_Font_GlyphDataRef>(t);

  return true;
}

int love_font_Rasterizer_getGlyphCount(LoveC_Font_RasterizerRef ref) {
  return unwrap<Rasterizer>(ref)->getGlyphCount();
}

LoveC_Bool love_font_Rasterizer_hasGlyphs(LoveC_Font_RasterizerRef ref, const char* glyphs, LoveC_Bool* outHasGlyph, char** outError) {
  auto rasterizer = unwrap<Rasterizer>(ref);

  try {
    *outHasGlyph = rasterizer->hasGlyphs(glyphs);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_font_Rasterizer_hasGlyph(LoveC_Font_RasterizerRef ref, LoveC_UInt32 glyph, LoveC_Bool* outHasGlyph, char** outError) {
  auto rasterizer = unwrap<Rasterizer>(ref);

  try {
    *outHasGlyph = rasterizer->hasGlyph(glyph);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}
