#ifndef LOVE_FILESYSTEM_C_FILESYSTEM_H
#define LOVE_FILESYSTEM_C_FILESYSTEM_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN


typedef void* LoveC_FilesystemRef;

LOVE_EXPORT LoveC_Bool love_filesystem_register_module(char** error);
LOVE_EXPORT LoveC_FilesystemRef love_filesystem_get_instance();
LOVE_EXPORT LoveC_Bool love_filesystem_init(LoveC_FilesystemRef filesystem, const char* argv0, char** error);

LOVE_C_EXTERN_C_END

#endif // LOVE_FILESYSTEM_C_FILESYSTEM_H
