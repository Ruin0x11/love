#ifndef LOVE_PHYSICS_BOX2D_C_WORLD_H
#define LOVE_PHYSICS_BOX2D_C_WORLD_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN

LOVE_C_DEFINE_OPAQUE_TYPE(Physics_World);

LOVE_EXPORT LoveC_Result love_physics_World_update(LoveC_Physics_WorldRef ref, float dt, int velocityiterations, int positioniterations, char** outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_PHYSICS_BOX2D_C_WORLD_H
