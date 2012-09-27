#pragma once

#include <list>

enum InputType {NORM_DOWN, NORM_UP, SPEC_DOWN, SPEC_UP};

class InputController {
public:
  virtual ~InputController() {}
  virtual bool key(InputType itype, int k, double x, double y)=0; //takes x and y normalized to screen.
protected:  
};

class InputManager {
public:
  InputManager();
  ~InputManager();
  void addController(InputController*);
  void key(InputType itype, int k, double x, double y);
protected:
  std::list<InputController*> m_controllers;
};