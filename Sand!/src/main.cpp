#include "globals.h"
#include "background.h"
#include "player.h"

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(windowWidth, windowHeight, "Sand!");
	SetTargetFPS(GetFPS());

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