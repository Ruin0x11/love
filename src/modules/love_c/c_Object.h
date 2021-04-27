#ifndef LOVE_LOVE_C_C_OBJECT_H
#define LOVE_LOVE_C_C_OBJECT_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "types.h"

LOVE_C_EXTERN_C_BEGIN


typedef void* LoveC_ObjectRef;

LOVE_EXPORT LoveC_Int love_Object_getReferenceCount(LoveC_ObjectRef ref);
LOVE_EXPORT void love_Object_retain(LoveC_ObjectRef ref);
LOVE_EXPORT void love_Object_release(LoveC_ObjectRef ref);

LOVE_C_EXTERN_C_END

#endif // LOVE_LOVE_C_C_OBJECT_H
