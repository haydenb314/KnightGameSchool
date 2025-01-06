#include <iostream>
#include "raylib.h"
#include "Knight.h"

int main() {

    InitWindow(1600, 900, "Knight Game");
    SetTargetFPS(60);

    Knight knight;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(PURPLE);

        knight.drawKnight();

        EndDrawing();

    }
}