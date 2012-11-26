#pragma once

#include <Eigen/Core>
#include <string>
#include "object.h"
#include "attributes.h"
#include "enums.h"

using namespace Eigen;
using namespace std;

class Entity : public Object {
public:
  Entity();
  virtual ~Entity();
  virtual eEntityUpdate update(int mils);
    
  virtual void setRenderable(Renderable* r);
  virtual Renderable* getRenderable();
  virtual bool isRenderable();

  virtual void setCollideInfo(CollideInfo* c);
  virtual CollideInfo* getCollideInfo();
  virtual bool isCollidable();
  
  virtual void setPhysInfo(PhysInfo* p);
  virtual PhysInfo* getPhysInfo();
  virtual bool isMovable();
  
  virtual void setTransform(Transform2f* t);
  virtual Transform2f* getTransform();
  
  virtual void translate(Vector2f v);
  virtual void rotate(Vector2f v);
  virtual void scale(Vector2f v);
  
protected:
  Transform2f* m_transform;
  PhysInfo* m_physInfo;
  Renderable* m_renderable;
  CollideInfo* m_collideInfo;

};

class TextEntity : public Entity {
public:
  TextEntity(string text, int size);
protected:
  string m_text;
  int m_size;
};



