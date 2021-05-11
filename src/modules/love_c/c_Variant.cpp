#include "c_Variant.h"

#include "common/c_wrap.h"
#include "runtime_c.h"

#include "common/Variant.h"

using namespace love;


LoveC_Variant_Type love_Variant_getType(LoveC_VariantRef ref) {
  auto type = unwrap<Variant>(ref)->getType();
  return static_cast<LoveC_Variant_Type>(type);
}

const LoveC_Variant_Data* love_Variant_getData(LoveC_VariantRef ref) {
  auto& data = unwrap<Variant>(ref)->getData();
  return reinterpret_cast<const LoveC_Variant_Data*>(&data);
}
