#include "c_Type.h"

#include "common/c_wrap.h"
#include "runtime_c.h"

#include "common/types.h"

using namespace love;


const char* love_Type_getName(const LoveC_TypeRef ref) {
  return unwrap<Type>(ref)->getName();
}

LoveC_UInt32 love_Type_getId(const LoveC_TypeRef ref) {
  return unwrap<Type>(ref)->getId();
}

LoveC_TypeRef love_Type_byName(const char *name) {
  return wrap<LoveC_TypeRef>(Type::byName(name));
}
