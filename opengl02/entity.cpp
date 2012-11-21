#include "entity.h"
  
Entity::Entity(Collision* col, Renderer* rend, Physics* phys) {
  m_physics = phys;
  m_collision = col;
  m_renderer = rend;
}