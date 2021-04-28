#include "c_Font.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Font.h"

using namespace love;
using namespace love::graphics;


float love_graphics_Font_getHeight(LoveC_FontRef ref) {
  return unwrap<Font>(ref)->getHeight();
}

LoveC_Bool love_graphics_Font_getWidth(LoveC_FontRef ref, const char* str, float* outWidth, char** outError) {
  auto font = unwrap<Font>(ref);
  std::string str_(str);

  try {
   *outWidth = font->getWidth(str_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_Font_getWidth__glyph(LoveC_FontRef ref, LoveC_UInt32 glyph, float* outWidth, char** outError) {
  auto font = unwrap<Font>(ref);

  try {
   *outWidth = font->getWidth(glyph);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_Font_getWrap(LoveC_FontRef ref, const LoveC_Font_ColoredString** text, float wrap, int* outLineWidths, char** outLines, char** outError) {
  auto font = unwrap<Font>(ref);

  std::vector<Font::ColoredString> text_;
  std::vector<std::string> lines;
  std::vector<int> widths;

  for (int i = 0; text[i]; i++) {
    Font::ColoredString str;
    str.str = std::string(text[i]->str);
    str.color.r = text[i]->color.r;
    str.color.g = text[i]->color.g;
    str.color.b = text[i]->color.b;
    str.color.a = text[i]->color.a;
    text_.emplace_back(str);
  }

  try {
    font->getWrap(text_, wrap, lines, &widths);
  } catch(const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  outLineWidths = (int*)malloc(sizeof(int)*widths.size());

  for (int i = 0; i < (int) lines.size(); i++) {
    outLineWidths[i] = widths[i];
  }

  outLines = (char**)malloc(sizeof(char*)*lines.size());

  for (int i = 0; i < (int) lines.size(); i++) {
    outLines[i] = strdup(lines[i].c_str());
  }

  return true;
}

void love_graphics_Font_setLineHeight(LoveC_FontRef ref, float height) {
  unwrap<Font>(ref)->setLineHeight(height);
}

float love_graphics_Font_getLineHeight(LoveC_FontRef ref) {
  return unwrap<Font>(ref)->getLineHeight();
}

LoveC_Bool love_graphics_Font_setFilter(LoveC_FontRef ref, const LoveC_Texture_Filter* filter, char** outError) {
  auto font = unwrap<Font>(ref);

  Texture::Filter f = font->getFilter();
  f.min = static_cast<Texture::FilterMode>(filter->min);
  f.mag = static_cast<Texture::FilterMode>(filter->mag);
  f.anisotropy = filter->anisotropy;

  try {
    font->setFilter(f);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_graphics_Font_getFilter(LoveC_FontRef ref, LoveC_Texture_Filter* outFilter) {
  auto font = unwrap<Font>(ref);

  Texture::Filter f = font->getFilter();
  outFilter->min = static_cast<LoveC_Texture_FilterMode>(f.min);
  outFilter->mag = static_cast<LoveC_Texture_FilterMode>(f.mag);
  outFilter->anisotropy = f.anisotropy;
}

float love_graphics_Font_getAscent(LoveC_FontRef ref) {
  return unwrap<Font>(ref)->getAscent();
}

float love_graphics_Font_getDescent(LoveC_FontRef ref) {
  return unwrap<Font>(ref)->getDescent();
}

float love_graphics_Font_getBaseline(LoveC_FontRef ref) {
  return unwrap<Font>(ref)->getBaseline();
}

LoveC_Bool love_graphics_Font_hasGlyphs(LoveC_FontRef ref, const char* glyphs, LoveC_Bool* outHasGlyph, char** outError) {
  auto font = unwrap<Font>(ref);

  try {
    *outHasGlyph = font->hasGlyphs(glyphs);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_Font_hasGlyph(LoveC_FontRef ref, LoveC_UInt32 glyph, LoveC_Bool* outHasGlyph, char** outError) {
  auto font = unwrap<Font>(ref);

  try {
    *outHasGlyph = font->hasGlyph(glyph);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_Font_getKerning(LoveC_FontRef ref, const char* left, const char* right, float* outKerning, char** outError) {
  auto font = unwrap<Font>(ref);

  try {
    *outKerning = font->getKerning(left, right);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_Font_getKerning__glyph(LoveC_FontRef ref, LoveC_UInt32 left, LoveC_UInt32 right, float* outKerning, char** outError) {
  auto font = unwrap<Font>(ref);

  try {
    *outKerning = font->getKerning(left, right);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_Font_setFallbacks(LoveC_FontRef ref, LoveC_FontRef** fallbacks, char** outError) {
  auto font = unwrap<Font>(ref);
  std::vector<graphics::Font *> fallbacks_;

  for (int i = 0; fallbacks[i]; i++) {
    fallbacks_.push_back(unwrap<Font>(fallbacks[i]));
  }

  try {
    font->setFallbacks(fallbacks_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

float love_graphics_Font_getDPIScale(LoveC_FontRef ref) {
  return unwrap<Font>(ref)->getDPIScale();
}
