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
  
  if (!peek()->update(mils)) pop();
  
  return true;
}

void StateManager::kill(){
  while (!isEmpty()) {
    pop();
  }
}
  
void StateManager::input(void){
  //TODO: imp
}

bool StateManager::isEmpty(){
  return m_states.empty();
}
