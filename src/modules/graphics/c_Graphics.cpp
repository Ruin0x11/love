#include "c_Graphics.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Graphics.h"

#include "opengl/Graphics.h"

using namespace love;
using namespace love::graphics;

#define instance() (Module::getInstance<Graphics>(Module::M_GRAPHICS))


LoveC_GraphicsRef love_graphics_getInstance() {
  auto inst = instance();
  return wrap<LoveC_GraphicsRef>(inst);
}


void love_graphics_reset(LoveC_GraphicsRef ref) {
  unwrap<Graphics>(ref)->reset();
}

LoveC_Bool love_graphics_clear(LoveC_GraphicsRef ref, const LoveC_Colorf** colors, int stencilOpt, double depthOpt, char** outError) {
  auto graphics = unwrap<Graphics>(ref);

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
      graphics->clear(color, stencil, depth);
    } else {
      graphics->clear(colors_, stencil, depth);
    }
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_graphics_discard(LoveC_GraphicsRef ref, LoveC_Bool* colorbuffers, LoveC_Bool depthstencil) {
  auto graphics = unwrap<Graphics>(ref);
  std::vector<bool> colorbuffers_;

  if (colorbuffers != nullptr) {
    int i;
    for (i = 0; colorbuffers[i] != LOVE_C_NIL; i++) {
      colorbuffers_.push_back(colorbuffers[i]);
    }
  }

  graphics->discard(colorbuffers_, depthstencil);
}

LoveC_Bool love_graphics_present(LoveC_GraphicsRef ref, char** outError) {
  auto graphics = unwrap<Graphics>(ref);

  try {
    // TODO screenshot callbacks
    graphics->present(nullptr);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_graphics__setDefaultShaderCode(LoveC_GraphicsRef ref, LoveC_Shader_StandardShader std, LoveC_Shader_Language lang, LoveC_Bool isGammaCorrected, LoveC_ShaderStage_StageType stage, const char* code, char** outError) {
  auto std_ = static_cast<Shader::StandardShader>(std);
  auto lang_ = static_cast<Shader::Language>(lang);
  auto stage_ = static_cast<Shader::Language>(stage);

  int index;
  if (isGammaCorrected) {
    index = 1;
  } else {
    index = 0;
  }

  Graphics::defaultShaderCode[std_][lang_][index].source[stage_] = std::string(code);

  return true;
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
