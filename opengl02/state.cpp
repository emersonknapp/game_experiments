#include "state.h"

using namespace std;

//************
// STATE    
//************
State::State() {
  m_running = true;
}

bool State::running() {
  return m_running;
}

void State::kill() {
  m_running = false;
} 

eStateUpdate State::update(int mils) {
  return ST_OK;
}


