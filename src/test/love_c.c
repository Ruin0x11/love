/* #ifdef LOVE_BUILD_C_API */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shaders.h"
#include "nogame.h"

#include "../modules/love_c/love_c.h"
#include "../modules/love_c/c_Object.h"
#include "../modules/love_c/c_Data.h"
#include "../modules/love_c/c_Matrix.h"
#include "../modules/love_c/c_Variant.h"
#include "../modules/filesystem/c_Filesystem.h"
#include "../modules/window/c_Window.h"
#include "../modules/graphics/c_Graphics.h"
#include "../modules/graphics/c_Image.h"
#include "../modules/font/c_Font.h"
#include "../modules/event/c_Event.h"
#include "../modules/image/c_Image.h"
#include "../modules/data/c_DataModule.h"
#include "../modules/timer/c_Timer.h"
#include "../modules/physics/box2d/c_Physics.h"

#define DEBUG LOVE_C_TRUE

static LoveC_FontRef defaultFont;

int load_default_font(char** outError) {
  int result;

  LoveC_FileRef file = NULL;
  if (!love_filesystem_newFile("MS-Gothic.ttf", MODE_READ, &file, outError)) {
    return LOVE_C_FALSE;
  }

  LoveC_FileDataRef fileData = NULL;
  result = love_filesystem_File_read__FileData(file, -1, &fileData, outError);
  love_Object_retain((LoveC_ObjectRef)file);
  if (!result) {
    return LOVE_C_FALSE;
  }

  printf("FileData size: %d\n", love_Data_getSize((LoveC_DataRef)fileData));

  LoveC_Font_RasterizerRef rasterizer = NULL;
  result = love_font_newTrueTypeRasterizer(fileData, 12, 1.0, HINTING_NORMAL, &rasterizer, outError);
  love_Object_retain((LoveC_ObjectRef)fileData);
  if (!result) {
    return LOVE_C_FALSE;
  }

  printf("Glyph count: %d\n", love_font_Rasterizer_getGlyphCount(rasterizer));

  LoveC_Texture_Filter filter = {
    .min = FILTER_LINEAR,
    .mag = FILTER_LINEAR,
    .mipmap = FILTER_NONE,
    .anisotropy = 1.0f
  };

  result = love_graphics_newFont(rasterizer, &filter, &defaultFont, outError);
  love_Object_retain((LoveC_ObjectRef)rasterizer);
  if (!result) {
    return LOVE_C_FALSE;
  }

  return LOVE_C_TRUE;
}

int init(char* argv0) {
  char* error = NULL;

  if (!love_c_init(&error)) {
    printf("Error: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  char* exepath = NULL;
  love_filesystem_getExecutablePath(&exepath);
  if (exepath == NULL) {
    printf("No exepath\n");
    return LOVE_C_FALSE;
  }

  printf("Exepath: %s\n", exepath);

  LoveC_Bool is_fused = love_filesystem_setSource(exepath, &error);
  if (is_fused) {
    printf("Is fused\n", error);
    free(error);
  }

  love_filesystem_setFused(is_fused);

  if (!love_filesystem_init(argv0, &error)) {
    printf("Error love_filesystem_init: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  if (!love_filesystem_setIdentity("love_c", 1, &error)) {
    printf("Error love_filesystem_setIdentity: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }


#define SET_SHADER(lang)                                                \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_VERTEX, SHADER_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_PIXEL, SHADER_##lang##_PIXEL, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_VERTEX, SHADER_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_PIXEL, SHADER_##lang##_VIDEOPIXEL, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_VERTEX, SHADER_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_FALSE, STAGE_PIXEL, SHADER_##lang##_ARRAYPIXEL, NULL);

#define SET_SHADER_GAMMA(lang)                                          \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_VERTEX, SHADER_GAMMA_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_PIXEL, SHADER_GAMMA_##lang##_PIXEL, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_VERTEX, SHADER_GAMMA_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_PIXEL, SHADER_GAMMA_##lang##_VIDEOPIXEL, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_VERTEX, SHADER_GAMMA_##lang##_VERTEX, NULL); \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang, LOVE_C_TRUE, STAGE_PIXEL, SHADER_GAMMA_##lang##_ARRAYPIXEL, NULL);

  SET_SHADER(GLSL1);
  SET_SHADER(ESSL1);
  SET_SHADER(GLSL3);
  SET_SHADER(ESSL3);
  SET_SHADER_GAMMA(GLSL1);
  SET_SHADER_GAMMA(ESSL1);
  SET_SHADER_GAMMA(GLSL3);
  SET_SHADER_GAMMA(ESSL3);

  love_window_setTitle("Love C");

  LoveC_Window_WindowSettings settings;
  settings.fullscreen = LOVE_C_FALSE;
  settings.fstype = FULLSCREEN_MAX_ENUM;
  settings.vsync = 1;
  settings.msaa = 0;
  settings.stencil = LOVE_C_TRUE;
  settings.depth = 0;
  settings.resizable = LOVE_C_FALSE;
  settings.minwidth = 1;
  settings.minheight = 1;
  settings.borderless = LOVE_C_FALSE;
  settings.centered = LOVE_C_TRUE;
  settings.display = 0;
  settings.highdpi = LOVE_C_FALSE;
  settings.usedpiscale = LOVE_C_TRUE;
  settings.refreshrate = 0.0;
  settings.useposition = LOVE_C_FALSE;
  settings.x = 0;
  settings.y = 0;

  if (!love_window_setMode(800, 600, &settings, &error)) {
    printf("Error initializing window: %s\n", error);
    return LOVE_C_FALSE;
  }

  if (!load_default_font(&error)) {
    printf("Failed to load default font: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  return LOVE_C_TRUE;
}

/* BG_CLOUD_1_PNG = */
/*   BG_CLOUD_1_PNG_2X = */
/*   BG_CLOUD_2_PNG = */
/*   BG_CLOUD_2_PNG_2X = */
/*   BG_CLOUD_3_PNG_2X = */
/*   CLOUD_3_PNG_2X = */
/*   CLOUD_4_PNG = */
/*   CLOUD_4_PNG_2X = */
/*   CHAIN_A_PNG = */
/*   CHAIN_A_PNG_2X = */
/*   CHAIN_E_PNG = */
/*   CHAIN_E_PNG_2X = */
/*   CHAIN_G_PNG = */
/*   CHAIN_G_PNG_2X = */
/*   CHAIN_M_PNG = */
/*   CHAIN_M_PNG_2X = */
/*   CHAIN_N_PNG = */
/*   CHAIN_N_PNG_2X = */
/*   CHAIN_O_PNG = */
/*   CHAIN_O_PNG_2X = */
/*   CHAIN_SQUARE_PNG = */
/*   CHAIN_SQUARE_PNG_2X = */
/*   DUCKLOON_BLINK_PNG = */
/*   DUCKLOON_BLINK_PNG_2X = */
/*   DUCKLOON_NORMAL_PNG = */
/*   DUCKLOON_NORMAL_PNG_2X = */

static LoveC_Graphics_ImageRef img_duckloon_normal;
static LoveC_Graphics_ImageRef img_duckloon_blink;

static LoveC_Graphics_ImageRef img_n;
static LoveC_Graphics_ImageRef img_o;
static LoveC_Graphics_ImageRef img_g;
static LoveC_Graphics_ImageRef img_a;
static LoveC_Graphics_ImageRef img_m;
static LoveC_Graphics_ImageRef img_e;
static LoveC_Graphics_ImageRef img_square;

static LoveC_Graphics_ImageRef img_cloud_1;
static LoveC_Graphics_ImageRef img_cloud_2;
static LoveC_Graphics_ImageRef img_cloud_3;
static LoveC_Graphics_ImageRef img_cloud_4;
static LoveC_Graphics_ImageRef cloud_images[4];

static LoveC_Physics_WorldRef world;

#define STEP (1.0f/20.0f)
float g_t = 0.0f;
float g_step = 0.0f;
int g_frame_count = 0;
int g_step_count = 0;

int load_image(const char* bytes, LoveC_Graphics_Image_Settings* settings, LoveC_Graphics_ImageRef* outImage, char** outError) {
  char* decodedData;
  LoveC_SizeT decodedDataSize;
  if (!love_data_decode(ENCODE_BASE64, bytes, strlen(bytes), &decodedData, &decodedDataSize, outError)) {
    return LOVE_C_FALSE;
  }

  LoveC_DataRef data;
  if (!love_data_newByteData__data(decodedData, decodedDataSize, (LoveC_Data_ByteDataRef*)&data, outError)) {
    return LOVE_C_FALSE;
  }

  LoveC_Image_ImageDataRef imageData;

  int result = love_image_newImageData__Data(data, &imageData, outError);
  love_Object_release((LoveC_ObjectRef)data);
  if (!result)
    return LOVE_C_FALSE;

  LoveC_Graphics_Image_SlicesRef slices = love_Graphics_Image_Slices_construct(TEXTURE_2D);

  love_Graphics_Image_Slices_set(slices, 0, 0, (LoveC_Image_ImageDataBaseRef)imageData);
  love_Object_release((LoveC_ObjectRef)imageData);

  result = love_graphics_newImage(slices, settings, outImage, outError);
  love_Graphics_Image_Slices_delete(slices);
  if (!result)
    return LOVE_C_FALSE;

  return LOVE_C_TRUE;
}

typedef struct State {
  float t0;
  float x0;
  float y0;
  float r0;

  float t1;
  float x1;
  float y1;
  float r1;
} State;

void nogame_State_init(State* state, LoveC_Physics_BodyRef body) {
  state->t0 = 0.0f;
  state->x0 = love_physics_Body_getX(body);
  state->y0 = love_physics_Body_getY(body);
  state->r0 = love_physics_Body_getAngle(body);

  state->t1 = state->t0;
  state->x1 = state->x0;
  state->y1 = state->y0;
  state->r1 = state->r0;
}

void nogame_State_save(State* state, LoveC_Physics_BodyRef body, float t) {
  state->t0 = state->t1;
  state->x0 = state->x1;
  state->y0 = state->y1;
  state->r0 = state->r1;

  state->t1 = t;
  state->x1 = love_physics_Body_getX(body);
  state->y1 = love_physics_Body_getY(body);
  state->r1 = love_physics_Body_getAngle(body);
}

typedef struct Blink {
  float closed_t;
  float next_blink_t;
} Blink;

typedef struct Duckloon {
  LoveC_Physics_BodyRef body;
  LoveC_Physics_ShapeRef shape;
  LoveC_Physics_FixtureRef fixture;
  LoveC_Graphics_ImageRef img;
  Blink blink;
  LoveC_Physics_JointRef pin;
  State state;
} Duckloon;

typedef struct CloudTrack {
  int x;
  int y;
  int initial_offset;
  int h_spacing;
  LoveC_Graphics_ImageRef img;
  int w;
  float speed;
  unsigned int count;
  unsigned int initial_img;
} CloudTrack;

void nogame_CloudTrack_init(CloudTrack* cloudTrack, float x, float y, float offset, float speed, LoveC_Graphics_ImageRef img) {
  cloudTrack->x = x;
  cloudTrack->y = y;
  cloudTrack->initial_offset = offset;
  cloudTrack->h_spacing = 50;
  cloudTrack->img = img;
  cloudTrack->w = cloudTrack->h_spacing + (int)love_Graphics_Image_getWidth(cloudTrack->img);
  cloudTrack->speed = speed;
  cloudTrack->count = love_graphics_getWidth() / cloudTrack->w + 2;
  cloudTrack->initial_img = rand() % 4;
}

int nogame_CloudTrack_draw(const CloudTrack* cloudTrack, char** outError) {
  int abs_offset = (cloudTrack->initial_offset + (cloudTrack->speed * g_t));
  int offset = abs_offset % cloudTrack->w;

  static LoveC_Colorf color = {
    .r = 1.0f,
    .g = 1.0f,
    .b = 1.0f,
    .a = 0.3f,
  };
  love_graphics_setColor(&color);

  LoveC_Matrix4 pos;

  for (int i = 0; i < cloudTrack->count; i++) {
    float x = cloudTrack->x + i * (love_Graphics_Image_getWidth(cloudTrack->img) + cloudTrack->h_spacing) + offset - cloudTrack->w;
    float y = cloudTrack->y;
    unsigned int img_no = abs_offset / cloudTrack->w;
    LoveC_Graphics_ImageRef img = cloud_images[(cloudTrack->initial_img + i - img_no) % 4];

    love_Matrix4_setTranslation(&pos, x, y);
    if (!love_graphics_draw((LoveC_DrawableRef)img, &pos, outError)) {
      return LOVE_C_FALSE;
    }
  }

  return LOVE_C_TRUE;
}

typedef struct Clouds {
  CloudTrack* tracks;
  size_t max;
} Clouds;

static Clouds clouds;

int nogame_Clouds_draw(const Clouds* clouds, char** outError) {
  for (int i = 0; i < clouds->max; i++) {
    if (!nogame_CloudTrack_draw(&clouds->tracks[i], outError)) {
      return LOVE_C_FALSE;
    }
  }
  return LOVE_C_TRUE;
}

int nogame_Clouds_init(Clouds* clouds) {
  int layer_height = 100;
  int max = love_graphics_getHeight() / layer_height;

  clouds->max = max;
  clouds->tracks = (CloudTrack*)malloc(clouds->max * sizeof(CloudTrack));
  if (!clouds->tracks) {
    printf("Error nogame_Clouds_init: out of memory\n");
    return LOVE_C_FALSE;
  }

  for (int i = 0; i < clouds->max; i++) {
    int w = love_Graphics_Image_getWidth(img_cloud_1) / 2 * i;
    nogame_CloudTrack_init(&clouds->tracks[i], 0, 20 + i * layer_height, w, 40, img_cloud_1);
  }

  return LOVE_C_TRUE;
}

int nogame_update(float dt, char** error) {
  g_t += dt;

  while (g_t > g_step) {
    g_step += STEP;
    g_step_count += 1;
  }

  return LOVE_C_TRUE;
}

int nogame_draw(char** outError) {
  if (!nogame_Clouds_draw(&clouds, outError)) {
    printf("Error nogame_Clouds_draw: %s\n", *outError);
    return LOVE_C_FALSE;
  }

  if (DEBUG) {
    static LoveC_Colorf color = {
      .r = 0.0f,
      .g = 0.0f,
      .b = 0.0f,
      .a = 0.5f
    };

    static LoveC_Font_ColoredString texts[1];
    texts[0].color = color;
    char buf[256];
    texts[0].str = buf;

    static LoveC_Matrix4 pos;

    sprintf(buf, "FPS: %f", love_timer_getFPS());
    love_Matrix4_setTranslation(&pos, 50, 50);
    if (!love_graphics_print(texts, &defaultFont, &pos, outError)) {
      printf("Error love_graphics_print: %s\n", *outError);
      return LOVE_C_FALSE;
    }

    sprintf(buf, "Time: %f", g_t);
    love_Matrix4_setTranslation(&pos, 50, 65);
    if (!love_graphics_print(texts, &defaultFont, &pos, outError)) {
      printf("Error love_graphics_print: %s\n", *outError);
      return LOVE_C_FALSE;
    }

    sprintf(buf, "g_step: %f", g_step);
    love_Matrix4_setTranslation(&pos, 50, 80);
    if (!love_graphics_print(texts, &defaultFont, &pos, outError)) {
      printf("Error love_graphics_print: %s\n", *outError);
      return LOVE_C_FALSE;
    }

    sprintf(buf, "Frame: %d", g_frame_count);
    love_Matrix4_setTranslation(&pos, 50, 95);
    if (!love_graphics_print(texts, &defaultFont, &pos, outError)) {
      printf("Error love_graphics_print: %s\n", *outError);
      return LOVE_C_FALSE;
    }

    sprintf(buf, "Step: %d", g_step_count);
    love_Matrix4_setTranslation(&pos, 50, 110);
    if (!love_graphics_print(texts, &defaultFont, &pos, outError)) {
      printf("Error love_graphics_print: %s\n", *outError);
      return LOVE_C_FALSE;
    }
  }

  g_frame_count += 1;

  return LOVE_C_TRUE;
}

int create_world(char** outError) {
  int wx = love_graphics_getWidth();
  int wy = love_graphics_getHeight();

  if (!love_physics_newWorld(0, 9.81 * 64, LOVE_C_FALSE, &world, outError)) {
    return LOVE_C_FALSE;
  }

  if (!nogame_Clouds_init(&clouds)) {
    return LOVE_C_FALSE;
  }

  return LOVE_C_TRUE;
}

int load_nogame_images(char** outError) {
  int dpiscale = love_window_getDPIScale();
  LoveC_Graphics_Image_Settings settings = {
    .mipmaps = LOVE_C_FALSE,
    .linear = LOVE_C_FALSE,
    .dpiScale = dpiscale > 1.0f ? 2.0f : 1.0f
  };

#define LOAD_IMAGE(to, from) \
  if (!load_image(from, &settings, &to, outError)) { \
    return LOVE_C_FALSE; \
  }

  if (dpiscale > 1.0f) {
    LOAD_IMAGE(img_duckloon_normal, DUCKLOON_NORMAL_PNG_2X);
    LOAD_IMAGE(img_duckloon_blink, DUCKLOON_BLINK_PNG_2X);

    LOAD_IMAGE(img_n, CHAIN_N_PNG_2X);
    LOAD_IMAGE(img_o, CHAIN_O_PNG_2X);
    LOAD_IMAGE(img_g, CHAIN_G_PNG_2X);
    LOAD_IMAGE(img_a, CHAIN_A_PNG_2X);
    LOAD_IMAGE(img_m, CHAIN_M_PNG_2X);
    LOAD_IMAGE(img_e, CHAIN_E_PNG_2X);
    LOAD_IMAGE(img_square, CHAIN_SQUARE_PNG_2X);

    LOAD_IMAGE(img_cloud_1, BG_CLOUD_1_PNG_2X);
    LOAD_IMAGE(img_cloud_2, BG_CLOUD_2_PNG_2X);
    LOAD_IMAGE(img_cloud_3, BG_CLOUD_3_PNG_2X);
    LOAD_IMAGE(img_cloud_4, BG_CLOUD_4_PNG_2X);
  } else {
    LOAD_IMAGE(img_duckloon_normal, DUCKLOON_NORMAL_PNG);
    LOAD_IMAGE(img_duckloon_blink, DUCKLOON_BLINK_PNG);

    LOAD_IMAGE(img_n, CHAIN_N_PNG);
    LOAD_IMAGE(img_o, CHAIN_O_PNG);
    LOAD_IMAGE(img_g, CHAIN_G_PNG);
    LOAD_IMAGE(img_a, CHAIN_A_PNG);
    LOAD_IMAGE(img_m, CHAIN_M_PNG);
    LOAD_IMAGE(img_e, CHAIN_E_PNG);
    LOAD_IMAGE(img_square, CHAIN_SQUARE_PNG);

    LOAD_IMAGE(img_cloud_1, BG_CLOUD_1_PNG)
    LOAD_IMAGE(img_cloud_2, BG_CLOUD_2_PNG);
    LOAD_IMAGE(img_cloud_3, BG_CLOUD_3_PNG);
    LOAD_IMAGE(img_cloud_4, BG_CLOUD_4_PNG);
  }
#undef LOAD_IMAGE

  cloud_images[0] = img_cloud_1;
  cloud_images[1] = img_cloud_2;
  cloud_images[2] = img_cloud_3;
  cloud_images[3] = img_cloud_4;

  return LOVE_C_TRUE;
}

int nogame() {
  char* error = NULL;

  LoveC_Colorf bg = {
    .r = 43.0f / 255.0f,
    .g = 165.0f / 255.0f,
    .b = 223.0f / 255.0f,
    .a = 1.0f
  };
  love_graphics_setBackgroundColor(&bg);
  if (!love_physics_setMeter(64, &error)) {
    printf("Error love_graphics_setMeter: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  if (!load_nogame_images(&error)) {
    printf("Error load_nogame_images: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  if (!create_world(&error)) {
    return LOVE_C_FALSE;
  }

  LoveC_Colorf colors[1];
  colors[0] = bg;

  LoveC_Bool *discards = malloc(sizeof(LoveC_Bool)*20);
  discards[0] = LOVE_C_TRUE;
  discards[1] = LOVE_C_NIL;

  LoveC_Event_MessageRef mes;

  while (1) {
    if (!love_event_pump(&error)) {
      printf("Error love_event_pump: %s\n", error);
      free(error);
      return LOVE_C_FALSE;
    }

    if (love_event_poll(&mes)) {
      const char* name = love_Event_Message_getName(mes);
      printf("Event received: %s\n", name);
      if (strcmp(name, "quit") == 0) {
        break;
      }
    }

    float dt = love_timer_step();

    if (!nogame_update(dt, &error)) {
      printf("Error nogame_update: %s\n", error);
      return LOVE_C_FALSE;
    }

    if (love_graphics_isActive()) {
      love_graphics_origin();
      if (!love_graphics_clear(colors, 1, LOVE_C_NIL, LOVE_C_NIL, &error)) {
        printf("Error love_graphics_clear: %s\n", error);
        free(error);
        return LOVE_C_FALSE;
      }

      if (!nogame_draw(&error)) {
        printf("Error nogame_draw: %s\n", error);
        free(error);
        return LOVE_C_FALSE;
      }

      if (!love_graphics_present(&error)) {
        printf("Error love_graphics_present: %s\n", error);
        free(error);
        return LOVE_C_FALSE;
      }
    }

    love_timer_sleep(0.001);
  }

  return LOVE_C_TRUE;
}

int main(int argc, char *argv[]) {
  char* error = NULL;

  if (!init(argv[0])) {
    return 1;
  }

  printf("Hello, world! %s\n", love_c_version());

  if (!nogame()) {
    return 1;
  }

  return 0;
}

/* #endif */
