#include "c_Graphics.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Graphics.h"
#include "Font.h"
#include "ParticleSystem.h"

#include "opengl/Graphics.h"

using namespace love;
using namespace love::graphics;

#define instance() (Module::getInstance<Graphics>(Module::M_GRAPHICS))


void love_graphics_reset() {
  instance()->reset();
}

LoveC_Bool love_graphics_clear(const LoveC_Colorf** colors, int stencilOpt, double depthOpt, char** outError) {
  OptionalColorf color(Colorf(0.0f, 0.0f, 0.0f, 0.0f));
  std::vector<OptionalColorf> colors_;

  OptionalInt stencil(0);
  OptionalDouble depth(1.0);

  if (colors != nullptr) {
    int i;
    for (i = 0; colors[i]; i++) {
      colors_.emplace_back(Colorf(colors[i]->r, colors[i]->g, colors[i]->b, colors[i]->a));
    }
  }

  if (stencilOpt != LOVE_C_NIL) {
    stencil.value = stencilOpt;
    stencil.hasValue = true;
  } else {
    stencil.hasValue = false;
  }

  if (depthOpt != LOVE_C_NIL) {
    depth.value = depthOpt;
    depth.hasValue = true;
  } else {
    depth.hasValue = false;
  }

  try {
    if (colors_.empty()) {
      instance()->clear(color, stencil, depth);
    } else {
      instance()->clear(colors_, stencil, depth);
    }
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_graphics_discard(LoveC_Bool* colorbuffers, LoveC_Bool depthstencil) {
  std::vector<bool> colorbuffers_;

  if (colorbuffers != nullptr) {
    int i;
    for (i = 0; colorbuffers[i] != LOVE_C_NIL; i++) {
      colorbuffers_.push_back(colorbuffers[i]);
    }
  }

  instance()->discard(colorbuffers_, depthstencil);
}

LoveC_Bool love_graphics_present(char** outError) {
  try {
    // TODO screenshot callbacks
    instance()->present(nullptr);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_isCreated() {
  return instance()->isCreated();
}

LoveC_Bool love_graphics_isActive() {
  return instance()->isActive();
}

LoveC_Bool love_graphics_isGammaCorrect() {
  return graphics::isGammaCorrect();
}

int love_graphics_getWidth() {
  return instance()->getWidth();
}

int love_graphics_getHeight() {
  return instance()->getHeight();
}

int love_graphics_getPixelWidth() {
  return instance()->getPixelWidth();
}

int love_graphics_getPixelHeight() {
  return instance()->getPixelHeight();
}

float love_graphics_getDPIScale() {
  return instance()->getScreenDPIScale();
}

Graphics::RenderTarget convertRenderTarget(LoveC_Graphics_RenderTarget* target) {
  auto canvas = unwrap<Canvas>(target->canvas);

  Graphics::RenderTarget temp;
  temp.canvas = canvas;
  temp.slice = target->slice;
  temp.mipmap = target->mipmap;

  return std::move(temp);
}

LoveC_Bool love_graphics_setCanvas(LoveC_Graphics_RenderTargets *targetsOpt, char** outError) {
  Graphics::RenderTargets targets;

  if (targetsOpt != nullptr) {
    if (targetsOpt->colors != nullptr) {
      int i;
      for (i = 0; targetsOpt->colors[i]; i++) {
        targets.colors.push_back(convertRenderTarget(targetsOpt->colors[i]));
      }
    }
    targets.depthStencil = convertRenderTarget(targetsOpt->depthStencil);
    targets.temporaryRTFlags = targets.temporaryRTFlags;
  }

  try {
    if (targets.getFirstTarget().canvas != nullptr)
      instance()->setCanvas(targets);
    else
      instance()->setCanvas();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_graphics_getCanvas(LoveC_Graphics_RenderTargets *outTargets) {
  Graphics::RenderTargets targets = instance()->getCanvas();

  for (int i = 0; i < (int) targets.colors.size(); i++) {
    auto color = targets.colors[i];
    outTargets->colors[i]->canvas = wrap<LoveC_CanvasRef>(color.canvas);
    outTargets->colors[i]->slice = color.slice;
    outTargets->colors[i]->mipmap = color.mipmap;
  }
  outTargets->colors[targets.colors.size()] = nullptr;

  outTargets->depthStencil->canvas = wrap<LoveC_CanvasRef>(targets.depthStencil.canvas);
  outTargets->depthStencil->slice = targets.depthStencil.slice;
  outTargets->depthStencil->mipmap = targets.depthStencil.mipmap;

  outTargets->temporaryRTFlags = targets.temporaryRTFlags;
}

void love_graphics_setScissor(const LoveC_Rect* rect) {
  auto rect_ = unwrap<const Rect>(rect);

  instance()->setScissor(*rect_);
}

void love_graphics_setScissor__clear() {
  instance()->setScissor();
}

void love_graphics_intersectScissor(const LoveC_Rect* rect) {
  auto rect_ = unwrap<const Rect>(rect);

  instance()->intersectScissor(*rect_);
}

LoveC_Bool love_graphics_getScissor(LoveC_Rect* outRect) {
  auto outRect_ = unwrap<Rect>(outRect);

  Rect rect;
  if (!instance()->getScissor(*outRect_))
    return false;

  return true;
}

LoveC_Bool love_graphics_drawToStencilBuffer(LoveC_Graphics_StencilAction action, int stencilvalue, char** outError) {
  auto action_ = static_cast<StencilAction>(action);

  try {
    instance()->drawToStencilBuffer(action_, stencilvalue);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_stopDrawToStencilBuffer(LoveC_Graphics_StencilAction action, char** outError) {
  auto action_ = static_cast<StencilAction>(action);

  try {
    instance()->stopDrawToStencilBuffer();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_setStencilTest(LoveC_Graphics_CompareMode mode, int comparevalue, char** outError) {
  auto mode_ = static_cast<CompareMode>(mode);

  try {
    instance()->setStencilTest(mode_, comparevalue);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_graphics_getStencilTest(LoveC_Graphics_CompareMode* outMode, int* outComparevalue) {
  CompareMode compare = CompareMode::COMPARE_ALWAYS;
  int comparevalue = 1;
  instance()->getStencilTest(compare, comparevalue);

  *outMode = static_cast<LoveC_Graphics_CompareMode>(compare);
  *outComparevalue = comparevalue;
}

LoveC_Result love_graphics_newImage(LoveC_Graphics_Image_SlicesRef slices, LoveC_Graphics_Image_Settings* settingsOpt, LoveC_Graphics_ImageRef* outImage, char** outError) {
  auto slices_ = unwrap<Image::Slices>(slices);
  Image::Settings settings_;

  if (settingsOpt != nullptr) {
    settings_.mipmaps = settingsOpt->mipmaps;
    settings_.linear = settingsOpt->linear;
    settings_.dpiScale = settingsOpt->dpiScale;
  }

  Image* t = nullptr;

  try {
    t = instance()->newImage(*slices_, settings_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outImage = wrap<LoveC_Graphics_ImageRef>(t);

  return true;
}

LoveC_QuadRef love_graphics_newQuad(const LoveC_Quad_Viewport* v, double sw, double sh) {
  auto v_ = unwrap<const Quad::Viewport>(v);

  Quad* quad = instance()->newQuad(*v_, sw, sh);

  return wrap<LoveC_QuadRef>(quad);
}

LoveC_Bool love_graphics_newFont(LoveC_Font_RasterizerRef rasterizer, LoveC_Texture_Filter* filter, LoveC_FontRef* outFont, char** outError) {
  auto rasterizer_ = unwrap<font::Rasterizer>(rasterizer);

  Texture::Filter filter_;
  filter_.min = static_cast<Texture::FilterMode>(filter->min);
  filter_.mag = static_cast<Texture::FilterMode>(filter->mag);
  filter_.mipmap = static_cast<Texture::FilterMode>(filter->mipmap);
  filter_.anisotropy = filter->anisotropy;

  Font* t;

  try {
    t = instance()->newFont(rasterizer_, filter_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outFont = wrap<LoveC_FontRef>(t);

  return true;
}

LoveC_Bool love_graphics_newSpriteBatch(LoveC_TextureRef texture, int size, LoveC_Graphics_Vertex_Usage usage, LoveC_SpriteBatchRef* outSpriteBatch, char** outError) {
  auto texture_ = unwrap<Texture>(texture);
  auto usage_ = static_cast<vertex::Usage>(usage);

  SpriteBatch* t = nullptr;

  try {
    t = instance()->newSpriteBatch(texture_, size, usage_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outSpriteBatch = wrap<LoveC_SpriteBatchRef>(t);

  return true;
}

LoveC_Bool love_graphics_newParticleSystem(LoveC_TextureRef texture, int size, LoveC_ParticleSystemRef* outParticleSystem, char** outError) {
  auto texture_ = unwrap<Texture>(texture);

  if (size < 1 || size > ParticleSystem::MAX_PARTICLES) {
    *outError = strdup("Invalid ParticleSystem size");
    return false;
  }

  ParticleSystem* t = nullptr;

  try {
    t = instance()->newParticleSystem(texture_, size);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outParticleSystem = wrap<LoveC_ParticleSystemRef>(t);

  return true;
}

LOVE_EXPORT LoveC_Bool love_graphics_newCanvas(const LoveC_Canvas_Settings* settingsOpt, LoveC_CanvasRef* outCanvas, char** outError) {
  Canvas::Settings settings;

  if (settingsOpt) {
    settings.width = settingsOpt->width;
    settings.height = settingsOpt->height;
    settings.layers = settingsOpt->layers;
    settings.mipmaps = static_cast<Canvas::MipmapMode>(settingsOpt->mipmaps);
    settings.format = static_cast<PixelFormat>(settingsOpt->format);
    settings.type = static_cast<TextureType>(settingsOpt->type);
    settings.dpiScale = settingsOpt->dpiScale;
    settings.msaa = settingsOpt->msaa;
    if (settingsOpt->readable == LOVE_C_NIL) {
      settings.readable.hasValue = false;
    } else {
      settings.readable.value = settingsOpt->readable;
      settings.readable.hasValue = true;
    }
  }

  Canvas *canvas = nullptr;

  try {
    canvas = instance()->newCanvas(settings);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outCanvas = wrap<LoveC_CanvasRef>(canvas);

  return true;
}

LoveC_Bool love_graphics_newShader(const char* vertexsource, const char* pixelsource, LoveC_ShaderRef* outShader, char** outError) {
  std::string vertexsource_(vertexsource);
  std::string pixelsource_(pixelsource);

  Shader* t = nullptr;

  try {
    t = instance()->newShader(vertexsource_, pixelsource_);
  } catch(std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outShader = wrap<LoveC_ShaderRef>(t);

  return true;
}

LoveC_Bool love_graphics_validateShader(LoveC_Bool gles, const char* vertexsource, const char* pixelsource, char** outShaderError, char** outError) {
  std::string vertexsource_(vertexsource);
  std::string pixelsource_(pixelsource);

  std::string err;
  bool success = false;

  try {
    success = instance()->validateShader(gles, vertexsource_, pixelsource_, err);
  } catch(std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  if (!success) {
    *outShaderError = strdup(err.c_str());
  }

  return success;
}

LoveC_Bool love_graphics_newMesh__standard(LoveC_Vertex** vertices, LoveC_Graphics_PrimitiveType drawmode, LoveC_Graphics_Vertex_Usage usage, LoveC_MeshRef* outMesh, char** outError) {
  auto drawmode_ = static_cast<PrimitiveType>(drawmode);
  auto usage_ = static_cast<vertex::Usage>(usage);

  std::vector<Vertex> vertices_;
  int i;
  for (i = 0; vertices[i]; i++) {
    Vertex v;

    v.x = vertices[i]->x;
    v.y = vertices[i]->y;
    v.s = vertices[i]->s;
    v.t = vertices[i]->t;

    v.color.r = vertices[i]->color.r;
    v.color.g = vertices[i]->color.g;
    v.color.b = vertices[i]->color.b;
    v.color.a = vertices[i]->color.a;

    vertices_.emplace_back(v);
  }

  Mesh* t;

  try {
    t = instance()->newMesh(vertices_, drawmode_, usage_);
  } catch(const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outMesh = wrap<LoveC_MeshRef>(t);

  return true;
}

LoveC_Bool love_graphics_newMesh__standard_count(int count, LoveC_Graphics_PrimitiveType drawmode, LoveC_Graphics_Vertex_Usage usage, LoveC_MeshRef* outMesh, char** outError) {
  auto drawmode_ = static_cast<PrimitiveType>(drawmode);
  auto usage_ = static_cast<vertex::Usage>(usage);

  Mesh* t = nullptr;

  try {
    t = instance()->newMesh(count, drawmode_, usage_);
  } catch(const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outMesh = wrap<LoveC_MeshRef>(t);

  return true;
}

void love_graphics_setColor(const LoveC_Colorf* color) {
  Colorf c;

  c.r = color->r;
  c.g = color->g;
  c.b = color->b;
  c.a = color->a;

  instance()->setColor(c);
}

void love_graphics_getColor(LoveC_Colorf* outColor) {
  Colorf c = instance()->getColor();

  outColor->r = c.r;
  outColor->g = c.g;
  outColor->b = c.b;
  outColor->a = c.a;
}

void love_graphics_setBackgroundColor(const LoveC_Colorf* color) {
  Colorf c;

  c.r = color->r;
  c.g = color->g;
  c.b = color->b;
  c.a = color->a;

  instance()->setBackgroundColor(c);
}

void love_graphics_getBackgroundColor(LoveC_Colorf* outColor) {
  Colorf c = instance()->getBackgroundColor();

  outColor->r = c.r;
  outColor->g = c.g;
  outColor->b = c.b;
  outColor->a = c.a;
}

void love_graphics_setFont(LoveC_FontRef* fontOpt) {
  auto fontOpt_ = unwrap<Font>(fontOpt);

  instance()->setFont(fontOpt_);
}

LoveC_Bool love_graphics_getFont(LoveC_FontRef* outFont, char** outError) {
  Font* t = nullptr;

  try {
    t = instance()->getFont();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outFont = wrap<LoveC_FontRef>(t);

  return true;
}

void love_graphics_setColorMask(const LoveC_Graphics_ColorMask* mask) {
  auto mask_ = unwrap<const Graphics::ColorMask>(mask);

  instance()->setColorMask(*mask_);
}

void love_graphics_getColorMask(LoveC_Graphics_ColorMask* outMask) {
  Graphics::ColorMask mask = instance()->getColorMask();
  outMask->r = mask.r;
  outMask->g = mask.g;
  outMask->b = mask.b;
  outMask->a = mask.a;
}

LoveC_Bool love_graphics_setBlendMode(LoveC_Graphics_BlendMode mode, LoveC_Graphics_BlendAlpha alphamode, char** outError) {
  auto mode_ = static_cast<Graphics::BlendMode>(mode);
  auto alphamode_ = static_cast<Graphics::BlendAlpha>(alphamode);

  try {
    instance()->setBlendMode(mode_, alphamode_);
  } catch (std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_graphics_getBlendMode(LoveC_Graphics_BlendMode* outMode, LoveC_Graphics_BlendAlpha* outAlphamode) {
  Graphics::BlendAlpha alphamode;
  Graphics::BlendMode mode = instance()->getBlendMode(alphamode);

  *outMode = static_cast<LoveC_Graphics_BlendMode>(mode);
  *outAlphamode = static_cast<LoveC_Graphics_BlendAlpha>(alphamode);
}

void love_graphics_setDefaultFilter(const LoveC_Texture_Filter* filter) {
  Texture::Filter f;

  f.min = static_cast<Texture::FilterMode>(filter->min);
  f.mag = static_cast<Texture::FilterMode>(filter->mag);
  f.mipmap = static_cast<Texture::FilterMode>(filter->mipmap);
  f.anisotropy = filter->anisotropy;

  instance()->setDefaultFilter(f);
}

void love_graphics_getDefaultFilter(LoveC_Texture_Filter* outFilter) {
  Texture::Filter f = instance()->getDefaultFilter();

  outFilter->min = static_cast<LoveC_Texture_FilterMode>(f.min);
  outFilter->mag = static_cast<LoveC_Texture_FilterMode>(f.mag);
  outFilter->mipmap = static_cast<LoveC_Texture_FilterMode>(f.mipmap);
  outFilter->anisotropy = f.anisotropy;
}

void love_graphics_setDefaultMipmapFilter(LoveC_Texture_FilterMode filter, float sharpness) {
  auto filter_ = static_cast<Texture::FilterMode>(filter);

  instance()->setDefaultMipmapFilter(filter_, sharpness);
}

void love_graphics_getDefaultMipmapFilter(LoveC_Texture_FilterMode* outFilter, float* outSharpness) {
  Texture::FilterMode filter;
  float sharpness;

  instance()->getDefaultMipmapFilter(&filter, &sharpness);

  *outFilter = static_cast<LoveC_Texture_FilterMode>(filter);
  *outSharpness = sharpness;
}

void love_graphics_setLineWidth(float width) {
  instance()->setLineWidth(width);
}

void love_graphics_setLineStyle(LoveC_Graphics_LineStyle style) {
  auto style_ = static_cast<Graphics::LineStyle>(style);
  instance()->setLineStyle(style_);
}

void love_graphics_setLineJoin(LoveC_Graphics_LineJoin join) {
  auto join_ = static_cast<Graphics::LineJoin>(join);
  instance()->setLineJoin(join_);
}

float love_graphics_getLineWidth() {
  return instance()->getLineWidth();
}

LoveC_Graphics_LineStyle love_graphics_getLineStyle() {
  auto style = instance()->getLineStyle();
  return static_cast<LoveC_Graphics_LineStyle>(style);
}

LoveC_Graphics_LineJoin love_graphics_getLineJoin() {
  auto join = instance()->getLineJoin();
  return static_cast<LoveC_Graphics_LineJoin>(join);
}

void love_graphics_setPointSize(float size) {
  instance()->setPointSize(size);
}

float love_graphics_getPointSize() {
  return instance()->getPointSize();
}

LoveC_Bool love_graphics_setDepthMode(LoveC_Graphics_CompareMode compare, LoveC_Bool write, char** outError) {
  auto compare_ = static_cast<CompareMode>(compare);

  try {
    instance()->setDepthMode(compare_, write);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_setDepthMode__clear(char** outError) {
  try {
    instance()->setDepthMode();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_graphics_getDepthMode(LoveC_Graphics_CompareMode* outCompare, LoveC_Bool* outWrite) {
  CompareMode compare = CompareMode::COMPARE_ALWAYS;
  bool write = false;
  instance()->getDepthMode(compare, write);

  *outCompare = static_cast<LoveC_Graphics_CompareMode>(compare);
  *outWrite = write;
}

LoveC_Bool love_graphics_setMeshCullMode(LoveC_Graphics_CullMode mode, char** outError) {
  auto mode_ = static_cast<CullMode>(mode);

  try {
    instance()->setMeshCullMode(mode_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Graphics_CullMode love_graphics_getMeshCullMode(LoveC_Graphics_CullMode* outMode) {
  CullMode mode = instance()->getMeshCullMode();
  return static_cast<LoveC_Graphics_CullMode>(mode);
}

LoveC_Bool love_graphics_setFrontFaceWinding(LoveC_Graphics_Vertex_Winding winding, char** outError) {
  auto winding_ = static_cast<vertex::Winding>(winding);

  try {
    instance()->setFrontFaceWinding(winding_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Graphics_Vertex_Winding love_graphics_getFrontFaceWinding() {
  vertex::Winding winding = instance()->getFrontFaceWinding();
  return static_cast<LoveC_Graphics_Vertex_Winding>(winding);
}

void love_graphics_setWireframe(LoveC_Bool wireframe) {
  instance()->setWireframe(wireframe);
}

LoveC_Bool love_graphics_isWireframe() {
  return instance()->isWireframe();
}

void love_graphics_setShader(LoveC_ShaderRef* shader) {
  if (shader == nullptr) {
    instance()->setShader();
  } else {
    auto shader_ = unwrap<Shader>(shader);
    instance()->setShader(shader_);
  }
}

LoveC_ShaderRef love_graphics_getShader() {
  auto shader = instance()->getShader();
  return wrap<LoveC_ShaderRef>(shader);
}

LoveC_Bool love_graphics_setDefaultShaderCode(LoveC_Shader_StandardShader std, LoveC_Shader_Language lang, LoveC_Bool isGammaCorrected, LoveC_ShaderStage_StageType stage, const char* code, char** outError) {
  auto std_ = static_cast<Shader::StandardShader>(std);
  auto lang_ = static_cast<Shader::Language>(lang);
  auto stage_ = static_cast<ShaderStage::StageType>(stage);

  int index;
  if (isGammaCorrected) {
    index = 1;
  } else {
    index = 0;
  }

  Graphics::defaultShaderCode[std_][lang_][index].source[stage_] = std::string(code);

  return true;
}

void love_graphics_getSupported(LoveC_Graphics_Capabilities* outCaps) {
  const Graphics::Capabilities &caps = instance()->getCapabilities();

  for (int i = 0; i < (int) Graphics::LIMIT_MAX_ENUM; i++)
    {
      outCaps->limits[i] = caps.limits[i];
    }

  for (int i = 0; i < (int) Graphics::FEATURE_MAX_ENUM; i++)
    {
      outCaps->features[i] = caps.features[i];
    }

  for (int i = 0; i < (int) graphics::TEXTURE_MAX_ENUM; i++)
    {
      outCaps->textureTypes[i] = caps.textureTypes[i];
    }
}

LoveC_Bool love_graphics_isCanvasFormatSupported(LoveC_Graphics_PixelFormat format, LoveC_OptionalBool readable) {
  auto format_ = static_cast<PixelFormat>(format);

  if (readable == LOVE_C_NIL) {
    return instance()->isCanvasFormatSupported(format_);
  } else {
    return instance()->isCanvasFormatSupported(format_, readable);
  }
}

LoveC_Bool love_graphics_isImageFormatSupported(LoveC_Graphics_PixelFormat format) {
  auto format_ = static_cast<PixelFormat>(format);

  return instance()->isImageFormatSupported(format_);
}

LoveC_Bool love_graphics_getRendererInfo(LoveC_Graphics_RendererInfo* outInfo, char** outError) {
  Graphics::RendererInfo info;

  try {
    info = instance()->getRendererInfo();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  outInfo->name = strdup(info.name.c_str());
  outInfo->version = strdup(info.version.c_str());
  outInfo->vendor = strdup(info.vendor.c_str());
  outInfo->device = strdup(info.device.c_str());

  return true;
}

void love_graphics_getStats(LoveC_Graphics_Stats* outStats) {
  Graphics::Stats stats = instance()->getStats();

  outStats->drawCalls = stats.drawCalls;
  outStats->drawCallsBatched = stats.drawCallsBatched;
  outStats->canvasSwitches = stats.canvasSwitches;
  outStats->shaderSwitches = stats.shaderSwitches;
  outStats->canvases = stats.canvases;
  outStats->images = stats.images;
  outStats->fonts = stats.fonts;
  outStats->textureMemory = stats.textureMemory;
}

Matrix4 convertMatrix4(const LoveC_Matrix4* matrixOpt) {
  if (matrixOpt != nullptr) {
    return std::move(Matrix4(matrixOpt->elements));
  } else {
    return std::move(Matrix4(0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0));
  }
}

LoveC_Bool love_graphics_draw(LoveC_DrawableRef drawable, const LoveC_Matrix4* matrixOpt, char** outError) {
  auto drawable_ = unwrap<Drawable>(drawable);

  Matrix4 m = convertMatrix4(matrixOpt);

  try {
    instance()->draw(drawable_, m);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_draw__texture(LoveC_TextureRef texture, LoveC_QuadRef quad, const LoveC_Matrix4* matrixOpt, char** outError) {
  auto texture_ = unwrap<Texture>(texture);
  auto quad_ = unwrap<Quad>(quad);

  Matrix4 m = convertMatrix4(matrixOpt);

  try {
    instance()->draw(texture_, quad_, m);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_drawLayer(LoveC_TextureRef texture, int layer, const LoveC_Matrix4* matrixOpt, char** outError) {
  auto texture_ = unwrap<Texture>(texture);

  Matrix4 m = convertMatrix4(matrixOpt);

  try {
    instance()->drawLayer(texture_, layer, m);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_drawLayer__quad(LoveC_TextureRef texture, int layer, LoveC_QuadRef quad, const LoveC_Matrix4* matrixOpt, char** outError) {
  auto texture_ = unwrap<Texture>(texture);
  auto quad_ = unwrap<Quad>(quad);

  Matrix4 m = convertMatrix4(matrixOpt);

  try {
    instance()->drawLayer(texture_, layer, quad_, m);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_drawInstanced(LoveC_MeshRef mesh, const LoveC_Matrix4* matrixOpt, int instancecount, char** outError) {
  auto mesh_ = unwrap<Mesh>(mesh);

  Matrix4 m = convertMatrix4(matrixOpt);

  try {
    instance()->drawInstanced(mesh_, m, instancecount);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

Font::ColoredString convertColoredString(const LoveC_Font_ColoredString* str) {
  Font::ColoredString str_;

  str_.str = std::string(str->str);
  str_.color.r = str->color.r;
  str_.color.g = str->color.g;
  str_.color.b = str->color.b;
  str_.color.a = str->color.a;

  return std::move(str_);
}

LoveC_Bool love_graphics_print(const LoveC_Font_ColoredString* strs, LoveC_FontRef* fontOpt, const LoveC_Matrix4* matrixOpt, char** outError) {
  std::vector<Font::ColoredString> strs_;

  if (strs == nullptr) {
    *outError = strdup("No text was provided to love.graphics.print.");
    return false;
  }

  for (; strs->str; strs++) {
    strs_.push_back(convertColoredString(strs));
  }

  Matrix4 m = convertMatrix4(matrixOpt);

  try {
    if (fontOpt != nullptr) {
      auto font_ = unwrap<Font>(*fontOpt);
      instance()->print(strs_, font_, m);
    } else {
      instance()->print(strs_, m);
    }
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_printf(const LoveC_Font_ColoredString* strs, LoveC_FontRef* fontOpt, float wrap, LoveC_Font_AlignMode align, const LoveC_Matrix4* matrixOpt, char** outError) {
  auto align_ = static_cast<Font::AlignMode>(align);
  std::vector<Font::ColoredString> strs_;

  if (strs == nullptr) {
    *outError = strdup("No text was provided to love.graphics.print.");
    return false;
  }

  int i;
  for (; strs; strs++) {
    strs_.push_back(convertColoredString(strs));
  }

  Matrix4 m = convertMatrix4(matrixOpt);

  try {
    if (fontOpt != nullptr) {
      auto font_ = unwrap<Font>(fontOpt);
      instance()->printf(strs_, font_, wrap, align_, m);
    } else {
      instance()->printf(strs_, wrap, align_, m);
    }
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_points(const LoveC_Vector2* positions, const LoveC_Colorf* colors, LoveC_Int64 numpoints, char** outError) {
  auto positions_ = unwrap<const Vector2>(positions);
  auto colors_ = unwrap<const Colorf>(colors);

  try {
    instance()->points(positions_, colors_, numpoints);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_polyline(const LoveC_Vector2* coords, LoveC_Int64 numvertices, char** outError) {
  auto coords_ = unwrap<const Vector2>(coords);

  try {
    instance()->polyline(coords_, numvertices);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_rectangle(LoveC_Graphics_DrawMode mode, float x, float y, float w, float h, float rx, float ry, LoveC_OptionalInt points, char** outError) {
  auto mode_ = static_cast<Graphics::DrawMode>(mode);

  try {
    if (points == LOVE_C_NIL)
      instance()->rectangle(mode_, x, y, w, h, rx, ry);
    else
      instance()->rectangle(mode_, x, y, w, h, rx, ry, points);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_circle(LoveC_Graphics_DrawMode mode, float x, float y, float radius, LoveC_OptionalInt points, char** outError) {
  auto mode_ = static_cast<Graphics::DrawMode>(mode);

  try {
    if (points == LOVE_C_NIL)
      instance()->circle(mode_, x, y, radius);
    else
      instance()->circle(mode_, x, y, radius, points);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_ellipse(LoveC_Graphics_DrawMode mode, float x, float y, float a, float b, LoveC_OptionalInt points, char** outError) {
  auto mode_ = static_cast<Graphics::DrawMode>(mode);

  try {
    if (points == LOVE_C_NIL)
      instance()->ellipse(mode_, x, y, a, b);
    else
      instance()->ellipse(mode_, x, y, a, b, points);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_arc(LoveC_Graphics_DrawMode mode, LoveC_Graphics_ArcMode arcmode, float x, float y, float radius, float angle1, float angle2, LoveC_OptionalInt points, char** outError) {
  auto mode_ = static_cast<Graphics::DrawMode>(mode);
  auto arcmode_ = static_cast<Graphics::ArcMode>(arcmode);

  try {
    if (points == LOVE_C_NIL)
      instance()->arc(mode_, arcmode_, x, y, radius, angle1, angle2);
    else
      instance()->arc(mode_, arcmode_, x, y, radius, angle1, angle2, points);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_polygon(LoveC_Graphics_DrawMode mode, const LoveC_Vector2* coords, LoveC_Int64 numvertices, char** outError) {
  auto mode_ = static_cast<Graphics::DrawMode>(mode);
  auto coords_ = unwrap<const Vector2>(coords);

  try {
    instance()->polygon(mode_, coords_, numvertices);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_graphics_flushBatch() {
  instance()->flushStreamDraws();
}

LoveC_Int64 love_graphics_getStackDepth() {
  return instance()->getStackDepth();
}

LoveC_Bool love_graphics_push(LoveC_Graphics_StackType stype, char** outError) {
  auto stype_ = static_cast<Graphics::StackType>(stype);

  try {
    instance()->push(stype_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics_pop(char** outError) {
  try {
    instance()->pop();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_graphics_rotate(float angle) {
  instance()->rotate(angle);
}

void love_graphics_scale(float sx, float sy) {
  instance()->scale(sx, sy);
}

void love_graphics_translate(float x, float y) {
  instance()->translate(x, y);
}

void love_graphics_shear(float kx, float ky) {
  instance()->shear(kx, ky);
}

void love_graphics_origin() {
  instance()->origin();
}

void love_graphics_transformPoint(const LoveC_Vector2* p, LoveC_Vector2* outPoint) {
  auto p_ = unwrap<const Vector2>(p);
  auto p2 = instance()->transformPoint(*p_);
  outPoint->x = p2.x;
  outPoint->y = p2.y;
}

void love_graphics_inverseTransformPoint(const LoveC_Vector2* p, LoveC_Vector2* outPoint) {
  auto p_ = unwrap<const Vector2>(p);
  auto p2 = instance()->inverseTransformPoint(*p_);
  outPoint->x = p2.x;
  outPoint->y = p2.y;
}


LoveC_Bool love_graphics_registerModule(char** outError) {
  Graphics *instance = instance();
  if (instance == nullptr) {
    try {
      instance = new opengl::Graphics();
    } catch (const std::exception &e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  WrappedModule w;
  w.module = instance;
  w.name = "graphics";
  w.type = &Graphics::type;
  w.functions = nullptr;
  w.types = nullptr;

  return love_c::register_module(w, outError);
}
