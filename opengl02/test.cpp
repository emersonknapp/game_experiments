#include "factory.h"
#include "statemanager.h"
#include <assert.h>
#include <iostream>

using namespace std;

ObjectFactory* fact;

void run(void(*cb)()) {
  cb();
  fact->resetIDCounter();
}

void testObjectFactory() {
  cout << "Testing object factory" << endl;
  Object* o0 = fact->getNewObject();
  assert(o0->getOID() == 0);
  Object* o1 = fact->getNewObject();
  assert(o1->getOID() == 1);
}

void testStateManager() {
  cout << "Testing state manager" << endl;
  StateManager sm;
  sm.push(fact->getNewState());
  
  assert(sm.peek()->getOID() == 0);
  assert(sm.numStates() == 1);
  
  sm.push(fact->getNewState());
  sm.swap(fact->getNewState());
  
  assert(sm.peek()->getOID() == 2);
  assert(sm.peekPrev()->getOID() == 0);
  assert(sm.numStates()==2);
  
  sm.kill();
  
  assert(sm.numStates()==0);
}

void testScene() {
  cout << "Testing scene" << endl;
  Scene s;
  Entity* e = fact->getNewEntity();
  e->setRenderable(new RendText("a",1));
  s.addEntity(e);
  //s has (0)
  s.addEntity(fact->getNewEntity());
  //s has (0,1)
  vector<Entity*> rends = s.getRenderableEntities();
  assert(rends.size() == 1);
  assert(s.getEntities().size() == 2);
  s.removeEntity(e);
  assert(s.getEntities().size() == 1);
  assert(s.getRenderableEntities().size() == 0);
}

int main() {
  fact = new ObjectFactory();
  run(testObjectFactory);
  run(testStateManager);
  run(testScene);
  cout << "All tests passed." << endl;
  return 0;
}



