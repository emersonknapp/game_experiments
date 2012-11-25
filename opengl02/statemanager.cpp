#include "statemanager.h"

StateManager::StateManager(){
  
}

StateManager::~StateManager() {
  if (!isEmpty())
  for (vector<State*>::iterator it = m_states.begin(); it <= m_states.end(); it++) {
    delete *it;
  }
}
  
void StateManager::push(State* s){
  m_states.push_back(s);
}

void StateManager::pop(){
  delete peek();
  m_states.pop_back();
}

State* StateManager::peek(){
  return m_states.back();
}

State* StateManager::peekPrev(){
  return m_states.at(m_states.size()-2);
}

void StateManager::swap(State* s){
  pop();
  push(s);
}

bool StateManager::update(int mils) {
  if (isEmpty()) return false;
  
  eStateUpdate su = peek()->update(mils);
  switch (su) {
    case ST_POP:
      pop();
      break;
    case ST_PUSH: //TODO
    case ST_SWAP: //TODO
    default:
      break;
  }
  return true;
}

#include <iostream>
void StateManager::kill(){
  while (!isEmpty()) {
    pop();
  }
}

bool StateManager::isEmpty(){
  return m_states.empty();
}

int StateManager::numStates() {
  return m_states.size();
}