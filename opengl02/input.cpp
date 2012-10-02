#include "input.h"
#include <iostream>

using namespace std;

InputManager::InputManager() {
}

InputManager::~InputManager() {
  for (list<InputController*>::iterator it = m_controllers.begin(); it != m_controllers.end(); it++) {
    delete *it;
  }
}

void InputManager::key(InputType itype, int k, double x, double y) {
  for (list<InputController*>::iterator it = m_controllers.begin(); it != m_controllers.end(); it++) {
    if ((*it)->key(itype, k, x, y)) 
      break; 
  }
}

void InputManager::addController(InputController* con) {
  m_controllers.push_back(con);
}

Controlled::~Controlled() {
  m_ctrl->removeControlled(this);
}

void Controlled::registerController(InputController* ic) {
  m_ctrl = ic;
}