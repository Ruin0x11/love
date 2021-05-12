/* #ifdef LOVE_BUILD_C_API */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shaders.h"

#include "../modules/love_c/love_c.h"
#include "../modules/love_c/c_Object.h"
#include "../modules/love_c/c_Data.h"
#include "../modules/love_c/c_Matrix.h"
#include "../modules/love_c/c_Variant.h"
#include "../modules/filesystem/c_Filesystem.h"
#include "../modules/window/c_Window.h"
#include "../modules/graphics/c_Graphics.h"
#include "../modules/font/c_Font.h"
#include "../modules/event/c_Event.h"

int init() {
  char* error = NULL;

  if (!love_c_init(&error)) {
    printf("Error: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  char* exepath = NULL;
  love_filesystem_getExecutablePath(&exepath);
  if (exepath == NULL) {
    printf("No exepath\n");
    return LOVE_C_FALSE;
  }

  printf("Exepath: %s\n", exepath);

  LoveC_Bool is_fused = love_filesystem_setSource(exepath, &error);
  if (is_fused) {
    printf("Is fused\n", error);
    free(error);
  }

  love_filesystem_setFused(is_fused);

#define SET_SHADER(lang)                                                \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_VERTEX, SHADER_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_PIXEL, SHADER_##lang##_PIXEL, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_VERTEX, SHADER_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_PIXEL, SHADER_##lang##_VIDEOPIXEL, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_VERTEX, SHADER_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_PIXEL, SHADER_##lang##_ARRAYPIXEL, NULL);

#define SET_SHADER_GAMMA(lang)                                                \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_VERTEX, SHADER_GAMMA_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_PIXEL, SHADER_GAMMA_##lang##_PIXEL, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_VERTEX, SHADER_GAMMA_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_PIXEL, SHADER_GAMMA_##lang##_VIDEOPIXEL, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_VERTEX, SHADER_GAMMA_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_PIXEL, SHADER_GAMMA_##lang##_ARRAYPIXEL, NULL);

  SET_SHADER(GLSL1)
  SET_SHADER(ESSL1)
  SET_SHADER(GLSL3)
  SET_SHADER(ESSL3)
  SET_SHADER_GAMMA(GLSL1)
  SET_SHADER_GAMMA(ESSL1)
  SET_SHADER_GAMMA(GLSL3)
  SET_SHADER_GAMMA(ESSL3)

  love_window_setTitle("Love C");

  LoveC_Window_WindowSettings settings;
  settings.fullscreen = LOVE_C_FALSE;
  settings.fstype = FULLSCREEN_MAX_ENUM;
  settings.vsync = 1;
  settings.msaa = 0;
  settings.stencil = LOVE_C_TRUE;
  settings.depth = 0;
  settings.resizable = LOVE_C_FALSE;
  settings.minwidth = 1;
  settings.minheight = 1;
  settings.borderless = LOVE_C_FALSE;
  settings.centered = LOVE_C_TRUE;
  settings.display = 0;
  settings.highdpi = LOVE_C_FALSE;
  settings.usedpiscale = LOVE_C_TRUE;
  settings.refreshrate = 0.0;
  settings.useposition = LOVE_C_FALSE;
  settings.x = 0;
  settings.y = 0;

  if (!love_window_setMode(800, 600, &settings, &error)) {
    printf("Error initializing window: %s\n", error);
    return LOVE_C_FALSE;
  }

  return LOVE_C_TRUE;
}

int nogame() {
  return LOVE_C_TRUE;
}

int main(int argc, char *argv[]) {
  char* error = NULL;

  if (!init()) {
    return 1;
  }

  printf("Hello, world! %s\n", love_c_version());

  if (!nogame()) {
    return 1;
  }

  return 0;
}

/* #endif */
