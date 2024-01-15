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
    std::vector<Move> moves = b.allMoves();
    int i = 0;
    while (moves.size() > 0) {
        i++;
        RatedMove m = b.bestMove(5);
        b.makeMove(m.move);
        moves = b.forcedMoves();
        std::cout<<"Move "<<i<<" - ";
        Debug::printMove(m.move);
        std::cout<<"Played by "<<(b.getTurn()?"black":"white")<< " and rated "<<m.value<<"\n";
        b.print();
        std::cout<<"\n";
    }
    std::cout<<RND::getFloat();
    return 0;
}