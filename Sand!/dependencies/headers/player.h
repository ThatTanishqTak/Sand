#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

class Player : public GameObjects
{
public:
	Player();
	~Player();

	virtual void Update();
	virtual void Render();

private:
	struct Particles
	{

	};
};

#endif