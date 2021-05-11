#include "c_Timer.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Timer.h"

using namespace love;
using namespace love::timer;

#define instance() (Module::getInstance<Timer>(Module::M_TIMER))


LOVE_EXPORT double love_timer_step(){
  return instance()->step();
}

LOVE_EXPORT double love_timer_getDelta(){
  return instance()->getDelta();
}

LOVE_EXPORT int love_timer_getFPS(){
  return instance()->getFPS();
}

LOVE_EXPORT double love_timer_getAverageDelta(){
  return instance()->getAverageDelta();
}

LOVE_EXPORT void love_timer_sleep(double seconds){
  instance()->sleep(seconds);
}

LOVE_EXPORT double love_timer_getTime(){
  return instance()->getTime();
}


LoveC_Result love_timer_registerModule(char** outError) {
  Timer *instance = instance();
  if (instance == nullptr) {
    try {
      instance = new love::timer::Timer();
    } catch (const std::exception &e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  WrappedModule w;
  w.module = instance;
  w.name = "timer";
  w.type = &Module::type;
  w.functions = nullptr;
  w.types = nullptr;

  return love_c::register_module(w, outError);
}
