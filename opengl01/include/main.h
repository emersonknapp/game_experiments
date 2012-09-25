#ifndef _MAIN_H
#define _MAIN_H

#include "common.h"

#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif


#include "classes.h"
#include "scene.h"
#include "mesh.h"
#include "entity.h"




#endif