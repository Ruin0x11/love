#include "c_Fixture.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Fixture.h"

using namespace love;
using namespace love::physics::box2d;


void love_physics_Fixture_setRestitution(LoveC_Physics_FixtureRef ref, float restitution) {
  unwrap<Fixture>(ref)->setRestitution(restitution);
}
