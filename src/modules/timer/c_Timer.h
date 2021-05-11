#ifndef LOVE_TIMER_C_TIMER_H
#define LOVE_TIMER_C_TIMER_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN

LOVE_EXPORT double love_timer_step();
LOVE_EXPORT double love_timer_getDelta();
LOVE_EXPORT int love_timer_getFPS();
LOVE_EXPORT double love_timer_getAverageDelta();
LOVE_EXPORT void love_timer_sleep(double seconds);
LOVE_EXPORT double love_timer_getTime();

LOVE_EXPORT LoveC_Result love_timer_registerModule(char **outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_TIMER_C_TIMER_H
