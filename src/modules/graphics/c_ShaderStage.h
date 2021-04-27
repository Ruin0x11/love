#ifndef LOVE_GRAPHICS_C_SHADERSTAGE_H
#define LOVE_GRAPHICS_C_SHADERSTAGE_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN


typedef enum LoveC_ShaderStage_StageType
{
    STAGE_VERTEX,
    STAGE_PIXEL,
    STAGE_MAX_ENUM
} LoveC_ShaderStage_StageType;


LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_SHADERSTAGE_H
