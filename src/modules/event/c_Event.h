#ifndef LOVE_EVENT_C_EVENT_H
#define LOVE_EVENT_C_EVENT_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "love_c/c_Variant.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_Event_MessageHandle;
typedef struct LoveC_Event_MessageHandle* LoveC_Event_MessageRef;

LOVE_EXPORT LoveC_Event_MessageRef love_Event_Message_construct(const char* name, const LoveC_VariantRef* args, LoveC_Int64 argsSize);
LOVE_EXPORT const char* love_Event_Message_getName(LoveC_Event_MessageRef messageRef);
LOVE_EXPORT void love_Event_Message_getArgs(LoveC_Event_MessageRef messageRef, LoveC_VariantRef** outArgs, LoveC_Int64* outSize);

LOVE_EXPORT LoveC_Bool love_event_poll(LoveC_Event_MessageRef* outMessage);
LOVE_EXPORT LoveC_Result love_event_pump(char** outError);
LOVE_EXPORT LoveC_Result love_event_wait(LoveC_Event_MessageRef* outMessage, char** outError);
LOVE_EXPORT void love_event_push(LoveC_Event_MessageRef messageRef);
LOVE_EXPORT LoveC_Result love_event_clear(char** outError);

LOVE_EXPORT LoveC_Bool love_event_registerModule(char** outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_EVENT_C_EVENT_H
