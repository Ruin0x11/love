#ifndef LOVE_GRAPHICS_C_FONT_H
#define LOVE_GRAPHICS_C_FONT_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

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


LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_FONT_H
