#pragma once
#include "Piece.h"
#include <cctype>

class Pawn : public Piece
{
private:
    
public:
    Pawn(char pieceIcon, int cord, sf::Texture* pieceTexture, std::string* currentBoardString);
    Pawn();
    ~Pawn();
    
    std::vector<int>* getBasicMoves() override;
    std::vector<int>* getValidMoves() override;

    //pawn is weird and can't capture forward
    std::vector<int>* getCapturableSpaces() override;
};
