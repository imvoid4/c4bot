#pragma once

inline int board[42];
// 0: Blank
// 1: Red
// 2: Yellow

constexpr int _BLANK = 0;
constexpr int _RED = 1;
constexpr int _YELLOW = 2;

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

inline void UnMove(int row, int col) {
    board[row*7+col] = _BLANK;
}

inline bool InBounds(int row, int col) {
    return row >= 0 && row < 6 && col >= 0 && col < 7;
}

inline int CountDirection(int row, int col, int dr, int dc, int player) {
    int count = 0;

    row += dr;
    col += dc;

    while (InBounds(row, col) && board[row * 7 + col] == player) {
        count++;
        row += dr;
        col += dc;
    }
    return count;
}

inline bool CheckWin(int row, int col) {
    int player = board[row * 7 + col];

    if (player == _BLANK) return false;

    constexpr int dirs[4][2] = {
        {0, 1},   // -
        {1, 0},   // |
        {1, 1},   // \      . <- no touchy
        {1,-1}    // /
    };

    for (auto& d : dirs) {
        int count = 1;

        count += CountDirection(row, col, d[0], d[1], player);
        count += CountDirection(row, col, -d[0], -d[1], player);

        if (count >= 4)
            return true;
    }

    return false;
}
