#include "background.h"
#include <iostream>

Background::Background() : cellWidth(10.0f), cellHeight(10.0f),
						   rows(windowWidth / cellWidth), cols(windowHeight / cellHeight),
						   grid(rows, std::vector<int>(cols, 0))
{
	rectangles = Make2DGrid(rows, cols);
	gridR = { 0.0f, 0.0f, static_cast<float>(cellWidth), static_cast<float>(cellHeight) };

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++) { std::cout << grid[i][j] << " "; }
		std::cout << std::endl;
	}

	gameObject.push_back(this);
}

Background::~Background()
{

}

void Background::Update()
{
    if (IsMouseButtonPressed(0))
    {
        for (const auto& rect : rectangles)
        {
            if (CheckCollisionPointRec({ mouseX, mouseY }, rect))
            {
                int gridX = static_cast<int>(rect.y / cellHeight);
                int gridY = static_cast<int>(rect.x / cellWidth);

                if (gridX >= 0 && gridX < grid.size() && gridY >= 0 && gridY < grid[0].size())
                {
                    grid[gridX][gridY] = 1;
                    std::cout << "Collision detected at grid cell (" << gridX << ", " << gridY << ")" << " " << grid[gridX][gridY] << std::endl;

					//DrawRectangle(rect.x, rect.y, rect.width, rect.height, WHITE);
                }
            }
        }

		//DEBUG

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				std::cout << grid[i][j] << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;

		//DEBUG
    }

	if (IsMouseButtonPressed(1))
	{
		for (const auto& rect : rectangles)
		{
			if (CheckCollisionPointRec({ mouseX, mouseY }, rect))
			{
				int gridX = static_cast<int>(rect.y / cellHeight);
				int gridY = static_cast<int>(rect.x / cellWidth);

				if (gridX >= 0 && gridX < grid.size() && gridY >= 0 && gridY < grid[0].size())
				{
					grid[gridX][gridY] = 0;
					std::cout << "Collision detected at grid cell (" << gridX << ", " << gridY << ")" << " " << grid[gridX][gridY] << std::endl;
				}
			}
		}

		//DEBUG

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				std::cout << grid[i][j] << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;

		//DEBUG
	}
}


void Background::Render() 
{ 
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			// Calculate the position of the rectangle based on the grid cell
			float rectX = j * cellHeight;
			float rectY = i * cellWidth;

			// Determine the color based on the grid cell's state
			Color color = grid[i][j] == 1 ? WHITE : BLACK;

			// Draw the rectangle
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