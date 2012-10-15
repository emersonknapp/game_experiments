#pragma once

#include <list>
#include "object.h"
#define INPUT_DEBUG false

enum InputType {NORM_DOWN, NORM_UP, SPEC_DOWN, SPEC_UP};


class Controller;
class InputManager;

/// Simple interface to allow message passing between controller and controlled
/// All entities targeted by Controller must implement this
class Controlled {
};

///Controller interface is the way for an outside source to control a game entity
///Could be user input or AI
class Controller : public Object {
public:
  virtual ~Controller() {}
  virtual void setControlled(Controlled*)=0;
  //virtual void addControlled(Controlled* c)=0;
  //virtual void removeControlled(Controlled* c)=0;
};

/// InputController interface takes user input from the InputManager and invokes the proper methods in its Controlled entity.
class InputController : public Controller {
public:
  virtual ~InputController() {}
  virtual bool key(InputType itype, int k, double x, double y)=0; //takes x and y normalized to screen.
  virtual void setControlled(Controlled*)=0;
  virtual Controlled* getControlled()=0;
};

///in: Raw user data
///contains: controllers
///Sends to proper controllers
class InputManager {
public:
  InputManager();
  ~InputManager();
  void addController(InputController*);
  void removeControllerFor(Controlled*);
  void key(InputType itype, int k, double x, double y);
protected:
  std::list<InputController*> m_controllers;
};