#include "si_game.h"

#define CALLBACK_DEBUG false
#define TITLE_DEBUG false
#define OBJECT_DEBUG false

using namespace std;

SI_Game::SI_Game(int argc, char* argv[]) {
  m_viewport = new Viewport(SCREEN_WIDTH, SCREEN_HEIGHT);
  m_factory = new SIObjectFactory();
  
  m_renderer = new Renderer();
  m_collision = new Collision();
  m_physics = new Physics();
  
  m_running = false;


  glutInit(&argc, argv);
	
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(-1, -1);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(WINDOW_CAPTION);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(-10,10,-10,10);
	
	glutIgnoreKeyRepeat(1);
	
}

SI_Game::~SI_Game() {
  delete m_viewport;
  delete m_factory;
  
  /*
  for (vector<StateCtrlPair>::iterator it = m_states.begin(); it <= m_states.end(); it++) {
    delete *it;
  }
  */
}

void SI_Game::run() {
  if (STATE_DEBUG) cout << "Running Game" << endl;
  
  push(ST_TITLE);
    
  m_running = true;
  
	glutMainLoop();
}

void SI_Game::end() {
  m_running = false;
}

Viewport* SI_Game::getViewport() {
  return m_viewport;
}

//****************************************************
// Game State Managing Methods
//****************************************************
void SI_Game::push(eSIObject s){
  State* newState = m_factory->getNewState(s, this);
  if (newState != NULL) {
    InputController* newController = m_factory->getNewStateInputController(s, newState);
    StateCtrlPair newPair;
    newPair.state = newState;
    newPair.ctrl = newController;
    m_states.push_back(newPair);
  }
  if (STATE_DEBUG) cout << "Entering state " << newState->getOID() << " with type " << s << endl;
}

void SI_Game::pop(){
  StateCtrlPair s = m_states.back();
  m_states.pop_back();
  if (STATE_DEBUG) cout << "Leaving state " << s.state->getOID() << endl;
  delete s.state;
}

State* SI_Game::peek(){
  return m_states.back().state;
}
StateCtrlPair SI_Game::peekPair() {
  return m_states.back();
}

State* SI_Game::peekPrev(){
  return m_states.at(m_states.size()-2).state;
}

void SI_Game::swap(eSIObject s){
  pop();
  push(s);
}

bool SI_Game::update(int mils) {
  if (isEmpty()) return false;
  
  queue<StateUpdate>* suQueue = peek()->update(mils);
  while (!suQueue->empty()) {
    StateUpdate su = suQueue->front();
    suQueue->pop();
    eStateUpdate suType = su.type;
    switch (suType) {
      case ST_POP:
        pop(); 
      break;
      case ST_PUSH:
        //push((State*)su.ptr);
      break;
      case ST_SWAP: {
        swap(su.obj);
        break;
      }
      default:
      Warning("Unhandled update type.");
      break;
    }
  }
  
  return true;
}

void SI_Game::kill(){
  while (!isEmpty()) {
    pop();
  }
}

bool SI_Game::isEmpty(){
  return m_states.empty();
}


//****************************************************
// Handlers
//****************************************************
void SI_Game::draw() {	
  if (CALLBACK_DEBUG) cout << "game_draw" << endl;
  
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if (!isEmpty())
    peek()->draw(m_viewport);
  
  /*
  FTGLPixmapFont font("./data/trebuchet.ttf");
  if (font.Error()) 
    Error("Font broken.");
  font.FaceSize(72);
  
  glRasterPos2f(-1,.5);
  font.Render("Hello World!");
  */
  
	glFlush();
	glutSwapBuffers();		
}

void SI_Game::reshapeViewport(int w, int h) {
  if (CALLBACK_DEBUG) cout << "game_reshapeviewport" << endl;
	m_viewport->w = w;
	m_viewport->h = h;
	
	glViewport(0,0, w, h);
	//cout << w << " " << h << endl;
	//double aspect = (double)w/(double)h;
	//cout << aspect << endl;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	

}

void SI_Game::idle() {	
   if (CALLBACK_DEBUG) cout << "game_idle" << endl;
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
  if (!keepGoing) quitProgram();
	glutPostRedisplay();
}

void SI_Game::normalKeyDown(unsigned char key, int x, int y) {
  handleKey(NORM_DOWN, (int)key, x, y);
}

void SI_Game::normalKeyUp(unsigned char key, int x, int y) {
  handleKey(NORM_UP, (int)key, x, y);
}

void SI_Game::specialKeyDown(int key, int x, int y) {
  handleKey(SPEC_DOWN, key, x, y);
}

void SI_Game::specialKeyUp(int key, int x, int y) {
  handleKey(SPEC_UP, key, x, y);
}

void SI_Game::handleKey(InputType itype, int key, int x, int y) {
  if (peekPair().ctrl->key(itype, key, x, y))
    return;
  else
    return; //TODO: pass input into state
}

//****************************************************
// Getters/Setters
//****************************************************

Renderer* SI_Game::getRenderer() {
  return m_renderer;
}

Collision* SI_Game::getCollision() {
  return m_collision;
}

Physics* SI_Game::getPhysics() {
  return m_physics;
}

//****************************************************
// Factories
//****************************************************

void SIObjectFactory::assignOID(Object* o) {
  if (o != NULL) {
    ObjectID oid = nextID();
    o->setOID(oid);
  }
}

State* SIObjectFactory::getNewState(eSIObject es, SI_Game* game) {
  State* ret = NULL;
  switch (es) {
    case ST_TITLE:
      ret = new M_Title();
      break;
    case ST_PLAY:
      ret = new S_Play();
      break;
    default:
      stringstream ss;
      ss << "Tried to initialize undefined state " << es;
      Error(ss.str());
      ret = NULL;
  }
  assignOID(ret);
  ret->postCreate(game->getRenderer());
  if (RENDER_DEBUG) cout << "Created object " << ret->getOID() << " with renderer " << game->getRenderer() << endl;
  return ret;
}

InputController* SIObjectFactory::getNewStateInputController(eSIObject es, Object* controlled) {
  InputController* ret = NULL;
  switch (es) {
    case ST_TITLE:
      ret = new M_Title_Ctrl();
      break;
    case ST_PLAY:
      ret = new S_Play_Ctrl();
      break;
    default:
      stringstream ss;
      ss << "Tried to initialize controller for undefined state " << es;
      Error(ss.str());
  }
  assignOID(ret);
  ret->setControlled(controlled);
  return ret;
}


ObjectID SIObjectFactory::s_nextID = 0;

ObjectID SIObjectFactory::nextID() {
  if (OBJECT_DEBUG) cout << "Creating new Object ID " << s_nextID << endl;
  ObjectID oid = s_nextID;
  s_nextID++;
  return oid;
}
