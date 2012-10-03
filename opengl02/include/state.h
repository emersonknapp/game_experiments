#pragma once

#include <vector>
#include <queue>
#include <string>
#include "renderable.h"
#include "input.h"
#include "si_data.h"



//Allows for message passing from state back up to state manager on update.
//ST_OK is implicitly passed by not having any of the other state updates.
enum eStateUpdate {ST_POP, ST_PUSH, ST_SWAP, ENT_DEAD, ENT_NEW};

struct StateUpdate {
  eStateUpdate type;
  eSIObject obj;
  ObjectID id;
};

using namespace std;

class State : public Controlled {
public:
  State();
  virtual queue<StateUpdate>* update(int mils);
  virtual bool running(); //return false when state is finished, true otherwise
  virtual void kill(); //make this state end immediately on next update
  virtual vector<Renderable*>& getRenderables();
  virtual string name() {return "AbstractState";}
protected:
  bool m_running;
  queue<StateUpdate> m_lastUpdate;
  std::vector<Renderable*> m_renderables;
};

class Menu : public State {
public:
  virtual void selectItem(int i)=0;
};

/*
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
  
  std::vector<Renderable*>& getRenderables();
  
  //TODO: get info for renderer?
private:
  std::vector<State*> m_states;
};
*/