#ifndef LOVE_LOVE_C_H
#define LOVE_LOVE_C_H

// LOVE
#include "common/config.h"
#include "common/c_wrap.h"
#include "types.h"

LOVE_C_EXTERN_C_BEGIN

LOVE_EXPORT LoveC_Bool love_c_init(char** error);
LOVE_EXPORT const char *love_c_version();

LOVE_C_EXTERN_C_END

#endif // LOVE_LOVE_C_H
