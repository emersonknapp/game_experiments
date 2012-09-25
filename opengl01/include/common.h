#ifndef _COMMON_H
#define _COMMON_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>

#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif

#include <glut.h>
#include <glu.h>


#include <time.h>
#include <math.h>


#include <armadillo>

//NAMESPACES
using namespace std;
using namespace arma;

//DEBUG FLAGS
#define DBMAIN true
#define DEBUG true
#define DBCLASSES true
#define DBMESH true
#define DBENTITY true
#define DBSCENE true

//CONSTANTS
#define PI 3.14159265
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define EPSILON 0.001
#define MAXLINE 255

//MACROS
#define vec2 vec::fixed<2>
#define vec3 vec::fixed<3>
#define vec3u uvec::fixed<3>
#define vec4 vec::fixed<4>
#define mat3 mat::fixed<3,3>
#define mat4 mat::fixed<4,4>

//Simple function to display a message and exit the program with status 1
extern void quitProgram();
extern void Error(string);
extern void Warning(string);

enum {POINT, DIR};
enum {R, G, B};
enum {X, Y, Z};

#endif