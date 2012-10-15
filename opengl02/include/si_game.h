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
#include "input.h"
#include "quits.h"
#include "renderable.h"
#include "renderer.h"
#include "state.h"
#include "viewport.h"
#include "si_data.h"
#include "si_states.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_CAPTION "Space Intruders"

class SIObjectFactory {
public:
  State* getNewState(eSIObject);
  InputController* getNewStateInputController(eSIObject);
private:
  ObjectID nextID();
  static ObjectID s_nextID;
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
  State* peekPrev(); //returns state one down the stack, NULL if none
  void swap(eSIObject s); //convenience function, pop();push(s)  
  bool update(int mils);
  void kill(); //END EVERYTHING
  bool isEmpty();
  std::vector<Renderable*>& getRenderables();
  
private:
  
  Viewport* m_viewport;
  InputManager* m_inputMan;
  bool m_running;
  Renderer* m_renderer;
  SIObjectFactory* m_factory;
  std::vector<State*> m_states;
};



