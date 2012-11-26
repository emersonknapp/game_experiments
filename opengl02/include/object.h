#pragma once

typedef unsigned int ObjectID;

class Object {
public:
  Object();
  void setOID(ObjectID oid);
  ObjectID getOID();
protected:
  ObjectID m_oid;
private:
  static ObjectID s_nextID;
};