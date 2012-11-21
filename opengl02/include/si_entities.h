#pragma once

#include "Eigen/Core"
#include "si_data.h"
#include "input.h"

using namespace Eigen;


class Bullet : public Entity {
public:
  void collide(Entity* other);
private:
};

class Tank : public Entity, public Controlled {
public:
  Tank();
  ~Tank();
  eEntityUpdate update(int mils);
  void moveRight();
  void moveLeft();
  void shoot();
  void stopShooting();
private:
  bool m_shooting; //true: fire button held down
  float m_moveSpeed;
  Bullet* m_bullet;
  Vector2f m_position;
  Vector2f m_velocity;
};

class Invader : public Entity {
  
};

class InvaderFleet : public Entity {
  
};