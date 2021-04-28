#ifndef LOVE_GRAPHICS_C_FONT_H
#define LOVE_GRAPHICS_C_FONT_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "c_Texture.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_FontHandle;
typedef struct LoveC_FontHandle* LoveC_FontRef;

typedef enum LoveC_Font_AlignMode
  {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT,
    ALIGN_JUSTIFY,
    ALIGN_MAX_ENUM
  } LoveC_Font_AlignMode;

typedef struct LoveC_Font_ColoredString
{
  char* str;
  LoveC_Colorf color;
} LoveC_Font_ColoredString;

LOVE_EXPORT float love_graphics_Font_getHeight(LoveC_FontRef ref);
LOVE_EXPORT LoveC_Bool love_graphics_Font_getWidth(LoveC_FontRef ref, const char* str, float* outWidth, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_Font_getWidth__glyph(LoveC_FontRef ref, LoveC_UInt32 glyph, float* outWidth, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_Font_getWrap(LoveC_FontRef ref, const LoveC_Font_ColoredString** text, float wrap, int* outLineWidths, char** outLines, char** outError);
LOVE_EXPORT void love_graphics_Font_setLineHeight(LoveC_FontRef ref, float height);
LOVE_EXPORT float love_graphics_Font_getLineHeight(LoveC_FontRef ref);
LOVE_EXPORT LoveC_Bool love_graphics_Font_setFilter(LoveC_FontRef ref, const LoveC_Texture_Filter* filter, char** outError);
LOVE_EXPORT void love_graphics_Font_getFilter(LoveC_FontRef ref, LoveC_Texture_Filter* outFilter);
LOVE_EXPORT float love_graphics_Font_getAscent(LoveC_FontRef ref);
LOVE_EXPORT float love_graphics_Font_getDescent(LoveC_FontRef ref);
LOVE_EXPORT float love_graphics_Font_getBaseline(LoveC_FontRef ref);
LOVE_EXPORT LoveC_Bool love_graphics_Font_hasGlyphs(LoveC_FontRef ref, const char* glyphs, LoveC_Bool* outHasGlyph, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_Font_hasGlyph(LoveC_FontRef ref, LoveC_UInt32 glyph, LoveC_Bool* outHasGlyph, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_Font_getKerning(LoveC_FontRef ref, const char* left, const char* right, float* outKerning, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_Font_getKerning__glyph(LoveC_FontRef ref, LoveC_UInt32 left, LoveC_UInt32 right, float* outKerning, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_Font_setFallbacks(LoveC_FontRef ref, LoveC_FontRef** fallbacks, char** outError);
LOVE_EXPORT float love_graphics_Font_getDPIScale(LoveC_FontRef ref);


LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_FONT_H
