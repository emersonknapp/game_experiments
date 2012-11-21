#pragma once

//GL STUFF
#include <glut.h>
#include <glu.h>

//STDLIB STUFF
#include <vector>
#include <iostream>
#include <string>
#include <map>

//TIME STUFF
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

#include <Eigen/Core>
#include <FTGL/ftgl.h>
//GAME STUFF
#include "quits.h"
#include "state.h"
#include "input.h"
#include "si_data.h"
#include "si_states.h"
#include "viewport.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_CAPTION "Space Intruders"

class SI_Game;

class SIObjectFactory {
public:
  State* getNewState(eSIObject, SI_Game*);
  InputController* getNewStateInputController(eSIObject, Object*);
private:
  void assignOID(Object* o);
  ObjectID nextID();
  static ObjectID s_nextID;
};

struct StateCtrlPair {
  State* state;
  InputController* ctrl;
};


class SI_Game {
public:
  SI_Game(int argc, char* argv[]);
  ~SI_Game();
  
  //Game behaviors
  virtual void run();
  virtual void end();
  virtual void draw();
  virtual void reshapeViewport(int w, int h);
  virtual void idle();
  virtual void normalKeyDown(unsigned char key, int x, int y);
  virtual void normalKeyUp(unsigned char key, int x, int y);
  virtual void specialKeyDown(int key, int x, int y);
  virtual void specialKeyUp(int key, int x, int y);
  Viewport* getViewport();
  
  //StateManager behaviors
  void push(eSIObject); //pushes new state
  void pop(); //changes to previous state, returns current
  State* peek(); //returns current state
  StateCtrlPair peekPair();
  State* peekPrev(); //returns state one down the stack, NULL if none
  void swap(eSIObject s); //convenience function, pop();push(s)  
  bool update(int mils);
  void kill(); //END EVERYTHING
  bool isEmpty();
  
  virtual Renderer* getRenderer();
  virtual Collision* getCollision();
  virtual Physics* getPhysics();
  
private:
  void handleKey(InputType itype, int key, int x, int y);
  Viewport* m_viewport;
  bool m_running;
  SIObjectFactory* m_factory;
  std::vector<StateCtrlPair> m_states;
  
  Collision* m_collision;
  Renderer* m_renderer;
  Physics* m_physics;
};



