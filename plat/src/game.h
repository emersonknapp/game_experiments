#pragma once

#include "player.h"
#include <string>
#include <map>

class Game
{
public:
	Game();
	~Game();

	void update(float seconds);
	void draw();
	void end();

	void keyPressed(unsigned char, int, int);
	void keyReleased(unsigned char, int, int);
	void specialKeyPressed(int, int, int);
	void specialKeyReleased(int, int, int);


private:
	void loadGLTexture(std::string file, std::string identifier);
	void loadAnimations();


  	Player* m_player;
  	std::map<std::string, int> m_textures;
  	std::map<std::string, Animation*> m_animations;
	
};