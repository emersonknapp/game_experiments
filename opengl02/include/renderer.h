#pragma once

#include <vector>
#include <map>
#include <string>

#include <FTGL/ftgl.h>

#include "gl.h"
#include "glu.h"
#include "glut.h"
#include "object.h"
#include "attributes.h"
#include "scene.h"

#define RENDER_DEBUG true

using namespace Eigen;
using namespace std;

class Renderer {
public:
  Renderer();
  virtual ~Renderer();
  void render(Scene* scene);
protected:
  FTGLPixmapFont* m_font;
};