#include "raylib.h"
#include "include/move.hpp"

int main() {
    InitWindow(350, 350, "The Markus beating connect 4 bot [TM]");
    bool turn = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(0, 50, 350, 300, BLUE);

        for (int x=0; x<350; x+=50) {
            for (int y=50; y<350; y+=50) {
                Color color = BLACK;
                if (board[((y/50)-1)*7+(x/50)] == 1) color = RED;
                else if (board[((y/50)-1)*7+(x/50)] == 2) color = YELLOW;
                DrawCircle(x+25, y+25, 20, color);
            }
        }

        // draw preview
        int previewX = (GetMouseX() / 50) * 50;
        DrawCircle(previewX+25, 25, 20, RED);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !turn) MakeMove(GetMouseX()/50, _RED);

        if (playerWon == 1) break;
        if (playerWon == 2) break;

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
