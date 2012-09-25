#include "entity.h"

Entity::Entity(vec3 p, Scene* s) {
	pos = p;
	dir = vec("0 0 0");
	speed = 0;
	scene = s;
}
void Entity::update(float dt) {
	float newx = pos[0] + dir[0]*dt*speed;
	if (newx > scene->width()) {
		pos[0] = scene->width();
	} else if (newx < -scene->width()) {
		pos[0] = -scene->width();
	} else {
		pos[0] = newx;
	}
	
	float newy = pos[1] + dir[1]*dt*speed;
	if (newy > scene->height()) {
		pos[1] = scene->height();
	} else if (newy < 0) {
		pos[1] = 0;
	} else {
		pos[1] = newy;
	}
		
	//if (DBENTITY) cout << pos[0] << " " << pos[1] << endl;
}
void Entity::draw() {
	vec3 t = pos;
	glTranslatef(t[0], t[1], t[2]);
	glColor3f(.1,1,.1);
	glVertexPointer(3, GL_FLOAT, 0, mesh->verts);
	glDrawElements(GL_TRIANGLES, 3*mesh->n_poly, GL_UNSIGNED_INT, mesh->indices);
}
bool Entity::keyDown(unsigned char key) {
	switch(key) {
		default:
			return false;
	}
	return true;
}
void Entity::keyUp(unsigned char key) {
	switch(key) {
		
	}
}
bool Entity::specialKeyDown(int key) {
	return false;
}
void Entity::specialKeyUp(int key) {
	return;
}
vec3 Entity::position() {
	return pos;
}


Tank::Tank(Scene* s) : Entity(vec("0 0 0"), s) {
	mesh = new Mesh("data/tank.obj");
	speed = 2;
}
bool Tank::keyDown(unsigned char key) {
	switch(key) {
		case 32:
			mainGun();
		default:
			return false;
	}
	return true;
}
bool Tank::specialKeyDown(int key) {
	switch(key) {
		case GLUT_KEY_LEFT:
			dir[0] += -1; break;
		case GLUT_KEY_RIGHT:
			dir[0] += 1; break;
		default:
			return false;
	}
	return true;
}
void Tank::specialKeyUp(int key) {
	switch(key) {
		case GLUT_KEY_LEFT:
			dir[0] -= -1; break;
		case GLUT_KEY_RIGHT:
			dir[0] -= 1; break;
	}
}
void Tank::mainGun() {
	if (DBENTITY) cout << "Bang." << endl;
	vec bulletPos;
	bulletPos << pos[0] << pos[1] + .01 << 0 << endr;
	Bullet* b = new Bullet(vec("0 1 0"), bulletPos, 2, scene);
	scene->entities.push_back(b);
}

Bullet::Bullet(vec3 _dir, vec3 _pos, float _speed, Scene* s) : Entity(_pos, s) {
	dir = _dir;
	speed = _speed;
	mesh = new Mesh("data/bullet1.obj");
}

Invader::Invader(vec3 _pos, Scene* s) : Entity(_pos, s) {
	speed = 2;
	jump = .2;
	elapsed = 0;
	dir = vec("1 0 0");
	
	mesh = new Mesh("data/basicInvader.obj");
}
void Invader::update(float dt) {
	elapsed += dt;
	if (elapsed > 1.0/speed) {
		move();
		elapsed = 0;
	}
}
void Invader::move() {
	double newx = pos[0] + dir[0]*jump;
	if (abs(newx) > scene->width()) {
		pos[1] -= jump;
		dir = -dir;
	} else {
		pos[0] = newx;
	}
}

Fleet::Fleet(Scene* s) : Entity(vec("0 0 0"), s) {
	pos = vec("0 0 0");
	width = floor(scene->width()/2);
	height = floor(scene->height()/2);
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			vec invaderPos;
			invaderPos << i << j << 0 << endr;
			invaders.push_back(new Invader(invaderPos, s));
		}
	}
}
Fleet::Fleet(string filename, Scene* s) : Entity(vec("0 0 0"), s) {
	//TODO: this
}
void Fleet::update(float) {
	
}
void Fleet::move() {
	
}
void Fleet::destroy(int) {
	
}
void Fleet::refreshAABB() {
	
}
