#pragma once

#include <vector>
#include <map>
#include <string>

#include <FTGL/ftgl.h>

#include "gl.h"
#include "quits.h"
#include "object.h"

#define RENDER_DEBUG false

enum REND_TYPE {REND_TEXT, REND_QUAD, REND_BITMAP};

using namespace Eigen;
using namespace std;

class Renderable {
public:
  virtual REND_TYPE type()=0;
};

struct RenderInfo {
  Transform2D transform;
  Renderable* renderable;
};

class R_Text : public Renderable {
public:
  R_Text(std::string text, int size);
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

class Renderer {
public:
  Renderer();
  virtual ~Renderer();
  void render();
  void addRenderable(ObjectID, RenderInfo);
  void removeRenderable(ObjectID);
protected:
  map<ObjectID, RenderInfo> m_renderables;
  FTGLPixmapFont* m_font;
};