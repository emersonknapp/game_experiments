#include "openglheaders.h"
#include <stdio.h>
#include <sys/time.h>
#include <iostream>

#include <Eigen/Dense>
#include <assert.h>
#include "player.h"
#include "game.h"

#define WINDOW_WIDTH     640 
#define WINDOW_HEIGHT    480 

#define ESCAPE 27

using namespace Eigen;
using namespace std;


Game* gGame;
int window;

void loadGLTextures(void);
void initGL(void);
void resizeGLScene(int, int);
void idle(void);
void display(void);
void keyPressed(unsigned char, int, int);
void keyReleased(unsigned char, int, int);
void specialKeyPressed(int, int, int);
void specialKeyReleased(int, int, int);
void createGlutWindow(void);

void initGL(int width, int height)
{
  glEnable(GL_TEXTURE_2D);

  glClearColor(1.0f, 0.5f, 0.2f, 0.0f);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
  //gluPerspective(45.0f, (GLfloat)width/(GLfloat)height,0.1f,100.0f);
  glutIgnoreKeyRepeat(1);

  glMatrixMode(GL_MODELVIEW);

}

void resizeGLScene(int width, int height)
{
  if (height==0)
    height=1;

  glViewport(0,0,width,height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0, width, 0, height);
  glMatrixMode(GL_MODELVIEW);
}

void idle(void)
{
  static int lastTime = glutGet(GLUT_ELAPSED_TIME);

  int currentTime = glutGet(GLUT_ELAPSED_TIME);
  int dt = currentTime - lastTime;

  gGame->update(dt/1000.0);

  lastTime = currentTime;

}

void display(void)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glLoadIdentity();

  gGame->draw();

  glutSwapBuffers();
  glutPostRedisplay();
} 

void keyPressed(unsigned char key, int x, int y)
{

  if (key == ESCAPE)
  {
    glutDestroyWindow(window);
    exit(0);
  }
  else
  {
    gGame->keyPressed(key, x, y);
  }
}

void keyReleased(unsigned char key, int x, int y)
{
  gGame->keyReleased(key, x, y);
}

void specialKeyPressed(int key, int x, int y)
{
  gGame->specialKeyPressed(key, x, y);
}

void specialKeyReleased(int key, int x, int y)
{
  gGame->specialKeyReleased(key, x, y);
}

void createGlutWindow()
{
  glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT); 
  glutInitWindowPosition (100, 100); 
  window = glutCreateWindow("Super Excellent Game");
  glutDisplayFunc(&display);
  glutReshapeFunc(&resizeGLScene);
  glutKeyboardFunc(&keyPressed);
  glutKeyboardUpFunc(&keyReleased);
  glutSpecialFunc(&specialKeyPressed);
  glutSpecialUpFunc(&specialKeyReleased);
  glutIdleFunc(&idle);
  //glutFullScreen();
}

int main(int argc, char** argv) 
{ 
  glutInit(&argc, argv); 
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA); 
  createGlutWindow();
  initGL(WINDOW_WIDTH, WINDOW_HEIGHT);

  gGame = new Game();

  glutMainLoop();

  return 1;
}
