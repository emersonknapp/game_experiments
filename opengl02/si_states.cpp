#include "si_states.h"

//****************************************************
// Title Menu
//****************************************************

M_Title::M_Title() {
  m_renderables.push_back(new R_Text(-1,.5,"Title", 72));
  m_renderables.push_back(new R_Text(-1,.2,"[P]lay", 36));
  m_renderables.push_back(new R_Text(-1,-.1,"[Q]uit", 36));
}

queue<StateUpdate>* M_Title::update(int mils) {
  if (!running()) {
    m_lastUpdate.push((StateUpdate){ST_POP, SI_NULL, 0});
  }
  
  return &m_lastUpdate;
}

void M_Title::selectItem(int i) {
  /*
  0: [P]lay game.
  1: [Q]uit.
  */
  switch (i) {
    case 0: {
      m_lastUpdate.push((StateUpdate){ST_SWAP, ST_PLAY, 0});
      break;
    }
    case 1: {
      m_running = false;
      break;
    }
  }
}

std::vector<Renderable*>& M_Title::getRenderables() {
  return m_renderables;
}

bool Ctrl_M_Title::key(InputType itype, int k, double x, double y) {
  if (m_menu == NULL) {
    Warning("Controller accessing NULL controlled.");
    return false;
  }
    
  bool ret=true;
  unsigned char ckey = (unsigned char)k;
  switch (itype) 
  {
    case NORM_DOWN:
      switch (ckey) 
      {
        case 'q':
        case 'Q':
          m_menu->selectItem(1);
          break;
        case 'p':
        case 'P':
          m_menu->selectItem(0);
          break;
        default:
          ret=false;
        break;
      }
    break;
    default:
      ret=false;
    break;
  }
  if (ret && INPUT_DEBUG) cout << "TitleCtrl got this" << endl;
  return ret;
}

Controlled* Ctrl_M_Title::getControlled() {
  return m_menu;
}

//****************************************************
// Play State
//****************************************************
S_Play::S_Play() {
  m_renderables.push_back(new R_Text(-1,.7,"Play", 15));
}

bool Ctrl_Play::key(InputType itype, int k, double x, double y) {
  if (m_playstate == NULL) {
    Warning("Controller accessing NULL controlled.");
    return false;
  }
  bool ret=true;
  unsigned char ckey = (unsigned char)k;
  switch (itype) 
  {
    case NORM_DOWN:
      switch (ckey) 
      {
        case 'q':
        case 'Q':
          m_playstate->kill();
          break;
        default:
          ret=false;
        break;
      }
    break;
    default:
      ret=false;
    break;
  }
  return ret;
}