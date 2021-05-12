#include "c_Physics.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "Physics.h"

using namespace love;
using namespace love::physics::box2d;

#define instance() (Module::getInstance<Physics>(Module::M_PHYSICS))


LoveC_Result love_physics_newWorld(float gx, float gy, LoveC_Bool sleep, LoveC_Physics_WorldRef* outWorld, char **outError){
  World* world;

  try {
    world = instance()->newWorld(gx, gy, sleep);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outWorld = wrap<LoveC_Physics_WorldRef>(world);

  return true;
}

LoveC_Result love_physics_newBody(LoveC_Physics_WorldRef world, float x, float y, LoveC_Physics_Body_Type btype, LoveC_Physics_BodyRef* outBody, char **outError){
  auto world_ = unwrap<World>(world);
  auto btype_ = static_cast<love::physics::Body::Type>(btype);

  Body* body;

  try {
    body = instance()->newBody(world_, x, y, btype_);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outBody = wrap<LoveC_Physics_BodyRef>(body);

  return true;
}

LoveC_Result love_physics_newFixture(LoveC_Physics_BodyRef body, LoveC_Physics_ShapeRef shape, float density, LoveC_Physics_FixtureRef* outFixture, char** outError){
  auto body_ = unwrap<Body>(body);
  auto shape_ = unwrap<Shape>(shape);

  Fixture* fixture;

  try {
    fixture = instance()->newFixture(body_, shape_, density);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outFixture = wrap<LoveC_Physics_FixtureRef>(body);

  return true;
}

LoveC_Result love_physics_newCircleShape(float x, float y, float radius, LoveC_Physics_CircleShapeRef* outCircleShape, char **outError){
  CircleShape* shape;

  try {
    shape = instance()->newCircleShape(x, y, radius);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outCircleShape = wrap<LoveC_Physics_CircleShapeRef>(shape);

  return true;
}

LoveC_Result love_physics_newRectangleShape(float x, float y, float w, float h, float angle, LoveC_Physics_PolygonShapeRef* outRectangleShape, char **outError){
  PolygonShape* shape;

  try {
    shape = instance()->newRectangleShape(x, y, w, h, angle);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outRectangleShape = wrap<LoveC_Physics_PolygonShapeRef>(shape);

  return true;
}

LoveC_Result love_physics_newEdgeShape(float x1, float y1, float x2, float y2, LoveC_Physics_EdgeShapeRef* outEdgeShape, char **outError){
  EdgeShape* shape;

  try {
    shape = instance()->newEdgeShape(x1, y1, x2, y2);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outEdgeShape = wrap<LoveC_Physics_EdgeShapeRef>(shape);

  return true;
}

LoveC_Result love_physics_newPolygonShape(float* xs, float* ys, LoveC_SizeT vertexcount, LoveC_Physics_PolygonShapeRef* outPolygonShape, char **outError){
  if (vertexcount < 3) {
    char* err = (char*)malloc(256);
    sprintf(err, "Expected a minimum of 3 vertices, got %d.", vertexcount);
    *outError = err;
    return false;
  } else if (vertexcount > b2_maxPolygonVertices) {
    char* err = (char*)malloc(256);
    sprintf(err, "Expected a maximum of %d vertices, got %d.", b2_maxPolygonVertices, vertexcount);
    *outError = err;
    return false;
  }

  b2Vec2 vecs[b2_maxPolygonVertices];

  for (size_t i = 0; i < vertexcount; i++) {
    float x = xs[i];
    float y = ys[i];
    vecs[i] = Physics::scaleDown(b2Vec2(x, y));
  }

  b2PolygonShape* s = new b2PolygonShape();

  try {
    s->Set(vecs, vertexcount);
  } catch (const std::exception& e) {
    delete s;
    *outError = strdup(e.what());
    return false;
  }

  PolygonShape* shape = new PolygonShape(s);

  *outPolygonShape = wrap<LoveC_Physics_PolygonShapeRef>(shape);

  return true;
}

LoveC_Result love_physics_newChainShape(float* xs, float* ys, LoveC_SizeT vertexcount, LoveC_Bool loop, LoveC_Physics_ChainShapeRef* outChainShape, char **outError){
  b2Vec2 *vecs = new b2Vec2[vertexcount];

  for (size_t i = 0; i < vertexcount; i++) {
    float x = xs[i];
    float y = ys[i];
    vecs[i] = Physics::scaleDown(b2Vec2(x, y));
  }

  b2ChainShape* s = new b2ChainShape();

  try {
    if (loop)
      s->CreateLoop(vecs, vertexcount);
    else
      s->CreateChain(vecs, vertexcount);
  } catch (const std::exception& e) {
    delete[] vecs;
    delete s;
    *outError = strdup(e.what());
    return false;
  }

  ChainShape* shape = new ChainShape(s);

  *outChainShape = wrap<LoveC_Physics_ChainShapeRef>(shape);

  return true;
}

LoveC_Result love_physics_newDistanceJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float x1, float y1, float x2, float y2, LoveC_Bool collideConnected, LoveC_Physics_DistanceJointRef* outDistanceJoint, char **outError){
  auto body1_ = unwrap<Body>(body1);
  auto body2_ = unwrap<Body>(body2);

  DistanceJoint* joint;

  try {
    joint = instance()->newDistanceJoint(body1_, body2_, x1, y1, x2, y2, collideConnected);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outDistanceJoint = wrap<LoveC_Physics_DistanceJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newMouseJoint(LoveC_Physics_BodyRef body, float x, float y, LoveC_Physics_MouseJointRef* outMouseJoint, char **outError){
  auto body_ = unwrap<Body>(body);

  MouseJoint* joint;

  try {
    joint = instance()->newMouseJoint(body_, x, y);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outMouseJoint = wrap<LoveC_Physics_MouseJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newRevoluteJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, LoveC_Bool collideConnected, LoveC_Physics_RevoluteJointRef* outRevoluteJoint, char **outError){
  auto body1_ = unwrap<Body>(body1);
  auto body2_ = unwrap<Body>(body2);

  RevoluteJoint* joint;

  try {
    joint = instance()->newRevoluteJoint(body1_, body2_, xA, yA, xB, yB, collideConnected);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outRevoluteJoint = wrap<LoveC_Physics_RevoluteJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newRevoluteJoint__referenceAngle(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_RevoluteJointRef* outRevoluteJoint, char **outError){
  auto body1_ = unwrap<Body>(body1);
  auto body2_ = unwrap<Body>(body2);

  RevoluteJoint* joint;

  try {
    joint = instance()->newRevoluteJoint(body1_, body2_, xA, yA, xB, yB, collideConnected, referenceAngle);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outRevoluteJoint = wrap<LoveC_Physics_RevoluteJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newPrismaticJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, float ax, float ay, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_PrismaticJointRef* outPrismaticJoint, char **outError){
  auto body1_ = unwrap<Body>(body1);
  auto body2_ = unwrap<Body>(body2);

  PrismaticJoint* joint;

  try {
    joint = instance()->newPrismaticJoint(body1_, body2_, xA, yA, xB, yB, ax, ay, collideConnected, referenceAngle);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outPrismaticJoint = wrap<LoveC_Physics_PrismaticJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newPulleyJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float gx1, float gy1, float gx2, float gy2, float x1, float y1, float x2, float y2, float ratio, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_PulleyJointRef* outPulleyJoint, char **outError){
  auto body1_ = unwrap<Body>(body1);
  auto body2_ = unwrap<Body>(body2);

  PulleyJoint* joint;

  try {
    joint = instance()->newPulleyJoint(body1_, body2_, b2Vec2(gx1, gy1), b2Vec2(gx2, gy2), b2Vec2(x1, y1), b2Vec2(x2, y2), ratio, collideConnected);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outPulleyJoint = wrap<LoveC_Physics_PulleyJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newGearJoint(LoveC_Physics_JointRef joint1, LoveC_Physics_JointRef joint2, float ratio, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_GearJointRef* outGearJoint, char **outError){
  auto joint1_ = unwrap<Joint>(joint1);
  auto joint2_ = unwrap<Joint>(joint2);

  GearJoint* joint;

  try {
    joint = instance()->newGearJoint(joint1_, joint2_, ratio, collideConnected);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outGearJoint = wrap<LoveC_Physics_GearJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newFrictionJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, LoveC_Bool collideConnected, LoveC_Physics_FrictionJointRef* outFrictionJoint, char **outError){
  auto body1_ = unwrap<Body>(body1);
  auto body2_ = unwrap<Body>(body2);

  FrictionJoint* joint;

  try {
    joint = instance()->newFrictionJoint(body1_, body2_, xA, yA, xB, yB, collideConnected);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outFrictionJoint = wrap<LoveC_Physics_FrictionJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newWeldJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_WeldJointRef* outWeldJoint, char **outError){
  auto body1_ = unwrap<Body>(body1);
  auto body2_ = unwrap<Body>(body2);

  WeldJoint* joint;

  try {
    joint = instance()->newWeldJoint(body1_, body2_, xA, yA, xB, yB, collideConnected, referenceAngle);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outWeldJoint = wrap<LoveC_Physics_WeldJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newWheelJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float xA, float yA, float xB, float yB, float ax, float ay, LoveC_Bool collideConnected, float referenceAngle, LoveC_Physics_WheelJointRef* outWheelJoint, char **outError){
  auto body1_ = unwrap<Body>(body1);
  auto body2_ = unwrap<Body>(body2);

  WheelJoint* joint;

  try {
    joint = instance()->newWheelJoint(body1_, body2_, xA, yA, xB, yB, ax, ay, collideConnected);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outWheelJoint = wrap<LoveC_Physics_WheelJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newRopeJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float x1, float y1, float x2, float y2, float maxLength, LoveC_Bool collideConnected, LoveC_Physics_RopeJointRef* outRopeJoint, char **outError){
  auto body1_ = unwrap<Body>(body1);
  auto body2_ = unwrap<Body>(body2);

  RopeJoint* joint;

  try {
    joint = instance()->newRopeJoint(body1_, body2_, x1, y1, x2, y2, maxLength, collideConnected);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outRopeJoint = wrap<LoveC_Physics_RopeJointRef>(joint);

  return true;
}

LoveC_Result love_physics_newMotorJoint(LoveC_Physics_BodyRef body1, LoveC_Physics_BodyRef body2, float correctionFactor, LoveC_Bool collideConnected, LoveC_Physics_MotorJointRef* outMotorJoint, char **outError){
  auto body1_ = unwrap<Body>(body1);
  auto body2_ = unwrap<Body>(body2);

  MotorJoint* joint;

  try {
    joint = instance()->newMotorJoint(body1_, body2_, correctionFactor, collideConnected);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outMotorJoint = wrap<LoveC_Physics_MotorJointRef>(joint);

  return true;
}

LoveC_Result love_physics_getDistance(LoveC_Physics_FixtureRef fixture1, LoveC_Physics_FixtureRef fixture2, float* outDistance, float* outAx, float* outAy, float* outBx, float* outBy, char** outError){
  Fixture *fixtureA = unwrap<Fixture>(fixture1);
  Fixture *fixtureB = unwrap<Fixture>(fixture2);

  float distance, ax, ay, bx, by;

  try {
    distance = instance()->getDistance(fixtureA, fixtureB, ax, ay, bx, by);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  *outDistance = distance,
    *outAx = ax;
  *outAy = ay;
  *outBx = bx;
  *outBy = by;

  return true;
}

LoveC_Result love_physics_setMeter(float meter, char** outError){
  try {
    instance()->setMeter(meter);
  } catch (const std::exception& e) {
    *outError = strdup(e.what());
    return false;
  }

  return true;
}

float love_physics_getMeter(){
  return instance()->getMeter();
}


LoveC_Result love_physics_registerModule(char** outError) {
  Physics *instance = instance();
  if (instance == nullptr) {
    try {
      instance = new Physics();
    } catch (const std::exception &e) {
      *outError = strdup(e.what());
      return false;
    }
  }

  WrappedModule w;
  w.module = instance;
  w.name = "physics";
  w.type = &Module::type;
  w.functions = nullptr;
  w.types = nullptr;

  return love_c::register_module(w, outError);
}
