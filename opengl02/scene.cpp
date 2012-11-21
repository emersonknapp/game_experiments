#include "scene.h"

SI_Scene::SI_Scene() {
  //m_physics = new Physics(); //TODO
  //m_collision = new Collision(); //TODO
  //m_renderer = new Renderer(); //TODO
  //m_input = new InputManager(); //TODO
  //m_bounds = new Bounds; //TODO 
}

void SI_Scene::addEntity(ObjectID entOID, Entity* entPtr) {
  m_entities[entOID] = entPtr;
}

void SI_Scene::removeEntity(ObjectID ent) {
  m_entities.erase(ent);
}