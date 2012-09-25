#ifndef _ENTITY_H
#define _ENTITY_H

#include "common.h"
#include "mesh.h"
#include "classes.h"
#include "scene.h"

class Scene;

class Entity {
public:
	Mesh* mesh;
	Entity(vec3 pos, Scene*);
	virtual void draw();
	virtual void update(float);
	virtual bool keyDown(unsigned char);
	virtual void keyUp(unsigned char);
	virtual bool specialKeyDown(int);
	virtual void specialKeyUp(int);
	vec3 position();	
protected:
	vec3 pos;
	vec3 dir;
	float speed;
	AABB* aabb;
	Scene* scene;
};

class Tank : public Entity {
public:
	Tank(Scene*);
	bool keyDown(unsigned char);
	bool specialKeyDown(int);
	void specialKeyUp(int);
	void mainGun();
};

class Bullet : public Entity {
public:
	Bullet(vec3 dir, vec3 pos, float speed, Scene*);
	void hit(Entity*);
};

class Invader : public Entity {
public:
	Invader(vec3, Scene*);
	void update(float);
	void move();
protected:
	float jump, elapsed;
	int x, y;
};

class Fleet : public Entity {
public:
	Fleet(Scene*);
	Fleet(std::string filename, Scene*);
	void update(float);
	void move();
	void destroy(int);
	void refreshAABB();
	
protected:
	vector<Invader*> invaders;
	int width, height;
	AABB* aabb;
	float jump, elapsed;
	
};

#endif