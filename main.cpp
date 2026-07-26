#include "raylib.h"
#include "include/move.hpp"

int main() {
    InitWindow(350, 350, "The Markus beating connect 4 bot [TM]");

    while (!WindowShouldClose()) {
        BeginDrawing();

        DrawRectangle(0, 50, 350, 300, BLUE);

        for (int x=0; x<350; x+=50) {
            for (int y=50; y<350; y+=50) {
                Color color = BLACK;
                if (board[(y/50)*7+x] == 1) color = RED;
                else if (board[(y/50)*7+x] == 2) color = YELLOW;
                DrawCircle(x+25, y+25, 20, BLACK);
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
