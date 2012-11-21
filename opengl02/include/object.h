#pragma once

#include <Eigen/Core>

typedef unsigned int ObjectID;

using namespace Eigen;

class Object {
public:
  void setOID(ObjectID oid) { m_oid = oid; }
  ObjectID getOID() {return m_oid;}
protected:
  ObjectID m_oid;
};

///Translation, rotation, scale
struct Transform2D {
  Vector2f translation;
  Vector2f rotation;
  Vector2f scale;
};

///Movement information, for now just velocity
struct Movement {
  Vector2f velocity;
};

///Check for collision,
///Axis-aligned bounding box for now
struct Bounds {
  Vector2f min;
  Vector2f max;
  bool invert;
};