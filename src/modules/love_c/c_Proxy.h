#ifndef LOVE_LOVE_C_C_PROXY_H
#define LOVE_LOVE_C_C_PROXY_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "types.h"

#include "c_Type.h"
#include "c_Object.h"

LOVE_C_EXTERN_C_BEGIN


typedef struct LoveC_Proxy {
  LoveC_TypeRef type;
  LoveC_ObjectRef object;
} LoveC_Proxy;


LOVE_C_EXTERN_C_END

#endif // LOVE_LOVE_C_C_OBJECT_H
