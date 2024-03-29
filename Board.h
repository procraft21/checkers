#include "Defs.h"
#include <vector>
#ifndef BOARD_H
#define BOARD_H

struct RatedMove {
    const Move move;
    float value;
    RatedMove(Move m, float val) : move(m), value(val) {};
};


class Board {
    private:
        Piece board[8][4];
        /// true -> white
        /// false -> black
        bool turn = true;
        std::vector<Move> combos;
        std::vector<Move> possibleCombos(int i, int j);
        const float posVals[7] = {1.25, 1.1, 1, 1.075, 1.15, 1.225, 1.3};
    public:
        Board(Piece copy[][4]);
        Board();
        ~Board() {}
        float value();
        void print();
        /// @brief Makes a move on the board
        /// @param m The move (presumed legal)
        void makeMove(Move m);
        std::vector<Move> allMoves();
        std::vector<Move> forcedMoves();
        RatedMove bestMove(int depth);
        bool getTurn() {return turn;};
};

#endif