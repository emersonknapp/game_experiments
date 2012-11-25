#include "si_entities.h"

Entity::Entity() {
  m_alive = true;
  m_position = Vector2f(0,0);
  m_nextPosition = Vector2f(0,0);
  m_velocity = Vector2f(0,0);
}
void Entity::setPosition(Vector2f pos) {
  m_position = pos;
}
Vector2f Entity::getPosition() {
  return m_position;
}
Vector2f Entity::getNextPosition() {
  return m_nextPosition;
}
void Entity::finalizeMove(bool accept) {
  if (accept)
    m_position = m_nextPosition;
  else
    m_nextPosition = m_position;
}

bool Entity::isAlive() {
  return m_alive;
}

eEntityUpdate Entity::update(int mils) {
  m_nextPosition = m_position + ((float)mils / 1000.0f)*m_velocity;
}

void Entity::kill() {
  m_alive = false;
}

void Bullet::collide(Entity* other) {
  other->kill();
  m_alive = false;
}

Tank::Tank() {
  Entity::Entity();
  m_shootSpeed = 500;
  m_bulletFired = false;
  m_moveSpeed = .2f;
  m_shooting = false;
  m_shotWarmdown = 0;
  
  //Initialize bullet, but keep inactive.
  m_bullet = new Bullet();
  m_bullet->kill();
}

Tank::~Tank() {
  delete m_bullet;
}

eEntityUpdate Tank::update(int mils) {
  Entity::update(mils);
  //TODO: implement
}

void Tank::moveRight() {
  m_velocity += Vector2f(1,0);
}

void Tank::moveLeft() {
  m_velocity += Vector2f(-1,0);
}

void Tank::shoot() {
  if (!m_shooting) {
    m_shooting = true;
    m_bulletFired = true;
  }
}

void Tank::stopShooting() {
  m_shooting = false;
}

eSIObject Tank::getSpawned() {
  if (m_bulletFired) return BULLET;
  else return SI_NULL;
}



