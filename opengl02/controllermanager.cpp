#include "controllermanager.h"

ControllerManager::ControllerManager(StateController* sc) {
  m_stateController = sc;
}

ControllerManager::~ControllerManager() {
  delete m_stateController;
  std::map<ObjectID, InputController*>::iterator it;
  for (it = m_inputControllers.begin(); it != m_inputControllers.end(); it++) {
    delete it->second;
  }
  std::map<ObjectID, Controller*>::iterator it2;
  for (it2 = m_controllers.begin(); it2 != m_controllers.end(); it2++) {
    delete it2->second;
  }
}

void ControllerManager::addController(ObjectID controlled, Controller* controller) {
  m_controllers[controlled] = controller;
}
void ControllerManager::addController(ObjectID controlled, InputController* controller) {
  m_inputControllers[controlled] = controller;
}
void ControllerManager::removeController(ObjectID controlled) {
  m_controllers.erase(controlled);
  m_inputControllers.erase(controlled);
}

void ControllerManager::key(bool special, bool keyDown, int k, double x, double y) {
  std::map<ObjectID, InputController*>::iterator it;
  if (m_stateController->key(special, keyDown, k, x, y)) return;
  for (it = m_inputControllers.begin(); it != m_inputControllers.end(); it++) {
    if ((*it).second->key(special, keyDown, k, x, y)) return;
  }
}

eStateUpdate ControllerManager::stateUpdate(Scene* scene, int mils) {
  return m_stateController->stateUpdate(scene, mils);
}

void ControllerManager::entityUpdate(Scene* scene, int mils) {
  std::map<ObjectID, InputController*>::iterator it;
  for (it = m_inputControllers.begin(); it != m_inputControllers.end(); it++) {
    (*it).second->update(scene, mils);
  }
  std::map<ObjectID, Controller*>::iterator it2;
  for (it2 = m_controllers.begin(); it2 != m_controllers.end(); it2++) {
    (*it2).second->update(scene, mils);
  }
}