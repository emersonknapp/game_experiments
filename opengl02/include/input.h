#pragma once

#include <list>

enum InputType {NORM_DOWN, NORM_UP, SPEC_DOWN, SPEC_UP};


/// InputController interface takes user input from the InputManager and invokes the proper methods in its Controlled entity.
class InputController {
public:
  virtual ~InputController() {}
  virtual bool key(InputType itype, int k, double x, double y)=0; //takes x and y normalized to screen.
  virtual void removeControlled(Controlled* c);
protected:  
};

/// Simple interface to allow message passing between controller and controlled
/// All entities targeted by Controller must implement this
class Controlled {
public:
  virtual void registerController(InputController* ic);
protected:
  InputController* m_ctrl;
};

///in: Raw user data
///contains: controllers
///Sends to proper controllers
class InputManager {
public:
  InputManager();
  ~InputManager();
  void addController(InputController*);
  void key(InputType itype, int k, double x, double y);
protected:
  std::list<InputController*> m_controllers;
};