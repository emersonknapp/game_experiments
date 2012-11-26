#include "state.h"

using namespace std;

//************
// STATE    
//************
State::State(ObjectFactory* fact) {
  m_running = true;
  m_scene = NULL;
  m_ctrlMan = NULL;
  m_renderer = NULL;
  m_factory = fact;
}

State::~State() {
  if (m_scene != NULL) delete m_scene;
  if (m_ctrlMan != NULL) delete m_ctrlMan;
  if (m_renderer != NULL) delete m_renderer;
}

bool State::running() {
  return m_running;
}

void State::kill() {
  m_running = false;
} 

eStateUpdate State::update(int mils) {
  return ST_OK;
  //TODO: ctrl, move, collide
  //in that order.
  //should i delegate that to subclass? probably not necessary
}

void State::key(bool special, bool keyDown, int k, double x, double y) {
  if (m_ctrlMan != NULL) {
    m_ctrlMan->key(special, keyDown, k, x, y);
  }
}

void State::draw() {
  if (m_renderer != NULL)
    m_renderer->render(m_scene);
}

Renderer* State::getRenderer() {
  return m_renderer;
}


