// LOVE
#include "common/version.h"

#include "modules/filesystem/c_Filesystem.h"
#include "modules/window/c_Window.h"
#include "modules/graphics/c_Graphics.h"
#include "modules/image/c_Image.h"
#include "modules/font/c_Font.h"
#include "modules/event/c_Event.h"
#include "modules/data/c_DataModule.h"
#include "modules/timer/c_Timer.h"
#include "modules/physics/box2d/c_Physics.h"

#include "love_c.h"

LoveC_Bool love_init(char** error) {
  if (!love_filesystem_registerModule(error)) {
    return false;
  }

  if (!love_window_registerModule(error)) {
    return false;
  }

  if (!love_graphics_registerModule(error)) {
    return false;
  }

  if (!love_image_registerModule(error)) {
    return false;
  }

  if (!love_font_registerModule(error)) {
    return false;
  }

  if (!love_event_registerModule(error)) {
    return false;
  }

  if (!love_data_registerModule(error)) {
    return false;
  }

  if (!love_timer_registerModule(error)) {
    return false;
  }

  if (!love_physics_registerModule(error)) {
    return false;
  }

  return true;
}

const char *love_getOS() {
#ifdef LOVE_WINDOWS_UWP
  return "UWP";
#elif LOVE_WINDOWS
  return "Windows";
#elif defined(LOVE_MACOSX)
  return "OS X";
#elif defined(LOVE_IOS)
  return "iOS";
#elif defined(LOVE_ANDROID)
  return "Android";
#elif defined(LOVE_LINUX)
  return "Linux";
#else
  return "Unknown";
#endif
}
