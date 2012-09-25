#ifndef _CLASSES_H
#define _CLASSES_H

#include "common.h"



class Viewport {
public:
	Viewport ();
	Viewport (int width, int height);
	int w;
	int h;
};

class AABB {
public:
	AABB(vec3, vec3);
	AABB();
	bool intersect(AABB*);
	AABB* concat(AABB*);
private:
	vec3 min;
	vec3 max;
};



#endif