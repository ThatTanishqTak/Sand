#include "player.h"

Player::Player()
{
	gameObject.push_back(this);
}

Player::~Player()
{

}

void Player::Update()
{
	if (IsMouseButtonDown(0) || IsMouseButtonDown(1))
	{ 
		mouseX = GetMouseX();
		mouseY = GetMouseY();
	}
}

void Player::Render()
{

}