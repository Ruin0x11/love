/* #ifdef LOVE_BUILD_C_API */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../modules/love_c/love_c.h"
#include "../modules/love_c/c_Object.h"
#include "../modules/filesystem/c_Filesystem.h"
#include "../modules/window/c_Window.h"

#define TRUE (1)
#define FALSE (0)

int init() {
  char* error = NULL;

  if (!love_c_init(&error)) {
    printf("Error: %s\n", error);
    free(error);
    return FALSE;
  }

  LoveC_FilesystemRef filesystem = love_filesystem_getInstance();

  char* exepath = NULL;
  love_filesystem_getExecutablePath(filesystem, &exepath);
  if (exepath == NULL) {
    printf("No exepath\n");
    return FALSE;
  }

  printf("Exepath: %s\n", exepath);

  LoveC_Bool is_fused = love_filesystem_setSource(filesystem, exepath, &error);
  if (is_fused) {
    printf("Is fused\n", error);
    free(error);
  }

  love_filesystem_setFused(filesystem, is_fused);



  LoveC_WindowRef window = love_window_getInstance();


  love_window_setTitle(window, "Love C");

  LoveC_Window_WindowSettings settings;
  settings.fullscreen = FALSE;
  settings.fstype = FULLSCREEN_MAX_ENUM;
  settings.vsync = 1;
  settings.msaa = 0;
  settings.stencil = TRUE;
  settings.depth = 0;
  settings.resizable = FALSE;
  settings.minwidth = 1;
  settings.minheight = 1;
  settings.borderless = FALSE;
  settings.centered = TRUE;
  settings.display = 0;
  settings.highdpi = FALSE;
  settings.usedpiscale = TRUE;
  settings.refreshrate = 0.0;
  settings.useposition = FALSE;
  settings.x = 0;
  settings.y = 0;

  if (!love_window_setMode(window, 800, 600, &settings, &error)) {
    printf("Error initializing window: %s\n", error);
    return FALSE;
  }

  return TRUE;
}

int test_filesystem(char* argv0) {
  char* error = NULL;

  LoveC_FilesystemRef filesystem = love_filesystem_getInstance();
  printf("%x\n", filesystem);

  if (!love_filesystem_init(filesystem, argv0, &error)) {
    printf("Error love_filesystem_init: %s\n", error);
    free(error);
    return FALSE;
  }

  const char* str = NULL;
  love_filesystem_getIdentity(filesystem, &str);
  printf("Identity: %s\n", str);

  if (!love_filesystem_setIdentity(filesystem, "love_c", 1, &error)) {
    printf("Error love_filesystem_setIdentity: %s\n", error);
    free(error);
    return FALSE;
  }

  love_filesystem_getIdentity(filesystem, &str);
  printf("Identity: %s\n", str);
  printf("Refcount: %d\n", love_Object_getReferenceCount((LoveC_ObjectRef)filesystem));

  LoveC_FileDataRef fileData = NULL;

  if (!love_filesystem_newFileData__string(filesystem, "asdfg", "test.txt", &fileData, &error)) {
    printf("Error love_filesystem_newFileData: %s\n", error);
    free(error);
    return FALSE;
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
    return FALSE;
  }

  love_filesystem_File_getFilename(file, &str);
  printf("File filename: %s\n", str);

  love_filesystem_File_getExtension(file, &str);
  printf("File extension: %s\n", str);

  char data[] = "print('piyo')";

  if (!love_filesystem_File_write__void_ptr(file, data, strlen(data), &error)) {
    printf("Error love_filesystem_write__void_ptr: %s\n", error);
    free(error);
    return FALSE;
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
    return FALSE;
  }

  printf("Real directory: %s\n", real);
  free(real);

  return TRUE;
}

int test_window() {
  LoveC_WindowRef window = love_window_getInstance();

  printf("Window: %x\n", window);

  printf("Window isOpen: %s\n", love_window_isOpen(window));

  return TRUE;
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

  return 0;
}

/* #endif */
