#include "game.h"
#include "openglheaders.h"
#include "stringutils.h"
#include <SOIL.h>

#include <dirent.h>
#include <map>

//TODO: probably remove
#include <iostream>

Game::Game()
{
  loadAnimations();

  m_player = new Player(Vector2d(0,0), Vector2d(32,32));
  m_player->setAnimation(Player::ANI_STAND, m_animations["man_stand"]);
  m_player->setAnimation(Player::ANI_WALK, m_animations["man_walk"]);
  m_player->setAnimation(Player::ANI_RISE, m_animations["man_rise"]);
  m_player->setAnimation(Player::ANI_FALL, m_animations["man_fall"]);

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
      m_player->force(-1,0, true);
      break;
    case GLUT_KEY_RIGHT:
      m_player->force(1,0, true);
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
      m_player->force(1,0, true);
      break;
    case GLUT_KEY_RIGHT:
      m_player->force(-1,0, true);
      break;
    case GLUT_KEY_UP:
      m_player->jump();
      break;
    case GLUT_KEY_DOWN:
      break;
    default:
      break;
  }
}

void Game::loadAnimations()
{
	
	DIR *dir;
	struct dirent *ent;
  std::string aniPath = "./resources/animations/";
	if ((dir = opendir(aniPath.c_str())))
	{
		while ((ent = readdir(dir)) != NULL)
		{
      std::string dirName = ent->d_name;
      if (StringUtils::endswith(dirName, ".ani"))
      {
        std::string aniName = dirName.substr(0, dirName.length()-4);
        std::string imageFile(aniPath);
        imageFile.append(dirName);
        std::string dataFile(imageFile);

        imageFile.append("/spritesheet.png");
        dataFile.append("/CelData.plist");

        //std::cout << "Loading ani '" << aniName << "' with files" << std::endl << "  " << imageFile << std::endl << "  " << dataFile << std::endl;

        loadGLTexture(imageFile, aniName);
        m_animations[aniName] = new Animation(m_textures[aniName], dataFile);

      }
		}
	}
	else
	{
		perror("Could not open resources/animations directory!");
		assert(false);
	}
	
}

void Game::loadGLTexture(std::string file, std::string identifier)
{
  int newTex = SOIL_load_OGL_texture
      (
       	file.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
      );
  if (newTex == 0)
  {
    printf("SOIL loading error: %s\n", SOIL_last_result());
    assert(false);
  }

  m_textures[identifier] = newTex;

  glBindTexture(GL_TEXTURE_2D, newTex);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
}