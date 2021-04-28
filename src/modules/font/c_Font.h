#ifndef LOVE_FONT_C_FONT_H
#define LOVE_FONT_C_FONT_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Module.h"
#include "modules/filesystem/c_FileData.h"
#include "modules/image/c_ImageData.h"
#include "c_Rasterizer.h"
#include "c_GlyphData.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_Module_FontHandle;
typedef struct LoveC_Module_FontHandle* LoveC_Module_FontRef;

LOVE_EXPORT LoveC_Module_FontRef love_font_getInstance();

LOVE_EXPORT LoveC_Bool love_font_newRasterizer(LoveC_Module_FontRef ref, LoveC_FileDataRef fileData, LoveC_Font_RasterizerRef* outRasterizer, char** outError);
LOVE_EXPORT LoveC_Bool love_font_newTrueTypeRasterizer(LoveC_Module_FontRef ref, LoveC_FileDataRef fileData, int size, float dpiscale, LoveC_Font_TrueTypeRasterizer_Hinting hinting, LoveC_Font_RasterizerRef* outRasterizer, char** outError);
LOVE_EXPORT LoveC_Bool love_font_newBMFontRasterizer(LoveC_Module_FontRef ref, LoveC_FileDataRef fileData, LoveC_ImageDataRef** images, float dpiscale, LoveC_Font_RasterizerRef* outRasterizer, char** outError);
LOVE_EXPORT LoveC_Bool love_font_newImageRasterizer(LoveC_Module_FontRef ref, LoveC_ImageDataRef imageData, const char* glyphs, int extraspacing, float dpiscale, LoveC_Font_RasterizerRef* outRasterizer, char** outError);
LOVE_EXPORT LoveC_Bool love_font_newGlyphData(LoveC_Module_FontRef ref, LoveC_Font_RasterizerRef rasterizer, LoveC_UInt32 codepoint, LoveC_Font_GlyphDataRef* outGlyphData, char** outError);

LOVE_EXPORT LoveC_Bool love_font_registerModule(char** outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_FONT_C_FONT_H
