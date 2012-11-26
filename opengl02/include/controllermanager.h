#pragma once

#include "controller.h"
#include "object.h"
#include <map>

class ControllerManager {
public:
  ControllerManager(StateController* sc);
  virtual ~ControllerManager();
  
  virtual void addController(ObjectID controlled, Controller* controller);
  virtual void addController(ObjectID controlled, InputController* controller);
  virtual void removeController(ObjectID controlled);
  
  virtual void key(bool special, bool keyDown, int k, double x, double y);
  
  virtual eStateUpdate stateUpdate(Scene* scene, int mils);
  virtual void entityUpdate(Scene* scene, int mils);
protected:
  std::map<ObjectID, Controller*> m_controllers;
  std::map<ObjectID, InputController*> m_inputControllers;
  StateController* m_stateController;
};

