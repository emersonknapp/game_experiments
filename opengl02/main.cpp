#include "main.h"


Game* g_game;

//****************************************************
// Callbacks
//****************************************************
void drawCB() {
  g_game->draw();
}
void reshapeViewportCB(int w, int h) {
  g_game->reshapeViewport(w, h);
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

//****************************************************
// Main
//****************************************************

int main(int argc, char *argv[]) {
	//srand(time(NULL));
  g_game = new SI_Game(argc, argv);
	
  glutKeyboardFunc(normalKeyDownCB);
  glutKeyboardUpFunc(normalKeyUpCB);
	glutSpecialFunc(specialKeyDownCB);
	glutSpecialUpFunc(specialKeyUpCB);
	glutIdleFunc(idleCB);
  glutDisplayFunc(drawCB);			
  glutReshapeFunc(reshapeViewportCB);
  
  g_game->run();
  return 0;
}