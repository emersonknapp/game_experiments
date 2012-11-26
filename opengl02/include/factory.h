#pragma once

#include "object.h"
#include "entity.h"
//#include "state.h"
#include <string>

//#include <vector>

class ObjectFactory {
public:
  Object* getNewObject();
  Entity* getNewEntity(eEntities type);
  Entity* getNewTextEntity(std::string text, int size);
  void resetIDCounter();
protected:
  //std::vector<Object*> m_objects;
private:
  void assignOID(Object* o);
  ObjectID nextID();
  static ObjectID s_nextID;
};