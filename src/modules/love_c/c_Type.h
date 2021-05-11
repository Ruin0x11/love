#ifndef LOVE_LOVE_C_C_TYPE_H
#define LOVE_LOVE_C_C_TYPE_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "types.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_TypeHandle;
typedef struct LoveC_TypeHandle* LoveC_TypeRef;


const char* love_Type_getName(const LoveC_TypeRef ref);
LoveC_UInt32 love_Type_getId(const LoveC_TypeRef ref);
LoveC_TypeRef love_Type_byName(const char *name);


LOVE_C_EXTERN_C_END

#endif // LOVE_LOVE_C_C_OBJECT_H
