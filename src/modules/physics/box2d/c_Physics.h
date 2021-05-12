#ifndef LOVE_PHYSICS_BOX2D_C_PHYSICS_H
#define LOVE_PHYSICS_BOX2D_C_PHYSICS_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

#include "c_World.h"
#include "c_Contact.h"
#include "c_Body.h"
#include "c_Fixture.h"
#include "c_Shape.h"
#include "c_CircleShape.h"
#include "c_PolygonShape.h"
#include "c_EdgeShape.h"
#include "c_ChainShape.h"
#include "c_Joint.h"
#include "c_MouseJoint.h"
#include "c_DistanceJoint.h"
#include "c_PrismaticJoint.h"
#include "c_RevoluteJoint.h"
#include "c_PulleyJoint.h"
#include "c_GearJoint.h"
#include "c_FrictionJoint.h"
#include "c_WeldJoint.h"
#include "c_WheelJoint.h"
#include "c_RopeJoint.h"
#include "c_MotorJoint.h"

LOVE_C_EXTERN_C_BEGIN

LOVE_EXPORT LoveC_Result love_physics_newWorld(float gx, float gy, LoveC_Bool sleep, LoveC_Physics_WorldRef* outWorld, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newBody(LoveC_Physics_WorldRef world, float x, float y, LoveC_Physics_Body_Type btype, LoveC_Physics_BodyRef* outBody, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newFixture(LoveC_Physics_BodyRef body, LoveC_Physics_ShapeRef shape, float density, LoveC_Physics_FixtureRef* outFixture, char** outError);
LOVE_EXPORT LoveC_Result love_physics_newCircleShape(float x, float y, float radius, LoveC_Physics_CircleShapeRef* outCircleShape, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newRectangleShape(float x, float y, float w, float h, float angle, LoveC_Physics_PolygonShapeRef* outRectangleShape, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newEdgeShape(float x1, float y1, float x2, float y2, LoveC_Physics_EdgeShapeRef* outEdgeShape, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newPolygonShape(float* xs, float* ys, LoveC_SizeT vertexcount, LoveC_Physics_PolygonShapeRef* outPolygonShape, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newChainShape(float* xs, float* ys, LoveC_SizeT vertexcount, LoveC_Bool loop, LoveC_Physics_ChainShapeRef* outChainShape, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newDistanceJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float x1, float y1, float x2, float y2, LoveC_Bool collideConnected, LoveC_Physics_DistanceJointRef* outDistanceJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newMouseJoint(LoveC_Physics_BodyRef body, float x, float y, LoveC_Physics_MouseJointRef* outMouseJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newRevoluteJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_RevoluteJointRef* outRevoluteJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newPrismaticJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, float ax, float ay, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_PrismaticJointRef* outPrismaticJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newPulleyJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float gx1, float gy1, float gx2, float gy2, float x1, float y1, float x2, float y2, float ratio, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_PulleyJointRef* outPulleyJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newGearJoint(LoveC_Physics_JointRef joint1, LoveC_Physics_JointRef joint2, float ratio, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_GearJointRef* outGearJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newFrictionJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, LoveC_Bool collideConnected, LoveC_Physics_FrictionJointRef* outFrictionJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newWeldJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_WeldJointRef* outWeldJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newWheelJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, float ax, float ay, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_WheelJointRef* outWheelJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newRopeJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float x1, float y1, float x2, float y2, float maxLength, LoveC_Bool collideConnected, LoveC_Physics_RopeJointRef* outRopeJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_newMotorJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float correctionFactor, LoveC_Bool collideConnected, LoveC_Physics_MotorJointRef* outMotorJoint, char **outError);
LOVE_EXPORT LoveC_Result love_physics_getDistance(LoveC_Physics_FixtureRef fixture1, LoveC_Physics_FixtureRef fixture2, float* outDistance, float* outAx, float* outAy, float* outBx, float* outBy, char** outError);
LOVE_EXPORT LoveC_Result love_physics_setMeter(float meter, char** outError);
LOVE_EXPORT float love_physics_getMeter();

LOVE_EXPORT LoveC_Result love_physics_registerModule(char **outError);

LOVE_C_EXTERN_C_END

#endif // LOVE_PHYSICS_BOX2D_C_PHYSICS_H
