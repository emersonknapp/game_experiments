#pragma once

typedef unsigned int ObjectID;

class Object {
public:
  void setOID(ObjectID oid) { m_oid = oid; }
  ObjectID getOID() {return m_oid;}
protected:
  ObjectID m_oid;
};