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

void Renderer::render(Scene* scene) {
  //if (RENDER_DEBUG) cout << "Rendering" << endl;
  vector<Entity*> rendies = scene->getRenderableEntities();
  vector<Entity*>::iterator it;
  
  for (it = rendies.begin(); it != rendies.end(); it++) {
    Renderable* rbl = (*it)->getRenderable();
    REND_TYPE rt = rbl->type();
    Transform2f off = (*it)->getTransform();
    
    glRasterPos2f(off.getTranslation()(0), off.getTranslation()(1));
    switch (rt) {
      case REND_TEXT:
      {
        m_font->FaceSize(((R_Text*)(rbl))->m_size);
        m_font->Render(((R_Text*)(rbl))->m_text.c_str());
        break;
      }
      break;
      default:
      Warning("Unrenderable object received.");
    }
  }

}
