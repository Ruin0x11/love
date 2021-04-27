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


LoveC_FilesystemRef love_filesystem_getInstance() {
  auto inst = instance();
  return wrap<LoveC_FilesystemRef>(inst);
}

LoveC_Bool love_filesystem_init(LoveC_FilesystemRef ref, const char* argv0, char** outError) {
  try {
    unwrap<Filesystem>(ref)->init(argv0);
  } catch (const std::exception &e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

void love_filesystem_setFused(LoveC_FilesystemRef ref, LoveC_Bool fused) {
  unwrap<Filesystem>(ref)->setFused(fused);
}

LoveC_Bool love_filesystem_isFused(LoveC_FilesystemRef ref) {
  return unwrap<Filesystem>(ref)->isFused();
}

void love_filesystem_setAndroidSaveExternal(LoveC_FilesystemRef ref, LoveC_Bool useExternal) {
  unwrap<Filesystem>(ref)->setAndroidSaveExternal(useExternal);
}

LoveC_Bool love_filesystem_setIdentity(LoveC_FilesystemRef ref, const char* identity, LoveC_Bool append, char** outError) {
  if (!unwrap<Filesystem>(ref)->setIdentity(identity, append)) {
      *outError = strdup("Could not set write directory.");
      return false;
  }
  return true;
}

void love_filesystem_getIdentity(LoveC_FilesystemRef ref, const char** outIdentity) {
  auto real = unwrap<Filesystem>(ref);
  *outIdentity = strdup(real->getIdentity());
}

LoveC_Bool love_filesystem_setSource(LoveC_FilesystemRef ref, const char* source, char** outError) {
  if (!unwrap<Filesystem>(ref)->setSource(source)) {
      *outError = strdup("Could not set source.");
      return false;
  }
  return true;
}

void love_filesystem_getSource(LoveC_FilesystemRef ref, const char** outSource) {
  auto real = unwrap<Filesystem>(ref);
  *outSource = strdup(real->getSource());
}

LoveC_Bool love_filesystem_mount__string(LoveC_FilesystemRef ref, const char* archive, const char* mountpoint, LoveC_Bool append) {
  auto real = unwrap<Filesystem>(ref);
  return real->mount(archive, mountpoint, append);
}

LoveC_Bool love_filesystem_unmount__string(LoveC_FilesystemRef ref, const char* archive) {
  auto real = unwrap<Filesystem>(ref);
  return real->unmount(archive);
}

LoveC_Bool love_filesystem_newFile(LoveC_FilesystemRef ref, const char* filename, LoveC_File_Mode mode, LoveC_FileRef *outFile, char** outError) {
    auto real = unwrap<Filesystem>(ref);
    auto real_mode = static_cast<File::Mode>(mode);

	File *t = real->newFile(filename);

	if (real_mode != File::MODE_CLOSED)
	{
		try
		{
			if (!t->open(real_mode))
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

LoveC_Bool love_filesystem_newFileData__string(LoveC_FilesystemRef ref, const char* str, const char* filename, LoveC_FileDataRef *outFileData, char** outError) {
    auto real = unwrap<Filesystem>(ref);

	size_t length = 0;
	FileData *t = nullptr;

    try {
      t = real->newFileData(str, length, filename);
    } catch(const std::exception& e) {
      *outError = strdup(e.what());
      return false;
    }

    *outFileData = t;
    return true;
}

void love_filesystem_getWorkingDirectory(LoveC_FilesystemRef ref, const char** outWorkingDirectory) {
    auto real = unwrap<Filesystem>(ref);

    *outWorkingDirectory = real->getWorkingDirectory();
}

void love_filesystem_getUserDirectory(LoveC_FilesystemRef ref, char** outUserDirectory) {
    auto real = unwrap<Filesystem>(ref);

    *outUserDirectory = strdup(real->getUserDirectory().c_str());
}

void love_filesystem_getAppdataDirectory(LoveC_FilesystemRef ref, char** outAppdataDirectory) {
    auto real = unwrap<Filesystem>(ref);

    *outAppdataDirectory = strdup(real->getAppdataDirectory().c_str());
}

void love_filesystem_getSaveDirectory(LoveC_FilesystemRef ref, const char** outSaveDirectory) {
    auto real = unwrap<Filesystem>(ref);

    *outSaveDirectory = real->getSaveDirectory();
}

void love_filesystem_getSourceBaseDirectory(LoveC_FilesystemRef ref, char** outSourceBaseDirectory) {
    auto real = unwrap<Filesystem>(ref);

    *outSourceBaseDirectory = strdup(real->getSourceBaseDirectory().c_str());
}

LoveC_Bool love_filesystem_getRealDirectory(LoveC_FilesystemRef ref, const char* filename, char** outRealDirectory, char** outError) {
    auto real = unwrap<Filesystem>(ref);

    try {
      *outRealDirectory = strdup(real->getRealDirectory(filename).c_str());
      return true;
    } catch(const std::exception& e) {
      *outError = strdup(e.what());
      return false;
    }
}

void love_filesystem_getExecutablePath(LoveC_FilesystemRef ref, char** outExecutablePath) {
    auto real = unwrap<Filesystem>(ref);

    *outExecutablePath = strdup(real->getExecutablePath().c_str());
}

LoveC_Bool love_filesystem_getInfo(LoveC_FilesystemRef ref, const char* filepath, LoveC_Filesystem_InfoStruct* outInfo) {
    auto real = unwrap<Filesystem>(ref);

	Filesystem::Info info = {};

    if (!real->getInfo(filepath, info)) {
      return false;
    }

    outInfo->size = info.size;
    outInfo->modtime = info.modtime;
    outInfo->type = static_cast<LoveC_Filesystem_FileType>(info.type);
    return true;
}

LoveC_Bool love_filesystem_createDirectory(LoveC_FilesystemRef ref, const char* filepath) {
    auto real = unwrap<Filesystem>(ref);

    return real->createDirectory(filepath);
}

LoveC_Bool love_filesystem_remove(LoveC_FilesystemRef ref, const char* filepath) {
    auto real = unwrap<Filesystem>(ref);

    return real->remove(filepath);
}

LoveC_Bool love_filesystem_read(LoveC_FilesystemRef ref, const char* filename, LoveC_Int64 size, LoveC_FileDataRef *outFileData, char** outError) {
    auto real = unwrap<Filesystem>(ref);

    try {
      *outFileData = real->read(filename, size);
    } catch(const std::exception& e){
      *outError = strdup(e.what());
      return false;
    }

    return true;
}

LoveC_Bool love_filesystem_write(LoveC_FilesystemRef ref, const char* filename, const void* data, LoveC_Int64 size, char** outError) {
    auto real = unwrap<Filesystem>(ref);

    try {
      real->write(filename, data, size);
    } catch(const std::exception& e){
      *outError = strdup(e.what());
      return false;
    }

    return true;
}

LoveC_Bool love_filesystem_append(LoveC_FilesystemRef ref, const char* filename, const void* data, LoveC_Int64 size, char** outError) {
    auto real = unwrap<Filesystem>(ref);

    try {
      real->append(filename, data, size);
    } catch(const std::exception& e){
      *outError = strdup(e.what());
      return false;
    }

    return true;
}

LoveC_Bool love_filesystem_getDirectoryItems(LoveC_FilesystemRef ref, const char* dir, char*** outItems, LoveC_Int64 *outSize) {
  auto real = unwrap<Filesystem>(ref);
  std::vector<std::string> items;

  instance()->getDirectoryItems(dir, items);

  for (int i = 0; i < (int) items.size(); i++) {
    *(outItems[i]) = strdup(items[i].c_str());
  }

  *outSize = items.size();

  return true;
}

void love_filesystem_setSymlinksEnabled(LoveC_FilesystemRef ref, LoveC_Bool enable) {
    auto real = unwrap<Filesystem>(ref);

    real->setSymlinksEnabled(enable);
}

LoveC_Bool love_filesystem_areSymlinksEnabled(LoveC_FilesystemRef ref) {
    auto real = unwrap<Filesystem>(ref);

    return real->areSymlinksEnabled();
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
