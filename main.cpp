// goal: add gravity
// run func g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o game

#include <iostream>
#include <raylib.h>

// config
const int window_width = 900;
const int window_height = 900;

const int grid_x = 150;
const int grid_y = 150;

const int atom_size = window_width/grid_x;
const float update_rate = .05;



// backend
void createCoords(int coords[grid_x][grid_y]) {
    for(int x = 0; x < grid_x; x++){
		for (int y = 0; y < grid_y; y++) {
			coords[x][y] = 0;
		}
    }
}

void simulate(int coords[grid_x][grid_y]) {
    for(int x = 0; x < grid_x; x++){
        for (int y = grid_y - 1; y >= 0; y--) {

            if (coords[x][y] == 1) {
                if (y + 1 < grid_y) {
                    if (coords[x][y + 1] == 0) {
                        coords[x][y + 1] = 1;
                        coords[x][y] = 0;
                    }
                }
            }
        }
    }
}

// rendering
void fillBlock(int coords[grid_x][grid_y]) {
	Vector2 clickPosition = GetMousePosition();

	int cell_x = clickPosition.x / atom_size;
	int cell_y = clickPosition.y / atom_size;

	if (coords[cell_x][cell_y] == 0) {
		coords[cell_x][cell_y] = 1;
	} else {
		coords[cell_x][cell_y] = 0;
	}
}

Color colorCheck(int cell) {
	if (cell == 1) {
		return WHITE;
	} else {
		return BLACK;
	}
}

void updateGrid(int coords[grid_x][grid_y]) {
	for(int x = 0; x < grid_x; x++){
		for (int y = 0; y < grid_y; y++) {

			DrawRectangle((float)x * atom_size, (float)y * atom_size, (float) atom_size, (float) atom_size, colorCheck(coords[x][y]));
		}
    }
}

int main() {

	// startup
	int coords[grid_x][grid_y];
	createCoords(coords);
	InitWindow(window_width, window_height, "Conways fake game");

	// simulation startup
	float time = 0.;
	int simulations = 0;

	while (!WindowShouldClose()){

	    time += GetFrameTime();

		// input
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) fillBlock(coords);

		//backend
		if (time >= update_rate) {

		    time = 0.0f;
			simulations += 1;

            simulate(coords);
		}

		// rendering
		BeginDrawing();
			ClearBackground(WHITE); // background
			updateGrid(coords);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
