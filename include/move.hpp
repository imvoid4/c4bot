#pragma once

inline int board[42];
// 0: Blank
// 1: Red
// 2: Yellow

inline bool MakeMove(int col, int player) {
    if (col < 0 || col >= 7) return false;

    for (int row = 5; row >= 0; row--) {
        int index = row * 7 + col;

        if (board[index] == 0) {
            board[index] = player;
            return true;
        }
    }

    return false;
}

inline bool UnMove(int row, int col) {
    board[row*7+col] = 0;
}
