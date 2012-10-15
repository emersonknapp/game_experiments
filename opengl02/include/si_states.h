#pragma once

#include "input.h"
#include "state.h"
#include "quits.h"


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
  //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                std::queue<StateUpdate>* update(int mils);
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