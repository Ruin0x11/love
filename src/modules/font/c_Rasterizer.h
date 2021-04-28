#ifndef LOVE_FONT_C_RASTERIZER_H
#define LOVE_FONT_C_RASTERIZER_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "c_GlyphData.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_Font_RasterizerHandle;
typedef struct LoveC_Font_RasterizerHandle* LoveC_Font_RasterizerRef;


typedef enum LoveC_Font_TrueTypeRasterizer_Hinting
  {
    HINTING_NORMAL,
    HINTING_LIGHT,
    HINTING_MONO,
    HINTING_NONE,
    HINTING_MAX_ENUM
  } LoveC_Font_TrueTypeRasterizer_Hinting;

LOVE_EXPORT float love_font_Rasterizer_getHeight(LoveC_Font_RasterizerRef ref);
LOVE_EXPORT float love_font_Rasterizer_getAdvance(LoveC_Font_RasterizerRef ref);
LOVE_EXPORT float love_font_Rasterizer_getAscent(LoveC_Font_RasterizerRef ref);
LOVE_EXPORT float love_font_Rasterizer_getDescent(LoveC_Font_RasterizerRef ref);
LOVE_EXPORT float love_font_Rasterizer_getLineHeight(LoveC_Font_RasterizerRef ref);
LOVE_EXPORT LoveC_Bool love_font_Rasterizer_getGlyphData(LoveC_Font_RasterizerRef ref, LoveC_UInt32 codepoint, LoveC_Font_GlyphDataRef* outGlyphData, char** outError);
LOVE_EXPORT int love_font_Rasterizer_getGlyphCount(LoveC_Font_RasterizerRef ref);
LOVE_EXPORT LoveC_Bool love_font_Rasterizer_hasGlyphs(LoveC_Font_RasterizerRef ref, const char* glyphs, LoveC_Bool* outHasGlyph, char** outError);
LOVE_EXPORT LoveC_Bool love_font_Rasterizer_hasGlyph(LoveC_Font_RasterizerRef ref, LoveC_UInt32 glyph, LoveC_Bool* outHasGlyph, char** outError);


LOVE_C_EXTERN_C_END

#endif // LOVE_FONT_C_RASTERIZER_H
