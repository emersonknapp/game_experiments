#include "render.h"


R_Text::R_Text(std::string text, int size) {
  m_text = text;
  m_size = size;
}

Renderer::Renderer() {
  m_font = new FTGLPixmapFont("./data/trebuchet.ttf");
  if (m_font->Error()) 
    Error("Font broken.");
  m_font->FaceSize(72);
}

Renderer::~Renderer() {
  delete m_font;
}

void Renderer::render() {
  if (RENDER_DEBUG) cout << "Rendering" << endl;
  map<ObjectID, RenderInfo>::iterator it;
  
  for (it = m_renderables.begin(); it != m_renderables.end(); it++) {
    Renderable* rbl = it->second.renderable;
    REND_TYPE rt = rbl->type();
    Transform2D off = it->second.transform;
    
    glRasterPos2f(off.translation(0), off.translation(1));
    switch (rt) {
      case REND_TEXT:
        m_font->FaceSize(((R_Text*)(rbl))->m_size);
        m_font->Render(((R_Text*)(rbl))->m_text.c_str());
      break;
      default:
      Warning("Unrenderable object received.");
    }
  }
  /*
  case REND_TEXT:
  glRasterPos2f(off(0), off(1));
  m_font->FaceSize(((R_Text*)(*it))->m_size);
  m_font->Render(((R_Text*)(*it))->m_text.c_str());
  */

}

void Renderer::addRenderable(ObjectID entOID, RenderInfo entRend) {
  if (RENDER_DEBUG) cout << "Adding renderable for object " << entOID << endl;
  m_renderables[entOID] = entRend;
  if (RENDER_DEBUG) cout << "Added" << endl;
}

void Renderer::removeRenderable(ObjectID entOID) {
  m_renderables.erase(entOID);
}

