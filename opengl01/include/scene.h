#ifndef _SCENE_H
#define _SCENE_H

#include "common.h"
#include "entity.h"

class Entity;

class Scene {
public:
	Scene(float, float);
	void update(float);
	int intersect(Entity*);
	vector<Entity*> entities;
	Entity* controlEntity;
	float width();
	float height();
	
	void processNormalKeys(unsigned char, int, int);
         
	void processNormalKeyups(unsigned char, int, int);
         
	void processSpecialKeys(int, int, int);
         
	void processSpecialKeyups(int, int, int);
private:
	float _width, _height;
};



#endif