#include "raylib.h"
#include "rlgl.h"
#include "GL/gl.h"
#include "include/move.hpp"

#include "include/search.hpp"

int main() {
    bool botShouldPlay;

    SetTraceLogLevel(LOG_NONE);
    InitWindow(350, 350, "The Markus beating connect 4 bot [TM]");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        bool isRedTurn = !turn;
        int previewX = (GetMouseX() / 50) * 50;
        if (!playerWon && isRedTurn) {
            DrawCircle(previewX + 25, 25, 20, YELLOW);
        }
        if (playerWon == 0) {
            if (isRedTurn) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    int col = GetMouseX() / 50;
                    if (MakeMove(col))
                        botShouldPlay = true;
                }
            }
            else if (botShouldPlay) {
                botShouldPlay = false;
                int bestCol = GetBestMove();
                MakeMove(bestCol);
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(0, 50, 350, 300, BLUE);
        rlDrawRenderBatchActive();
        glBlendFunc(GL_ONE, GL_ZERO);
        for (int x = 0; x < 350; x += 50) {
            for (int y = 50; y < 350; y += 50) {
                int col = x / 50;
                int row = (y / 50) - 1;
                Color color = {0, 0, 0, 0};
                int tile = GetTile(row, col);
                if (tile == _RED) color = RED;
                else if (tile == _YELLOW) color = YELLOW;
                DrawCircle(x + 25, y + 25, 20, color);
            }
        }
        rlDrawRenderBatchActive();
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (playerWon == 1) DrawText("Red player won!", 10, 10, 30, RED);
        if (playerWon == 2) DrawText("Yellow player won!", 10, 10, 30, YELLOW);
        if (playerWon == 3) DrawText("It's a draw!", 10, 10, 30, WHITE);
        if (playerWon && IsKeyPressed(KEY_R)) ResetBoard();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
