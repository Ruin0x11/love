#include "c_Data.h"

#include "common/c_wrap.h"
#include "runtime_c.h"

#include "common/Data.h"

using namespace love;


LoveC_DataRef love_Data_clone(const LoveC_DataRef ref) {
  auto clone = unwrap<Data>(ref)->clone();
  return wrap<LoveC_DataRef>(clone);
}

void* love_Data_getData(const LoveC_DataRef ref) {
  return unwrap<Data>(ref)->getData();
}

LoveC_Int64 love_Data_getSize(const LoveC_DataRef ref) {
  return unwrap<Data>(ref)->getSize();
}
