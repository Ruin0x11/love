#ifndef LOVE_LOVE_C_C_DATA_H
#define LOVE_LOVE_C_C_DATA_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "types.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_DataHandle;
typedef struct LoveC_DataHandle* LoveC_DataRef;


LoveC_DataRef love_Data_clone(const LoveC_DataRef ref);
void* love_Data_getData(const LoveC_DataRef ref);
LoveC_Int64 love_Data_getSize(const LoveC_DataRef ref);


LOVE_C_EXTERN_C_END

#endif // LOVE_LOVE_C_C_OBJECT_H
