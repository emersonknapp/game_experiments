#include "si_game.h"

#define CALLBACK_DEBUG false
#define STATE_DEBUG false
#define TITLE_DEBUG false

using namespace std;

SI_Game::SI_Game(int argc, char* argv[]) {
  m_viewport = new Viewport(SCREEN_WIDTH, SCREEN_HEIGHT);
  m_inputMan = new InputManager();
  m_renderer = new Renderer();
  m_stateFactory = new SIStateFactory();
  
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
  delete m_inputMan;
  delete m_renderer;
  delete m_stateFactory;
  
  for (vector<State*>::iterator it = m_states.begin(); it <= m_states.end(); it++) {
    delete *it;
  }
}

void SI_Game::run() {
  if (STATE_DEBUG) cout << "Running Game" << endl;
  
  push(SI_ST_TITLE);
  
  //InputController* start_ctrl = m_controllerFactory->getNewStateInputController(SI_ST_TITLE);
  //start_ctrl->setControlled((Controlled*)peek());
  //m_inputMan->addController(start_ctrl);
    
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
  State* newState = m_stateFactory->getNewState(s);
  if (newState != NULL) {
    m_states.push_back(newState);
    InputController* newController = m_controllerFactory->getNewStateInputController(s);
    if (newController != NULL) {
      newController->setControlled(newState);
      m_inputMan->addController(newController);
    }
  }
}

void SI_Game::pop(){
  State* s = m_states.back();
  m_states.pop_back();
  m_inputMan->removeControllerFor(s);
}

State* SI_Game::peek(){
  return m_states.back();
}

State* SI_Game::peekPrev(){
  return m_states.at(m_states.size()-2);
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

std::vector<Renderable*>& SI_Game::getRenderables() {
  return peek()->getRenderables();
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
    m_renderer->render(getRenderables());
  
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
	float dt;
#ifdef _WIN32
	DWORD currentTime = GetTickCount();
	dt = (float)(currentTime - lastTime)*0.001f; 
#else
	timeval currentTime;
	gettimeofday(&currentTime, NULL);
	dt = (float)((currentTime.tv_sec - lastTime.tv_sec) + 1e-6*(currentTime.tv_usec - lastTime.tv_usec));
#endif
	lastTime = currentTime;
	
	bool keepGoing = update(0); //TODO: this should be actual time update
  if (!keepGoing) quitProgram();
	glutPostRedisplay();
}

void SI_Game::normalKeyDown(unsigned char key, int x, int y) {
  m_inputMan->key(NORM_DOWN, (int)key, 0.0, 0.0);
}

void SI_Game::normalKeyUp(unsigned char key, int x, int y) {
  m_inputMan->key(NORM_UP, (int)key, 0.0, 0.0); //TODO: actual value mapping
}

void SI_Game::specialKeyDown(int key, int x, int y) {
	m_inputMan->key(SPEC_DOWN, key, 0.0, 0.0); //TODO: actual value mapping
}

void SI_Game::specialKeyUp(int key, int x, int y) {
	m_inputMan->key(SPEC_UP, key, 0.0, 0.0); //TODO: actual value mapping
}

//****************************************************
// Factories
//****************************************************

State* SIStateFactory::getNewState(eSIObject es) {
  switch (es) {
    case SI_ST_TITLE:
      return new M_Title();
    case SI_ST_PLAY:
      return new S_Play();
    default:
      stringstream ss;
      ss << "Tried to initialize undefined state " << es;
      Error(ss.str());
      return NULL;
  }
}

InputController* SIControllerFactory::getNewStateInputController(eSIObject es) {
  switch (es) {
    case SI_ST_TITLE:
      return new Ctrl_M_Title();
    case SI_ST_PLAY:
      return new Ctrl_Play();
    default:
    stringstream ss;
    ss << "Tried to initialize controller for undefined state " << es;
    Error(ss.str());
    return NULL;
  }
}

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
      m_lastUpdate.push((StateUpdate){ST_SWAP, SI_ST_PLAY, 0});
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
