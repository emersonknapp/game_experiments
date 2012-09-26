#include "main.h"

//****************************************************
// Global Variables
//****************************************************
Viewport			viewport;
vector<Mesh*>		meshes;
Scene*				scene;



//****************************************************
// Helper Functions
//****************************************************

void setPixel(float x, float y, GLfloat r, GLfloat g, GLfloat b) {
	glColor3f(r, g, b);
	glVertex2f(x, y);
}

void quitProgram() {
	exit(0);
}

void quitProgram(int code) {
	exit(code);
}

void Error(string msg) {
	cout << msg << endl;
	quitProgram(1);
}
void Warning(string msg) {
	cout << "Warning: " << msg << endl;
}

void Usage() {

}

//***************************************************
// Function what actually draws to screen
//***************************************************
void displayScene() {	
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(-.15, -1.1, -3);
	//glRotatef(-40, 1, 0, 0);
	
	for (size_t i=0; i<scene->entities.size(); i++) {
		glPushMatrix();
		Entity* e = scene->entities[i];
		e->draw();
		glPopMatrix();
	}

	
	glFlush();
	glutSwapBuffers();		

}

//Reshape the viewport if the window is resized
void reshapeViewport(int w, int h) {
	viewport.w = w;
	viewport.h = h;
	
	glViewport(0,0, w, h);
	//cout << w << " " << h << endl;
	double aspect = (double)w/(double)h;
	//cout << aspect << endl;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45, aspect, 1.0f, 1000.0f);
	

}

void idle() {
	
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
	
	scene->update(dt);
	glutPostRedisplay();
}

//Deals with normal keydowns
void processNormalKeys(unsigned char key, int x, int y) {
	//escape, q, spacebar quit
	string name;
	switch(key) {
		case 27:
		case 'q':
			quitProgram();
			break;
		default:
			scene->processNormalKeys(key, x, y);
	}
}

void processNormalKeyups(unsigned char key, int x, int y) {
	scene->processNormalKeyups(key, x, y);
}

void processSpecialKeys(int key, int x, int y) {
	scene->processSpecialKeys(key, x, y);
}

void processSpecialKeyups(int key, int x, int y) {
	scene->processSpecialKeyups(key, x, y);
}




void initGL() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	glDepthFunc(GL_LEQUAL);
	
	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
   	glEnable(GL_COLOR_MATERIAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	GLfloat LightAmbient[]= {0, 0, 0, 1};
	GLfloat LightDiffuse[]= {.4, .4, .4, 1};				
	GLfloat LightPosition[]= { 2, 5, 0, 1};
	GLfloat LightSpecular[]={.1,.1,.1,1};
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
	glEnable(GL_LIGHT1);
	
	//glutFullScreen();
}

void initScene(){
	initGL();
	
	scene = new Scene(1.2, 2);

	reshapeViewport(viewport.w,viewport.h);
}


void processArgs(int argc, char* argv[]) {
	if (argc < 0) {
		Usage();
	}
	string arg;
	for (int i=0; i<argc; i++) {
		arg = argv[i];
		cout << arg << endl;
	}

}

int main(int argc, char *argv[]) {
	//srand(time(NULL));
	
	viewport = Viewport(SCREEN_WIDTH, SCREEN_HEIGHT);
	processArgs(argc, argv);
	
	
  	glutInit(&argc, argv);

  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  	glutInitWindowSize(viewport.w, viewport.h);
  	glutInitWindowPosition(-1, -1);
  	glutCreateWindow("SI");

	initScene();

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(processNormalKeyups);
	glutSpecialFunc(processSpecialKeys);
	glutSpecialUpFunc(processSpecialKeyups);
	glutIdleFunc(idle);
  	glutDisplayFunc(displayScene);			
  	glutReshapeFunc(reshapeViewport);

	glutMainLoop();

  
  	return 0;
}