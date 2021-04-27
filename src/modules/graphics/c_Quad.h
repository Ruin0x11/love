#ifndef LOVE_GRAPHICS_C_QUAD_H
#define LOVE_GRAPHICS_C_QUAD_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_QuadHandle;
typedef struct LoveC_QuadHandle* LoveC_QuadRef;

typedef struct LoveC_Quad_Viewport
{
  double x, y;
  double w, h;
} LoveC_Quad_Viewport;


LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_QUAD_H
