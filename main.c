#include <stdio.h>
#include "raylib.h"

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 600
#define TILE_SIZE 5

typedef struct Ant {
	Vector2 pos;
	Vector2 dir;
	Color color;
} Ant;
Ant ant;

typedef struct Tile {
	bool colored; // If colored, tile is black.
} Tile;
Tile tileMap[SCREEN_WIDTH / TILE_SIZE][SCREEN_HEIGHT / TILE_SIZE];

void DrawTiles() {
	for (int i = 0; i < SCREEN_WIDTH / TILE_SIZE; i++) {
		for (int j = 0; j < SCREEN_HEIGHT / TILE_SIZE; j++) {
			DrawRectangleV(
				(Vector2) { i * TILE_SIZE, j * TILE_SIZE },
				(Vector2) { TILE_SIZE, TILE_SIZE },
				tileMap[i][j].colored ? BLACK : WHITE
			);
		}
	}
}

void DrawAnt() {
	DrawRectangleV(ant.pos, (Vector2) { TILE_SIZE, TILE_SIZE }, ant.color);
}

void UpdateAnt() {
	int ix = (int) ant.pos.x / TILE_SIZE;
	int iy = (int) ant.pos.y / TILE_SIZE;

	ant.dir = (Vector2) { ant.dir.y, ant.dir.x };
	if (tileMap[ix][iy].colored) {
		ant.dir.y *= -1;
	}
	else {
		ant.dir.x *= -1;
	}
	ant.pos.x += ant.dir.x * TILE_SIZE;
	ant.pos.y += ant.dir.y * TILE_SIZE;

	if (ant.pos.x < 0) ant.pos.x = SCREEN_WIDTH - TILE_SIZE;	
	if (ant.pos.y < 0) ant.pos.y = SCREEN_HEIGHT - TILE_SIZE;	
	if (ant.pos.x > SCREEN_WIDTH) ant.pos.x = TILE_SIZE;
	if (ant.pos.y > SCREEN_HEIGHT) ant.pos.y = -TILE_SIZE;	

	tileMap[ix][iy].colored = !tileMap[ix][iy].colored;
}

int main() {
	const int screenWidth = SCREEN_WIDTH;
	const int screenHeight = SCREEN_HEIGHT;

	const int gridWidth = screenWidth / TILE_SIZE;
	const int gridHeight = screenHeight / TILE_SIZE;

	ant.pos = (Vector2) { screenWidth / 2 - TILE_SIZE, screenHeight / 2 - TILE_SIZE};
	ant.dir = (Vector2) { 0, 1 }; // Traveling to the right
	ant.color = RED;

	bool simulationMode = false;
	int frames = 0;
	int totalFPS = 0;
	const int endFrame = 100000;

	InitWindow(screenWidth, screenHeight, "Langton's Ant");
	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(RAYWHITE);

			if (simulationMode) {
				if (frames == endFrame) {
					printf("Picture took %d seconds\n", endFrame / (totalFPS / frames));
				}
				else if (frames >= endFrame) {
					DrawTiles();
				} else {
					UpdateAnt();
				}
				frames++;
				totalFPS += GetFPS();
			}
			else {
				UpdateAnt();
				DrawTiles();
				DrawAnt();
			}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
