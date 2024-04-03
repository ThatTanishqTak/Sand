#include "background.h"
#include <sstream>

Background::Background() : cellSize(10.0f), rows(windowWidth / cellSize), 
							cols(windowHeight / cellSize), 
							grid(static_cast<__int64>(rows), std::vector<int>(static_cast<__int64>(cols), 0))
{
	player = std::make_unique<Player>();
	rectangles = Make2DGrid(static_cast<int>(rows), static_cast<int>(cols));

	gameObject.push_back(this);
}

Background::~Background() { /* EMPTY */ }

void Background::Update()
{
	UpdateGrid(0, player->currentParticle); // On left click
	Physics();
}

void Background::Render() 
{
	RenderGrid();
	UI();
}

//------------------------------------------------START UP FUNCTION()--------------------------------------------------------------------------------//

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

//-------------------------------------------------ALL THE UPDATE FUNCTIONS()------------------------------------------------------------------------------//

void Background::UpdateGrid(int button, int action)
{
	if (IsMouseButtonDown(button)) 
	{
		for (const auto& rect : rectangles) 
		{
			if (CheckCollisionPointRec({ mouseX, mouseY }, rect))
			{
				int gridX = static_cast<int>(rect.y / cellSize);
				int gridY = static_cast<int>(rect.x / cellSize);

				if (gridX >= 0 && gridX < grid.size() && gridY >= 0 && gridY < grid[0].size())
				{ 
					switch (player->currentParticle)
					{
						case 0: // Eraser
							grid[gridX][gridY] = 0;
							break;
						case 1: // Sand
							grid[gridX][gridY] = player->sand.ID;
							break;
						case 2: // Water
							grid[gridX][gridY] = player->water.ID;
							break;
						case 3: // Stone
							grid[gridX][gridY] = player->stone.ID;
							break;
						case 4: // Gas
							grid[gridX][gridY] = player->gas.ID;
							break;
						default:
							break;
					}
				}
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

				if (state == player->sand.ID) // Sand physics
				{
					if (i + 1 < rows && j < cols)
					{
						int below = grid[i + 1][j];
						int belowR = grid[i + 1][j + 1];
						int belowL = grid[i + 1][j - 1];

						if (below == 0 || belowR == 0 || belowL == 0)
						{
							newGrid[i][j] = 0;

							if (below == 0) { newGrid[i + 1][j] = player->sand.ID; }
							else if (belowR == 0) { newGrid[i][j + 1] = player->sand.ID; }
							else if (belowL == 0) { newGrid[i][j - 1] = player->sand.ID; }
						}
						else { newGrid[i][j] = player->sand.ID; }
					}
				}
				if (state == player->water.ID) // Water physics
				{
					if (i + 1 < rows && j < cols)
					{
						int below = grid[i + 1][j];
						int belowR = grid[i + 1][j + 1];
						int belowL = grid[i + 1][j - 1];
						int right = grid[i][j + 1];
						int left = grid[i][j - 1];

						if (below == 0 || belowR == 0 || belowL == 0 || right == 0 || left == 0)
						{
							newGrid[i][j] = 0;

							if (below == 0) { newGrid[i + 1][j] = player->water.ID; }
							else if (belowR == 0) { newGrid[i + 1][j + 1] = player->water.ID; }
							else if (belowL == 0) { newGrid[i + 1][j - 1] = player->water.ID; }
							else if (right == 0) { newGrid[i][j + 1] = player->water.ID; }
							else if (left == 0) { newGrid[i][j - 1] = player->water.ID; }
							
						}
						else if (newGrid[i][j] == player->water.ID) { newGrid[i + 1][j] = player->water.ID; }
					}
				}
				if (state == player->gas.ID) // Gas physics
				{
					if (i > 0 && j < cols)
					{
						int above = grid[i - 1][j];
						int aboveR = grid[i - 1][j + 1];
						int aboveL = grid[i - 1][j - 1];
						int right = grid[i][j + 1];
						int left = grid[i][j - 1];

						if (above == 0)
						{
							newGrid[i][j] = 0;

							if (above == 0) { newGrid[i - 1][j] = player->gas.ID; }
							else if (aboveR == 0) { newGrid[i - 1][j + 1] = player->gas.ID; }
							else if (aboveL == 0) { newGrid[i - 1][j - 1] = player->gas.ID; }
							else if (right == 0) { newGrid[i][j + 1] = player->gas.ID; }
							else if (left == 0) { newGrid[i][j - 1] = player->gas.ID; }
						}
						else if (newGrid[i][j] == player->gas.ID) { newGrid[i][j] = player->gas.ID; }
					}
				}
				if (state == player->stone.ID) { newGrid[i][j] = player->stone.ID; } // Stone physics
			}
		}
	}

	grid = newGrid;
}

//-------------------------------------------------ALL THE RENDER FUNCTIONS()------------------------------------------------------------------------------//

void Background::UI() { DrawText(player->selectedParticle.c_str(), 10, 10, 24, RED); }

void Background::RenderGrid()
{
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			float rectX = j * cellSize;
			float rectY = i * cellSize;

			Color color;
			switch (grid[i][j])
			{
			case 1: // sand.ID = 1
				color = player->sand.color;
				break;
			case 2: // water.ID = 2
				color = player->water.color;
				break;
			case 3: // stone.ID = 3
				color = player->stone.color;
				break;
			case 4: // gas.ID = 4
				color = player->gas.color;
				break;
			default:
				color = BLACK; // Default color for empty cell
				break;
			}

			DrawRectangle(static_cast<int>(rectX), static_cast<int>(rectY), static_cast<int>(cellSize), static_cast<int>(cellSize), color);
		}
	}
}