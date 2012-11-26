#include "factory.h"

#include <iostream>

using namespace std;

void ObjectFactory::assignOID(Object* o) {
 ObjectID oid = nextID();
  o->setOID(oid);
}

Object* ObjectFactory::getNewObject() {
  Object* ret = new Object();
  assignOID(ret);
  //m_objects.push_back(ret);
  return ret;
}

/*
State* ObjectFactory::getNewState() {
  State* ret = new State();
  assignOID(ret);
  //m_objects.push_back(ret);
  return ret;
}
*/

Entity* ObjectFactory::getNewEntity(eEntities type) {
  Entity* ret = new Entity();
  assignOID(ret);
  return ret;
}


ObjectID ObjectFactory::s_nextID = 0;

void ObjectFactory::resetIDCounter() {
  s_nextID = 0;
}

ObjectID ObjectFactory::nextID() {
  ObjectID oid = s_nextID++;
  return oid;
}