#pragma once
#include "Piece.h"
#include <cctype>

class Bishop : public Piece
{
private:
    
public:
    Bishop(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture);
    ~Bishop();
    
    std::vector<int> getBasicMoves() override;
    std::vector<int> getMyCapturableSpaces(std::string boardToCheck) override;

    void preformSpecialMove(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy) override;
    std::vector<int> getSpecialMoves() override;

    std::vector<int> getValidMoves() override;
    //void movePiece(int moveIndex, bool testMoveOnCopyBoard, std::string* boardStrToChange, std::vector<Piece*>* piecesVectToChange) override;
};
