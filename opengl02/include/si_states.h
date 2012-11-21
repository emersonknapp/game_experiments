#pragma once

#include "input.h"
#include "state.h"
#include "quits.h"
#include "entity.h"
#include "scene.h"
#include "si_data.h"
#include "Eigen/Core"


/* TITLE */
class M_Title : public Menu {
public:
  M_Title();
  void init();
  std::queue<StateUpdate>* update(int mils);
  void selectItem(int i);
private:
};

class M_Title_Ctrl : public InputController {
public:
  bool key(InputType itype, int k, double x, double y); //takes x and y normalized to screen.
  void setControlled(Object* cont);
protected:
  M_Title* m_controlled;
};

/* PLAY */
class S_Play : public State {
public:
  S_Play();
  void init();
  std::queue<StateUpdate>* update(int mils);
private:
  SI_Scene* m_scene;
};

class S_Play_Ctrl : public InputController {
public:
  bool key(InputType itype, int k, double x, double y);
  void setControlled(Object* cont);
protected:
  S_Play* m_controlled;
};
