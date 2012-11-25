#pragma once

#include <Eigen/Core>
using namespace Eigen;
///Translation, rotation, scale
class Transform2D {
public:
  Transform2D();
  void translate(Vector2f tr);
  void rotate(Vector2f ro);
  void scale(Vector2f sc);
  Vector2f getTranslation();
  Vector2f getRotation();
  Vector2f getScale();
private:
  Vector2f m_translation;
  Vector2f m_rotation;
  Vector2f m_scale;
};

///Check for collision,
///Axis-aligned bounding box for now
struct Bounds {
  Vector2f min;
  Vector2f max;
  bool invert;
};