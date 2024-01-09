#include "Board.h"
#include "Defs.h"

int main() {
    Board b = Board();
    // Piece p[8][4];
    // for (int i = 0; i < 8; i++)
    //     for (int j = 0; j < 4; j++)
    //         p[i][j] = empty;
    // p[2][3] = black;
    // p[5][3] = white;
    // Board b = Board(p);
    b.print();
    std::vector moves = b.allMoves();
    int i = 0;
    while (moves.size() > 0) {
        Move m = b.bestMove(4).move;
        b.makeMove(m);
        moves = b.forcedMoves();
        std::cout<<"From: ("<<m.start.x<<", "<<m.start.y<<") To: ("<<m.end.x<<", "<<m.end.y<<")"<<m.eat<<"\n";
        b.print();
        std::cout<<"\n";
    }
    return 0;
}