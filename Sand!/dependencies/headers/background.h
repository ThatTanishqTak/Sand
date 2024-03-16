#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "globals.h"

class Background : public GameObjects
{
public:
	Background();
	~Background();

	virtual void Update();
	virtual void Render();

private:
	float cellWidth;
	float cellHeight;
	float rows;
	float cols;

	std::vector<std::vector<int>> grid;
	std::vector<Rectangle> rectangles;

	std::vector<Rectangle> Make2DGrid(int row, int col);
	void Drawing();
	void Erasing();
};

#endif