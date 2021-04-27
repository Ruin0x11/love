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

LOVE_EXPORT void love_graphics_reset(LoveC_GraphicsRef ref);
LOVE_EXPORT LoveC_Bool love_graphics_clear(LoveC_GraphicsRef ref, const LoveC_Colorf** colors, int stencilOpt, double depthOpt, char** outError);
LOVE_EXPORT void love_graphics_discard(LoveC_GraphicsRef ref, LoveC_Bool* colorbuffers, LoveC_Bool depthstencil);
LOVE_EXPORT void love_graphics_present(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_isCreated(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_isActive(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_isGammaCorrect(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getWidth(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getHeight(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getDimensions(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getPixelWidth(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getPixelHeight(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getPixelDimensions(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getDPIScale(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setCanvas(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getCanvas(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_captureScreenshot(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setScissor(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_intersectScissor(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getScissor(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_stencil(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setStencilTest(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getStencilTest(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics__optImageSettings(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics__pushNewImage(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newCubeImage(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newArrayImage(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newVolumeImage(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newImage(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newQuad(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newFont(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newImageFont(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newSpriteBatch(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newParticleSystem(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newCanvas(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getShaderSource(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newShader(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_validateShader(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newMesh(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newText(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_newVideo(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setColor(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getColor(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setBackgroundColor(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getBackgroundColor(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setNewFont(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setFont(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getFont(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setColorMask(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getColorMask(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setBlendMode(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getBlendMode(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setDefaultFilter(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getDefaultFilter(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setDefaultMipmapFilter(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getDefaultMipmapFilter(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setLineWidth(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setLineStyle(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setLineJoin(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getLineWidth(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getLineStyle(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getLineJoin(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setPointSize(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getPointSize(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setDepthMode(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getDepthMode(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setMeshCullMode(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getMeshCullMode(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setFrontFaceWinding(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getFrontFaceWinding(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setWireframe(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_isWireframe(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setShader(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getShader(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_setDefaultShaderCode(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getSupported(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics__getFormats(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getCanvasFormats(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getImageFormats(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getTextureTypes(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getRendererInfo(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getSystemLimits(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getStats(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_draw(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_drawLayer(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_drawInstanced(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_print(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_printf(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_points(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_line(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_rectangle(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_circle(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_ellipse(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_arc(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_polygon(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_flushBatch(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_getStackDepth(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_push(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_pop(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_rotate(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_scale(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_translate(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_shear(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_origin(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_applyTransform(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_replaceTransform(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_transformPoint(LoveC_GraphicsRef ref);
LOVE_EXPORT void love_graphics_inverseTransformPoint(LoveC_GraphicsRef ref);

LOVE_EXPORT LoveC_Bool love_graphics__setDefaultShaderCode(LoveC_GraphicsRef ref, LoveC_Shader_StandardShader std, LoveC_Shader_Language lang, LoveC_Bool isGammaCorrected, LoveC_ShaderStage_StageType stage, const char* code, char** outError);

LOVE_EXPORT LoveC_Bool love_graphics_registerModule(char** outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_GRAPHICS_H
