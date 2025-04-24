#pragma once
#include "Piece.h"
//#include "Game.h"

class Pawn : public Piece
{
private:
    bool isFirstTurn = true;
    
public:
    Pawn(char pieceIcon, int cord);
    Pawn();
    ~Pawn();
    
    std::vector<int>* getBasicMoves() override;
    std::vector<int>* getValidMoves() override;

    //pawn is weird and can't capture forward
    std::vector<int>* getCapturableSpaces() override;
};
