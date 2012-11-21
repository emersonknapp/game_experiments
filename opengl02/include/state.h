#pragma once

#include <vector>
#include <queue>
#include <string>
#include "si_data.h"
#include "object.h"
#include "viewport.h"
#include "render.h"

#define STATE_DEBUG true


//Allows for message passing from state back up to state manager on update.
enum eStateUpdate {ST_POP, ST_PUSH, ST_SWAP, ENT_DEAD, ENT_NEW};

struct StateUpdate {
  eStateUpdate type;
  eSIObject obj;
  ObjectID id;
};

using namespace std;

class State : public Object {
public:
  State();
  virtual void init()=0;
  virtual void postCreate(Renderer* rend);
  virtual queue<StateUpdate>* update(int mils);
  virtual void draw(Viewport* viewport);
  virtual bool running(); //return false when state is finished, true otherwise
  virtual void kill(); //make this state end immediately on next update
protected:
  bool m_running;
  queue<StateUpdate> m_updates;
  Renderer* m_renderer;
private:
  
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
  
  
private:
  std::vector<State*> m_states;
};
*/