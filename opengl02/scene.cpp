#include "scene.h"

Scene::~Scene() {
  std::set<Entity*>::iterator it;
  for (it = m_entities.begin(); it != m_entities.end(); it++) {
    delete (*it);
  }
}
void Scene::addEntity(Entity* ent) {
  m_entities.insert(ent);
}
void Scene::removeEntity(Entity* ent) {
  m_entities.erase(ent);
}

std::set<Entity*> Scene::getEntities() {
  return m_entities;
}

std::vector<Entity*> Scene::getRenderableEntities() {
  std::set<Entity*>::iterator it;
  std::vector<Entity*> ret;
  for (it = m_entities.begin(); it != m_entities.end(); it++) {
    if ((*it)->isRenderable())
      ret.push_back(*it);
  }
  return ret;
}

std::vector<Entity*> Scene::getCollidableEntities() {
  std::set<Entity*>::iterator it;
  std::vector<Entity*> ret;
  for (it = m_entities.begin(); it != m_entities.end(); it++) {
    if ((*it)->isCollidable())
      ret.push_back(*it);
  }
  return ret;
}

std::vector<Entity*> Scene::getMovableEntities() {
  std::set<Entity*>::iterator it;
  std::vector<Entity*> ret;
  for (it = m_entities.begin(); it != m_entities.end(); it++) {
    if ((*it)->isMovable())
      ret.push_back(*it);
  }
  return ret;
}