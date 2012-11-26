#include "controller.h"
#include "enums.h"
#include "state.h"
#include "statemanager.h"
#include "controllermanager.h"
#include "factory.h"
#include "entity.h"

StateManager* g_game;

class TestFactory : public ObjectFactory {
public:  
};

class TestStateController : public StateController {
public:
  eStateUpdate stateUpdate(Scene* scene, int mils) {
    while (!m_events.empty()) {
      KeyEvent ke = m_events.front();
      m_events.pop();
      if (ke.keyDown) {
        switch (ke.key) {
          case 'q':
          //case 'Q':
            return ST_POP;
            break;
          case 'p':
          case 'P':
            //ST_SWAP to new state
            break;
          default:
            break;
        }
      }
    }
    return ST_OK;
  }
};

class TestState : public State {
protected:
  TestFactory* m_factory;
public:
  TestState(TestFactory* fact) : State(fact) {
    m_factory = fact;
    m_renderer = new Renderer();
    m_scene = new Scene();
    m_ctrlMan = new ControllerManager(new TestStateController());
    TextEntity* te = new TextEntity("TestState", 72);
    te->translate(Vector2f(-1,.5));
    m_scene->addEntity(te);
  }
  eStateUpdate update(int mils) {
    eStateUpdate ret = m_ctrlMan->stateUpdate(m_scene, mils);
    m_ctrlMan->entityUpdate(m_scene, mils);
    //TODO: move, collide
    return ret;
  }
  
};

class FramerateWidget : public TextEntity {
public:
  eEntityUpdate update(int mils) {
    return ENT_OK;
  }
};

void drawCB() {
  g_game->draw();
}
void reshapeViewportCB(int w, int h) {
	glViewport(0,0, w, h);
}

void idleCB() {
  g_game->idle();
}
void normalKeyDownCB(unsigned char key, int x, int y) {
  g_game->normalKeyDown(key, x, y);
}
void normalKeyUpCB(unsigned char key, int x, int y) {
  g_game->normalKeyUp(key, x, y);
}
void specialKeyDownCB(int key, int x, int y) {
  g_game->specialKeyDown(key, x, y);
}
void specialKeyUpCB(int key, int x, int y) {
  g_game->specialKeyUp(key, x, y);
}

int main() {
  TestFactory* fact = new TestFactory();
  g_game = new StateManager(fact);
  g_game->push(new TestState(fact));
  
  char* argv[1];
  int argc = 1;
  argv[0] = strdup("test");
  glutInit(&argc, argv);
  glutInitWindowSize(600,400);
  glutInitWindowPosition(-1,-1);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow("TestWindow");
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  gluOrtho2D(-1,1,-1,1);
  glutIgnoreKeyRepeat(1);
  
  glutKeyboardFunc(normalKeyDownCB);
  glutKeyboardUpFunc(normalKeyUpCB);
	glutSpecialFunc(specialKeyDownCB);
	glutSpecialUpFunc(specialKeyUpCB);
	glutIdleFunc(idleCB);
  glutDisplayFunc(drawCB);			
  glutReshapeFunc(reshapeViewportCB);
  
  glutMainLoop();
  
}