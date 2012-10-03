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
  if (INPUT_DEBUG) cout << "Key " << itype << ":" << k << endl;
  if (m_controllers.empty())
    return;
  for (list<InputController*>::iterator it = m_controllers.begin(); it != m_controllers.end(); it++) {
    if ((*it)->key(itype, k, x, y)) 
      break; 
  }
}

void InputManager::addController(InputController* con) {
  if (INPUT_DEBUG) cout << "Adding new controller." << endl;
  m_controllers.push_back(con);
}

void InputManager::removeControllerFor(Controlled* ctrld) {
  list<InputController*>::iterator it;
  for (it = m_controllers.begin(); it != m_controllers.end(); it++) {
    if ( (*it)->getControlled() == ctrld) {
      m_controllers.erase(it);
    }
  }
}

/*
void Controlled::registerController(InputController* ic) {
  m_ctrl = ic;
}

void Controlled::unregisterController(InputController* ic) {
  m_ctrl->removeControlled(this);
}
*/