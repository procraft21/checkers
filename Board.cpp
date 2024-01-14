#include "Board.h"

const Move Move::emptyMove = Move(0, 0, 0, 0);

bool Debug::printInBestMove = false;
bool Debug::inner = false;
int Debug::prog = 0;
bool Debug::printInMoves = false;

Board::Board(Piece copy[][4]) {
    for (int i = 0; i < 8; i++) 
        for (int j = 0; j < 4; j++)
            board[i][j] = copy[i][j];
}

Board::Board() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 4; j++) {
            if (i < 3)
                board[i][j] = black;
            else if (i > 4)
                board[i][j] = white;
            else 
                board[i][j] = empty;
        }
    }
}

int Board::value() {
    int val = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                if (board[i][j] == white)
                    val++;
                else if (board[i][j] == black)
                    val--;
                else if (board[i][j] == whiteQueen)
                    val += 2;
                else if (board[i][j] == blackQueen)
                    val -= 2;
            }
        }
    }
    return val;
}

void Board::print() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            char prt;
            switch (board[i][j])
            {
            case empty:
                prt = '_';
                break;
            case white:
                prt = 'w';
                break;
            case black:
                prt = 'b';
                break;
            case whiteQueen:
                prt = 'W';
                break;
            case blackQueen:
                prt = 'B';
                break;
            default:
                prt = ' ';
                break;
            }   
            printf("%c ", prt);
        }
        printf("\n");
        if (!(i % 2))
            printf(" ");
    }
}

void Board::makeMove(Move m) {
    board[m.end.y][m.end.x] = board[m.start.y][m.start.x];
    if (m.end.y == 7 && board[m.end.y][m.end.x] == black)
        board[m.end.y][m.end.x] = blackQueen;
    if (m.end.y == 0 && board[m.end.y][m.end.x] == white)
        board[m.end.y][m.end.x] = whiteQueen;
    board[m.start.y][m.start.x] = empty;
    if (m.eat) {
        board[(m.start.y + m.end.y)/2]
             [(m.start.y % 2 == 1 && m.end.x < m.start.x) || 
              (m.start.y % 2 == 0 && m.end.x > m.start.x) ? 
              m.start.x : m.end.x] = empty;
        combos = possibleCombos(m.end.y, m.end.x);
        if (combos.size() > 0)
            turn = !turn;
    }
    turn = !turn;
}

std::vector<Move> Board::allMoves() {
    std::vector<Move> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (turn) {
                if ((board[i][j] == white || board[i][j] == whiteQueen) && i > 0) {
                    if (i % 2) {
                        if (board[i-1][j] == empty)
                            moves.push_back(Move(j, i, j, i-1));
                        else if (i > 1 && j > 0 && (board[i-1][j] == black || board[i-1][j] == blackQueen) && board[i-2][j-1] == empty)
                            moves.push_back(Move(j, i, j-1, i-2));
                        if (j < 3 && board[i-1][j+1] == empty)
                            moves.push_back(Move(j, i, j+1, i-1));
                        else if (i > 1 && j < 3 && (board[i-1][j+1] == black || board[i-1][j+1] == blackQueen) && board[i-2][j+1] == empty)
                            moves.push_back(Move(j, i, j+1, i-2));
                    }
                    else {
                        if (board[i-1][j] == empty)
                            moves.push_back(Move(j, i, j, i-1));
                        else if (i > 1 && j < 3 && (board[i-1][j] == black || board[i-1][j] == blackQueen) && board[i-2][j+1] == empty)
                            moves.push_back(Move(j, i, j+1, i-2));
                        if (j > 0 && board[i-1][j-1] == empty)
                            moves.push_back(Move(j, i, j-1, i-1));
                        else if (i > 1 && j > 0 && (board[i-1][j-1] == black || board[i-1][j-1] == blackQueen) && board[i-2][j-1] == empty)
                            moves.push_back(Move(j, i, j-1, i-2));
                    }
                }
            }
            else {
                if ((board[i][j] == black || board[i][j] == blackQueen) && i < 7) {
                    if (i % 2) {
                        if (board[i+1][j] == empty)
                            moves.push_back(Move(j, i, j, i+1));
                        else if (i < 6 && j > 0 && (board[i+1][j] == white || board[i+1][j] == whiteQueen) && board[i+2][j-1] == empty)
                            moves.push_back(Move(j, i, j-1, i+2));
                        if (j < 3 && board[i+1][j+1] == empty)
                            moves.push_back(Move(j, i, j+1, i+1));
                        else if (i < 6 && j < 3 && (board[i+1][j+1] == white || board[i+1][j+1] == whiteQueen) && board[i+2][j+1] == empty)
                            moves.push_back(Move(j, i, j+1, i+2));
                    }
                    else {
                        if (board[i+1][j] == empty)
                            moves.push_back(Move(j, i, j, i+1));
                        else if (i < 6 && j < 3 && (board[i+1][j] == white || board[i+1][j] == whiteQueen) && board[i+2][j+1] == empty)
                            moves.push_back(Move(j, i, j+1, i+2));
                        if (j > 0 && board[i+1][j-1] == empty)
                            moves.push_back(Move(j, i, j-1, i+1));
                        else if (i < 6 && j > 0 && (board[i+1][j-1] == white || board[i+1][j-1] == whiteQueen) && board[i+2][j-1] == empty)
                            moves.push_back(Move(j, i, j-1, i+2));
                    }
                }
            }
        }
    }
    return moves;
}

std::vector<Move> Board::forcedMoves() {
    if (combos.size() > 0) {
        std::vector<Move> temp = combos;
        combos.clear();
        if (Debug::printInMoves) {
            std::cout<<"\n";
            print();
            for (Move m : temp) 
                Debug::printMove(m);
            std::cout<<"\n";
        }
        return temp;
    }
    std::vector<Move> normalMoves;
    std::vector<Move> eatingMoves;
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (turn) {
                if ((board[i][j] == white || board[i][j] == whiteQueen) && i > 0) {
                    if (i % 2) {
                        if (board[i-1][j] == empty)
                            normalMoves.push_back(Move(j, i, j, i-1));
                        else if (i > 1 && j > 0 && (board[i-1][j] == black || board[i-1][j] == blackQueen) && board[i-2][j-1] == empty)
                            eatingMoves.push_back(Move(j, i, j-1, i-2));
                        if (j < 3 && board[i-1][j+1] == empty)
                            normalMoves.push_back(Move(j, i, j+1, i-1));
                        else if (i > 1 && j < 3 && (board[i-1][j+1] == black || board[i-1][j+1] == blackQueen) && board[i-2][j+1] == empty)
                            eatingMoves.push_back(Move(j, i, j+1, i-2));
                    }
                    else {
                        if (board[i-1][j] == empty)
                            normalMoves.push_back(Move(j, i, j, i-1));
                        else if (i > 1 && j < 3 && (board[i-1][j] == black || board[i-1][j] == blackQueen) && board[i-2][j+1] == empty)
                            eatingMoves.push_back(Move(j, i, j+1, i-2));
                        if (j > 0 && board[i-1][j-1] == empty)
                            normalMoves.push_back(Move(j, i, j-1, i-1));
                        else if (i > 1 && j > 0 && (board[i-1][j-1] == black || board[i-1][j-1] == blackQueen) && board[i-2][j-1] == empty)
                            eatingMoves.push_back(Move(j, i, j-1, i-2));
                    }
                }
            }
            else {
                if ((board[i][j] == black || board[i][j] == blackQueen) && i < 7) {
                    if (i % 2) {
                        if (board[i+1][j] == empty)
                            normalMoves.push_back(Move(j, i, j, i+1));
                        else if (i < 6 && j > 0 && (board[i+1][j] == white || board[i+1][j] == whiteQueen) && board[i+2][j-1] == empty)
                            eatingMoves.push_back(Move(j, i, j-1, i+2));
                        if (j < 3 && board[i+1][j+1] == empty)
                            normalMoves.push_back(Move(j, i, j+1, i+1));
                        else if (i < 6 && j < 3 && (board[i+1][j+1] == white || board[i+1][j+1] == whiteQueen) && board[i+2][j+1] == empty)
                            eatingMoves.push_back(Move(j, i, j+1, i+2));
                    }
                    else {
                        if (board[i+1][j] == empty)
                            normalMoves.push_back(Move(j, i, j, i+1));
                        else if (i < 6 && j < 3 && (board[i+1][j] == white || board[i+1][j] == whiteQueen) && board[i+2][j+1] == empty)
                            eatingMoves.push_back(Move(j, i, j+1, i+2));
                        if (j > 0 && board[i+1][j-1] == empty)
                            normalMoves.push_back(Move(j, i, j-1, i+1));
                        else if (i < 6 && j > 0 && (board[i+1][j-1] == white || board[i+1][j-1] == whiteQueen) && board[i+2][j-1] == empty)
                            eatingMoves.push_back(Move(j, i, j-1, i+2));
                    }
                }
            }
        }
    }
    
    if (Debug::printInMoves) {
        std::cout<<"\n";
        print();
        for (Move m : normalMoves) 
            Debug::printMove(m);
        for (Move m : eatingMoves) 
            Debug::printMove(m);
        std::cout<<"\n";
    }
    if (eatingMoves.size() == 0)
        return normalMoves;
    return eatingMoves;
}

std::vector<Move> Board::possibleCombos(int i, int j) {
    std::vector<Move> moves;
    if (turn) {
        if ((board[i][j] == white || board[i][j] == whiteQueen) && i > 1) {
            if (i % 2) {
                if (j > 0 && (board[i-1][j] == black || board[i-1][j] == blackQueen) && board[i-2][j-1] == empty)
                    moves.push_back(Move(j, i, j-1, i-2));
                if (j < 3 && (board[i-1][j+1] == black || board[i-1][j+1] == blackQueen) && board[i-2][j+1] == empty)
                    moves.push_back(Move(j, i, j+1, i-2));
            }
            else {
                if (j < 3 && (board[i-1][j] == black || board[i-1][j] == blackQueen) && board[i-2][j+1] == empty)
                    moves.push_back(Move(j, i, j+1, i-2));
                if (j > 0 && (board[i-1][j-1] == black || board[i-1][j-1] == blackQueen) && board[i-2][j-1] == empty)
                    moves.push_back(Move(j, i, j-1, i-2));
            }
        }
    }
    else {
        if ((board[i][j] == black || board[i][j] == blackQueen) && i < 6) {
            if (i % 2) {
                if (j > 0 && (board[i+1][j] == white || board[i+1][j] == whiteQueen) && board[i+2][j-1] == empty)
                    moves.push_back(Move(j, i, j-1, i+2));
                if (j < 3 && (board[i+1][j+1] == white || board[i+1][j+1] == whiteQueen) && board[i+2][j+1] == empty)
                    moves.push_back(Move(j, i, j+1, i+2));
            }
            else {
                if (j < 3 && (board[i+1][j] == white || board[i+1][j] == whiteQueen) && board[i+2][j+1] == empty)
                    moves.push_back(Move(j, i, j+1, i+2));
                if (j > 0 && (board[i+1][j-1] == white || board[i+1][j-1] == whiteQueen) && board[i+2][j-1] == empty)
                    moves.push_back(Move(j, i, j-1, i+2));
            }
        }
    }
    if (Debug::printInMoves) {
        std::cout<<"\n";
        print();
        std::cout<<"\nsize: "<<moves.size();
        for (Move m : moves)
            Debug::printMove(m);
        std::cout<<"\n";
    }
    return moves;
}

RatedMove Board::bestMove(int depth) {
    float best = -1000;
    RatedMove *curBestMove = nullptr;
    if (Debug::prog == 10 && depth == 0)
        Debug::printInMoves = true;
    else if (Debug::prog > 10 && depth == 0)
        Debug::printInMoves = false;
    std::vector<Move> moves = forcedMoves();
    if (moves.size() == 0) 
        return RatedMove(Move::emptyMove, value()*30);

    if (depth > 0) {
        for (Move m : moves) {
            Piece eaten;
            if (m.eat) 
                eaten = board[(m.start.y + m.end.y)/2]
                             [(m.start.y % 2 == 1 && m.end.x < m.start.x) || 
                              (m.start.y % 2 == 0 && m.end.x > m.start.x) ? 
                               m.start.x : m.end.x];
            Piece eater = board[m.start.y][m.start.x];
            bool curTurn = turn;
            bool shouldBeFine = true;
            if (Debug::printInBestMove && depth == 3) {
                std::cout<<"Testing: ";
                Debug::printMove(m);
                print();
            }
            // if (m.start.x == 2 && m.start.y == 7 && m.end.x == 2 && m.end.y == 6)
            //     Debug::inner = true;
            // if (board[7][0] == empty && board[7][1] == empty) {
            //     Debug::printMove(m);
            //     std::cout<<"before move at depth "<<depth<<"\n";
            //     std::cout<<"\n";
            //     shouldBeFine = false;
            // }
            makeMove(m);
            if (depth == 1 && Debug::prog == 10) {
                Debug::printMove(m);
                print();
                std::cout<<"\n";
            }
            // if (board[7][0] == empty && board[7][1] == empty) {
            //     Debug::printMove(m);
            //     std::cout<<"after move at depth "<<depth<<"\n";
            //     std::cout<<"\n";
            // }
            RatedMove cur = RatedMove(m, bestMove(depth-1).value);
            if (m.eat) 
                board[(m.start.y + m.end.y)/2]
                     [(m.start.y % 2 == 1 && m.end.x < m.start.x) || 
                      (m.start.y % 2 == 0 && m.end.x > m.start.x) ? 
                       m.start.x : m.end.x] = eaten;
            if (turn != curTurn)
                cur.value *= -1;
            turn = curTurn;
            board[m.start.y][m.start.x] = eater;
            board[m.end.y][m.end.x] = empty;
            // if (board[7][0] == empty && board[7][1] == empty && shouldBeFine) {
            //     Debug::printMove(m);
            //     std::cout<<"after undoing move at depth "<<depth<<"\n";
            //     std::cout<<"\n";
            // }
            if (Debug::printInBestMove && depth == 3) {
                std::cout<<"After undoing: ";
                Debug::printMove(m);
                print();
                Debug::printInBestMove = false;
            }
            if (cur.value > best) {
                RatedMove temp = cur;
                curBestMove = &temp;
                best = cur.value;
            }
        }
    }
    else {
        if (Debug::inner) {
            std::cout<<"\nCHECKING IN BRANCH NUMBER: "<<++Debug::prog<<"\n";
            std::cout<<"\n";
        }
        for (Move m : moves) {
            Piece eaten;
            if (m.eat) 
                eaten = board[(m.start.y + m.end.y)/2]
                             [(m.start.y % 2 == 1 && m.end.x < m.start.x) || 
                              (m.start.y % 2 == 0 && m.end.x > m.start.x) ? 
                               m.start.x : m.end.x];
            Piece eater = board[m.start.y][m.start.x];
            bool curTurn = turn;
            if (Debug::inner && Debug::prog == 11) {
                std::cout<<"Trying move (inner): ";
                Debug::printMove(m);
                std::cout<<(eater == 0 ? "_" : "p")<<" == "<<(board[m.start.y][m.start.x] == 0 ? "_" : "p");
                print();
                std::cout<<"\n";
            }
            makeMove(m);
            combos.clear();
            RatedMove cur = RatedMove(m, value() * (turn ? 1 : -1) + RND::getFloat()*0.2-0.1);
            if (m.eat) 
                board[(m.start.y + m.end.y)/2]
                     [(m.start.y % 2 == 1 && m.end.x < m.start.x) || 
                      (m.start.y % 2 == 0 && m.end.x > m.start.x) ? 
                       m.start.x : m.end.x] = eaten;
            if (turn != curTurn)
                cur.value *= -1;
            turn = curTurn;
            board[m.start.y][m.start.x] = eater;
            board[m.end.y][m.end.x] = empty;
            if (Debug::inner && Debug::prog == 11) {
                std::cout<<"After undoing move (inner): ";
                Debug::printMove(m);
                std::cout<<(eater == 0 ? "_" : "p")<<"\n";
                print();
                std::cout<<"\n";
            }
            if (cur.value > best) {
                best = cur.value;
                RatedMove temp = cur;
                curBestMove = &temp;
            }
        }
    }
    return *curBestMove;
}