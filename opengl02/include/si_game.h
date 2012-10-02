#pragma once

#include "game.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_CAPTION "Space Intruders"

class SI_Game : public Game {
public:
  SI_Game(int argc, char* argv[]);
  ~SI_Game();
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
private:
  Viewport* m_viewport;
  StateManager* m_stateMan;
  InputManager* m_inputMan;
  bool m_running;
  Renderer* m_renderer;
};

class M_Title : public Menu {
public:
  M_Title();
  StateUpdate update(int mils);
  void selectItem(int i);
  std::vector<Renderable*>& getRenderables();
};

class S_Play : public State {
public:
  S_Play();
  StateUpdate update(int mils);
};

class Ctrl_M_Title : public InputController {
public:
  Ctrl_M_Title(M_Title* menu);
  virtual bool key(InputType itype, int k, double x, double y);
private:
  M_Title* m_menu;
};

