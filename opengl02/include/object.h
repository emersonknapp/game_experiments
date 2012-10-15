#pragma once

typedef unsigned int ObjectID;

class Object {
public:
  void setOID(ObjectID oid) { m_oid = oid; }
protected:
  ObjectID m_oid;
};