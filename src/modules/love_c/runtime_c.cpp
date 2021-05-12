#include "runtime_c.h"

#include "common/Module.h"

namespace love {
namespace love_c {

LoveC_Result register_module(const WrappedModule& m, char** outError) {
  m.type->init();

  try {
    Module::registerInstance(m.module);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

}
}
