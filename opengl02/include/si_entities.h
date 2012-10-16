#pragma once

#include "Eigen/Core"
#include "si_data.h"

using namespace Eigen;
enum eEntityUpdate {
  OK,
  MOVE,
  DEAD,
  SPAWN
};

class Entity {
public:
  Entity();
  virtual void setPosition(Vector2f pos);
  virtual Vector2f getPosition();
  virtual Vector2f getNextPosition();
  virtual eEntityUpdate update(int mils);
  virtual eSIObject getSpawned() {return SI_NULL;}
  virtual void collide(Entity* other) {}
  virtual void kill();
protected:
  bool m_alive;
  Vector2f m_position;
  Vector2f m_nextPosition;
  Vector2f m_velocity;
};

class Bullet : public Entity {
public:
  void collide(Entity* other);
private:
};

class Tank : public Entity {
public:
  Tank();
  eEntityUpdate update(int mils);
  void moveRight();
  void moveLeft();
  void shoot();
  void stopShooting();
  eSIObject getSpawned();
private:
  bool m_shooting; //true: fire button held down
  bool m_bulletFired; //true: fire a bullet on next update
  int m_shotWarmdown; //time (ms) since last shot fired
  int m_shootSpeed; //minimum time (ms) between shots
  float m_moveSpeed;
  Vector2f m_position;
  Vector2f m_velocity;
};

class Invader : public Entity {
  
};