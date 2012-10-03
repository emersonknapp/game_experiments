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

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_CAPTION "Space Intruders"


class SIStateFactory {
public:
  State* getNewState(eSIObject);
};

class SIControllerFactory {
public:
  InputController* getNewStateInputController(eSIObject);
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
  SIStateFactory* m_stateFactory;
  SIControllerFactory* m_controllerFactory;
  std::vector<State*> m_states;
};



/* TITLE */
class M_Title : public Menu {
public:
  M_Title();
  std::queue<StateUpdate>* update(int mils);
  void selectItem(int i);
  std::vector<Renderable*>& getRenderables();
};

class Ctrl_M_Title : public InputController {
public:
  Ctrl_M_Title() : m_menu(NULL) {}
  void setControlled(Controlled* c) { m_menu = (M_Title*)(c);}
  virtual bool key(InputType itype, int k, double x, double y);
  Controlled* getControlled();
  //void addControlled(Controlled* mt);
  //void removeControlled(Controlled* mt);
private:
  M_Title* m_menu;
};

/* PLAY */
class S_Play : public State {
public:
  S_Play();
  //std::queue<StateUpdate>* update(int mils);
  //std::vector<Renderable*>& getRenderables();
};

class Ctrl_Play : public InputController {
public:
  Ctrl_Play() : m_playstate(NULL) {}
  void setControlled(Controlled* c) { m_playstate = (S_Play*)(c);}
  Controlled* getControlled() {return m_playstate;}
  bool key(InputType itype, int k, double x, double y);

private:
  S_Play* m_playstate;
};



