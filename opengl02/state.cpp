#include "state.h"

using namespace std;

//************
// STATE    
//************
State::State() {
  m_running = true;
}

bool State::running() {
  return m_running;
}

void State::kill() {
  m_running = false;
} 

State* State::getSuccessor() {
  return m_successor;
}

std::vector<Renderable*>& State::getRenderables() {
  return m_renderables;
}

//************
// STATE MANAGER
//************

StateManager::StateManager(){
  
}

StateManager::~StateManager() {
  for (vector<State*>::iterator it = m_states.begin(); it <= m_states.end(); it++) {
    delete *it;
  }
}
  
void StateManager::push(State* s){
  m_states.push_back(s);
}

void StateManager::pop(){
  delete m_states.back();
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
  
  StateUpdate su = peek()->update(mils);
  switch (su) {
    case ST_POP:
      pop(); 
    break;
    case ST_PUSH:
      push(peek()->getSuccessor());
    break;
    case ST_SWAP:
      swap(peek()->getSuccessor());
    break;
    default:
    break;
  }
  
  return true;
}

void StateManager::kill(){
  while (!isEmpty()) {
    pop();
  }
}

bool StateManager::isEmpty(){
  return m_states.empty();
}

std::vector<Renderable*>& StateManager::getRenderables() {
  return peek()->getRenderables();
}
