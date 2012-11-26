#include "factory.h"
#include "statemanager.h"
#include "renderer.h"
#include "scene.h"
#include <assert.h>
#include <iostream>

//GL STUFF
#include <glut.h>
#include <glu.h>

using namespace std;

ObjectFactory* g_fact;
Renderer* g_rend;
Scene* g_scene;

void done() {
  cout << "All tests passed" << endl;
  exit(0);
}

void run(void(*cb)()) {
  cb();
  g_fact->resetIDCounter();
}

void testObjectFactory() {
  cout << "Testing object factory" << endl;
  Object* o0 = g_fact->getNewObject();
  assert(o0->getOID() == 0);
  Object* o1 = g_fact->getNewObject();
  assert(o1->getOID() == 1);
}

void testStateManager() {
  cout << "Testing state manager" << endl;
  StateManager sm;
  sm.push(g_fact->getNewState());
  
  assert(sm.peek()->getOID() == 0);
  assert(sm.numStates() == 1);
  
  sm.push(g_fact->getNewState());
  sm.swap(g_fact->getNewState());
  
  assert(sm.peek()->getOID() == 2);
  assert(sm.peekPrev()->getOID() == 0);
  assert(sm.numStates()==2);
  
  sm.kill();
  
  assert(sm.numStates()==0);
}

void testScene() {
  cout << "Testing scene" << endl;
  Scene s;
  Entity* e = g_fact->getNewEntity();
  e->setRenderable(new RendText("a",1));
  s.addEntity(e);
  //s has (0)
  s.addEntity(g_fact->getNewEntity());
  //s has (0,1)
  vector<Entity*> rends = s.getRenderableEntities();
  assert(rends.size() == 1);
  assert(s.getEntities().size() == 2);
  s.removeEntity(e);
  assert(s.getEntities().size() == 1);
  assert(s.getRenderableEntities().size() == 0);
}

////////////////
///RENDERING
////////////////
void normalKeyDownCB(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':
    case 'Q':
      done();
      break;
    default:
    break; 
  }
}

void runRender() {
  g_rend->render(g_scene);
}

void initGL() {

}

void testRender() {
  g_rend = new Renderer();
  g_scene = new Scene();
  
  initGL();
  TextEntity* te = new TextEntity("Hey gurl", 72);
  te->translate(Vector2f(-1,.5));
  g_scene->addEntity(te);
  
  glutMainLoop();
}




int main(int argc, char* argv[]) {
  g_fact = new ObjectFactory();

  
  run(testObjectFactory);
  run(testStateManager);
  run(testScene);
  
  //Run rendertest last, because glut is dumb
  run(testRender);
  
  return 0;
}






