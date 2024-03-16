#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

class GameObjects
{
public:
	GameObjects() = default;
	~GameObjects() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;
};

#endif