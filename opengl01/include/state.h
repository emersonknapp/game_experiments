#ifndef STATE_H
#define STATE_H

#include <vector>

class State() {
public:
  State();
  bool update(int mils); //return false when state is finished, true otherwise
  void kill(); //make this state end immediately on next update
  
};

class StateManager() {
public:
  StateManager();
  addState(State)
};


#endif