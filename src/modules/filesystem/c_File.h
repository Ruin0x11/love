#ifndef LOVE_FILESYSTEM_C_FILE_H
#define LOVE_FILESYSTEM_C_FILE_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Data.h"
#include "c_FileData.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_FileHandle;
typedef struct LoveC_FileHandle* LoveC_FileRef;

typedef enum LoveC_File_Mode {
  MODE_CLOSED,
  MODE_READ,
  MODE_WRITE,
  MODE_APPEND,
  MODE_MAX_ENUM
} LoveC_File_Mode;

typedef enum LoveC_File_BufferMode {
  BUFFER_NONE,
  BUFFER_LINE,
  BUFFER_FULL,
  BUFFER_MAX_ENUM
} LoveC_File_BufferMode;

LOVE_EXPORT LoveC_Bool love_filesystem_File_open(LoveC_FileRef ref, LoveC_File_Mode mode, char** outError);
LOVE_EXPORT LoveC_Bool love_filesystem_File_close(LoveC_FileRef ref);
LOVE_EXPORT LoveC_Bool love_filesystem_File_isOpen(LoveC_FileRef ref);
LOVE_EXPORT LoveC_Int64 love_filesystem_File_getSize(LoveC_FileRef ref, char** outError);

LOVE_EXPORT LoveC_Bool love_filesystem_File_read__FileData(LoveC_FileRef ref, LoveC_Int64 size, LoveC_FileDataRef *outFileData, char** outError);
LOVE_EXPORT LoveC_Bool love_filesystem_File_read__void_ptr(LoveC_FileRef ref, void *dst, LoveC_Int64 size, char** outError);

LOVE_EXPORT LoveC_Bool love_filesystem_File_write__void_ptr(LoveC_FileRef ref, void *data, LoveC_Int64 size, char** outError);
LOVE_EXPORT LoveC_Bool love_filesystem_File_write__Data(LoveC_FileRef ref, LoveC_DataRef dataRef, LoveC_Int64 size, char** outError);

LOVE_EXPORT LoveC_Bool love_filesystem_File_flush(LoveC_FileRef ref, char** outError);
LOVE_EXPORT LoveC_Bool love_filesystem_File_isEOF(LoveC_FileRef ref);
LOVE_EXPORT LoveC_Int64 love_filesystem_File_tell(LoveC_FileRef ref);
LOVE_EXPORT LoveC_Bool love_filesystem_File_seek(LoveC_FileRef ref, LoveC_UInt64 pos);
LOVE_EXPORT LoveC_File_BufferMode love_filesystem_File_getBuffer(LoveC_FileRef ref, LoveC_Int64 *outSize);
LOVE_EXPORT LoveC_File_Mode love_filesystem_File_getMode(LoveC_FileRef ref);
LOVE_EXPORT void love_filesystem_File_getFilename(LoveC_FileRef ref, const char** outFilename);
LOVE_EXPORT void love_filesystem_File_getExtension(LoveC_FileRef ref, const char** outExtension);


LOVE_C_EXTERN_C_END

#endif // LOVE_FILESYSTEM_C_FILE_H
