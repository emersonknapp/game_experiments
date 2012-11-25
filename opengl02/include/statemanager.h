#pragma once

#include "state.h"

class StateManager {
public:
  StateManager();
  ~StateManager();
  
  void push(State* s); //pushes new state
  void pop(); //changes to previous state, returns current
  State* peek(); //returns current state
  State* peekPrev(); //returns state one down the stack, NULL if none
  void swap(State* s); //convenience function, pop();push(s)
  
  bool update(int mils);
  void kill(); //END EVERYTHING
  
  bool isEmpty();
  int numStates();
  
protected:
  std::vector<State*> m_states;
};