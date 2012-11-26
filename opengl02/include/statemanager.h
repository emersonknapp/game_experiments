#pragma once

#include "state.h"
#include "factory.h"

#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif
#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif

class StateManager {
public:
  StateManager(ObjectFactory* fact);
  virtual ~StateManager();
   
   //StateActions
  virtual void push(State* s); //pushes new state
  virtual void pop(); //changes to previous state, returns current
  virtual State* peek(); //returns current state
  virtual State* peekPrev(); //returns state one down the stack, NULL if none
  virtual void swap(State* s); //convenience function, pop();push(s)
   
   //Timey-wimey
  virtual bool update(int mils);
  virtual void kill(); //END EVERYTHING
   
   //Callbacks
  virtual void draw();
   //virtual void reshapeViewport(int w, int h);
  virtual void idle();
  virtual void normalKeyDown(unsigned char key, int x, int y);
  virtual void normalKeyUp(unsigned char key, int x, int y);
  virtual void specialKeyDown(int key, int x, int y);
  virtual void specialKeyUp(int key, int x, int y);
   
   //StateInfo
  virtual bool isEmpty();
  virtual int numStates();
  
protected:
  std::vector<State*> m_states;
  ObjectFactory* m_factory;
};