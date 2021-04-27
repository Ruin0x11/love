#ifndef LOVE_GRAPHICS_C_GRAPHICS_H
#define LOVE_GRAPHICS_C_GRAPHICS_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Module.h"
#include "c_Shader.h"
#include "c_ShaderStage.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_GraphicsHandle;
typedef struct LoveC_GraphicsHandle* LoveC_GraphicsRef;

LOVE_EXPORT LoveC_GraphicsRef love_graphics_getInstance();

/* LOVE_EXPORT int love_graphics_getDisplayCount(LoveC_GraphicsRef ref); */
/* LOVE_EXPORT LoveC_Bool love_graphics_getDisplayName(LoveC_GraphicsRef ref, int index, const char** outDisplayName, char** outError); */
/* LOVE_EXPORT LoveC_Bool love_graphics_setMode(LoveC_GraphicsRef ref, int width, int height, const LoveC_Graphics_GraphicsSettings* settingsOpt, char** outError); */

LOVE_EXPORT LoveC_Bool love_graphics__setDefaultShaderCode(LoveC_GraphicsRef ref, LoveC_Shader_StandardShader std, LoveC_Shader_Language lang, LoveC_Bool isGammaCorrected, LoveC_ShaderStage_StageType stage, const char* code, char** outError);

LOVE_EXPORT LoveC_Bool love_graphics_registerModule(char** outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_GRAPHICS_H
