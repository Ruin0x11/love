#include "c_Body.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Body.h"

using namespace love;
using namespace love::physics::box2d;

float love_physics_Body_getX(LoveC_Physics_BodyRef ref) {
  return unwrap<Body>(ref)->getX();
}

float love_physics_Body_getY(LoveC_Physics_BodyRef ref) {
  return unwrap<Body>(ref)->getY();
}

float love_physics_Body_getAngle(LoveC_Physics_BodyRef ref) {
  return unwrap<Body>(ref)->getAngle();
}

void love_physics_Body_setAngularDamping(LoveC_Physics_BodyRef ref, float damping) {
  unwrap<Body>(ref)->setAngularDamping(damping);
}

void love_physics_Body_setLinearDamping(LoveC_Physics_BodyRef ref, float damping) {
  unwrap<Body>(ref)->setLinearDamping(damping);
}

void love_physics_Body_applyForceToCenter(LoveC_Physics_BodyRef ref, float fx, float fy, LoveC_Bool wake) {
  unwrap<Body>(ref)->applyForce(fx, fy, wake);
}

void love_physics_Body_applyForce(LoveC_Physics_BodyRef ref, float fx, float fy, float rx, float ry, LoveC_Bool wake) {
  unwrap<Body>(ref)->applyForce(fx, fy, rx, ry, wake);
}
