#pragma once

#include "entity.h"

#include <set>
#include <vector>

class Scene {
public:
  //Scene();
  virtual ~Scene();
  virtual void addEntity(Entity* ent);
  virtual void removeEntity(Entity* ent);
  virtual std::set<Entity*> getEntities();
  virtual std::vector<Entity*> getRenderableEntities();
  virtual std::vector<Entity*> getCollidableEntities();
  virtual std::vector<Entity*> getMovableEntities();
protected:
  std::set<Entity*> m_entities;
};
