#pragma once
#include "Piece.h"
//#include "Game.h"

class King : public Piece
{
private:
    /* data */
public:
    King(Board* board, char pieceIcon, int cord, sf::Texture* pieceTexture, std::vector<Animation> listOfAnimations);
    ~King();
    
    std::vector<int> getBasicMoves() override;
    std::vector<int> getMyCapturableSpaces(std::string boardToCheck) override;
    std::vector<int> getSpecialMoves() override;
    void preformSpecialMove(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy) override;
    std::vector<int> getValidMoves() override;
};