#pragma once
#include "Piece.h"
#include <cctype>

class Rook : public Piece
{
private:
    
public:
    Rook(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture);
    ~Rook();
    
    std::vector<int>* getBasicMoves() override;
    std::vector<int>* getMyCapturableSpaces(std::string boardToCheck) override;
    bool checkIfSpecialMoveCanBePreformed() override;

    std::vector<int>* getValidMoves() override;
    //void movePiece(int moveIndex, bool testMoveOnCopyBoard, std::string* boardStrToChange, std::vector<Piece*>* piecesVectToChange) override;
};
