#ifndef LOVE_PHYSICS_C_BODY_H
#define LOVE_PHYSICS_C_BODY_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "physics/c_Body.h"

LOVE_C_EXTERN_C_BEGIN

LOVE_EXPORT float love_physics_Body_getX(LoveC_Physics_BodyRef ref);
LOVE_EXPORT float love_physics_Body_getY(LoveC_Physics_BodyRef ref);
LOVE_EXPORT float love_physics_Body_getAngle(LoveC_Physics_BodyRef ref);
LOVE_EXPORT void love_physics_Body_setAngularDamping(LoveC_Physics_BodyRef ref, float damping);
LOVE_EXPORT void love_physics_Body_setLinearDamping(LoveC_Physics_BodyRef ref, float damping);
LOVE_EXPORT void love_physics_Body_applyForceToCenter(LoveC_Physics_BodyRef ref, float fx, float fy, LoveC_Bool wake);
LOVE_EXPORT void love_physics_Body_applyForce(LoveC_Physics_BodyRef ref, float fx, float fy, float rx, float ry, LoveC_Bool wake);
LOVE_EXPORT void love_physics_Body_getWorldPoint(LoveC_Physics_BodyRef ref, float x, float y, float* outX, float* outY);
LOVE_EXPORT void love_physics_Body_getWorldVector(LoveC_Physics_BodyRef ref, float x, float y, float* outX, float* outY);

LOVE_C_EXTERN_C_END

#endif // LOVE_PHYSICS_C_BODY_H
