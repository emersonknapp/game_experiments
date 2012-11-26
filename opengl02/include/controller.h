#pragma once

#include "object.h"
#include "scene.h"
#include "entity.h"
#include "enums.h"
#include <queue>

///Controller is the interface for an outside source (AI or user) to control entities in the scene
class Controller : public Object {
public:
  Controller(Entity* ctrld);
  virtual void update(Scene* scene, int mils);
  virtual void setControlled(Entity* ctrld);
protected:
  Entity* m_controlled;
};

struct KeyEvent {
  bool special;
  bool keyDown;
  int key;
  double x;
  double y;
};

/// InputController takes user input (keyboard for now) and conveys commands to its entity
class InputController : public Controller {
public:
  InputController(Entity* ctrld) : Controller(ctrld) {}
  virtual bool key(bool special, bool keyDown, int k, double x, double y); //takes x and y normalized to screen.
protected:
  std::queue<KeyEvent> m_events; //events since last update
};

//Does not actually control an entity.
// Sees scene, and passes commands back up to state
class StateController : public InputController {
public:
  StateController();
  virtual eStateUpdate stateUpdate(Scene* scene, int mils);
};