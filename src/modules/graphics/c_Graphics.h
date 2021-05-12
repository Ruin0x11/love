#ifndef LOVE_GRAPHICS_C_GRAPHICS_H
#define LOVE_GRAPHICS_C_GRAPHICS_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Module.h"
#include "modules/love_c/c_Matrix.h"
#include "c_Canvas.h"
#include "c_Font.h"
#include "c_Image.h"
#include "c_Mesh.h"
#include "c_ParticleSystem.h"
#include "c_Quad.h"
#include "c_Shader.h"
#include "c_ShaderStage.h"
#include "c_SpriteBatch.h"
#include "c_Texture.h"
#include "modules/font/c_Rasterizer.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_DrawableHandle;
typedef struct LoveC_DrawableHandle* LoveC_DrawableRef;

	typedef enum LoveC_Graphics_DrawMode
	{
		DRAW_LINE,
		DRAW_FILL,
		DRAW_MAX_ENUM
	} LoveC_Graphics_DrawMode;

	typedef enum LoveC_Graphics_ArcMode
	{
		ARC_OPEN,
		ARC_CLOSED,
		ARC_PIE,
		ARC_MAX_ENUM
	} LoveC_Graphics_ArcMode;

	typedef enum LoveC_Graphics_BlendMode
	{
		BLEND_ALPHA,
		BLEND_ADD,
		BLEND_SUBTRACT,
		BLEND_MULTIPLY,
		BLEND_LIGHTEN,
		BLEND_DARKEN,
		BLEND_SCREEN,
		BLEND_REPLACE,
		BLEND_NONE,
		BLEND_MAX_ENUM
	} LoveC_Graphics_BlendMode;

	typedef enum LoveC_Graphics_BlendAlpha
	{
		BLENDALPHA_MULTIPLY,
		BLENDALPHA_PREMULTIPLIED,
		BLENDALPHA_MAX_ENUM
	} LoveC_Graphics_BlendAlpha;

	typedef enum LoveC_Graphics_LineStyle
	{
		LINE_ROUGH,
		LINE_SMOOTH,
		LINE_MAX_ENUM
	} LoveC_Graphics_LineStyle;

	typedef enum LoveC_Graphics_LineJoin
	{
		LINE_JOIN_NONE,
		LINE_JOIN_MITER,
		LINE_JOIN_BEVEL,
		LINE_JOIN_MAX_ENUM
	} LoveC_Graphics_LineJoin;

	typedef enum LoveC_Graphics_Feature
	{
		FEATURE_MULTI_CANVAS_FORMATS,
		FEATURE_CLAMP_ZERO,
		FEATURE_LIGHTEN,
		FEATURE_FULL_NPOT,
		FEATURE_PIXEL_SHADER_HIGHP,
		FEATURE_SHADER_DERIVATIVES,
		FEATURE_GLSL3,
		FEATURE_INSTANCING,
		FEATURE_MAX_ENUM
	} LoveC_Graphics_Feature;

	typedef enum LoveC_Graphics_Renderer
	{
		RENDERER_OPENGL = 0,
		RENDERER_OPENGLES,
		RENDERER_MAX_ENUM
	} LoveC_Graphics_Renderer;

	typedef enum LoveC_Graphics_SystemLimit
	{
		LIMIT_POINT_SIZE,
		LIMIT_TEXTURE_SIZE,
		LIMIT_VOLUME_TEXTURE_SIZE,
		LIMIT_CUBE_TEXTURE_SIZE,
		LIMIT_TEXTURE_LAYERS,
		LIMIT_MULTI_CANVAS,
		LIMIT_CANVAS_MSAA,
		LIMIT_ANISOTROPY,
		LIMIT_MAX_ENUM
	} LoveC_Graphics_SystemLimit;

	typedef enum LoveC_Graphics_StackType
	{
		STACK_ALL,
		STACK_TRANSFORM,
		STACK_MAX_ENUM
	} LoveC_Graphics_StackType;

typedef struct LoveC_Graphics_RenderTarget {
  LoveC_CanvasRef canvas;
  int slice;
  int mipmap;
} LoveC_Graphics_RenderTarget;

typedef struct LoveC_Graphics_RenderTargets {
  LoveC_Graphics_RenderTarget** colors;
  LoveC_Graphics_RenderTarget* depthStencil;
  LoveC_UInt32 temporaryRTFlags;
} LoveC_Graphics_RenderTargets;

typedef struct LoveC_Graphics_ColorMask {
  LoveC_Bool r;
  LoveC_Bool g;
  LoveC_Bool b;
  LoveC_Bool a;
} LoveC_Graphics_ColorMask;

typedef enum LoveC_Graphics_StencilAction
  {
    STENCIL_REPLACE,
    STENCIL_INCREMENT,
    STENCIL_DECREMENT,
    STENCIL_INCREMENT_WRAP,
    STENCIL_DECREMENT_WRAP,
    STENCIL_INVERT,
    STENCIL_MAX_ENUM
  } LoveC_Graphics_StencilAction;

typedef enum LoveC_Graphics_CompareMode
  {
    COMPARE_LESS,
    COMPARE_LEQUAL,
    COMPARE_EQUAL,
    COMPARE_GEQUAL,
    COMPARE_GREATER,
    COMPARE_NOTEQUAL,
    COMPARE_ALWAYS,
    COMPARE_NEVER,
    COMPARE_MAX_ENUM
  } LoveC_Graphics_CompareMode;


// http://escience.anu.edu.au/lecture/cg/surfaceModeling/image/surfaceModeling015.png
typedef enum LoveC_Graphics_PrimitiveType
{
	PRIMITIVE_TRIANGLES,
	PRIMITIVE_TRIANGLE_STRIP,
	PRIMITIVE_TRIANGLE_FAN,
	PRIMITIVE_POINTS,
	PRIMITIVE_MAX_ENUM
} LoveC_Graphics_PrimitiveType;

typedef enum LoveC_Graphics_AttributeStep
{
	STEP_PER_VERTEX,
	STEP_PER_INSTANCE,
	STEP_MAX_ENUM
} LoveC_Graphics_AttributeStep;

typedef enum LoveC_Graphics_CullMode
{
	CULL_NONE,
	CULL_BACK,
	CULL_FRONT,
	CULL_MAX_ENUM
} LoveC_Graphics_CullMode;

typedef enum LoveC_Graphics_Vertex_Usage
  {
    USAGE_STREAM,
    USAGE_DYNAMIC,
    USAGE_STATIC,
    USAGE_MAX_ENUM
  } LoveC_Graphics_Vertex_Usage;

typedef enum LoveC_Graphics_DataType
{
	DATA_UNORM8,
	DATA_UNORM16,
	DATA_FLOAT,
	DATA_MAX_ENUM
} LoveC_Graphics_DataType;

typedef enum LoveC_Graphics_Vertex_Winding
  {
	WINDING_CW,
	WINDING_CCW,
	WINDING_MAX_ENUM
  } LoveC_Graphics_Vertex_Winding;

typedef struct LoveC_Graphics_Capabilities
{
  double limits[LIMIT_MAX_ENUM];
  LoveC_Bool features[FEATURE_MAX_ENUM];
  LoveC_Bool textureTypes[TEXTURE_MAX_ENUM];
} LoveC_Graphics_Capabilities;

typedef struct LoveC_Graphics_RendererInfo
{
  char* name;
  char* version;
  char* vendor;
  char* device;
} LoveC_Graphics_RendererInfo;

typedef struct LoveC_Graphics_Stats
{
  int drawCalls;
  int drawCallsBatched;
  int canvasSwitches;
  int shaderSwitches;
  int canvases;
  int images;
  int fonts;
  LoveC_Int64 textureMemory;
} LoveC_Graphics_Stats;

/* LOVE_EXPORT int love_graphics_getDisplayCount(); */
/* LOVE_EXPORT LoveC_Bool love_graphics_getDisplayName(int index, const char** outDisplayName, char** outError); */
/* LOVE_EXPORT LoveC_Bool love_graphics_setMode(int width, int height, const LoveC_Graphics_GraphicsSettings* settingsOpt, char** outError); */

LOVE_EXPORT void love_graphics_reset();
LOVE_EXPORT LoveC_Bool love_graphics_clear(const LoveC_Colorf* colors, LoveC_SizeT colorsLength, int stencilOpt, double depthOpt, char** outError);
LOVE_EXPORT void love_graphics_discard(LoveC_Bool* colorbuffers, LoveC_Bool depthstencil);
LOVE_EXPORT LoveC_Bool love_graphics_present(char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_isCreated();
LOVE_EXPORT LoveC_Bool love_graphics_isActive();
LOVE_EXPORT LoveC_Bool love_graphics_isGammaCorrect();
LOVE_EXPORT int love_graphics_getWidth();
LOVE_EXPORT int love_graphics_getHeight();
LOVE_EXPORT int love_graphics_getPixelWidth();
LOVE_EXPORT int love_graphics_getPixelHeight();
LOVE_EXPORT float love_graphics_getDPIScale();
LOVE_EXPORT LoveC_Bool love_graphics_setCanvas(LoveC_Graphics_RenderTargets *targetsOpt, char** outError);
LOVE_EXPORT void love_graphics_getCanvas(LoveC_Graphics_RenderTargets *outTargets);
/* LOVE_EXPORT void love_graphics_captureScreenshot(); */
LOVE_EXPORT void love_graphics_setScissor(const LoveC_Rect* rect);
LOVE_EXPORT void love_graphics_setScissor__clear();
LOVE_EXPORT void love_graphics_intersectScissor(const LoveC_Rect* rect);
LOVE_EXPORT LoveC_Bool love_graphics_getScissor(LoveC_Rect* outRect);
LOVE_EXPORT LoveC_Bool love_graphics_drawToStencilBuffer(LoveC_Graphics_StencilAction action, int stencilvalue, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_stopDrawToStencilBuffer(LoveC_Graphics_StencilAction action, char** outError);
LOVE_EXPORT void love_graphics_getStencilTest(LoveC_Graphics_CompareMode* outMode, int* outComparevalue);
LOVE_EXPORT void love_graphics_getStencilTest(LoveC_Graphics_CompareMode* outMode, int* outComparevalue);
/* LOVE_EXPORT void love_graphics_newCubeImage(); */
/* LOVE_EXPORT void love_graphics_newArrayImage(); */
/* LOVE_EXPORT void love_graphics_newVolumeImage(); */
LOVE_EXPORT LoveC_Result love_graphics_newImage(LoveC_Graphics_Image_SlicesRef slices, LoveC_Graphics_Image_Settings* settingsOpt, LoveC_Graphics_ImageRef* outImage, char** outError);
LOVE_EXPORT LoveC_QuadRef love_graphics_newQuad(const LoveC_Quad_Viewport* v, double sw, double sh);
LOVE_EXPORT LoveC_Bool love_graphics_newFont(LoveC_Font_RasterizerRef rasterizer, LoveC_Texture_Filter* filter, LoveC_FontRef* outFont, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_newSpriteBatch(LoveC_TextureRef texture, int size, LoveC_Graphics_Vertex_Usage usage, LoveC_SpriteBatchRef* outSpriteBatch, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_newParticleSystem(LoveC_TextureRef texture, int size, LoveC_ParticleSystemRef* outParticleSystem, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_newCanvas(const LoveC_Canvas_Settings* settingsOpt, LoveC_CanvasRef* outCanvas, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_newShader(const char* vertexsource, const char* pixelsource, LoveC_ShaderRef* outShader, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_validateShader(LoveC_Bool gles, const char* vertexsource, const char* pixelsource, char** outShaderError, char** outError);

LOVE_EXPORT LoveC_Bool love_graphics_newMesh__standard(LoveC_Vertex** vertices, LoveC_Graphics_PrimitiveType drawmode, LoveC_Graphics_Vertex_Usage usage, LoveC_MeshRef* outMesh, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_newMesh__standard_count(int count, LoveC_Graphics_PrimitiveType drawmode, LoveC_Graphics_Vertex_Usage usage, LoveC_MeshRef* outMesh, char** outError);

// LOVE_EXPORT LoveC_Bool love_graphics_newText();
// LOVE_EXPORT void love_graphics_newVideo();
LOVE_EXPORT void love_graphics_setColor(const LoveC_Colorf* color);
LOVE_EXPORT void love_graphics_getColor(LoveC_Colorf* outColor);
LOVE_EXPORT void love_graphics_setBackgroundColor(const LoveC_Colorf* color);
LOVE_EXPORT void love_graphics_getBackgroundColor(LoveC_Colorf* outColor);
// LOVE_EXPORT void love_graphics_setNewFont();
LOVE_EXPORT void love_graphics_setFont(LoveC_FontRef* fontOpt);
LOVE_EXPORT LoveC_Bool love_graphics_getFont(LoveC_FontRef* outFont, char** outError);
LOVE_EXPORT void love_graphics_setColorMask(const LoveC_Graphics_ColorMask* color);
LOVE_EXPORT void love_graphics_getColorMask(LoveC_Graphics_ColorMask* outColor);
LOVE_EXPORT LoveC_Bool love_graphics_setBlendMode(LoveC_Graphics_BlendMode mode, LoveC_Graphics_BlendAlpha alphamode, char** outError);
LOVE_EXPORT void love_graphics_getBlendMode(LoveC_Graphics_BlendMode* outMode, LoveC_Graphics_BlendAlpha* outAlphamode);
LOVE_EXPORT void love_graphics_setDefaultFilter(const LoveC_Texture_Filter* filter);
LOVE_EXPORT void love_graphics_getDefaultFilter(LoveC_Texture_Filter* outFilter);
LOVE_EXPORT void love_graphics_setDefaultMipmapFilter(LoveC_Texture_FilterMode filter, float sharpness);
LOVE_EXPORT void love_graphics_getDefaultMipmapFilter(LoveC_Texture_FilterMode* outFilter, float* outSharpness);
LOVE_EXPORT void love_graphics_setLineWidth(float width);
LOVE_EXPORT void love_graphics_setLineStyle(LoveC_Graphics_LineStyle style);
LOVE_EXPORT void love_graphics_setLineJoin(LoveC_Graphics_LineJoin join);
LOVE_EXPORT float love_graphics_getLineWidth();
LOVE_EXPORT LoveC_Graphics_LineStyle love_graphics_getLineStyle();
LOVE_EXPORT LoveC_Graphics_LineJoin love_graphics_getLineJoin();
LOVE_EXPORT void love_graphics_setPointSize(float size);
LOVE_EXPORT float love_graphics_getPointSize();
LOVE_EXPORT LoveC_Bool love_graphics_setDepthMode(LoveC_Graphics_CompareMode compare, LoveC_Bool write, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_setDepthMode__clear(char** outError);
LOVE_EXPORT void love_graphics_getDepthMode(LoveC_Graphics_CompareMode* outCompare, LoveC_Bool* outWrite);
LOVE_EXPORT LoveC_Bool love_graphics_setMeshCullMode(LoveC_Graphics_CullMode mode, char** outError);
LOVE_EXPORT LoveC_Graphics_CullMode love_graphics_getMeshCullMode();
LOVE_EXPORT LoveC_Bool love_graphics_setFrontFaceWinding(LoveC_Graphics_Vertex_Winding winding, char** outError);
LOVE_EXPORT LoveC_Graphics_Vertex_Winding love_graphics_getFrontFaceWinding();
LOVE_EXPORT void love_graphics_setWireframe(LoveC_Bool wireframe);
LOVE_EXPORT LoveC_Bool love_graphics_isWireframe();
LOVE_EXPORT void love_graphics_setShader(LoveC_ShaderRef* shader);
LOVE_EXPORT LoveC_ShaderRef love_graphics_getShader();
LOVE_EXPORT LoveC_Bool love_graphics_setDefaultShaderCode(LoveC_Shader_StandardShader std, LoveC_Shader_Language lang, LoveC_Bool isGammaCorrected, LoveC_ShaderStage_StageType stage, const char* code, char** outError);
LOVE_EXPORT void love_graphics_getSupported(LoveC_Graphics_Capabilities* outCaps);
LOVE_EXPORT LoveC_Bool love_graphics_isCanvasFormatSupported(LoveC_Graphics_PixelFormat format, LoveC_OptionalBool readable);
LOVE_EXPORT LoveC_Bool love_graphics_isImageFormatSupported(LoveC_Graphics_PixelFormat format);
LOVE_EXPORT LoveC_Bool love_graphics_getRendererInfo(LoveC_Graphics_RendererInfo* outInfo, char** outError);
LOVE_EXPORT void love_graphics_getStats(LoveC_Graphics_Stats* outStats);

LOVE_EXPORT LoveC_Bool love_graphics_draw(LoveC_DrawableRef drawable, const LoveC_Matrix4* matrixOpt, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_draw__texture(LoveC_TextureRef texture, LoveC_QuadRef quad, const LoveC_Matrix4* matrixOpt, char** outError);

LOVE_EXPORT LoveC_Bool love_graphics_drawLayer(LoveC_TextureRef texture, int layer, const LoveC_Matrix4* matrixOpt, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_drawLayer__quad(LoveC_TextureRef texture, int layer, LoveC_QuadRef quad, const LoveC_Matrix4* matrixOpt, char** outError);

LOVE_EXPORT LoveC_Bool love_graphics_drawInstanced(LoveC_MeshRef mesh, const LoveC_Matrix4* matrixOpt, int instancecount, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_print(const LoveC_Font_ColoredString* strs, LoveC_FontRef* fontOpt, const LoveC_Matrix4* matrixOpt, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_printf(const LoveC_Font_ColoredString* strs, LoveC_FontRef* fontOpt, float wrap, LoveC_Font_AlignMode align, const LoveC_Matrix4* matrixOpt, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_points(const LoveC_Vector2* positions, const LoveC_Colorf* colors, LoveC_Int64 numpoints, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_polyline(const LoveC_Vector2* coords, LoveC_Int64 numvertices, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_rectangle(LoveC_Graphics_DrawMode mode, float x, float y, float w, float h, float rx, float ry, LoveC_OptionalInt points, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_circle(LoveC_Graphics_DrawMode mode, float x, float y, float radius, LoveC_OptionalInt points, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_ellipse(LoveC_Graphics_DrawMode mode, float x, float y, float a, float b, LoveC_OptionalInt points, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_arc(LoveC_Graphics_DrawMode mode, LoveC_Graphics_ArcMode arcmode, float x, float y, float radius, float angle1, float angle2, LoveC_OptionalInt points, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_polygon(LoveC_Graphics_DrawMode mode, const LoveC_Vector2* coords, LoveC_Int64 numvertices, char** outError);
LOVE_EXPORT void love_graphics_flushBatch();
LOVE_EXPORT LoveC_Int64 love_graphics_getStackDepth();
LOVE_EXPORT LoveC_Bool love_graphics_push(LoveC_Graphics_StackType stype, char** outError);
LOVE_EXPORT LoveC_Bool love_graphics_pop(char** outError);
LOVE_EXPORT void love_graphics_rotate(float angle);
LOVE_EXPORT void love_graphics_scale(float sx, float sy);
LOVE_EXPORT void love_graphics_translate();
LOVE_EXPORT void love_graphics_shear();
LOVE_EXPORT void love_graphics_origin();
/* LOVE_EXPORT void love_graphics_applyTransform(); */
/* LOVE_EXPORT void love_graphics_replaceTransform(); */
LOVE_EXPORT void love_graphics_transformPoint(const LoveC_Vector2* p, LoveC_Vector2* outPoint);
LOVE_EXPORT void love_graphics_inverseTransformPoint(const LoveC_Vector2* p, LoveC_Vector2* outPoint);

LOVE_EXPORT LoveC_Bool love_graphics_registerModule(char** outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_GRAPHICS_C_GRAPHICS_H
