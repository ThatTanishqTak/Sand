#include "player.h"

Player::Player() { gameObject.push_back(this); }

Player::~Player() { /* EMPTY */ }

void Player::Update()
{
	if (IsMouseButtonDown(0) || IsMouseButtonDown(1))
	{
		mouseX = static_cast<float>(GetMouseX());
		mouseY = static_cast<float>(GetMouseY());
	}
}

void Player::Render(){ /* EMPTY */ }