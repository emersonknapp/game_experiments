#pragma once

#include <vector>
#include "renderable.h"
#include "input.h"

enum StateUpdate {ST_OK, ST_POP, ST_PUSH, ST_SWAP};

class State {
public:
  State();
  virtual StateUpdate update(int mils)=0;
  virtual bool running(); //return false when state is finished, true otherwise
  virtual void kill(); //make this state end immediately on next update
  virtual State* getSuccessor();
  virtual std::vector<Renderable*>& getRenderables();
protected:
  bool m_running;
  std::vector<Renderable*> m_renderables;
  State* m_successor;
  StateUpdate m_nextUpdate;
};

class Menu : public State, public Controlled {
public:
  virtual void selectItem(int i)=0;
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
  
  bool isEmpty();
  
  std::vector<Renderable*>& getRenderables();
  
  //TODO: get info for renderer?
private:
  std::vector<State*> m_states;
};