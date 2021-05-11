#ifndef LOVE_C_VARIANT_H
#define LOVE_C_VARIANT_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "c_Proxy.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_VariantHandle;
typedef struct LoveC_VariantHandle* LoveC_VariantRef;

struct LoveC_Variant_SharedStringHandle;
typedef struct LoveC_Variant_SharedStringHandle* LoveC_Variant_SharedStringRef;

struct LoveC_Variant_SharedTableHandle;
typedef struct LoveC_Variant_SharedTableHandle* LoveC_Variant_SharedTableRef;

typedef enum LoveC_Variant_Type {
  VARIANT_UNKNOWN = 0,
  VARIANT_BOOLEAN,
  VARIANT_NUMBER,
  VARIANT_STRING,
  VARIANT_SMALLSTRING,
  VARIANT_LUSERDATA,
  VARIANT_LOVEOBJECT,
  VARIANT_NIL,
  VARIANT_TABLE
} LoveC_Variant_Type;

#define MAX_SMALL_STRING_LENGTH 15
typedef union LoveC_Variant_Data {
  LoveC_Bool boolean;
  double number;
  LoveC_Variant_SharedStringRef string;
  void *userdata;
  LoveC_Proxy objectproxy;
  LoveC_Variant_SharedTableRef table;
  struct {
    char str[MAX_SMALL_STRING_LENGTH];
    char len;
  } smallstring;
} LoveC_Variant_Data;
#undef MAX_SMALL_STRING_LENGTH

LOVE_EXPORT LoveC_Variant_Type love_Variant_getType(const LoveC_VariantRef ref);
LOVE_EXPORT const LoveC_Variant_Data* love_Variant_getData(const LoveC_VariantRef ref);


LOVE_C_EXTERN_C_END

#endif // LOVE_C_VARIANT_H
