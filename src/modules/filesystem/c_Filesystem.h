#ifndef LOVE_FILESYSTEM_C_FILESYSTEM_H
#define LOVE_FILESYSTEM_C_FILESYSTEM_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Module.h"

#include "c_File.h"
#include "c_FileData.h"

LOVE_C_EXTERN_C_BEGIN


typedef enum LoveC_Filesystem_FileType {
  FILETYPE_FILE,
  FILETYPE_DIRECTORY,
  FILETYPE_SYMLINK,
  FILETYPE_OTHER,
  FILETYPE_MAX_ENUM,
} LoveC_Filesystem_FileType;

typedef struct LoveC_Filesystem_InfoStruct {
  LoveC_Int64 size;
  LoveC_Int64 modtime;
  LoveC_Filesystem_FileType type;
} LoveC_Filesystem_InfoStruct;

LOVE_EXPORT LoveC_Bool love_filesystem_init(const char* argv0, char** outError);
LOVE_EXPORT void love_filesystem_setFused(LoveC_Bool fused);
LOVE_EXPORT LoveC_Bool love_filesystem_isFused();
LOVE_EXPORT void love_filesystem_setAndroidSaveExternal(LoveC_Bool useExternal);
LOVE_EXPORT LoveC_Bool love_filesystem_setIdentity(const char* identity, LoveC_Bool append, char** outError);
LOVE_EXPORT void love_filesystem_getIdentity(const char** outIdentity);
LOVE_EXPORT LoveC_Bool love_filesystem_setSource(const char* source, char** outError);
LOVE_EXPORT void love_filesystem_getSource(const char** outSource);

LOVE_EXPORT LoveC_Bool love_filesystem_mount__string(const char* archive, const char* mountpoint, LoveC_Bool append);
// TODO love_filesystem_mount__Data
// TODO love_filesystem_mount__DroppedFile

LOVE_EXPORT LoveC_Bool love_filesystem_unmount__string(const char* archive);
// TODO love_filesystem_unmount__Data

LOVE_EXPORT LoveC_Bool love_filesystem_newFile(const char* filename, LoveC_File_Mode mode, LoveC_FileRef *outFile, char** outError);

LOVE_EXPORT LoveC_Bool love_filesystem_newFileData__string(const char* data, const char* filename, LoveC_FileDataRef *outFileData, char** outError);
// TODO love_filesystem_newFileData__File

LOVE_EXPORT void love_filesystem_getWorkingDirectory(const char** outWorkingDirectory);
LOVE_EXPORT void love_filesystem_getUserDirectory(char** outUserDirectory);
LOVE_EXPORT void love_filesystem_getAppdataDirectory(char** outAppdataDirectory);
LOVE_EXPORT void love_filesystem_getSaveDirectory(const char** outSaveDirectory);
LOVE_EXPORT void love_filesystem_getSourceBaseDirectory(char** outSourceBaseDirectory);
LOVE_EXPORT LoveC_Bool love_filesystem_getRealDirectory(const char* filename, char** outRealDirectory, char** outError);
LOVE_EXPORT void love_filesystem_getExecutablePath(char** outExecutablePath);
LOVE_EXPORT LoveC_Bool love_filesystem_getInfo(const char* filepath, LoveC_Filesystem_InfoStruct* outInfo);
LOVE_EXPORT LoveC_Bool love_filesystem_createDirectory(const char* filepath);
LOVE_EXPORT LoveC_Bool love_filesystem_remove(const char* filepath);
LOVE_EXPORT LoveC_Bool love_filesystem_read(const char* filename, LoveC_Int64 size, LoveC_FileDataRef *outFileData, char** outError);
LOVE_EXPORT LoveC_Bool love_filesystem_write(const char* filename, const void* data, LoveC_Int64 size, char** outError);
LOVE_EXPORT LoveC_Bool love_filesystem_append(const char* filename, const void* data, LoveC_Int64 size, char** outError);
LOVE_EXPORT LoveC_Bool love_filesystem_getDirectoryItems(const char* dir, char*** outItems);
LOVE_EXPORT void love_filesystem_setSymlinksEnabled(LoveC_Bool enable);
LOVE_EXPORT LoveC_Bool love_filesystem_areSymlinksEnabled();

LOVE_EXPORT LoveC_Bool love_filesystem_registerModule(char** outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_FILESYSTEM_C_FILESYSTEM_H
