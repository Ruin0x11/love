#include "modules/love_c/runtime_c.h"

#include "c_Object.h"

#include "common/Object.h"

using namespace love;

LoveC_Int love_Object_getReferenceCount(LoveC_ObjectRef ref) {
  return unwrap<Object>(ref)->getReferenceCount();
}

void love_Object_retain(LoveC_ObjectRef ref) {
  unwrap<Object>(ref)->retain();
}

void love_Object_release(LoveC_ObjectRef ref) {
  unwrap<Object>(ref)->release();
}
