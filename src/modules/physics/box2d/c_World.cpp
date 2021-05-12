#include "c_World.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "World.h"

using namespace love;
using namespace love::physics::box2d;

LoveC_Result love_physics_World_update(LoveC_Physics_WorldRef ref, float dt, int velocityiterations, int positioniterations, char** outError) {
  auto world = unwrap<World>(ref);

  try {
    world->update(dt, velocityiterations, positioniterations);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}
