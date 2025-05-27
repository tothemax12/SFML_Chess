#pragma once
#include "Piece.h"
#include <cctype>

class Pawn : public Piece
{
private:
    
public:
    Pawn(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture);
    ~Pawn();

    //flags related to special moves
    bool iMovedTwoSpacesOfMyFirstTurn = false;
    bool iMovedTwoSpacesLastTurn = false;
    bool iMovedThreeSpacesForward = false;
    
    std::vector<int> getBasicMoves() override;
    //pawn is weird and can't capture forward
    std::vector<int> getMyCapturableSpaces(std::string boardToCheck) override;
    
    void preformSpecialMove(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy) override;
    std::vector<int> getSpecialMoves() override;

    std::vector<int> getValidMoves() override;

    void updatePiecesInformation(int currentGameTurn) override;

    //void movePiece(int moveIndex, bool testMoveOnCopyBoard, std::string* boardStrToChange, std::vector<Piece*>* piecesVectToChange) override;
};