#include "background.h"
#include <iostream>

Background::Background() : cellSize(10.0f),
						   rows(windowWidth / cellSize), cols(windowHeight / cellSize),
						   grid(static_cast<__int64>(rows), std::vector<int>(static_cast<__int64>(cols), 0))
{
	rectangles = Make2DGrid(static_cast<int>(rows), static_cast<int>(cols));

	gameObject.push_back(this);
}

Background::~Background()
{

}

void Background::Update()
{
	Drawing();

	Erasing();

	Physics();
}


void Background::Render() 
{ 
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			float rectX = j * cellSize;
			float rectY = i * cellSize;

			Color color = grid[i][j] == 1 ? BROWN : BLACK;
			DrawRectangle(static_cast<int>(rectX), static_cast<int>(rectY), static_cast<int>(cellSize), static_cast<int>(cellSize), color);
		}
	}
}

std::vector<Rectangle> Background::Make2DGrid(int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Rectangle rect = { static_cast<float>(i * cellSize), static_cast<float>(j * cellSize), cellSize, cellSize };
			rectangles.push_back(rect);
		}
	}

	return rectangles;
}

void Background::Drawing()
{
	if (IsMouseButtonDown(0))
	{
		for (const auto& rect : rectangles)
		{
			if (CheckCollisionPointRec({ mouseX, mouseY }, rect))
			{
				int gridX = static_cast<int>(rect.y / cellSize);
				int gridY = static_cast<int>(rect.x / cellSize);

				if (gridX >= 0 && gridX < grid.size() && gridY >= 0 && gridY < grid[0].size()) { grid[gridX][gridY] = 1; }
			}
		}
	}
}

void Background::Erasing()
{
	if (IsMouseButtonDown(1))
	{
		for (const auto& rect : rectangles)
		{
			if (CheckCollisionPointRec({ mouseX, mouseY }, rect))
			{
				int gridX = static_cast<int>(rect.y / cellSize);
				int gridY = static_cast<int>(rect.x / cellSize);

				if (gridX >= 0 && gridX < grid.size() && gridY >= 0 && gridY < grid[0].size()) { grid[gridX][gridY] = 0; }
			}
		}
	}
}

void Background::Physics()
{
	std::vector<std::vector<int>> newGrid = grid;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i < rows && j < cols)
			{
				int state = grid[i][j];
				if (state == 1)
				{
					if (i + 1 < rows && j < cols)
					{
						int below = grid[i + 1][j];
						int belowR = grid[i + 1][j + 1];
						int belowL = grid[i + 1][j - 1];

						if (below == 0)
						{
							newGrid[i][j] = 0;
							newGrid[i + 1][j] = 1;
						}
						else if (belowR == 0)
						{
							newGrid[i][j] = 0;
							newGrid[i][j + 1] = 1;
						}
						else if (belowL == 0)
						{
							newGrid[i][j] = 0;
							newGrid[i][j - 1] = 1;
						}
						else { newGrid[i][j] = 1; }
					}
				}
			}
		}
	}

	grid = newGrid;
}