/* #ifdef LOVE_BUILD_C_API */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../modules/love_c/love_c.h"
#include "../modules/filesystem/c_Filesystem.h"

int init() {
  char* error = NULL;

  if (!love_c_init(&error)) {
    printf("Error: %s\n", error);
    free(error);
    return 0;
  }

  LoveC_FilesystemRef filesystem = love_filesystem_getInstance();

  char* exepath = NULL;
  love_filesystem_getExecutablePath(filesystem, &exepath);
  if (exepath == NULL) {
    printf("No exepath\n");
    return 0;
  }

  printf("Exepath: %s\n", exepath);

  LoveC_Bool is_fused = love_filesystem_setSource(filesystem, exepath, &error);
  if (is_fused) {
    printf("Is fused\n", error);
    free(error);
  }

  love_filesystem_setFused(filesystem, is_fused);

  return 1;
}

int main(int argc, char *argv[]) {
  char* error = NULL;

  if (!init()) {
    return 1;
  }

  printf("Hello, world! %s\n", love_c_version());

  LoveC_FilesystemRef filesystem = love_filesystem_getInstance();
  printf("%x\n", filesystem);

  if (!love_filesystem_init(filesystem, argv[0], &error)) {
    printf("Error love_filesystem_init: %s\n", error);
    free(error);
    return 1;
  }

  const char* str = NULL;
  love_filesystem_getIdentity(filesystem, &str);
  printf("Identity: %s\n", str);

  if (!love_filesystem_setIdentity(filesystem, "love_c", 1, &error)) {
    printf("Error love_filesystem_setIdentity: %s\n", error);
    free(error);
    return 1;
  }

  love_filesystem_getIdentity(filesystem, &str);
  printf("Identity: %s\n", str);
  printf("Refcount: %d\n", love_Object_getReferenceCount(filesystem));

  LoveC_FileDataRef fileData = NULL;

  if (!love_filesystem_newFileData__string(filesystem, "asdfg", "test.txt", &fileData, &error)) {
    printf("Error love_filesystem_newFileData: %s\n", error);
    free(error);
    return 1;
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
    return 1;
  }

  love_filesystem_File_getFilename(file, &str);
  printf("File filename: %s\n", str);

  love_filesystem_File_getExtension(file, &str);
  printf("File extension: %s\n", str);

  char data[] = "print('piyo')";

  if (!love_filesystem_File_write__void_ptr(file, data, 10, &error)) {
    printf("Error love_filesystem_write__void_ptr: %s\n", error);
    free(error);
    return 1;
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
    return 1;
  }

  printf("Real directory: %s\n", real);
  free(real);

  return 0;
}

/* #endif */
