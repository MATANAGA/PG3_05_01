#include <Novice.h>
#include "Map.h"

void Map::DrawGrid() {
	const int gridSize = 50;
	const int cellSize = 40;

	for (int i = 0; i <= gridSize; ++i) {
		int y = i * cellSize;
		Novice::DrawLine(0, y, gridSize * cellSize, y, WHITE);

		int x = i * cellSize;
		Novice::DrawLine(x, 0, x, gridSize * cellSize, WHITE);
	}
}
