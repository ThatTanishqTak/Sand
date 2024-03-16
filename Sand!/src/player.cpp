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
	if (IsMouseButtonPressed(0) || IsMouseButtonPressed(1))
	{ 
		mouseX = GetMouseX();
		mouseY = GetMouseY();
	}
}

void Player::Render()
{

}