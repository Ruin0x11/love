#include "c_Filesystem.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Filesystem.h"
#include "File.h"

#include "physfs/Filesystem.h"

using namespace love;
using namespace love::filesystem;

#define instance() (Module::getInstance<Filesystem>(Module::M_FILESYSTEM))


LoveC_Bool love_filesystem_init(const char* argv0, char** outError) {
  try {
    instance()->init(argv0);
  } catch (const std::exception &e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_filesystem_setFused(LoveC_Bool fused) {
  instance()->setFused(fused);
}

LoveC_Bool love_filesystem_isFused() {
  return instance()->isFused();
}

void love_filesystem_setAndroidSaveExternal(LoveC_Bool useExternal) {
  instance()->setAndroidSaveExternal(useExternal);
}

LoveC_Bool love_filesystem_setIdentity(const char* identity, LoveC_Bool append, char** outError) {
  if (!instance()->setIdentity(identity, append)) {
    *outError = strdup("Could not set write directory.");
    return false;
  }
  return true;
}

void love_filesystem_getIdentity(const char** outIdentity) {
  *outIdentity = strdup(instance()->getIdentity());
}

LoveC_Bool love_filesystem_setSource(const char* source, char** outError) {
  if (!instance()->setSource(source)) {
    *outError = strdup("Could not set source.");
    return false;
  }
  return true;
}

void love_filesystem_getSource(const char** outSource) {
  *outSource = strdup(instance()->getSource());
}

LoveC_Bool love_filesystem_mount__string(const char* archive, const char* mountpoint, LoveC_Bool append) {
  return instance()->mount(archive, mountpoint, append);
}

LoveC_Bool love_filesystem_unmount__string(const char* archive) {
  return instance()->unmount(archive);
}

LoveC_Bool love_filesystem_newFile(const char* filename, LoveC_File_Mode mode, LoveC_FileRef *outFile, char** outError) {
  auto filesystem_mode = static_cast<File::Mode>(mode);

  File *t = instance()->newFile(filename);

  if (filesystem_mode != File::MODE_CLOSED)
    {
      try
        {
          if (!t->open(filesystem_mode))
            throw love::Exception("Could not open file.");
        }
      catch (love::Exception &e)
        {
          *outError = strdup(e.what());
          return false;
        }
    }

  *outFile = wrap<LoveC_FileRef>(t);
  return true;
}

LoveC_Bool love_filesystem_newFileData__string(const char* data, const char* filename, LoveC_FileDataRef *outFileData, char** outError) {
  size_t length = strlen(data);
  FileData *t = nullptr;

  try {
    t = instance()->newFileData(data, length, filename);
  } catch(const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outFileData = wrap<LoveC_FileDataRef>(t);
  return true;
}

void love_filesystem_getWorkingDirectory(const char** outWorkingDirectory) {
  *outWorkingDirectory = instance()->getWorkingDirectory();
}

void love_filesystem_getUserDirectory(char** outUserDirectory) {
  *outUserDirectory = strdup(instance()->getUserDirectory().c_str());
}

void love_filesystem_getAppdataDirectory(char** outAppdataDirectory) {
  *outAppdataDirectory = strdup(instance()->getAppdataDirectory().c_str());
}

void love_filesystem_getSaveDirectory(const char** outSaveDirectory) {
  *outSaveDirectory = instance()->getSaveDirectory();
}

void love_filesystem_getSourceBaseDirectory(char** outSourceBaseDirectory) {
  *outSourceBaseDirectory = strdup(instance()->getSourceBaseDirectory().c_str());
}

LoveC_Bool love_filesystem_getRealDirectory(const char* filename, char** outRealDirectory, char** outError) {
  try {
    *outRealDirectory = strdup(instance()->getRealDirectory(filename).c_str());
    return true;
  } catch(const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }
}

void love_filesystem_getExecutablePath(char** outExecutablePath) {
  *outExecutablePath = strdup(instance()->getExecutablePath().c_str());
}

LoveC_Bool love_filesystem_getInfo(const char* filepath, LoveC_Filesystem_InfoStruct* outInfo) {
  Filesystem::Info info = {};

  if (!instance()->getInfo(filepath, info)) {
    return false;
  }

  outInfo->size = info.size;
  outInfo->modtime = info.modtime;
  outInfo->type = static_cast<LoveC_Filesystem_FileType>(info.type);
  return true;
}

LoveC_Bool love_filesystem_createDirectory(const char* filepath) {
  return instance()->createDirectory(filepath);
}

LoveC_Bool love_filesystem_remove(const char* filepath) {
  return instance()->remove(filepath);
}

LoveC_Bool love_filesystem_read(const char* filename, LoveC_Int64 size, LoveC_FileDataRef *outFileData, char** outError) {
  try {
    *outFileData = wrap<LoveC_FileDataRef>(instance()->read(filename, size));
  } catch(const std::exception& e){
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_filesystem_write(const char* filename, const void* data, LoveC_Int64 size, char** outError) {
  try {
    instance()->write(filename, data, size);
  } catch(const std::exception& e){
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_filesystem_append(const char* filename, const void* data, LoveC_Int64 size, char** outError) {
  try {
    instance()->append(filename, data, size);
  } catch(const std::exception& e){
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_filesystem_getDirectoryItems(const char* dir, char*** outItems) {
  std::vector<std::string> items;

  instance()->getDirectoryItems(dir, items);

  *outItems = (char**)malloc(sizeof(char*)*(items.size()+1));

  for (int i = 0; i < (int) items.size(); i++) {
    (*outItems)[i] = strdup(items[i].c_str());
  }

  (*outItems)[items.size()] = nullptr;

  return true;
}

void love_filesystem_setSymlinksEnabled(LoveC_Bool enable) {
  instance()->setSymlinksEnabled(enable);
}

LoveC_Bool love_filesystem_areSymlinksEnabled() {
  return instance()->areSymlinksEnabled();
}


LoveC_Bool love_filesystem_registerModule(char** outError) {
  Filesystem *instance = instance();
  if (instance == nullptr) {
    try {
      instance = new physfs::Filesystem();
    } catch (const std::exception &e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  WrappedModule w;
  w.module = instance;
  w.name = "filesystem";
  w.type = &Filesystem::type;
  w.functions = nullptr;
  w.types = nullptr;

  return love_c::register_module(w, outError);
}
