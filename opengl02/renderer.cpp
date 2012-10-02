#include "renderer.h"


Renderer::Renderer() {
  m_font = new FTGLPixmapFont("./data/trebuchet.ttf");
  if (m_font->Error()) 
    Error("Font broken.");
  m_font->FaceSize(72);
}

Renderer::~Renderer() {
  delete m_font;
}

void Renderer::render(std::vector<Renderable*>& rv) {
  for (std::vector<Renderable*>::iterator it = rv.begin(); it != rv.end(); it++) {
    REND_TYPE rt = (*it)->type();
    Eigen::Vector2d off = (*it)->m_offset;
    switch (rt) {
      case REND_TEXT:
        glRasterPos2f(off(0), off(1));
        m_font->FaceSize(((R_Text*)(*it))->m_size);
        m_font->Render(((R_Text*)(*it))->m_text.c_str());
      break;
      default:
      Warning("Unhandled renderable type.");
      break;
    }
  }
}