#pragma once
#include <cstdint>
#include <vector>
using std::vector;

constexpr int WIDTH  = 7;
constexpr int HEIGHT = 6;
constexpr int H1     = HEIGHT + 1; // 7 — one extra "sentinel" row per column

constexpr int _BLANK  = 0;
constexpr int _RED    = 1;
constexpr int _YELLOW = 2;
constexpr int _DRAW   = 3;

// bitboard[0] = red stones, bitboard[1] = yellow stones.
// Each column occupies 7 consecutive bits (6 playable + 1 sentinel) starting
// at col*H1, bit 0 of a column = bottom row, bit HEIGHT-1 = top row.
inline uint64_t bitboard[2] = {0, 0};

inline int height[WIDTH] = {0, H1, 2*H1, 3*H1, 4*H1, 5*H1, 6*H1};

inline int playerWon = _BLANK;
inline bool turn = true;

struct Move {
    int col;
    uint64_t bit;
};
inline vector<Move> moves;

inline uint64_t columnMask(int col)  { return ((1ULL << HEIGHT) - 1) << (col * H1); }
inline uint64_t topMaskCol(int col)  { return 1ULL << (col * H1 + HEIGHT - 1); }

inline bool CanPlay(int col) {
    return !((bitboard[0] | bitboard[1]) & topMaskCol(col));
}

inline bool CheckWinBB(uint64_t b) {
    uint64_t m;
    m = b & (b >> H1);              if (m & (m >> (2 * H1)))            return true; // horizontal -
    m = b & (b >> HEIGHT);          if (m & (m >> (2 * HEIGHT)))        return true; // diagonal /
    m = b & (b >> (HEIGHT + 2));    if (m & (m >> (2 * (HEIGHT + 2))))  return true; // diagonal \  .
    m = b & (b >> 1);               if (m & (m >> 2))                   return true; // vertical |
    return false;
}

inline bool MakeMove(int col) {
    if (col < 0 || col >= WIDTH) return false;
    if (!CanPlay(col)) return false;

    int player = turn ? _RED : _YELLOW;
    int idx = player - 1; // 0 = red, 1 = yellow

    uint64_t bit = 1ULL << height[col];
    height[col]++;
    bitboard[idx] |= bit;
    moves.push_back({col, bit});

    if (CheckWinBB(bitboard[idx])) playerWon = player;
    turn = !turn;
    return true;
}

inline void UnMove() {
    Move m = moves.back();
    moves.pop_back();
    height[m.col]--;
    bitboard[0] &= ~m.bit;
    bitboard[1] &= ~m.bit;
    turn = !turn;
    playerWon = _BLANK;
}

inline vector<int> GetMoves() {
    vector<int> possible;
    for (int col = 0; col < WIDTH; col++)
        if (CanPlay(col)) possible.push_back(col);
    return possible;
}

inline int GetTile(int displayRow, int col) {
    int bitRow = HEIGHT - 1 - displayRow;
    uint64_t mask = 1ULL << (col * H1 + bitRow);
    if (bitboard[0] & mask) return _RED;
    if (bitboard[1] & mask) return _YELLOW;
    return _BLANK;
}

inline void ResetBoard() {
    bitboard[0] = bitboard[1] = 0;
    for (int c = 0; c < WIDTH; c++) height[c] = c * H1;
    moves.clear();
    playerWon = _BLANK;
    turn = false;
}
