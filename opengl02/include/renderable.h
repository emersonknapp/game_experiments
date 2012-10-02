#pragma once

#include <string>
#include <Eigen/Core>

enum REND_TYPE {REND_TEXT, REND_QUAD, REND_BITMAP};

using namespace Eigen;

class Renderable {
public:
  virtual REND_TYPE type()=0;
  Vector2d m_offset;
};

class R_Text : public Renderable {
public:
  R_Text(float x, float y, std::string text, int size);
  REND_TYPE type() {return REND_TEXT;}
  
  std::string m_text;
  int m_size;
};

class R_Quad : public Renderable {
public:
  REND_TYPE type() {return REND_QUAD;}
};

class R_Bitmap : public Renderable {
public:
  REND_TYPE type() {return REND_BITMAP;}
};