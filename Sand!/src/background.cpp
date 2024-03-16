#include "background.h"

Background::Background() : cellWidth(10.0f), cellHeight(10.0f),
						   rows(windowWidth / cellWidth), cols(windowHeight / cellHeight),
						   grid(rows, std::vector<int>(cols, 0))
{
	rectangles = Make2DGrid(rows, cols);

	gameObject.push_back(this);
}

Background::~Background()
{

}

void Background::Update()
{
	Drawing();

	Erasing();
}


void Background::Render() 
{ 
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			float rectX = j * cellHeight;
			float rectY = i * cellWidth;

			Color color = grid[i][j] == 1 ? WHITE : BLACK;
			DrawRectangle(rectX, rectY, cellWidth, cellHeight, color);
		}
	}
}

std::vector<Rectangle> Background::Make2DGrid(int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Rectangle rect = { static_cast<float>(i * cellWidth), static_cast<float>(j * cellHeight), cellWidth, cellHeight };
			rectangles.push_back(rect);
		}
	}

	return rectangles;
}

void Background::Drawing()
{
	if (IsMouseButtonPressed(0))
	{
		for (const auto& rect : rectangles)
		{
			if (CheckCollisionPointRec({ mouseX, mouseY }, rect))
			{
				int gridX = static_cast<int>(rect.y / cellHeight);
				int gridY = static_cast<int>(rect.x / cellWidth);

				if (gridX >= 0 && gridX < grid.size() && gridY >= 0 && gridY < grid[0].size()) { grid[gridX][gridY] = 1; }
			}
		}
	}
}

void Background::Erasing()
{
	if (IsMouseButtonPressed(1))
	{
		for (const auto& rect : rectangles)
		{
			if (CheckCollisionPointRec({ mouseX, mouseY }, rect))
			{
				int gridX = static_cast<int>(rect.y / cellHeight);
				int gridY = static_cast<int>(rect.x / cellWidth);

				if (gridX >= 0 && gridX < grid.size() && gridY >= 0 && gridY < grid[0].size()) { grid[gridX][gridY] = 0; }
			}
		}
	}
}