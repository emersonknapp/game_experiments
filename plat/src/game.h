#include "player.h"
#include <string>

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
	void loadGLTexture(std::string file);
	void loadAnimations();


  	Player* m_player;
  	std::vector<int> m_textures;
	
};