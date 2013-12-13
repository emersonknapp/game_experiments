#include "player.h"

#include <iostream>

using namespace Eigen;

Player::Player(Vector2d position, Vector2d size)
	: m_pos(position)
	, m_size(size)
	, m_currentAnimation(ANI_STAND)
	, m_speed(50)
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

void Player::force(double dvx, double dvy)
{
	bool flipX = m_velocity[0] < 0;

	m_velocity[0] += dvx*m_speed;
	m_velocity[1] += dvy*m_speed;


	if (m_velocity[0] != 0)
		m_currentAnimation = ANI_WALK;
	else
		m_currentAnimation = ANI_STAND;

	if (m_velocity[0] < 0) 
		m_animations[m_currentAnimation]->flipX(true);
	else if (m_velocity[0] > 0)
		m_animations[m_currentAnimation]->flipX(false);
	else
		m_animations[m_currentAnimation]->flipX(flipX);

}

void Player::update(double dt)
{
	m_pos += dt*m_velocity;
	m_animations[m_currentAnimation]->update(dt);
}