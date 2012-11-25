#pragma once

#include <map>
#include <vector>
#include "object.h"
#include "util.h"

///Movement information, for now just velocity
struct Movement {
  Vector2f velocity;
};

struct PhysicsInfo {
  Transform2D* transform;
  Movement* movement;
};

struct CollisionInfo {
  Transform2D* transform;
  Bounds* bounds;
};

class Physics {
public:
  void update(int mils);
protected:
  std::map<ObjectID, PhysicsInfo*> m_physicals;
};

class Collision {
public:
  void update();
protected:
  std::map<ObjectID, CollisionInfo*> m_collidableMap;
  std::vector<CollisionInfo*> m_collidables;
};