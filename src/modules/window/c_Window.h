#ifndef LOVE_WINDOW_C_WINDOW_H
#define LOVE_WINDOW_C_WINDOW_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "modules/love_c/c_Module.h"

LOVE_C_EXTERN_C_BEGIN


struct LoveC_WindowHandle;
typedef struct LoveC_WindowHandle* LoveC_WindowRef;

typedef struct LoveC_Window_WindowSize {
	int width;
	int height;
} LoveC_Window_WindowSize;

typedef enum LoveC_Window_FullscreenType {
  FULLSCREEN_EXCLUSIVE,
  FULLSCREEN_DESKTOP,
  FULLSCREEN_MAX_ENUM
} LoveC_Window_FullscreenType;

typedef enum LoveC_Window_MessageBoxType {
  MESSAGEBOX_ERROR,
  MESSAGEBOX_WARNING,
  MESSAGEBOX_INFO,
  MESSAGEBOX_MAX_ENUM
} LoveC_Window_MessageBoxType;

typedef struct LoveC_Window_MessageBoxData {
  LoveC_Window_MessageBoxType type;

  char* title;
  char* message;

  char** buttons;
  int enterButtonIndex;
  int escapeButtonIndex;

  LoveC_Bool attachToWindow;
} LoveC_Window_MessageBoxData;

typedef enum LoveC_Window_DisplayOrientation {
  ORIENTATION_UNKNOWN,
  ORIENTATION_LANDSCAPE,
  ORIENTATION_LANDSCAPE_FLIPPED,
  ORIENTATION_PORTRAIT,
  ORIENTATION_PORTRAIT_FLIPPED,
  ORIENTATION_MAX_ENUM
} LoveC_Window_DisplayOrientation;

typedef struct LoveC_Window_WindowSettings {
  LoveC_Bool fullscreen;
  LoveC_Window_FullscreenType fstype;
  int vsync;
  int msaa;
  LoveC_Bool stencil;
  int depth;
  LoveC_Bool resizable;
  int minwidth;
  int minheight;
  LoveC_Bool borderless;
  LoveC_Bool centered;
  int display;
  LoveC_Bool highdpi;
  LoveC_Bool usedpiscale;
  double refreshrate;
  LoveC_Bool useposition;
  int x;
  int y;
} LoveC_Window_WindowSettings;

LOVE_EXPORT LoveC_WindowRef love_window_getInstance();

LOVE_EXPORT int love_window_getDisplayCount(LoveC_WindowRef ref);
LOVE_EXPORT LoveC_Bool love_window_getDisplayName(LoveC_WindowRef ref, int index, const char** outDisplayName, char** outError);
LOVE_EXPORT LoveC_Bool love_window_setMode(LoveC_WindowRef ref, int width, int height, const LoveC_Window_WindowSettings* settingsOpt, char** outError);
LOVE_EXPORT void love_window_getMode(LoveC_WindowRef ref, int* outW, int* outH, LoveC_Window_WindowSettings* outSettings);
LOVE_EXPORT LoveC_Window_DisplayOrientation love_window_getDisplayOrientation(LoveC_WindowRef ref, int indexOpt);
LOVE_EXPORT LoveC_Int64 love_window_getFullscreenModes(LoveC_WindowRef ref, int indexOpt, LoveC_Window_WindowSize** outModes);
LOVE_EXPORT LoveC_Bool love_window_setFullscreen(LoveC_WindowRef ref, LoveC_Bool fullscreen, LoveC_Window_FullscreenType fstype, char** outError);
LOVE_EXPORT LoveC_Bool love_window_isOpen(LoveC_WindowRef ref);
LOVE_EXPORT LoveC_Bool love_window_close(LoveC_WindowRef ref, char** outError);
LOVE_EXPORT void love_window_getDesktopDimensions(LoveC_WindowRef ref, int indexOpt, int* outWidth, int* outHeight);
LOVE_EXPORT void love_window_setPosition(LoveC_WindowRef ref, int x, int y, int indexOpt);
LOVE_EXPORT void love_window_getPosition(LoveC_WindowRef ref, int* outX, int* outY, int* outIndex);
LOVE_EXPORT void love_window_getSafeArea(LoveC_WindowRef ref, int* outX, int* outY, int* outW, int* outH);
// TODO LOVE_EXPORT LoveC_Bool love_window_setIcon(LoveC_WindowRef ref, LoveC_ImageDataRef imageRef, char** outError);
// TODO LOVE_EXPORT void love_window_getIcon(LoveC_WindowRef ref, LoveC_ImageDataRef *outImageRef);
LOVE_EXPORT void love_window_setVSync(LoveC_WindowRef ref, int vsync);
LOVE_EXPORT int love_window_getVSync(LoveC_WindowRef ref);
LOVE_EXPORT void love_window_setDisplaySleepEnabled(LoveC_WindowRef ref, LoveC_Bool enable);
LOVE_EXPORT LoveC_Bool love_window_isDisplaySleepEnabled(LoveC_WindowRef ref);
LOVE_EXPORT void love_window_setTitle(LoveC_WindowRef ref, const char* title);
LOVE_EXPORT void love_window_getTitle(LoveC_WindowRef ref, char** outTitle);
LOVE_EXPORT LoveC_Bool love_window_hasFocus(LoveC_WindowRef ref);
LOVE_EXPORT LoveC_Bool love_window_hasMouseFocus(LoveC_WindowRef ref);
LOVE_EXPORT LoveC_Bool love_window_isVisible(LoveC_WindowRef ref);
LOVE_EXPORT double love_window_getDPIScale(LoveC_WindowRef ref);
LOVE_EXPORT double love_window_getNativeDPIScale(LoveC_WindowRef ref);
LOVE_EXPORT double love_window_toPixels__x(LoveC_WindowRef ref, double x);
LOVE_EXPORT void love_window_toPixels__wx_wy(LoveC_WindowRef ref, double wx, double wy, double* outPx, double* outPy);
LOVE_EXPORT double love_window_fromPixels__x(LoveC_WindowRef ref, double x);
LOVE_EXPORT void love_window_fromPixels__wx_wy(LoveC_WindowRef ref, double px, double py, double* outWx, double* outWy);
LOVE_EXPORT void love_window_minimize(LoveC_WindowRef ref);
LOVE_EXPORT void love_window_maximize(LoveC_WindowRef ref);
LOVE_EXPORT void love_window_restore(LoveC_WindowRef ref);
LOVE_EXPORT LoveC_Bool love_window_isMaximized(LoveC_WindowRef ref);
LOVE_EXPORT LoveC_Bool love_window_isMinimized(LoveC_WindowRef ref);
LOVE_EXPORT int love_window_showMessageBox(LoveC_WindowRef ref, const char* title, const char* message, LoveC_Window_MessageBoxType type, LoveC_Bool attachToWindow);
LOVE_EXPORT int love_window_showMessageBox__MessageBoxData(LoveC_WindowRef ref, const LoveC_Window_MessageBoxData* messageBox);
LOVE_EXPORT void love_window_requestAttention(LoveC_WindowRef ref, LoveC_Bool continuous);

LOVE_EXPORT LoveC_Bool love_window_registerModule(char** outError);


LOVE_C_EXTERN_C_END

#endif // LOVE_WINDOW_C_WINDOW_H
