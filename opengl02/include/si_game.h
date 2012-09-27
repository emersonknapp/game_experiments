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
  virtual void displayScene();
  virtual void reshapeViewport(int w, int h);
  virtual void idle();
  virtual void normalKeyDown(unsigned char key, int x, int y);
  virtual void normalKeyUp(unsigned char key, int x, int y);
  virtual void specialKeyDown(int key, int x, int y);
  virtual void specialKeyUp(int key, int x, int y);
  Viewport* getViewport();
};


class S_MenuTitle : public State {
public:
  bool update(int mils);
};
class Ctrl_MenuTitle : public InputController {
public:
  Ctrl_MenuTitle(S_MenuTitle* menu);
  virtual bool key(InputType itype, int k, double x, double y);
private:
  S_MenuTitle* m_menu;
};

