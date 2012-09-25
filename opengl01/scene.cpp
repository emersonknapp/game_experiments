#include "scene.h"

using namespace std;

Scene::Scene(float width, float height) {
	_width = width;
	_height = height;
	
	Entity* tank = new Tank(this);
	entities.push_back(tank);
	controlEntity = tank;
	//entities.push_back(new Fleet(width, height));
	//entities.push_back(new Fleet(width, height));
}
void Scene::update(float dt) {
	for (size_t i=0; i<entities.size(); i++) {
		entities[i]->update(dt);
	}
}
void Scene::processNormalKeys(unsigned char key, int x, int y) {
	switch(key) {
		default:
			controlEntity->keyDown(key);
	}
}
void Scene::processNormalKeyups(unsigned char key, int x, int y) {
	switch(key) {
		default:
			controlEntity->keyUp(key);
	}
}
void Scene::processSpecialKeys(int key, int x, int y) {
	switch(key) {
		default:
			controlEntity->specialKeyDown(key);
	}

}
void Scene::processSpecialKeyups(int key, int x, int y) {
	switch(key) {
		default:
			controlEntity->specialKeyUp(key);
	}
	
}
float Scene::width() {
	return _width;
}
float Scene::height() {
	return _height;
}