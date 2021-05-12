#include "c_Event.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Event.h"

#include "sdl/Event.h"

using namespace love;
using namespace love::event;

#define instance() (Module::getInstance<Event>(Module::M_EVENT))


LoveC_Event_MessageRef love_Event_Message_construct(const char* name, const LoveC_VariantRef* args, LoveC_Int64 argsSize) {
  if (argsSize > 0) {
    auto message = new Message(name);
    return wrap<LoveC_Event_MessageRef>(message);
  } else {
    auto realArgs = std::vector<Variant>(args, args + argsSize * sizeof(LoveC_VariantRef*));
    auto message = new Message(name, realArgs);
    return wrap<LoveC_Event_MessageRef>(message);
  }
}

const char *love_Event_Message_getName(LoveC_Event_MessageRef messageRef) {
  return unwrap<Message>(messageRef)->name.c_str();
}

void love_Event_Message_getArgs(LoveC_Event_MessageRef messageRef, LoveC_VariantRef** outArgs, LoveC_Int64* outSize) {
  auto message = unwrap<Message>(messageRef);

  size_t size = message->args.size();
  LoveC_VariantRef* args = (LoveC_VariantRef*)malloc(size * sizeof(LoveC_VariantRef));

  for (size_t i = 0; i < size; i++) {
    args[i] = wrap<LoveC_VariantRef>(&message->args[i]);
  }

  *outArgs = args;
  *outSize = size;
}

LoveC_Bool love_event_poll(LoveC_Event_MessageRef* outMessage) {
  Message *m = nullptr;

  if (instance()->poll(m)) {
    *outMessage = wrap<LoveC_Event_MessageRef>(m);
    return true;
  } else {
    return false;
  }
}

LoveC_Result love_event_pump(char** outError) {
  try {
    instance()->pump();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Result love_event_wait(LoveC_Event_MessageRef* outMessage, char** outError) {
  Message *m = nullptr;

  try {
    m = instance()->wait();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  if (m) {
    *outMessage = wrap<LoveC_Event_MessageRef>(m);
  }

  return true;
}

void love_event_push(LoveC_Event_MessageRef messageRef) {
  Message *m = unwrap<Message>(messageRef);
  instance()->push(m);
}

LoveC_Result love_event_clear(char** outError) {
  try {
    instance()->clear();
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_event_registerModule(char **outError) {
  Event *instance = instance();
  if (instance == nullptr) {
    try {
      instance = new sdl::Event();
    } catch (const std::exception &e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  WrappedModule w;
  w.module = instance;
  w.name = "event";
  w.type = &Event::type;
  w.functions = nullptr;
  w.types = nullptr;

  return love_c::register_module(w, outError);
}
