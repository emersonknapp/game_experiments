#include "entity.h"

Entity::Entity() : Object() {
  m_renderable = NULL;
  m_physInfo = NULL;
  m_collideInfo = NULL;
  m_transform = new Transform2f();
}

Entity::~Entity() {
  if (m_renderable != NULL) delete m_renderable;
  if (m_physInfo != NULL) delete m_physInfo;
  if (m_collideInfo != NULL) delete m_collideInfo;
  if (m_transform != NULL) delete m_transform;
}

eEntityUpdate Entity::update(int mils) {
  return ENT_OK;
}

void Entity::setRenderable(Renderable* r) {
  if (m_renderable != NULL) {delete m_renderable;}
  m_renderable = r;
}
Renderable* Entity::getRenderable() {
  return m_renderable;
}
bool Entity::isRenderable() {
  return m_renderable != NULL;
}

void Entity::setCollideInfo(CollideInfo* c) {
  if (m_collideInfo != NULL) {delete m_collideInfo;}
  m_collideInfo = c;
}
CollideInfo* Entity::getCollideInfo() {
  return m_collideInfo;
}
bool Entity::isCollidable() {
  return m_collideInfo != NULL;
}

void Entity::setPhysInfo(PhysInfo* p) {
  if (m_physInfo != NULL) {delete m_physInfo;}
  m_physInfo = p;
}
PhysInfo* Entity::getPhysInfo() {
  return m_physInfo;
}
bool Entity::isMovable() {
  return m_physInfo != NULL;
}

void Entity::setTransform(Transform2f* t) {
  if (m_transform != NULL) {delete m_transform;}
  m_transform = t;
}
Transform2f* Entity::getTransform() {
  return m_transform;
}

void Entity::translate(Vector2f v) {
  m_transform->translate(v);
}
void Entity::rotate(Vector2f v) {
  m_transform->rotate(v);
}
void Entity::scale(Vector2f v) {
  m_transform->scale(v);
}

TextEntity::TextEntity(string text, int size) {
  Entity::Entity();
  m_renderable = new RendText(text, size);
  m_text = text;
  m_size = size;
}
