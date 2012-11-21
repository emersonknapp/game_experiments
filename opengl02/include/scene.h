#pragma once

#include "entity.h"
#include "input.h"
#include <map>

class Scene {
public:
protected:
  //Physics* m_physics;
  //Collision* m_collision;
  Renderer* m_renderer;
  //InputManager* m_input;
  //Bounds* m_bounds;
};

class SI_Scene : public Scene {
public:
  SI_Scene();
  void addEntity(ObjectID ent, Entity* rend);
  void removeEntity(ObjectID ent);
private:
  std::map<ObjectID, Entity*> m_entities;
};
