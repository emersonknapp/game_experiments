#include "game.h"
#include "openglheaders.h"
#include <SOIL.h>

#include <dirent.h>

Game::Game()
{
	m_player = new Player(Vector2d(0,0), Vector2d(32,32));
	loadAnimations();
}

Game::~Game()
{

}

void Game::update(float seconds)
{
	m_player->update(seconds);
}

void Game::draw()
{
	m_player->draw();
}

void Game::end()
{

}

void Game::keyPressed(unsigned char key, int x, int y)
{

}

void Game::keyReleased(unsigned char key, int x, int y)
{

}

void Game::specialKeyPressed(int key, int x, int y)
{
  switch(key)         
  {
    case GLUT_KEY_LEFT:
      m_player->force(-1,0);
      break;
    case GLUT_KEY_RIGHT:
      m_player->force(1,0);
      break;
    case GLUT_KEY_UP:
      //xspeed += 0.1f;
      break;
    case GLUT_KEY_DOWN:
      //xspeed -= 0.1f;
      break;
    default:
      break;
  }
}

void Game::specialKeyReleased(int key, int x, int y)
{
  switch(key)           
  {
    case GLUT_KEY_LEFT:
      m_player->force(1,0);
      break;
    case GLUT_KEY_RIGHT:
      m_player->force(-1,0);
      break;
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_DOWN:
      break;
    default:
      break;
  }
}

void Game::loadAnimations()
{
	/*
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("./resources/animations")))
	{
		while ((ent = readdir(dir)) != NULL)
		{
			printf("%s\n", ent->d_name);
		}
	}
	else
	{
		perror("Could not open resources/animations directory!");
		assert(false);
	}
	*/
	loadGLTexture("resources/animations/standman.ani/standman.png");
	loadGLTexture("resources/animations/walkman.ani/walkman.png");
  	Animation* playerStandAni = new Animation(m_textures[0], "resources/animations/standman.ani/CelData.plist");
	Animation* playerWalkAni = new Animation(m_textures[1], "resources/animations/walkman.ani/CelData.plist");
	m_player->setAnimation(Player::ANI_STAND, playerStandAni);
  	m_player->setAnimation(Player::ANI_WALK, playerWalkAni);
}

void Game::loadGLTexture(std::string file)
{
  int newTex = SOIL_load_OGL_texture
      (
       	file.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
      );
  if (newTex == 0)
  {
    printf("SOIL loading error: %s\n", SOIL_last_result());
    assert(false);
  }

  m_textures.push_back(newTex);

  glBindTexture(GL_TEXTURE_2D, newTex);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
}