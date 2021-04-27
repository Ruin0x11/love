#ifndef LOVE_FILESYSTEM_C_FILESYSTEM_H
#define LOVE_FILESYSTEM_C_FILESYSTEM_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Module.h"

#include "c_File.h"
#include "c_FileData.h"

LOVE_C_EXTERN_C_BEGIN


typedef LoveC_ModuleRef LoveC_FilesystemRef;

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

LOVE_EXPORT LoveC_Bool love_filesystem_registerModule(char** outError);
LOVE_EXPORT LoveC_FilesystemRef love_filesystem_getInstance();
LOVE_EXPORT LoveC_Bool love_filesystem_init(LoveC_FilesystemRef ref, const char* argv0, char** outError);
LOVE_EXPORT void love_filesystem_setFused(LoveC_FilesystemRef ref, LoveC_Bool fused);
LOVE_EXPORT LoveC_Bool love_filesystem_isFused(LoveC_FilesystemRef filesystem);
LOVE_EXPORT void love_filesystem_setAndroidSaveExternal(LoveC_FilesystemRef ref, LoveC_Bool useExternal);
LOVE_EXPORT LoveC_Bool love_filesystem_setIdentity(LoveC_FilesystemRef ref, const char* identity, LoveC_Bool append, char** outError);
LOVE_EXPORT void love_filesystem_getIdentity(LoveC_FilesystemRef ref, const char** outIdentity);
LOVE_EXPORT LoveC_Bool love_filesystem_setSource(LoveC_FilesystemRef ref, const char* source, char** outError);
LOVE_EXPORT void love_filesystem_getSource(LoveC_FilesystemRef ref, const char** outSource);

LOVE_EXPORT LoveC_Bool love_filesystem_mount__string(LoveC_FilesystemRef ref, const char* archive, const char* mountpoint, LoveC_Bool append);
// TODO love_filesystem_mount__Data
// TODO love_filesystem_mount__DroppedFile

LOVE_EXPORT LoveC_Bool love_filesystem_unmount__string(LoveC_FilesystemRef ref, const char* archive);
// TODO love_filesystem_unmount__Data

LOVE_EXPORT LoveC_Bool love_filesystem_newFile(LoveC_FilesystemRef ref, const char* filename, LoveC_File_Mode mode, LoveC_FileRef *outFile, char** outError);

LOVE_EXPORT LoveC_Bool love_filesystem_newFileData__string(LoveC_FilesystemRef ref, const char* str, const char* filename, LoveC_FileDataRef *outFileData, char** outError);
// TODO love_filesystem_newFileData__File

LOVE_EXPORT void love_filesystem_getWorkingDirectory(LoveC_FilesystemRef ref, const char** outWorkingDirectory);
LOVE_EXPORT void love_filesystem_getUserDirectory(LoveC_FilesystemRef ref, char** outUserDirectory);
LOVE_EXPORT void love_filesystem_getAppdataDirectory(LoveC_FilesystemRef ref, char** outAppdataDirectory);
LOVE_EXPORT void love_filesystem_getSaveDirectory(LoveC_FilesystemRef ref, const char** outSaveDirectory);
LOVE_EXPORT void love_filesystem_getSourceBaseDirectory(LoveC_FilesystemRef ref, char** outSourceBaseDirectory);
LOVE_EXPORT LoveC_Bool love_filesystem_getRealDirectory(LoveC_FilesystemRef ref, const char* filename, char** outRealDirectory, char** outError);
LOVE_EXPORT void love_filesystem_getExecutablePath(LoveC_FilesystemRef ref, char** outExecutablePath);
LOVE_EXPORT LoveC_Bool love_filesystem_getInfo(LoveC_FilesystemRef ref, const char* filepath, LoveC_Filesystem_InfoStruct* outInfo);
LOVE_EXPORT LoveC_Bool love_filesystem_createDirectory(LoveC_FilesystemRef ref, const char* filepath);
LOVE_EXPORT LoveC_Bool love_filesystem_remove(LoveC_FilesystemRef ref, const char* filepath);
LOVE_EXPORT LoveC_Bool love_filesystem_read(LoveC_FilesystemRef ref, const char* filename, LoveC_Int64 size, LoveC_FileDataRef *outFileData, char** outError);
LOVE_EXPORT LoveC_Bool love_filesystem_write(LoveC_FilesystemRef ref, const char* filename, const void* data, LoveC_Int64 size, char** outError);
LOVE_EXPORT LoveC_Bool love_filesystem_append(LoveC_FilesystemRef ref, const char* filename, const void* data, LoveC_Int64 size, char** outError);
LOVE_EXPORT LoveC_Bool love_filesystem_getDirectoryItems(LoveC_FilesystemRef ref, const char* dir, char*** outItems, LoveC_Int64 *outSize);
LOVE_EXPORT void love_filesystem_setSymlinksEnabled(LoveC_FilesystemRef ref, LoveC_Bool enable);
LOVE_EXPORT LoveC_Bool love_filesystem_areSymlinksEnabled(LoveC_FilesystemRef ref);

LOVE_C_EXTERN_C_END

#endif // LOVE_FILESYSTEM_C_FILESYSTEM_H
