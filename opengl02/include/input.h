#pragma once

#include <map>
#include "object.h"
#define INPUT_DEBUG false

enum InputType {NORM_DOWN, NORM_UP, SPEC_DOWN, SPEC_UP};


class Controller;

///Controller interface is the way for an outside source to control a game entity
///Could be user input or AI
class Controller : public Object {
public:
};

/// InputController interface takes user input from the InputManager and invokes the proper methods in its Controlled entity.
class InputController : public Controller {
public:
  virtual ~InputController() {}
  virtual bool key(InputType itype, int k, double x, double y)=0; //takes x and y normalized to screen.
  virtual void setControlled(Object* cont)=0;
protected:
};


///in: Raw user data
///contains: controllers
///Sends to proper controllers
/*
class InputManager {
public:
  InputManager();
  ~InputManager();
  void addController(InputController*);
  void key(InputType itype, int k, double x, double y);
protected:
  std::map<ObjectID>
};
*/