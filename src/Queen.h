#pragma once
#include "Piece.h"
#include <cctype>

class Queen : public Piece
{
private:
    
public:
    Queen(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture);
    ~Queen();
    
    std::vector<int> getBasicMoves() override;
    std::vector<int> getMyCapturableSpaces(std::string boardToCheck) override;

    void preformSpecialMove(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy) override;
    std::vector<int> getSpecialMoves() override;

    std::vector<int> getValidMoves() override;
    //void movePiece(int moveIndex, bool testMoveOnCopyBoard, std::string* boardStrToChange, std::vector<Piece*>* piecesVectToChange) override;
};