#ifndef LOVE_PHYSICS_BOX2D_C_BODY_H
#define LOVE_PHYSICS_BOX2D_C_BODY_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN

typedef enum LoveC_Physics_Body_Type {
  BODY_INVALID,
  BODY_STATIC,
  BODY_DYNAMIC,
  BODY_KINEMATIC,
  BODY_MAX_ENUM
} LoveC_Physics_Body_Type;

LOVE_C_DEFINE_OPAQUE_TYPE(Physics_Body);

LOVE_C_EXTERN_C_END

#endif // LOVE_PHYSICS_BOX2D_C_BODY_H
