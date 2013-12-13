#pragma once

#include <OpenGL/gl.h>
#include <Eigen/Dense>
#include <vector>
#include "animation.h"

using namespace Eigen;

class Player
{
public:
	enum eAnimation
	{
		ANI_STAND,
		ANI_WALK,
		ANI_UPJUMP,
		ANI_DOWNJUMP,
		NUM_ANIMATIONS
	};

	Player(Vector2d position, Vector2d size);
	~Player();
	void setAnimation(eAnimation which, Animation* ani);
	void draw();
	void force(double dvx, double dvy);
	void update(double dt); //in seconds
private:
	Vector2d m_pos;
	Vector2d m_size;
	Vector2d m_velocity;
	eAnimation m_currentAnimation;
	Animation* m_animations[NUM_ANIMATIONS];
	double m_speed;

	//bool m_grounded;
};