#include "player.h"

#include <iostream>

using namespace Eigen;

Player::Player(Vector2d position, Vector2d size)
	: m_pos(position)
	, m_size(size)
	, m_currentAnimation(ANI_STAND)
	, m_speed(80)
	, m_grounded(true)
{
	m_velocity = Vector2d(0,0);
}

Player::~Player()
{}

void Player::setAnimation(eAnimation which, Animation* ani)
{
	m_animations[which] = ani;
}

void Player::draw()
{

	glTranslatef(m_pos[0], m_pos[1], 1.0f); 
	m_animations[m_currentAnimation]->draw();
}

void Player::force(double dvx, double dvy, bool useSpeed)
{
	bool flipX = m_velocity[0] < 0;

	double speedMod = useSpeed ? m_speed : 1;
	m_velocity[0] += dvx*speedMod;
	m_velocity[1] += dvy*speedMod;


	if (m_velocity[1] == 0)
	{
		if (m_velocity[0] != 0)
			m_currentAnimation = ANI_WALK;
		else
			m_currentAnimation = ANI_STAND;
	}
	else
	{
		m_currentAnimation = ANI_RISE;
		/*
		if (m_velocity[1] > 0)
			m_currentAnimation = ANI_RISE;
		else
			m_currentAnimation = ANI_FALL;
		*/
	}

	if (m_velocity[0] < 0) 
		m_animations[m_currentAnimation]->flipX(true);
	else if (m_velocity[0] > 0)
		m_animations[m_currentAnimation]->flipX(false);
	else
		m_animations[m_currentAnimation]->flipX(flipX);

}

void Player::jump()
{
	m_grounded = false;
	force(0, 500, false);
	//m_velocity[1] += 500;
}

void Player::update(double dt)
{
	if (!m_grounded)
		force(0, -400*dt, false);

	m_pos += dt*m_velocity;

	if (!m_grounded && m_pos[1] < 0)
	{
		m_pos[1] = 0;
		//m_velocity[1] = 0;
		force(0, -m_velocity[1], false);
		m_grounded = true;

	}
	m_animations[m_currentAnimation]->update(dt);


}