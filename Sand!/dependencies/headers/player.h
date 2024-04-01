#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"
#include <sstream>

class Player : public GameObjects
{
public:
	Player();
	~Player();

	virtual void Update();
	virtual void Render();

	int currentParticle;
	std::string selectedParticle;

	struct Particles
	{
		int ID;
		Color color;
	};

	Particles sand;
	Particles water;
	Particles stone;
	Particles gas;

private:
	void ChangeParticle();
	void UpdateUI();
};

#endif