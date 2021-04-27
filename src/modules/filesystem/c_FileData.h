#ifndef LOVE_FILESYSTEM_C_FILEDATA_H
#define LOVE_FILESYSTEM_C_FILEDATA_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Data.h"

LOVE_C_EXTERN_C_BEGIN


typedef LoveC_DataRef LoveC_FileDataRef;

LOVE_EXPORT void love_filesystem_FileData_getFilename(LoveC_FileDataRef ref, const char** outFilename);
LOVE_EXPORT void love_filesystem_FileData_getExtension(LoveC_FileDataRef ref, const char** outExtension);
LOVE_EXPORT void love_filesystem_FileData_getName(LoveC_FileDataRef ref, const char** outName);


LOVE_C_EXTERN_C_END

#endif // LOVE_FILESYSTEM_C_FILEDATA_H
