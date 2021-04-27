#include "c_Filesystem.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Filesystem.h"

#include "physfs/Filesystem.h"

using namespace love;
using namespace love::filesystem;

DEFINE_C_WRAPPER_FUNCTIONS(Filesystem, LoveC_FilesystemRef)

#define instance() (Module::getInstance<Filesystem>(Module::M_FILESYSTEM))

LoveC_FilesystemRef love_filesystem_get_instance() {
  auto inst = instance();
  return wrap(inst);
}

LoveC_Bool love_filesystem_init(LoveC_FilesystemRef filesystem, const char* argv0, char** error) {
  try {
    unwrap(filesystem)->init(argv0);
  } catch (const std::exception &e) {
    *error = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_filesystem_register_module(char** error) {
  Filesystem *instance = instance();
  if (instance == nullptr) {
    try {
      instance = new physfs::Filesystem();
    } catch (const std::exception &e) {
      *error = strdup(e.what());
      return false;
    }
  } else {
    instance->retain();
  }

  WrappedModule w;
  w.module = instance;
  w.name = "filesystem";
  w.type = &Filesystem::type;
  w.functions = nullptr;
  w.types = nullptr;

  return love_c::register_module(w, error);
}
