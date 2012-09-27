#pragma once


#include <glut.h>
#include <glu.h>

#include <time.h>
#include <math.h>

#include <Eigen/Core>

#include "si_game.h"

using namespace std;

//Misc
void setPixel(float x, float y, GLfloat r, GLfloat g, GLfloat b);

//Lazy
void initGL();
void processArgs(int argc, char* argv[]);
void initScene();