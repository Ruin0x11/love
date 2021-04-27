#ifndef LOVE_GRAPHICS_C_SHADER_H
#define LOVE_GRAPHICS_C_SHADER_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Module.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_ShaderHandle;
typedef struct LoveC_ShaderHandle* LoveC_ShaderRef;

typedef enum Language
  {
    LANGUAGE_GLSL1,
    LANGUAGE_ESSL1,
    LANGUAGE_GLSL3,
    LANGUAGE_ESSL3,
    LANGUAGE_MAX_ENUM
  } LoveC_Shader_Language;

typedef enum StandardShader
  {
    STANDARD_DEFAULT,
    STANDARD_VIDEO,
    STANDARD_ARRAY,
    STANDARD_MAX_ENUM
  } LoveC_Shader_StandardShader;


LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_SHADER_H
