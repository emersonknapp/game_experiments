#pragma once

#include <vector>
#include <string>
#include "object.h"
#include "scene.h"
#include "controllermanager.h"
#include "renderer.h"

#define STATE_DEBUG true

/*
TODO:
  collision
  physics

*/
//Allows for message passing from state back up to state manager on update.

using namespace std;

class State : public Object {
public:
  State();
  virtual ~State();
  virtual eStateUpdate update(int mils);
  virtual bool running(); //return false when state is finished, true otherwise
  virtual void kill(); //make this state end immediately on next update
  virtual void key(bool special, bool keyDown, int k, double x, double y);
  
  //Renderparts
  virtual void draw();
  virtual Renderer* getRenderer();
protected:
  bool m_running;
  Scene* m_scene;
  ControllerManager* m_ctrlMan;
  Renderer* m_renderer;
  // Physics* m_physics;
  // Collision* m_collision;
};