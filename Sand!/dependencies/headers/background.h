#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "globals.h"
#include "player.h"
#include <memory>

class Background : public GameObjects
{
public:
	Background();
	~Background();

	virtual void Update();
	virtual void Render();
private:
	//-------------------------VARIABLES-------------------------------------//

	float cellSize;
	float rows;
	float cols;

	std::vector<std::vector<int>> grid;
	std::vector<Rectangle> rectangles;

	std::unique_ptr<Player> player;

	//------------------------FUNCTION()----------------------------------//

	std::vector<Rectangle> Make2DGrid(int row, int col);
	void ModifyGrid(int button, int action);
	void Physics();
	void UI();
};

#endif