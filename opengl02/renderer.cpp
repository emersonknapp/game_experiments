#include "renderer.h"

Renderer::Renderer() {
  m_font = new FTGLPixmapFont("./data/trebuchet.ttf");
  if (m_font->Error()) 
    if (RENDER_DEBUG) cout << "Font Broken" << endl;
  m_font->FaceSize(72);
}

Renderer::~Renderer() {
  delete m_font;
}

void Renderer::render(Scene* scene) {
  //if (RENDER_DEBUG) cout << "Rendering" << endl;
  
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  vector<Entity*> rendies = scene->getRenderableEntities();
  vector<Entity*>::iterator it;
  
  for (it = rendies.begin(); it != rendies.end(); it++) {
    Renderable* rbl = (*it)->getRenderable();
    eRendType rt = rbl->getType();
    Transform2f* off = (*it)->getTransform();
    
    glRasterPos2f(off->getTranslation()(0), off->getTranslation()(1));
    //TODO: rotation and scale
    switch (rt) {
      case REND_TEXT:
      {
        m_font->FaceSize(((RendText*)(rbl))->m_size);
        m_font->Render(((RendText*)(rbl))->m_text.c_str());
        break;
      }
      break;
      default:
      if (RENDER_DEBUG) cout << "Unrenderable object received" << endl;
    }
  }

  glFlush();
  glutSwapBuffers();
}
