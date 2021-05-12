#include "c_Window.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Window.h"

#include "sdl/Window.h"

using namespace love;
using namespace love::window;

#define instance() (Module::getInstance<Window>(Module::M_WINDOW))


int love_window_getDisplayCount() {
  return instance()->getDisplayCount();
}

LoveC_Bool love_window_getDisplayName(int index, const char** outDisplayName, char** outError) {
  try {
    *outDisplayName = instance()->getDisplayName(index);
  } catch(const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_window_setMode(int width, int height, const LoveC_Window_WindowSettings* settingsOpt, char** outError) {
  if (settingsOpt == nullptr) {
    try {
      return instance()->setWindow(width, height, nullptr);
    } catch(const std::exception& e) {
      *outError = strdup(e.what());
      return false;
    }
  } else {
    WindowSettings loveSettings;
    loveSettings.fullscreen = settingsOpt->fullscreen;
    loveSettings.fstype = static_cast<Window::FullscreenType>(settingsOpt->fstype);
    loveSettings.vsync = settingsOpt->vsync;
    loveSettings.msaa = settingsOpt->msaa;
    loveSettings.stencil = settingsOpt->stencil;
    loveSettings.depth = settingsOpt->depth;
    loveSettings.resizable = settingsOpt->resizable;
    loveSettings.minwidth = settingsOpt->minwidth;
    loveSettings.minheight = settingsOpt->minheight;
    loveSettings.borderless = settingsOpt->borderless;
    loveSettings.centered = settingsOpt->centered;
    loveSettings.display = settingsOpt->display;
    loveSettings.highdpi = settingsOpt->highdpi;
    loveSettings.usedpiscale = settingsOpt->usedpiscale;
    loveSettings.refreshrate = settingsOpt->refreshrate;
    loveSettings.useposition = settingsOpt->useposition;
    loveSettings.x = settingsOpt->x;
    loveSettings.y = settingsOpt->y;

    try {
      return instance()->setWindow(width, height, &loveSettings);
    } catch(const std::exception& e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  return true;
}

void love_window_getMode(int* outW, int* outH, LoveC_Window_WindowSettings* outSettings) {
  int w, h;
  WindowSettings loveSettings;

  instance()->getWindow(w, h, loveSettings);

  *outW = w;
  *outH = h;

  outSettings->fullscreen = loveSettings.fullscreen;
  outSettings->fstype = static_cast<LoveC_Window_FullscreenType>(loveSettings.fstype);
  outSettings->vsync = loveSettings.vsync;
  outSettings->msaa = loveSettings.msaa;
  outSettings->stencil = loveSettings.stencil;
  outSettings->depth = loveSettings.depth;
  outSettings->resizable = loveSettings.resizable;
  outSettings->minwidth = loveSettings.minwidth;
  outSettings->minheight = loveSettings.minheight;
  outSettings->borderless = loveSettings.borderless;
  outSettings->centered = loveSettings.centered;
  outSettings->display = loveSettings.display;
  outSettings->highdpi = loveSettings.highdpi;
  outSettings->usedpiscale = loveSettings.usedpiscale;
  outSettings->refreshrate = loveSettings.refreshrate;
  outSettings->useposition = loveSettings.useposition;
  outSettings->x = loveSettings.x;
  outSettings->y = loveSettings.y;
}

LoveC_Window_DisplayOrientation love_window_getDisplayOrientation(int indexOpt) {
  int displayindex = indexOpt;
  if (indexOpt == LOVE_C_NIL) {
    int x, y;
    instance()->getPosition(x, y, displayindex);
  }

  Window::DisplayOrientation orientation = instance()->getDisplayOrientation(displayindex);

  return static_cast<LoveC_Window_DisplayOrientation>(orientation);
}

LoveC_Int64 love_window_getFullscreenModes(int indexOpt, LoveC_Window_WindowSize** outModes) {
  int displayindex = indexOpt;
  if (indexOpt == LOVE_C_NIL) {
    int x, y;
    instance()->getPosition(x, y, displayindex);
  }

  std::vector<Window::WindowSize> modes = instance()->getFullscreenSizes(displayindex);

  for (size_t i = 0; i < modes.size(); i++) {
    outModes[i]->width = modes[i].width;
    outModes[i]->height = modes[i].height;
  }

  return modes.size();
}

LoveC_Bool love_window_setFullscreen(LoveC_Bool fullscreen, LoveC_Window_FullscreenType fstype, char** outError) {
  auto fstype_love = static_cast<Window::FullscreenType>(fstype);

  bool success = false;

  try {
    if (fstype_love == Window::FULLSCREEN_MAX_ENUM) {
      success = instance()->setFullscreen(fullscreen);
    } else {
      success = instance()->setFullscreen(fullscreen, fstype_love);
    }
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return success;
}

LoveC_Bool love_window_isOpen() {
  return instance()->isOpen();
}

LoveC_Bool love_window_close(char** outError) {
  try {
    instance()->close();
  } catch (const std::exception& e) {
    return false;
  }

  return true;
}

void love_window_getDesktopDimensions(int indexOpt, int* outWidth, int* outHeight) {
  int width = 0, height = 0;
  int displayindex = indexOpt;

  if (indexOpt == LOVE_C_NIL) {
    int x, y;
    instance()->getPosition(x, y, displayindex);
  }

  instance()->getDesktopDimensions(displayindex, width, height);

  *outWidth = width;
  *outHeight = height;
}

void love_window_setPosition(int x, int y, int indexOpt) {
  int displayindex = indexOpt;

  if (indexOpt == LOVE_C_NIL) {
    int x, y;
    instance()->getPosition(x, y, displayindex);
  }

  instance()->setPosition(x, y, displayindex);
}

void love_window_getPosition(int* outX, int* outY, int* outIndex) {
  int x = 0;
  int y = 0;
  int displayindex = 0;
  instance()->getPosition(x, y, displayindex);

  *outX = x;
  *outY = y;
  *outIndex = displayindex;
}

void love_window_getSafeArea(int* outX, int* outY, int* outW, int* outH) {
  Rect area = instance()->getSafeArea();

  *outX = area.x;
  *outY = area.y;
  *outW = area.w;
  *outH = area.h;
}

// TODO LoveC_Bool love_window_setIcon(LoveC_Image_ImageDataRef imageRef, char** outError) {

// }

// TODO void love_window_getIcon(LoveC_Image_ImageDataRef *outImageRef) {

// }

void love_window_setVSync(int vsync) {
  instance()->setVSync(vsync);
}

int love_window_getVSync() {
  return instance()->getVSync();
}

void love_window_setDisplaySleepEnabled(LoveC_Bool enable) {
  instance()->setDisplaySleepEnabled(enable);
}

LoveC_Bool love_window_isDisplaySleepEnabled() {
  return instance()->isDisplaySleepEnabled();
}

void love_window_setTitle(const char* title) {
  instance()->setWindowTitle(title);
}

void love_window_getTitle(char** outTitle) {
  std::string title = instance()->getWindowTitle();
  *outTitle = strdup(title.c_str());
}

LoveC_Bool love_window_hasFocus() {
  return instance()->hasFocus();
}

LoveC_Bool love_window_hasMouseFocus() {
  return instance()->hasMouseFocus();
}

LoveC_Bool love_window_isVisible() {
  return instance()->isVisible();
}

double love_window_getDPIScale() {
  return instance()->getDPIScale();
}

double love_window_getNativeDPIScale() {
  return instance()->getNativeDPIScale();
}

double love_window_toPixels__x(double x) {
  return instance()->toPixels(x);
}

void love_window_toPixels__wx_wy(double wx, double wy, double* outPx, double* outPy) {
  double px = 0.0, py = 0.0;
  instance()->toPixels(wx, wy, px, py);

  *outPx = px;
  *outPy = py;
}

double love_window_fromPixels(double x) {
  return instance()->fromPixels(x);
}

void love_window_fromPixels(double px, double py, double* outWx, double* outWy) {
  double wx = 0.0, wy = 0.0;
  instance()->fromPixels(px, py, wx, wy);

  *outWx = wx;
  *outWy = wy;
}

void love_window_minimize() {
  instance()->minimize();
}

void love_window_maximize() {
  instance()->maximize();
}

void love_window_restore() {
  instance()->restore();
}

LoveC_Bool love_window_isMaximized() {
  return instance()->isMaximized();
}

LoveC_Bool love_window_isMinimized() {
  return instance()->isMinimized();
}

int love_window_showMessageBox(const char* title, const char* message, LoveC_Window_MessageBoxType type, LoveC_Bool attachToWindow) {
  std::string title_(title);
  std::string message_(message);
  auto type_ = static_cast<Window::MessageBoxType>(type);

  return instance()->showMessageBox(title_, message_, type_, attachToWindow);
}

int love_window_showMessageBox__MessageBoxData(const LoveC_Window_MessageBoxData* messageBox, int* outResult, char** outError) {
  Window::MessageBoxData data = {};

  data.type = static_cast<Window::MessageBoxType>(messageBox->type);

  data.title = std::string(messageBox->title);
  data.message = std::string(messageBox->message);

  int i;
  char** buttons = messageBox->buttons;
  for (i = 0; buttons[i]; i++) {
    std::string button_(buttons[i]);
    data.buttons.emplace_back(button_);
  }

  data.enterButtonIndex = messageBox->enterButtonIndex;
  data.escapeButtonIndex = messageBox->escapeButtonIndex;

  data.attachToWindow = messageBox->attachToWindow;

  return instance()->showMessageBox(data);
}

void love_window_requestAttention(LoveC_Bool continuous) {
  instance()->requestAttention(continuous);
}

LoveC_Bool love_window_registerModule(char** outError) {
  Window *instance = instance();
  if (instance == nullptr) {
    try {
      instance = new sdl::Window();
    } catch (const std::exception &e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  WrappedModule w;
  w.module = instance;
  w.name = "window";
  w.type = &Module::type;
  w.functions = nullptr;
  w.types = nullptr;

  return love_c::register_module(w, outError);
}
