#ifndef LOVE_PHYSICS_BOX2D_C_FIXTURE_H
#define LOVE_PHYSICS_BOX2D_C_FIXTURE_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN

LOVE_C_DEFINE_OPAQUE_TYPE(Physics_Fixture);

LOVE_EXPORT void love_physics_Fixture_setRestitution(LoveC_Physics_FixtureRef ref, float restitution);

LOVE_C_EXTERN_C_END

#endif // LOVE_PHYSICS_BOX2D_C_FIXTURE_H
