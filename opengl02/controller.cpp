#include "controller.h"

using namespace std;

Controller::Controller(Entity* ctrld) : m_controlled(ctrld) {}

void Controller::update(Scene* scene, int mils) {}

void Controller::setControlled(Entity* ctrld) {
  m_controlled = ctrld;
}

bool InputController::key(bool special, bool keyDown, int k, double x, double y) {
  KeyEvent ke = {special, keyDown, k, x, y};
  m_events.push(ke);
  return true;
  //TODO: key interface to tell if key was not received. for now, all controllers will receive key
}


StateController::StateController() : InputController(NULL) {
}

eStateUpdate StateController::stateUpdate(Scene* scene, int mils) {
  return ST_OK;
}