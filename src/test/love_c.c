/* #ifdef LOVE_BUILD_C_API */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shaders.h"

#include "../modules/love_c/love_c.h"
#include "../modules/love_c/c_Object.h"
#include "../modules/filesystem/c_Filesystem.h"
#include "../modules/window/c_Window.h"
#include "../modules/graphics/c_Graphics.h"

#define LOVE_C_TRUE (1)
#define LOVE_C_FALSE (0)

int init() {
  char* error = NULL;

  if (!love_c_init(&error)) {
    printf("Error: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  LoveC_FilesystemRef filesystem = love_filesystem_getInstance();

  char* exepath = NULL;
  love_filesystem_getExecutablePath(filesystem, &exepath);
  if (exepath == NULL) {
    printf("No exepath\n");
    return LOVE_C_FALSE;
  }

  printf("Exepath: %s\n", exepath);

  LoveC_Bool is_fused = love_filesystem_setSource(filesystem, exepath, &error);
  if (is_fused) {
    printf("Is fused\n", error);
    free(error);
  }

  love_filesystem_setFused(filesystem, is_fused);


  LoveC_GraphicsRef graphics = love_graphics_getInstance();

#define SET_SHADER(lang)                                                \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_VERTEX, SHADER_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_PIXEL, SHADER_##lang##_PIXEL, NULL); \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_VERTEX, SHADER_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_PIXEL, SHADER_##lang##_VIDEOPIXEL, NULL); \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_VERTEX, SHADER_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_PIXEL, SHADER_##lang##_ARRAYPIXEL, NULL);

#define SET_SHADER_GAMMA(lang)                                                \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_VERTEX, SHADER_GAMMA_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_PIXEL, SHADER_GAMMA_##lang##_PIXEL, NULL); \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_VERTEX, SHADER_GAMMA_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_PIXEL, SHADER_GAMMA_##lang##_VIDEOPIXEL, NULL); \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_VERTEX, SHADER_GAMMA_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(graphics, STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_PIXEL, SHADER_GAMMA_##lang##_ARRAYPIXEL, NULL);

  SET_SHADER(GLSL1)
  SET_SHADER(ESSL1)
  SET_SHADER(GLSL3)
  SET_SHADER(ESSL3)
  SET_SHADER_GAMMA(GLSL1)
  SET_SHADER_GAMMA(ESSL1)
  SET_SHADER_GAMMA(GLSL3)
  SET_SHADER_GAMMA(ESSL3)

  LoveC_WindowRef window = love_window_getInstance();


  love_window_setTitle(window, "Love C");

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

  if (!love_window_setMode(window, 800, 600, &settings, &error)) {
    printf("Error initializing window: %s\n", error);
    return LOVE_C_FALSE;
  }

  return LOVE_C_TRUE;
}

int test_filesystem(char* argv0) {
  char* error = NULL;

  LoveC_FilesystemRef filesystem = love_filesystem_getInstance();
  printf("%x\n", filesystem);

  if (!love_filesystem_init(filesystem, argv0, &error)) {
    printf("Error love_filesystem_init: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  const char* str = NULL;
  love_filesystem_getIdentity(filesystem, &str);
  printf("Identity: %s\n", str);

  if (!love_filesystem_setIdentity(filesystem, "love_c", 1, &error)) {
    printf("Error love_filesystem_setIdentity: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  love_filesystem_getIdentity(filesystem, &str);
  printf("Identity: %s\n", str);
  printf("Refcount: %d\n", love_Object_getReferenceCount((LoveC_ObjectRef)filesystem));

  LoveC_FileDataRef fileData = NULL;

  if (!love_filesystem_newFileData__string(filesystem, "asdfg", "test.txt", &fileData, &error)) {
    printf("Error love_filesystem_newFileData: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  love_filesystem_FileData_getFilename(fileData, &str);
  printf("FileData filename: %s\n", str);

  love_filesystem_FileData_getName(fileData, &str);
  printf("FileData name: %s\n", str);

  love_filesystem_FileData_getExtension(fileData, &str);
  printf("FileData extension: %s\n", str);


  LoveC_FileRef file = NULL;
  if (!love_filesystem_newFile(filesystem, "hoge.lua", MODE_WRITE, &file, &error)) {
    printf("Error love_filesystem_newFile: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  love_filesystem_File_getFilename(file, &str);
  printf("File filename: %s\n", str);

  love_filesystem_File_getExtension(file, &str);
  printf("File extension: %s\n", str);

  char data[] = "print('piyo')";

  if (!love_filesystem_File_write__void_ptr(file, data, strlen(data), &error)) {
    printf("Error love_filesystem_write__void_ptr: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  const char* working = NULL;
  love_filesystem_getWorkingDirectory(filesystem, &working);
  printf("Working directory: %s\n", working);

  char **files = malloc(sizeof(char*)*20);
  LoveC_Int64 size;
  love_filesystem_getDirectoryItems(filesystem, "", &files, &size);

  for (LoveC_Int64 i = 0; i < size; i++) {
    printf("FILE: %s\n", files[i]);
  }
  free(files);

  char* real = NULL;
  if (!love_filesystem_getRealDirectory(filesystem, "hoge.lua", &real, &error)) {
    printf("Error love_filesystem_getRealDirectory: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  printf("Real directory: %s\n", real);
  free(real);

  return LOVE_C_TRUE;
}

int test_window() {
  LoveC_WindowRef window = love_window_getInstance();

  printf("Window: %x\n", window);

  /* printf("Window isOpen: %s\n", love_window_isOpen(window)); */

  return LOVE_C_TRUE;
}

int test_graphics() {
  char* error = NULL;

  LoveC_GraphicsRef graphics = love_graphics_getInstance();

  printf("Graphics: %x\n", graphics);

  LoveC_Colorf **colors = malloc(sizeof(LoveC_Colorf*)*20);
  colors[0] = malloc(sizeof(LoveC_Colorf));
  colors[0]->r = 1.0f;
  colors[0]->g = 1.0f;
  colors[0]->b = 1.0f;
  colors[1] = NULL;

  LoveC_Bool *discards = malloc(sizeof(LoveC_Bool)*20);
  discards[0] = LOVE_C_TRUE;
  discards[1] = LOVE_C_NIL;

  LoveC_Colorf colorBox = {
    .r = 0.86,
    .g = 0.86,
    .b = 0.86,
    .a = 0.86,
  };

  LoveC_Colorf colorCell = {
    .r = 1.0,
    .g = 0.0,
    .b = 1.0,
    .a = 0.86,
  };

  int cellSize = 5;
  int cellDrawSize = cellSize - 1;
  int width = love_graphics_getWidth(graphics);
  int height = love_graphics_getHeight(graphics);
  int cellsX = width / cellSize;
  int cellsY = height / cellSize;

  int i, j;
  char** cells = malloc(sizeof(char*)*cellsY);
  char** nextcells = malloc(sizeof(char*)*cellsY);
  for (i = 0; i < cellsY; i++) {
    cells[i] = malloc(sizeof(char)*cellsX);
    nextcells[i] = malloc(sizeof(char)*cellsX);
    memset(cells[i], '\0', cellsX);
    memset(nextcells[i], '\0', cellsX);
  }

  int x, y, dx, dy;

  for (y = 0; y < cellsY; y++) {
    for (x = 0; x < cellsX; x++) {
      cells[y][x] = rand() % 2;
    }
  }

  for (i = 0; i < 1000; i++) {
    for (y = 0; y < cellsY; y++) {
      for (x = 0; x < cellsX; x++) {
        int neighborCount = 0;

        for (dy = -1; dy <= 1; dy++) {
          for (dx = -1; dx <= 1; dx++) {
            if (!(dx == 0 && dy == 0)) {
              if (y + dy >= 0 && y + dy < cellsY) {
                if (x + dx >= 0 && x + dx < cellsX) {
                  if (cells[y+dy][x+dx] == 1) {
                    neighborCount++;
                  }
                }
              }
            }
          }
        }

        if (neighborCount == 3 || (cells[y][x] == 1 && neighborCount == 2)) {
          nextcells[y][x] = 1;
        } else {
          nextcells[y][x] = 0;
        }
      }
    }

    for (j = 0; j < cellsY; j++) {
      memcpy(cells[j], nextcells[j], cellsX);
    }

    if (!love_graphics_clear(graphics, (const LoveC_Colorf**)colors, LOVE_C_NIL, LOVE_C_NIL, &error)) {
      printf("Error love_graphics_clear: %s\n", error);
      free(error);
      return LOVE_C_FALSE;
    }

    love_graphics_discard(graphics, discards, LOVE_C_TRUE);

    for (y = 0; y < cellsY; y++) {
      for (x = 0; x < cellsX; x++) {
        if (cells[y][x] == 1) {
          love_graphics_setColor(graphics, &colorCell);
        } else {
          love_graphics_setColor(graphics, &colorBox);
        }
        if (!love_graphics_rectangle(graphics, DRAW_FILL, x * cellSize, y * cellSize, cellDrawSize, cellDrawSize, 0.0, 0.0, LOVE_C_NIL, &error)) {
          printf("Error love_graphics_rectangle: %s\n", error);
          free(error);
          return LOVE_C_FALSE;
        }
      }
    }

    if (!love_graphics_present(graphics, &error)) {
      printf("Error love_graphics_present: %s\n", error);
      free(error);
      return LOVE_C_FALSE;
    }
  }

  free(colors);
  free(discards);

  return LOVE_C_TRUE;
}

int main(int argc, char *argv[]) {
  char* error = NULL;

  if (!init()) {
    return 1;
  }

  printf("Hello, world! %s\n", love_c_version());

  if (!test_filesystem(argv[0])) {
    return 1;
  }

  if (!test_window()) {
    return 1;
  }

  if (!test_graphics()) {
    return 1;
  }

  return 0;
}

/* #endif */
