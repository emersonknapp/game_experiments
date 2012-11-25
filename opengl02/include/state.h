#pragma once

#include <vector>
#include <string>
#include "object.h"
#include "scene.h"

#define STATE_DEBUG true

/*
TODO:
requires:
  scene
  controller
  renderer
optional:
  collision
  physics

*/
//Allows for message passing from state back up to state manager on update.
enum eStateUpdate {ST_OK, ST_POP, ST_PUSH, ST_SWAP};

using namespace std;

class State : public Object {
public:
  State();
  //virtual ~State(); //TODO
  virtual eStateUpdate update(int mils);
  virtual bool running(); //return false when state is finished, true otherwise
  virtual void kill(); //make this state end immediately on next update
protected:
  bool m_running;
  Scene* m_scene;
  //std::vector<Controller*>
  // Renderer* m_renderer;
  // Physics* m_physics;
  // Collision* m_collision;
};