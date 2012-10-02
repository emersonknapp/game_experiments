#pragma once

#include <vector>
#include <Eigen/Core>
#include <FTGL/ftgl.h>
#include "renderable.h"
#include "gl.h"
#include "quits.h"

class Renderer {
public:
  Renderer();
  ~Renderer();
  void render(std::vector<Renderable*>& rv);
private:
  FTGLPixmapFont* m_font;
};