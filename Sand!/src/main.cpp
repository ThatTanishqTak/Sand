#include "globals.h"
#include "background.h"
#include "player.h"

int main()
{
	InitWindow(windowWidth, windowHeight, "Sand!");
	SetTargetFPS(30);

	Player player;
	Background background;

	while (!WindowShouldClose())
	{
		for (GameObjects* gameObjects : gameObject) { gameObjects->Update(); }

		BeginDrawing();
		ClearBackground(BLACK);

		for (GameObjects* gameObjects : gameObject) { gameObjects->Render(); }

		EndDrawing();
	}

	CloseWindow();
	return 0;
}