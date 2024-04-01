#include "globals.h"
#include "background.h"
#include "player.h"

int main()
{
	InitWindow(windowWidth, windowHeight, "Sand!"); // Initialize window
	SetTargetFPS(35); // Lock the FPS to 35 to make the sand fall at a reasonable rate

	Player player;
	Background background;

	while (!WindowShouldClose()) // Main loop
	{
		for (GameObjects* gameObjects : gameObject) { gameObjects->Update(); }

		BeginDrawing();
		ClearBackground(BLACK);

		for (GameObjects* gameObjects : gameObject) { gameObjects->Render(); }

		EndDrawing();
	}

	CloseWindow(); // De-Initialize window
	
	return 0; // Exit code
}