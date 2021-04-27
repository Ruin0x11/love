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


LoveC_WindowRef love_window_getInstance() {
  auto inst = instance();
  return wrap<LoveC_WindowRef>(inst);
}

int love_window_getDisplayCount(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->getDisplayCount();
}

LoveC_Bool love_window_getDisplayName(LoveC_WindowRef ref, int index, const char** outDisplayName, char** outError) {
  auto window = unwrap<Window>(ref);

  try {
    *outDisplayName = window->getDisplayName(index);
  } catch(const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

LoveC_Bool love_window_setMode(LoveC_WindowRef ref, int width, int height, const LoveC_Window_WindowSettings* settingsOpt, char** outError) {
  auto window = unwrap<Window>(ref);

  if (settingsOpt == nullptr) {
    try {
      return window->setWindow(width, height, nullptr);
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
      return window->setWindow(width, height, &loveSettings);
    } catch(const std::exception& e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  return true;
}

void love_window_getMode(LoveC_WindowRef ref, int* outW, int* outH, LoveC_Window_WindowSettings* outSettings) {
  auto window = unwrap<Window>(ref);

  int w, h;
  WindowSettings loveSettings;

  window->getWindow(w, h, loveSettings);

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

LoveC_Window_DisplayOrientation love_window_getDisplayOrientation(LoveC_WindowRef ref, int indexOpt) {
  auto window = unwrap<Window>(ref);

  int displayindex = indexOpt;
  if (indexOpt == LOVE_C_NIL) {
    int x, y;
    window->getPosition(x, y, displayindex);
  }

  Window::DisplayOrientation orientation = window->getDisplayOrientation(displayindex);

  return static_cast<LoveC_Window_DisplayOrientation>(orientation);
}

LoveC_Int64 love_window_getFullscreenModes(LoveC_WindowRef ref, int indexOpt, LoveC_Window_WindowSize** outModes) {
  auto window = unwrap<Window>(ref);

  int displayindex = indexOpt;
  if (indexOpt == LOVE_C_NIL) {
    int x, y;
    window->getPosition(x, y, displayindex);
  }

  std::vector<Window::WindowSize> modes = instance()->getFullscreenSizes(displayindex);

  for (size_t i = 0; i < modes.size(); i++) {
    outModes[i]->width = modes[i].width;
    outModes[i]->height = modes[i].height;
  }

  return modes.size();
}

LoveC_Bool love_window_setFullscreen(LoveC_WindowRef ref, LoveC_Bool fullscreen, LoveC_Window_FullscreenType fstype, char** outError) {
  auto window = unwrap<Window>(ref);

  auto fstype_love = static_cast<Window::FullscreenType>(fstype);

  bool success = false;

  try {
    if (fstype_love == Window::FULLSCREEN_MAX_ENUM) {
      success = window->setFullscreen(fullscreen);
    } else {
      success = window->setFullscreen(fullscreen, fstype_love);
    }
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return success;
}

LoveC_Bool love_window_isOpen(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->isOpen();
}

LoveC_Bool love_window_close(LoveC_WindowRef ref, char** outError) {
  auto window = unwrap<Window>(ref);

  try {
    window->close();
  } catch (const std::exception& e) {
    return false;
  }

  return true;
}

void love_window_getDesktopDimensions(LoveC_WindowRef ref, int indexOpt, int* outWidth, int* outHeight) {
  auto window = unwrap<Window>(ref);

  int width = 0, height = 0;
  int displayindex = indexOpt;

  if (indexOpt == LOVE_C_NIL) {
    int x, y;
    window->getPosition(x, y, displayindex);
  }

  window->getDesktopDimensions(displayindex, width, height);

  *outWidth = width;
  *outHeight = height;
}

void love_window_setPosition(LoveC_WindowRef ref, int x, int y, int indexOpt) {
  auto window = unwrap<Window>(ref);

  int displayindex = indexOpt;

  if (indexOpt == LOVE_C_NIL) {
    int x, y;
    window->getPosition(x, y, displayindex);
  }

  window->setPosition(x, y, displayindex);
}

void love_window_getPosition(LoveC_WindowRef ref, int* outX, int* outY, int* outIndex) {
  auto window = unwrap<Window>(ref);

  int x = 0;
  int y = 0;
  int displayindex = 0;
  instance()->getPosition(x, y, displayindex);

  *outX = x;
  *outY = y;
  *outIndex = displayindex;
}

void love_window_getSafeArea(LoveC_WindowRef ref, int* outX, int* outY, int* outW, int* outH) {
  auto window = unwrap<Window>(ref);

  Rect area = window->getSafeArea();

  *outX = area.x;
  *outY = area.y;
  *outW = area.w;
  *outH = area.h;
}

// TODO LoveC_Bool love_window_setIcon(LoveC_WindowRef ref, LoveC_ImageDataRef imageRef, char** outError) {

// }

// TODO void love_window_getIcon(LoveC_WindowRef ref, LoveC_ImageDataRef *outImageRef) {

// }

void love_window_setVSync(LoveC_WindowRef ref, int vsync) {
  unwrap<Window>(ref)->setVSync(vsync);
}

int love_window_getVSync(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->getVSync();
}

void love_window_setDisplaySleepEnabled(LoveC_WindowRef ref, LoveC_Bool enable) {
  unwrap<Window>(ref)->setDisplaySleepEnabled(enable);
}

LoveC_Bool love_window_isDisplaySleepEnabled(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->isDisplaySleepEnabled();
}

void love_window_setTitle(LoveC_WindowRef ref, const char* title) {
  unwrap<Window>(ref)->setWindowTitle(title);
}

void love_window_getTitle(LoveC_WindowRef ref, char** outTitle) {
  auto window = unwrap<Window>(ref);

  std::string title = window->getWindowTitle();
  *outTitle = strdup(title.c_str());
}

LoveC_Bool love_window_hasFocus(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->hasFocus();
}

LoveC_Bool love_window_hasMouseFocus(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->hasMouseFocus();
}

LoveC_Bool love_window_isVisible(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->isVisible();
}

double love_window_getDPIScale(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->getDPIScale();
}

double love_window_getNativeDPIScale(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->getNativeDPIScale();
}

double love_window_toPixels__x(LoveC_WindowRef ref, double x) {
  return unwrap<Window>(ref)->toPixels(x);
}

void love_window_toPixels__wx_wy(LoveC_WindowRef ref, double wx, double wy, double* outPx, double* outPy) {
  auto window = unwrap<Window>(ref);

  double px = 0.0, py = 0.0;
  window->toPixels(wx, wy, px, py);

  *outPx = px;
  *outPy = py;
}

double love_window_fromPixels(LoveC_WindowRef ref, double x) {
  return unwrap<Window>(ref)->fromPixels(x);
}

void love_window_fromPixels(LoveC_WindowRef ref, double px, double py, double* outWx, double* outWy) {
  auto window = unwrap<Window>(ref);

  double wx = 0.0, wy = 0.0;
  window->fromPixels(px, py, wx, wy);

  *outWx = wx;
  *outWy = wy;
}

void love_window_minimize(LoveC_WindowRef ref) {
  unwrap<Window>(ref)->minimize();
}

void love_window_maximize(LoveC_WindowRef ref) {
  unwrap<Window>(ref)->maximize();
}

void love_window_restore(LoveC_WindowRef ref) {
  unwrap<Window>(ref)->restore();
}

LoveC_Bool love_window_isMaximized(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->isMaximized();
}

LoveC_Bool love_window_isMinimized(LoveC_WindowRef ref) {
  return unwrap<Window>(ref)->isMinimized();
}

int love_window_showMessageBox__simple(LoveC_WindowRef ref, const char* title, const char* message, LoveC_Window_MessageBoxType type, bool attachToWindow) {
  auto window = unwrap<Window>(ref);

  std::string title_(title);
  std::string message_(message);
  auto type_ = static_cast<Window::MessageBoxType>(type);

  return window->showMessageBox(title_, message_, type_, attachToWindow);
}

int love_window_showMessageBox__MessageBoxData(LoveC_WindowRef ref, const LoveC_Window_MessageBoxData* messageBox, int* outResult, char** outError) {
  auto window = unwrap<Window>(ref);

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

  return window->showMessageBox(data);
}

void love_window_requestAttention(LoveC_WindowRef ref, LoveC_Bool continuous) {
  unwrap<Window>(ref)->requestAttention(continuous);
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
