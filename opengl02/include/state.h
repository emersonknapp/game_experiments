#pragma once

#include <vector>

class State {
public:
  State();
  virtual bool update(int mils)=0;
  virtual bool running(); //return false when state is finished, true otherwise
  virtual void kill(); //make this state end immediately on next update
protected:
  bool m_running;
};

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
  
  void input(void); //TODO: implement inputs
  bool isEmpty();
  
  
  //TODO: get info for renderer?
private:
  std::vector<State*> m_states;
};