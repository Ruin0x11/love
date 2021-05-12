/* #ifdef LOVE_BUILD_C_API */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nogame.h"
#include "shaders.h"

#include "../modules/data/c_DataModule.h"
#include "../modules/event/c_Event.h"
#include "../modules/filesystem/c_Filesystem.h"
#include "../modules/font/c_Font.h"
#include "../modules/graphics/c_Graphics.h"
#include "../modules/graphics/c_Image.h"
#include "../modules/image/c_Image.h"
#include "../modules/love_c/c_Data.h"
#include "../modules/love_c/c_Matrix.h"
#include "../modules/love_c/c_Object.h"
#include "../modules/love_c/c_Variant.h"
#include "../modules/love_c/love_c.h"
#include "../modules/physics/box2d/c_Physics.h"
#include "../modules/timer/c_Timer.h"
#include "../modules/window/c_Window.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define DEBUG LOVE_C_TRUE

static LoveC_FontRef defaultFont;

int load_default_font(char **outError) {
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
  result = love_font_newTrueTypeRasterizer(fileData, 12, 1.0, HINTING_NORMAL,
                                           &rasterizer, outError);
  love_Object_retain((LoveC_ObjectRef)fileData);
  if (!result) {
    return LOVE_C_FALSE;
  }

  printf("Glyph count: %d\n", love_font_Rasterizer_getGlyphCount(rasterizer));

  LoveC_Texture_Filter filter = {.min = FILTER_LINEAR,
                                 .mag = FILTER_LINEAR,
                                 .mipmap = FILTER_NONE,
                                 .anisotropy = 1.0f};

  result = love_graphics_newFont(rasterizer, &filter, &defaultFont, outError);
  love_Object_retain((LoveC_ObjectRef)rasterizer);
  if (!result) {
    return LOVE_C_FALSE;
  }

  return LOVE_C_TRUE;
}

int init(char *argv0) {
  char *error = NULL;

  if (!love_init(&error)) {
    printf("Error: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  char *exepath = NULL;
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

#define SET_SHADER(lang)                                                       \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang,        \
                                     LOVE_C_FALSE, STAGE_VERTEX,               \
                                     SHADER_##lang##_VERTEX, NULL);            \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang,        \
                                     LOVE_C_FALSE, STAGE_PIXEL,                \
                                     SHADER_##lang##_PIXEL, NULL);             \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang,          \
                                     LOVE_C_FALSE, STAGE_VERTEX,               \
                                     SHADER_##lang##_VERTEX, NULL);            \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang,          \
                                     LOVE_C_FALSE, STAGE_PIXEL,                \
                                     SHADER_##lang##_VIDEOPIXEL, NULL);        \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang,          \
                                     LOVE_C_FALSE, STAGE_VERTEX,               \
                                     SHADER_##lang##_VERTEX, NULL);            \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang,          \
                                     LOVE_C_FALSE, STAGE_PIXEL,                \
                                     SHADER_##lang##_ARRAYPIXEL, NULL);

#define SET_SHADER_GAMMA(lang)                                                 \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang,        \
                                     LOVE_C_TRUE, STAGE_VERTEX,                \
                                     SHADER_GAMMA_##lang##_VERTEX, NULL);      \
  love_graphics_setDefaultShaderCode(STANDARD_DEFAULT, LANGUAGE_##lang,        \
                                     LOVE_C_TRUE, STAGE_PIXEL,                 \
                                     SHADER_GAMMA_##lang##_PIXEL, NULL);       \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang,          \
                                     LOVE_C_TRUE, STAGE_VERTEX,                \
                                     SHADER_GAMMA_##lang##_VERTEX, NULL);      \
  love_graphics_setDefaultShaderCode(STANDARD_VIDEO, LANGUAGE_##lang,          \
                                     LOVE_C_TRUE, STAGE_PIXEL,                 \
                                     SHADER_GAMMA_##lang##_VIDEOPIXEL, NULL);  \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang,          \
                                     LOVE_C_TRUE, STAGE_VERTEX,                \
                                     SHADER_GAMMA_##lang##_VERTEX, NULL);      \
  love_graphics_setDefaultShaderCode(STANDARD_ARRAY, LANGUAGE_##lang,          \
                                     LOVE_C_TRUE, STAGE_PIXEL,                 \
                                     SHADER_GAMMA_##lang##_ARRAYPIXEL, NULL);

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

  settings.resizable = LOVE_C_TRUE;
  settings.highdpi = LOVE_C_TRUE;
  love_graphics_setGammaCorrect(LOVE_C_TRUE);

  if (strcmp(love_getOS(), "iOS") == 0) {
    settings.borderless = LOVE_C_TRUE;
  }

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

static LoveC_Physics_WorldRef world = NULL;

#define STEP (1.0f / 20.0f)
float g_t = 0.0f;
float g_step = 0.0f;
int g_frame_count = 0;
int g_step_count = 0;

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

void nogame_State_init(State *state, LoveC_Physics_BodyRef body) {
  state->t0 = 0.0f;
  state->x0 = love_physics_Body_getX(body);
  state->y0 = love_physics_Body_getY(body);
  state->r0 = love_physics_Body_getAngle(body);

  state->t1 = state->t0;
  state->x1 = state->x0;
  state->y1 = state->y0;
  state->r1 = state->r0;
}

void nogame_State_save(State *state, LoveC_Physics_BodyRef body, float t) {
  state->t0 = state->t1;
  state->x0 = state->x1;
  state->y0 = state->y1;
  state->r0 = state->r1;

  state->t1 = t;
  state->x1 = love_physics_Body_getX(body);
  state->y1 = love_physics_Body_getY(body);
  state->r1 = love_physics_Body_getAngle(body);
}

void nogame_State_get(const State *state, float t, float *x, float *y,
                      float *r) {
  t = MIN(t, state->t1);
  t = MAX(t, state->t0);

  float p = (t - state->t0) / (state->t1 - state->t0);

  *x = state->x0 + p * (state->x1 - state->x0);
  *y = state->y0 + p * (state->y1 - state->y0);
  *r = state->r0 + p * (state->r1 - state->r0);
}

typedef struct Blink {
  float closed_t;
  float next_blink_t;
} Blink;

void nogame_Blink_init(Blink *blink) {
  blink->closed_t = 0.0f;
  blink->next_blink_t = 0.0f;
}

void nogame_Blink_update(Blink *blink, float dt) {
  blink->next_blink_t = MAX(0.0f, blink->next_blink_t - dt);
  blink->closed_t = MAX(0.0f, blink->closed_t - dt);

  if (blink->next_blink_t == 0.0f) {
    blink->next_blink_t = 5.0f + rand() % 3;
    blink->closed_t = 0.0f;
  }
}

LoveC_Bool nogame_Blink_is_closed(const Blink *blink) {
  return blink->closed_t > 0.0f;
}

typedef struct Duckloon {
  LoveC_Physics_BodyRef body;
  LoveC_Physics_ShapeRef shape;
  LoveC_Physics_FixtureRef fixture;
  LoveC_Graphics_ImageRef img;
  Blink blink;
  LoveC_Physics_JointRef pin;
  State state;
} Duckloon;

static Duckloon duckloon = {
  .body = NULL,
  .shape = NULL,
  .fixture = NULL,
  .img = NULL,
  .pin = NULL,
};

int nogame_Duckloon_init(Duckloon *duckloon, LoveC_Physics_WorldRef world,
                         float x, float y, char **outError) {
  if (duckloon->body != NULL) {
    love_Object_release((LoveC_ObjectRef)duckloon->body);
    duckloon->body = NULL;
  }

  if (!love_physics_newBody(world, x, y, BODY_DYNAMIC, &duckloon->body,
                            outError)) {
    return LOVE_C_FALSE;
  }

  love_physics_Body_setLinearDamping(duckloon->body, 0.8f);
  love_physics_Body_setAngularDamping(duckloon->body, 0.8f);

  static float xs[3] = {-55.0f, 0.0f, 55.0f};
  static float ys[3] = {-60.0f, 90.0f, -60.0f};

  if (duckloon->shape != NULL) {
    love_Object_release((LoveC_ObjectRef)duckloon->shape);
    duckloon->shape = NULL;
  }

  LoveC_Physics_PolygonShapeRef shape;

  if (!love_physics_newPolygonShape(xs, ys, 3, &shape, outError)) {
    return LOVE_C_FALSE;
  }

  duckloon->shape = (LoveC_Physics_ShapeRef)shape;

  if (duckloon->fixture != NULL) {
    love_Object_release((LoveC_ObjectRef)duckloon->fixture);
    duckloon->fixture = NULL;
  }

  if (!love_physics_newFixture(duckloon->body, duckloon->shape, 1.0,
                               &duckloon->fixture, outError)) {
    return LOVE_C_FALSE;
  }

  love_physics_Fixture_setRestitution(duckloon->fixture, 0.5);

  duckloon->img = img_duckloon_normal;

  nogame_Blink_init(&duckloon->blink);

  if (duckloon->pin != NULL) {
    love_Object_release((LoveC_ObjectRef)duckloon->pin);
    duckloon->pin = NULL;
  }

  LoveC_Physics_MouseJointRef joint;

  if (!love_physics_newMouseJoint(duckloon->body, x, y - 80, &joint,
                                  outError)) {
    return LOVE_C_FALSE;
  }

  duckloon->pin = (LoveC_Physics_JointRef)joint;

  nogame_State_init(&duckloon->state, duckloon->body);

  return LOVE_C_TRUE;
}

void nogame_Duckloon_step(Duckloon *duckloon) {
  nogame_State_save(&duckloon->state, duckloon->body, g_step);

  if (((int)g_step % 5) == 0) {
    love_physics_Body_applyForceToCenter(duckloon->body, rand() % 20 + 30, 0,
                                         LOVE_C_TRUE);
  }
}

void nogame_Duckloon_update(Duckloon *duckloon, float dt) {
  nogame_Blink_update(&duckloon->blink, dt);
}

int nogame_Duckloon_draw(const Duckloon *duckloon, char **outError) {
  float x, y, r;
  nogame_State_get(&duckloon->state, g_t, &x, &y, &r);

  LoveC_Graphics_ImageRef img = img_duckloon_normal;
  if (nogame_Blink_is_closed(&duckloon->blink)) {
    img = img_duckloon_blink;
  }

  static LoveC_Colorf color = {
      .r = 1.0f,
      .g = 1.0f,
      .b = 1.0f,
      .a = 1.0f,
  };
  love_graphics_setColor(&color);

  static LoveC_Matrix4 matrix;
  love_Matrix4_setTransformation(
      &matrix, x, y, r, 1.0f, 1.0f, love_Graphics_Image_getWidth(img) / 2,
      love_Graphics_Image_getHeight(img) / 2, 0.0f, 0.0f);

  if (!love_graphics_draw((LoveC_DrawableRef)img, &matrix, outError)) {
    return LOVE_C_FALSE;
  }

  if (DEBUG) {
    // TODO
  }

  return LOVE_C_TRUE;
}

void nogame_Duckloon_attachment_point(Duckloon *duckloon, float *x, float *y) {
  love_physics_Body_getWorldPoint(duckloon->body, 4, 90, x, y);
}

typedef struct Chain_Link {
  float x;
  float y;
  float radius;
  LoveC_Graphics_ImageRef img;
  LoveC_Physics_BodyRef body;
  LoveC_Physics_ShapeRef shape;
  LoveC_Physics_FixtureRef fixture;
  State state;
  LoveC_Physics_JointRef joint;
  LoveC_Physics_JointRef join2;
} Chain_Link;

typedef struct Chain {
  Chain_Link *links;
  char *str;
  int len;
} Chain;

static Chain chain;

int nogame_Chain_init(Chain *chain, LoveC_Physics_WorldRef world, float x,
                      float y, const char *str, Duckloon *duckloon,
                      char **outError) {
  if (chain->links != NULL) {
    for (int i = 0; i < chain->len; i++) {
      Chain_Link *link = &chain->links[i];
      love_Object_release((LoveC_ObjectRef)link->body);
      love_Object_release((LoveC_ObjectRef)link->shape);
      love_Object_release((LoveC_ObjectRef)link->fixture);
      love_Object_release((LoveC_ObjectRef)link->joint);
      if (link->join2 != NULL) {
        love_Object_release((LoveC_ObjectRef)link->join2);
      }
    }
    free(chain->links);
    chain->len = 0;
  }
  if (chain->str != NULL) {
    free(chain->str);
  }

  int len = strlen(str);
  chain->links = (Chain_Link *)malloc(len * sizeof(Chain_Link));
  chain->str = strdup(str);
  chain->len = len;

  typedef struct Chain_LinkInfo {
    char c;
    float radius;
    LoveC_Graphics_ImageRef img;
  } Chain_LinkInfo;
  static Chain_LinkInfo infos[9] = {
      {'n', 11, NULL}, {'o', 11, NULL}, {'g', 11, NULL},
      {'a', 11, NULL}, {'m', 11, NULL}, {'e', 11, NULL},
      {' ', 4, NULL},  {'#', 7, NULL},  {0x0, 0, NULL}};

  infos[0].img = img_n;
  infos[1].img = img_o;
  infos[2].img = img_g;
  infos[3].img = img_a;
  infos[4].img = img_m;
  infos[5].img = img_e;
  infos[6].img = NULL;
  infos[7].img = img_square;
  infos[8].img = NULL;

  for (int i = 0; i < len; i++) {
    Chain_Link *prev = NULL;

    if (i >= 1) {
      prev = &chain->links[i - 1];
    }

    Chain_Link *link = &chain->links[i];

    link->x = x;
    link->y = y;

    Chain_LinkInfo *info = NULL;
    for (Chain_LinkInfo *inf = infos; inf->c != 0x0; ++inf) {
      if (inf->c == str[i]) {
        info = inf;
        break;
      }
    }
    if (!info) {
      *outError = strdup("Missing chain draw info");
      return LOVE_C_FALSE;
    }

    link->radius = info->radius;
    link->img = info->img;

    if (prev != NULL) {
      link->y = prev->y + prev->radius + link->radius;
    }

    if (!love_physics_newBody(world, link->x, link->y, BODY_DYNAMIC,
                              &link->body, outError)) {
      return LOVE_C_FALSE;
    }

    love_physics_Body_setLinearDamping(link->body, 0.5);
    love_physics_Body_setAngularDamping(link->body, 0.5);

    LoveC_Physics_CircleShapeRef shape;

    if (!love_physics_newCircleShape(0.0f, 0.0f, link->radius, &shape,
                                     outError)) {
      return LOVE_C_FALSE;
    }

    link->shape = (LoveC_Physics_ShapeRef)shape;

    if (!love_physics_newFixture(link->body, link->shape, 0.1f / (float)(i + 1),
                                 &link->fixture, outError)) {
      return LOVE_C_FALSE;
    }

    nogame_State_init(&link->state, link->body);

    LoveC_Physics_RevoluteJointRef revoluteJoint;

    if (prev != NULL) {
      float xA = link->x;
      float yA = link->y - link->radius / 2;
      if (!love_physics_newRevoluteJoint(link->body, prev->body, xA, yA, xA, yA,
                                         LOVE_C_FALSE, &revoluteJoint,
                                         outError)) {
        return LOVE_C_FALSE;
      }
      link->joint = (LoveC_Physics_JointRef)revoluteJoint;

      LoveC_Physics_RopeJointRef ropeJoint;

      if (!love_physics_newRopeJoint(link->body, duckloon->body, link->x,
                                     link->y, x, y, link->y - y, LOVE_C_FALSE,
                                     &ropeJoint, outError)) {
        return LOVE_C_FALSE;
      }
      link->join2 = (LoveC_Physics_JointRef)ropeJoint;
    } else {
      float xA = link->x;
      float yA = link->y;
      if (!love_physics_newRevoluteJoint(link->body, duckloon->body, xA, yA, xA,
                                         yA, LOVE_C_FALSE, &revoluteJoint,
                                         outError)) {
        return LOVE_C_FALSE;
      }
      link->joint = (LoveC_Physics_JointRef)revoluteJoint;

      link->join2 = NULL;
    }
  }

  return LOVE_C_TRUE;
}

void nogame_Chain_step(Chain *chain) {
  for (int i = 0; i < chain->len; i++) {
    nogame_State_save(&chain->links[i].state, chain->links[i].body, g_step);
  }
}

int nogame_Chain_draw(const Chain *chain, char **outError) {
  LoveC_Vector2 points[32];
  assert(chain->len < 32);

  for (int i = 0; i < chain->len; i++) {
    float x, y, _r;
    nogame_State_get(&chain->links[i].state, g_t, &x, &y, &_r);
    points[i].x = x;
    points[i].y = y;
  }

  love_graphics_setLineWidth(3);

  static LoveC_Colorf color = {
      .r = 1.0f,
      .g = 1.0f,
      .b = 1.0f,
      .a = 0.7f,
  };
  love_graphics_setColor(&color);

  if (!love_graphics_polyline(points, chain->len, outError)) {
    return LOVE_C_FALSE;
  }

  static LoveC_Colorf linkColor = {
      .r = 1.0f,
      .g = 1.0f,
      .b = 1.0f,
      .a = 1.0f,
  };

  static LoveC_Matrix4 pos;

  for (int i = 0; i < chain->len; i++) {
    Chain_Link *link = &chain->links[i];
    if (link->img != NULL) {
      float x, y, r;
      nogame_State_get(&link->state, g_t, &x, &y, &r);
      float ox = love_Graphics_Image_getWidth(link->img) / 2;
      float oy = love_Graphics_Image_getHeight(link->img) / 2;
      love_graphics_setColor(&linkColor);
      love_Matrix4_setTransformation(&pos, x, y, r, 1.0f, 1.0f, ox, oy, 0.0f,
                                     0.0f);
      if (!love_graphics_draw((LoveC_DrawableRef)link->img, &pos, outError)) {
        return LOVE_C_FALSE;
      }
    }
  }

  if (DEBUG) {
    // TODO
  }

  return LOVE_C_TRUE;
}

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

void nogame_CloudTrack_init(CloudTrack *cloudTrack, float x, float y,
                            float offset, float speed,
                            LoveC_Graphics_ImageRef img) {
  cloudTrack->x = x;
  cloudTrack->y = y;
  cloudTrack->initial_offset = offset;
  cloudTrack->h_spacing = 50;
  cloudTrack->img = img;
  cloudTrack->w = cloudTrack->h_spacing +
                  (int)love_Graphics_Image_getWidth(cloudTrack->img);
  cloudTrack->speed = speed;
  cloudTrack->count = love_graphics_getWidth() / cloudTrack->w + 2;
  cloudTrack->initial_img = rand() % 4;
}

int nogame_CloudTrack_draw(const CloudTrack *cloudTrack, char **outError) {
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
    float x = cloudTrack->x +
              i * (love_Graphics_Image_getWidth(cloudTrack->img) +
                   cloudTrack->h_spacing) +
              offset - cloudTrack->w;
    float y = cloudTrack->y;
    unsigned int img_no = abs_offset / cloudTrack->w;
    unsigned int idx = abs(cloudTrack->initial_img + i - img_no) % 4;

    if (idx >= 0 && idx < 3) {
      LoveC_Graphics_ImageRef img = cloud_images[idx];
      assert(img);

      love_Matrix4_setTranslation(&pos, x, y);
      if (!love_graphics_draw((LoveC_DrawableRef)img, &pos, outError)) {
        return LOVE_C_FALSE;
      }
    }
  }

  return LOVE_C_TRUE;
}

typedef struct Clouds {
  CloudTrack *tracks;
  size_t max;
} Clouds;

static Clouds clouds;

int nogame_Clouds_draw(const Clouds *clouds, char **outError) {
  for (int i = 0; i < clouds->max; i++) {
    if (!nogame_CloudTrack_draw(&clouds->tracks[i], outError)) {
      return LOVE_C_FALSE;
    }
  }
  return LOVE_C_TRUE;
}

int nogame_Clouds_init(Clouds *clouds) {
  int layer_height = 100;
  int max = love_graphics_getHeight() / layer_height;

  if (clouds->tracks != NULL) {
    free(clouds->tracks);
    clouds->tracks = NULL;
  }

  clouds->max = max;
  clouds->tracks = (CloudTrack *)malloc(clouds->max * sizeof(CloudTrack));
  if (!clouds->tracks) {
    printf("Error nogame_Clouds_init: out of memory\n");
    return LOVE_C_FALSE;
  }

  for (int i = 0; i < clouds->max; i++) {
    int w = love_Graphics_Image_getWidth(img_cloud_1) / 2 * i;
    nogame_CloudTrack_init(&clouds->tracks[i], 0, 20 + i * layer_height, w, 40,
                           img_cloud_1);
  }

  return LOVE_C_TRUE;
}

int nogame_update(float dt, char **outError) {
  g_t += dt;

  while (g_t > g_step) {
    if (!love_physics_World_update(world, STEP, 8, 3, outError)) {
      return LOVE_C_FALSE;
    }
    g_step += STEP;

    nogame_Duckloon_step(&duckloon);
    nogame_Chain_step(&chain);

    g_step_count += 1;
  }

  nogame_Duckloon_update(&duckloon, dt);

  return LOVE_C_TRUE;
}

int nogame_draw(char **outError) {
  if (!nogame_Clouds_draw(&clouds, outError)) {
    printf("Error nogame_Clouds_draw: %s\n", *outError);
    return LOVE_C_FALSE;
  }

  if (!nogame_Duckloon_draw(&duckloon, outError)) {
    printf("Error nogame_Duckloon_draw: %s\n", *outError);
    return LOVE_C_FALSE;
  }

  if (!nogame_Chain_draw(&chain, outError)) {
    printf("Error nogame_Chain_draw: %s\n", *outError);
    return LOVE_C_FALSE;
  }

  if (DEBUG) {
    static LoveC_Colorf color = {.r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 0.5f};

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

int create_world(char **outError) {
  int wx = love_graphics_getWidth();
  int wy = love_graphics_getHeight();

  if (world != NULL) {
    love_Object_release((LoveC_ObjectRef) world);
    world = NULL;
  }

  if (!love_physics_newWorld(0, 9.81 * 64, LOVE_C_TRUE, &world, outError)) {
    return LOVE_C_FALSE;
  }

  if (!nogame_Duckloon_init(&duckloon, world, wx / 2, wy / 2 - 100, outError)) {
    return LOVE_C_FALSE;
  }

  float ax, ay;
  nogame_Duckloon_attachment_point(&duckloon, &ax, &ay);

  if (!nogame_Chain_init(&chain, world, ax, ay, "  n o # g a m e # ", &duckloon,
                         outError)) {
    return LOVE_C_FALSE;
  }

  if (!nogame_Clouds_init(&clouds)) {
    return LOVE_C_FALSE;
  }

  return LOVE_C_TRUE;
}

int load_image(const char *bytes, LoveC_Graphics_Image_Settings *settings,
               LoveC_Graphics_ImageRef *outImage, char **outError) {
  char *decodedData;
  LoveC_SizeT decodedDataSize;
  if (!love_data_decode(ENCODE_BASE64, bytes, strlen(bytes), &decodedData,
                        &decodedDataSize, outError)) {
    return LOVE_C_FALSE;
  }

  LoveC_DataRef data;
  if (!love_data_newByteData__data(decodedData, decodedDataSize,
                                   (LoveC_Data_ByteDataRef *)&data, outError)) {
    return LOVE_C_FALSE;
  }

  LoveC_Image_ImageDataRef imageData;

  int result = love_image_newImageData__Data(data, &imageData, outError);
  love_Object_release((LoveC_ObjectRef)data);
  if (!result)
    return LOVE_C_FALSE;

  LoveC_Graphics_Image_SlicesRef slices =
      love_Graphics_Image_Slices_construct(TEXTURE_2D);

  love_Graphics_Image_Slices_set(slices, 0, 0,
                                 (LoveC_Image_ImageDataBaseRef)imageData);
  love_Object_release((LoveC_ObjectRef)imageData);

  result = love_graphics_newImage(slices, settings, outImage, outError);
  love_Graphics_Image_Slices_delete(slices);
  if (!result)
    return LOVE_C_FALSE;

  return LOVE_C_TRUE;
}

int load_nogame_images(char **outError) {
  int dpiscale = love_window_getDPIScale();
  LoveC_Graphics_Image_Settings settings = {.mipmaps = LOVE_C_FALSE,
                                            .linear = LOVE_C_FALSE,
                                            .dpiScale =
                                                dpiscale > 1.0f ? 2.0f : 1.0f};

#define LOAD_IMAGE(to, from)                                                   \
  if (!load_image(from, &settings, &to, outError)) {                           \
    return LOVE_C_FALSE;                                                       \
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

void nogame_event_quit() {
  LoveC_Event_MessageRef mes = love_Event_Message_construct("quit", NULL, 0);
  love_event_push(mes);
  love_Object_release((LoveC_ObjectRef)mes);
}

void nogame_mousepressed(LoveC_Event_MessageRef mes) {
  LoveC_VariantRef* args;
  LoveC_SizeT size;
  love_Event_Message_getArgs(mes, &args, &size);
  assert(size == 5);

  double x = love_Variant_getData(args[0])->number;
  double y = love_Variant_getData(args[1])->number;
  printf("%d\n", love_Variant_getType(args[2]));
  double b = love_Variant_getData(args[2])->number;
  LoveC_Bool istouch = love_Variant_getData(args[3])->boolean;
  double clicks = love_Variant_getData(args[4])->number;

  free(args);

  if (istouch && clicks == 2) {
    char* buttons[2];
    buttons[0] = strdup("OK");
    buttons[1] = strdup("Cancel");

    LoveC_Window_MessageBoxData messagebox;
    messagebox.type = MESSAGEBOX_INFO;
    messagebox.title = strdup("Exit No-Game Screen");
    messagebox.message = strdup("");
    messagebox.buttons = buttons;
    messagebox.buttonCount = 2;
    if (love_window_showMessageBox__MessageBoxData(&messagebox) == 0) {
      nogame_event_quit();
    }

    free(messagebox.title);
    free(messagebox.message);
    free(messagebox.buttons[0]);
    free(messagebox.buttons[1]);
  }
}

int nogame() {
  char *error = NULL;

  LoveC_Colorf bg = {.r = 43.0f / 255.0f,
                     .g = 165.0f / 255.0f,
                     .b = 223.0f / 255.0f,
                     .a = 1.0f};
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
    printf("Error create_world: %s\n", error);
    free(error);
    return LOVE_C_FALSE;
  }

  LoveC_Colorf colors[1];
  colors[0] = bg;

  LoveC_Bool *discards = malloc(sizeof(LoveC_Bool) * 20);
  discards[0] = LOVE_C_TRUE;
  discards[1] = LOVE_C_NIL;

  LoveC_Event_MessageRef mes;

  while (1) {
    if (!love_event_pump(&error)) {
      printf("Error love_event_pump: %s\n", error);
      free(error);
      return LOVE_C_FALSE;
    }

    while (love_event_poll(&mes)) {
      const char *name = love_Event_Message_getName(mes);
      printf("Event received: %s\n", name);
      if (strcmp(name, "quit") == 0) {
        return LOVE_C_TRUE;
      } else if (strcmp(name, "mousepressed") == 0) {
        nogame_mousepressed(mes);
      } else if (strcmp(name, "resize") == 0) {
        if (!create_world(&error)) {
          printf("Error create_world: %s\n", error);
          free(error);
          return LOVE_C_FALSE;
        }
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
  char *error = NULL;

  if (!init(argv[0])) {
    return 1;
  }

  printf("Hello, world! %s\n", love_version());

  if (!nogame()) {
    return 1;
  }

  return 0;
}

/* #endif */
