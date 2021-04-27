/* #ifdef LOVE_BUILD_C_API */

#include <stdio.h>
#include "../modules/love_c/love_c.h"

int main() {
  printf("Hello, world! %s\n", love_version());
}

/* #endif */
