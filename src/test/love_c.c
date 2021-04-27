/* #ifdef LOVE_BUILD_C_API */

#include <stdio.h>
#include <stdlib.h>
#include "../modules/love_c/love_c.h"

#include "../modules/filesystem/c_Filesystem.h"

int main() {
  char* error = NULL;

  if (!love_c_init(&error)) {
    printf("Error: %s\n", error);
    free(error);
    return 1;
  }

  printf("Hello, world! %s\n", love_c_version());

  LoveC_FilesystemRef filesystem = love_filesystem_get_instance();
  printf("%x\n", filesystem);
}

/* #endif */
