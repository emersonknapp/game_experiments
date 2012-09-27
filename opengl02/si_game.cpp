#include "si_game.h"


using namespace std;

SI_Game::SI_Game(int argc, char* argv[])  {
  m_viewport = new Viewport(SCREEN_WIDTH, SCREEN_HEIGHT);
  m_stateMan = new StateManager();
  m_inputMan = new InputManager();
  
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
  delete m_stateMan;
}

void SI_Game::run() {
  S_MenuTitle* start = new S_MenuTitle();
  Ctrl_MenuTitle* start_ctrl = new Ctrl_MenuTitle(start);
  
  m_stateMan->push(start);
  m_inputMan->addController(start_ctrl);
  
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
// Handlers
//****************************************************
void SI_Game::displayScene() {	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*
	glTranslatef(-.15, -1.1, -3);
	//glRotatef(-40, 1, 0, 0);
	
	for (size_t i=0; i<scene->entities.size(); i++) {
		glPushMatrix();
		Entity* e = scene->entities[i];
		e->draw();
		glPopMatrix();
	}
	*/
	glFlush();
	glutSwapBuffers();		
}

void SI_Game::reshapeViewport(int w, int h) {
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
	
	bool keepGoing = m_stateMan->update(0); //TODO: this should be actual time update
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
// Title Menu
//****************************************************

bool S_MenuTitle::update(int mils) {
  if (!running()) return false;
  
  return true;
}

Ctrl_MenuTitle::Ctrl_MenuTitle(S_MenuTitle* menu) : m_menu(menu) {}

bool Ctrl_MenuTitle::key(InputType itype, int k, double x, double y) {
  bool ret=true;
  unsigned char ckey = (unsigned char)k;
  switch (itype) 
  {
    case NORM_DOWN:
      switch (ckey) 
      {
        case 'q':
        case 'Q':
          m_menu->kill();
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
