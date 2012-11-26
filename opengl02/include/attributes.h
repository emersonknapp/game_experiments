#pragma once

#include <Eigen/Core>
#include <string>
#include "enums.h"

using namespace Eigen;
using namespace std;


//////////////////////////
/// PHYSINFO
/////////////////////////
struct PhysInfo {
  Vector2f velocity;
};


//////////////////////////
/// RENDERABLE
/////////////////////////

class Renderable {
public:
  virtual eRendType getType() = 0;
};

class RendText : public Renderable {
public:
  RendText(string text, int size) : m_text(text), m_size(size) {}
  eRendType getType() {return REND_TEXT;}
  string m_text;
  int m_size;
};

//////////////////////////
/// COLLIDABLES
/////////////////////////

struct CollideInfo {
  // axis-aligned hitbox
  Vector2f offset;
  Vector2f size;
};

//////////////////////////
/// TRANSFORM
/////////////////////////

class Transform2f {
public:
  Transform2f();
  
  Vector2f getTranslation();
  void translate(Vector2f t);
  
  Vector2f getRotation();
  void rotate(Vector2f r);
  
  Vector2f getScale();
  void scale(Vector2f s);
private:
  Vector2f m_translation;
  Vector2f m_rotation;
  Vector2f m_scale;
};
