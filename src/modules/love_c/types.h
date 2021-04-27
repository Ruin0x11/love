#ifndef LOVE_C_TYPES_H
#define LOVE_C_TYPES_H

// C standard sized integer types.
#include <stdint.h>

#include "common/c_wrap.h"

LOVE_C_EXTERN_C_BEGIN


typedef int LoveC_Bool;
typedef int LoveC_Int;
typedef int64_t LoveC_Int64;
typedef uint64_t LoveC_UInt64;

typedef struct LoveC_Colorf {
  float r;
  float g;
  float b;
  float a;
} LoveC_Colorf;

#define LOVE_C_NIL (-1)
#define LOVE_C_TRUE (1)
#define LOVE_C_FALSE (0)


LOVE_C_EXTERN_C_END

#endif // LOVE_C_TYPES_H
