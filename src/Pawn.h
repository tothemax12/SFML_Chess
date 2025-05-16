#pragma once
#include "Piece.h"
#include <cctype>

class Pawn : public Piece
{
private:
    
public:
    Pawn(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture);
    ~Pawn();
    
    std::vector<int>* getBasicMoves() override;
    //pawn is weird and can't capture forward
    std::vector<int>* getMyCapturableSpaces(std::string boardToCheck) override;
    bool checkIfSpecialMoveCanBePreformed() override;

    std::vector<int>* getValidMoves() override;

    //void movePiece(int moveIndex, bool testMoveOnCopyBoard, std::string* boardStrToChange, std::vector<Piece*>* piecesVectToChange) override;
};
