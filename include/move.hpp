#pragma once
#include <vector>

using std::vector;

inline int board[42];
// 0: Blank
// 1: Red
// 2: Yellow

constexpr int _BLANK = 0;
constexpr int _RED = 1;
constexpr int _YELLOW = 2;
constexpr int _DRAW = 3;

inline int playerWon = 0;

struct Move {
    int row;
    int col;
};

inline vector<Move> moves;

inline bool turn = true;

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

inline bool CheckOpen(int row, int col, int need)
{
    int player = board[row * 7 + col];
    if (player == _BLANK) return false;
    constexpr int dirs[4][2] = {
        {0, 1},   // -
        {1, 0},   // |
        {1, 1},   // \      . <- no touchy
        {1,-1}    // /
    };
    for (auto& d : dirs)
    {
        int dr = d[0], dc = d[1];
        int posCount = CountDirection(row, col, dr, dc, player);
        int negCount = CountDirection(row, col, -dr, -dc, player);
        int total = 1 + posCount + negCount;
        if (total < need) continue;

        int posEndR = row + dr * (posCount + 1);
        int posEndC = col + dc * (posCount + 1);
        int negEndR = row - dr * (negCount + 1);
        int negEndC = col - dc * (negCount + 1);

        bool posOpen = InBounds(posEndR, posEndC) && board[posEndR * 7 + posEndC] == _BLANK;
        bool negOpen = InBounds(negEndR, negEndC) && board[negEndR * 7 + negEndC] == _BLANK;

        if (posOpen || negOpen)
            return true;
    }
    return false;
}

inline bool Check3(int row, int col) { return CheckOpen(row, col, 3); }
inline bool Check2(int row, int col) { return CheckOpen(row, col, 2); }

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

inline bool MakeMove(int col)
{
    if (col < 0 || col >= 7)
        return false;

    int player = turn ? _RED : _YELLOW;

    for (int row = 5; row >= 0; row--)
    {
        int index = row * 7 + col;

        if (board[index] == _BLANK)
        {
            board[index] = player;
            moves.push_back({row, col});

            if (CheckWin(row, col))
                playerWon = player;

            turn = !turn;
            return true;
        }
    }

    return false;
}

inline void UnMove()
{
    Move m = moves.back();
    moves.pop_back();

    board[m.row * 7 + m.col] = _BLANK;

    turn = !turn;
    playerWon = 0;
}

inline vector<Move> GetMoves()
{
    vector<Move> possibleMoves;

    for (int col = 0; col < 7; col++)
    {
        if (board[col] == _BLANK)
            possibleMoves.push_back({-1, col});
    }

    return possibleMoves;
}
