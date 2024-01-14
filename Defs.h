#include <iostream>
#ifndef DEFS_H
#define DEFS_H
enum Piece {empty, white, black, whiteQueen, blackQueen};

struct Square {
    const int x, y;
    Square(int _x, int _y) : x(_x), y(_y) {}
};

struct Move {
    const Square start, end;
    const bool eat;
    static const Move emptyMove;
    Move(int x1, int y1, int x2, int y2) : start(Square(x1, y1)), end(Square(x2, y2)), eat(y2-y1 > 0 ? y2-y1-1 : y1-y2-1) {}
};

struct Debug {
    static bool printInBestMove;
    static bool inner;
    static void printMove(Move m) { std::cout<<"From: ("<<m.start.x<<", "<<m.start.y<<") To: ("<<m.end.x<<", "<<m.end.y<<") "<<(m.eat ? "eat" : "normal")<<"\n"; }
    static int prog;
    static bool printInMoves;
};

struct RND {
    static float getFloat() {
        srand(time(0)*rand());
        return (rand()%200)/200.0;
    }
};

#endif
