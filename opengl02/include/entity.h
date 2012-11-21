#pragma once

#include <Eigen/Core>
#include <map>
#include <queue>
#include "object.h"
#include "render.h"
#include "physics.h"

using namespace Eigen;
using namespace std;

enum eEntityUpdate {
  OK,
  DEAD,
  SPAWN
};

//TODO: probably move imp to si_entities?
/*
struct SpawnInfo {
  eSIObject type;
  PhysicsInfo* physicsInfo;
};
*/

class Entity : public Object {
public:
  Entity(Collision* col, Renderer* rend, Physics* phys);
  virtual void init()=0;
  virtual void update(int mils)=0;
  virtual eEntityUpdate postUpdate()=0;
  //queue<eSIObject> getSpawns(); //TODO
protected:
  Transform2D* m_transform;
  Movement* m_movement;
  Renderable* m_renderable;
  Collision* m_collision;
  Renderer* m_renderer;
  Physics* m_physics;
  //queue<eSIObject> spawns;
};



