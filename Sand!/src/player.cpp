#include "player.h"

Player::Player()
{
	currentParticle = 1;

	sand.ID = 1;
	sand.color = BROWN;

	water.ID = 2;
	water.color = BLUE;

	stone.ID = 3;
	stone.color = LIGHTGRAY;

	gas.ID = 4;
	gas.color = DARKGRAY;

	selectedParticle = "Sand";

	gameObject.push_back(this); 
}

Player::~Player() { /* EMPTY */ }

void Player::Update()
{
	if (IsMouseButtonDown(0) || IsMouseButtonDown(1)) // Get the mouse position while mouse buttons are being pressed
	{
		mouseX = static_cast<float>(GetMouseX());
		mouseY = static_cast<float>(GetMouseY());
	}

	ChangeParticle();
	UpdateUI();
}

void Player::Render() { /* EMPTY */ }

void Player::ChangeParticle()
{
	if (IsKeyPressed(KEY_UP)) { currentParticle += 1; }
	if (IsKeyPressed(KEY_DOWN)) { currentParticle -= 1; }

	if (currentParticle > 4) { currentParticle = 0; }
	if (currentParticle < 0) { currentParticle = 4; }
}

void Player::UpdateUI()
{
	switch (currentParticle)
	{
	case 0:
		selectedParticle = "Eraser";
		break;
	case 1:
		selectedParticle = "Sand";
		break;
	case 2:
		selectedParticle = "Water";
		break;
	case 3:
		selectedParticle = "Stone";
		break;
	case 4:
		selectedParticle = "Gas";
		break;
	default:
		break;
	}
}