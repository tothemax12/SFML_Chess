#pragma once
#include <string>
#include "Piece.h"
#include "Pawn.h"

class Game
{
private:
std::string board;
std::vector<Piece> piecesCurrentlyOnBoard;
Pawn testPawn1;
Pawn testPawn2;

public:
    Game();
    ~Game();
    void printBoard();
    void overWriteBoardAtLocation(int cord, char thingOnSpace);
    std::vector<Piece>* getPiecesCurrentlyOnBoard();
};
