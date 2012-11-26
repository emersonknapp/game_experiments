#include "statemanager.h"

StateManager::StateManager(){
}

StateManager::~StateManager() {
  if (!isEmpty())
  for (vector<State*>::iterator it = m_states.begin(); it <= m_states.end(); it++) {
    delete *it;
  }
}
  
void StateManager::push(State* s){
  m_states.push_back(s);
}

void StateManager::pop(){
  delete peek();
  m_states.pop_back();
}

State* StateManager::peek(){
  return m_states.back();
}

State* StateManager::peekPrev(){
  return m_states.at(m_states.size()-2);
}

void StateManager::swap(State* s){
  pop();
  push(s);
}

bool StateManager::update(int mils) {
  if (isEmpty()) return false;
  
  eStateUpdate su = peek()->update(mils);
  switch (su) {
    case ST_POP:
      pop();
      break;
    case ST_PUSH: //TODO
      
    case ST_SWAP: //TODO
    default:
      break;
  }
  return true;
}

void StateManager::draw() {
  if (!isEmpty())
    peek()->draw();
}

/*
void StateManager::reshapeViewport(int w, int h) {
//TODO: implement
  //peek()->getRenderer()->reshapeViewport(w, h);
}
*/

void StateManager::idle() {
  //Calculate time since last frame and update accordingly
  int dt;
  #ifdef _WIN32
  DWORD currentTime = GetTickCount();
  dt = currentTime - lastTime; 
  #else
  timeval currentTime;
  gettimeofday(&currentTime, NULL);
  dt = 1000*(currentTime.tv_sec - lastTime.tv_sec) + 1e-3*(currentTime.tv_usec - lastTime.tv_usec);
  #endif
  lastTime = currentTime;

  bool keepGoing = update(dt);
  if (!keepGoing) std::exit(0);
  glutPostRedisplay();
}

void StateManager::normalKeyDown(unsigned char key, int x, int y) {
  peek()->key(false, true, key, x, y);
}
void StateManager::normalKeyUp(unsigned char key, int x, int y) {
  peek()->key(false, false, key, x, y);
}
void StateManager::specialKeyDown(int key, int x, int y) {
  peek()->key(true, true, key, x, y);
}
void StateManager::specialKeyUp(int key, int x, int y) {
  peek()->key(true, false, key, x, y);
}

void StateManager::kill(){
  while (!isEmpty()) {
    pop();
  }
}

bool StateManager::isEmpty(){
  return m_states.empty();
}

int StateManager::numStates() {
  return m_states.size();
}