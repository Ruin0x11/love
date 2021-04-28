#include "c_File.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "File.h"

using namespace love;
using namespace love::filesystem;


LoveC_Bool love_filesystem_File_open(LoveC_FileRef ref, LoveC_File_Mode mode, char** outError) {
  auto file = unwrap<File>(ref);
  auto file_mode = static_cast<File::Mode>(mode);

  try {
    return file->open(file_mode);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }
}

LoveC_Bool love_filesystem_File_close(LoveC_FileRef ref) {
  auto file = unwrap<File>(ref);

  return file->close();
}

LoveC_Bool love_filesystem_File_isOpen(LoveC_FileRef ref) {
  auto file = unwrap<File>(ref);

  return file->isOpen();
}

LoveC_Int64 love_filesystem_File_getSize(LoveC_FileRef ref, char** outError) {
  auto file = unwrap<File>(ref);

  try {
    return file->getSize();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }
}


LoveC_Bool love_filesystem_File_read__FileData(LoveC_FileRef ref, LoveC_Int64 size, LoveC_FileDataRef *outFileData, char** outError) {
  auto file = unwrap<File>(ref);
  FileData* d = nullptr;

  try {
    d = file->read(size);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outFileData = wrap<LoveC_FileDataRef>(d);

  return true;
}

LoveC_Bool love_filesystem_File_read__void_ptr(LoveC_FileRef ref, void *dst, LoveC_Int64 size, char** outError) {
  auto file = unwrap<File>(ref);

  try {
    return file->read(dst, size);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }
}


LoveC_Bool love_filesystem_File_write__void_ptr(LoveC_FileRef ref, void *data, LoveC_Int64 size, char** outError) {
  auto file = unwrap<File>(ref);

  try {
    return file->write(data, size);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }
}

LoveC_Bool love_filesystem_File_write__Data(LoveC_FileRef ref, LoveC_DataRef dataRef, LoveC_Int64 size, char** outError) {
  auto file = unwrap<File>(ref);
  auto data = unwrap<Data>(dataRef);

  try {
    return file->write(data, size);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }
}


LoveC_Bool love_filesystem_File_flush(LoveC_FileRef ref, char** outError) {
  auto file = unwrap<File>(ref);

  try {
    return file->flush();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }
}

LoveC_Bool love_filesystem_File_isEOF(LoveC_FileRef ref) {
  auto file = unwrap<File>(ref);

  return file->isEOF();
}

LoveC_Int64 love_filesystem_File_tell(LoveC_FileRef ref) {
  auto file = unwrap<File>(ref);

  return file->tell();
}

LoveC_Bool love_filesystem_File_seek(LoveC_FileRef ref, LoveC_UInt64 pos) {
  auto file = unwrap<File>(ref);

  return file->seek(pos);
}

LoveC_File_BufferMode love_filesystem_File_getBuffer(LoveC_FileRef ref, LoveC_Int64 *outSize) {
  auto file = unwrap<File>(ref);
  int64 size = 0;

  File::BufferMode bufmode = file->getBuffer(size);
  auto bufmode_wrap = static_cast<LoveC_File_BufferMode>(bufmode);

  *outSize = size;
  return bufmode_wrap;
}

LoveC_File_Mode love_filesystem_File_getMode(LoveC_FileRef ref) {
  auto file = unwrap<File>(ref);

  File::Mode mode = file->getMode();
  auto mode_wrap = static_cast<LoveC_File_Mode>(mode);

  return mode_wrap;
}

void love_filesystem_File_getFilename(LoveC_FileRef ref, const char** outFilename) {
  auto file = unwrap<File>(ref);

  *outFilename = file->getFilename().c_str();
}

void love_filesystem_File_getExtension(LoveC_FileRef ref, const char** outExtension) {
  auto file = unwrap<File>(ref);

  *outExtension = file->getExtension().c_str();
}
