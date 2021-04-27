#include "runtime_c.h"

#include "common/Module.h"

namespace love {
namespace love_c {

LoveC_Bool register_module(const WrappedModule& m, char** error) {
  m.type->init();

  try {
    Module::registerInstance(m.module);
  } catch (const std::exception& e) {
    *error = strdup(e.what());
    return false;
  }

  return true;
}

}
}
