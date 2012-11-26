#pragma once

#include "object.h"
#include "entity.h"
#include "state.h"

//#include <vector>

class ObjectFactory {
public:
  Object* getNewObject();
  State* getNewState();
  Entity* getNewEntity();
  void resetIDCounter();
protected:
  //std::vector<Object*> m_objects;
private:
  void assignOID(Object* o);
  ObjectID nextID();
  static ObjectID s_nextID;
};

/*
class SIObjectFactory {
public:
  State* getNewState(eSIObject, SI_Game*);
  InputController* getNewStateInputController(eSIObject, Object*);
private:
  void assignOID(Object* o);
  ObjectID nextID();
  static ObjectID s_nextID;
};
*/