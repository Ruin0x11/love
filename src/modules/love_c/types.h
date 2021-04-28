#ifndef LOVE_C_TYPES_H
#define LOVE_C_TYPES_H

// C standard sized integer types.
#include <stdint.h>

#include "common/c_wrap.h"

LOVE_C_EXTERN_C_BEGIN


typedef int LoveC_Bool;
typedef int LoveC_OptionalBool; // 0 (false), 1 (true) or -1 (nil)
typedef int LoveC_Int;
typedef int LoveC_OptionalInt; // > 0 or -1 (nil)
typedef int64_t LoveC_Int64;
typedef uint32_t LoveC_UInt32;
typedef uint64_t LoveC_UInt64;

typedef struct LoveC_Colorf {
  float r;
  float g;
  float b;
  float a;
} LoveC_Colorf;

typedef struct LoveC_Color32 {
  LoveC_UInt32 r;
  LoveC_UInt32 g;
  LoveC_UInt32 b;
  LoveC_UInt32 a;
} LoveC_Color32;

typedef struct LoveC_Vertex
{
	float x, y;
	float s, t;
	LoveC_Color32 color;
} LoveC_Vertex;

typedef struct LoveC_Vector2
{
  float x;
  float y;
} LoveC_Vector2;

typedef struct LoveC_Rect
{
  int x, y;
  int w, h;
} LoveC_Rect;

#define LOVE_C_NIL (-1)
#define LOVE_C_TRUE (1)
#define LOVE_C_FALSE (0)


LOVE_C_EXTERN_C_END

#endif // LOVE_C_TYPES_H
