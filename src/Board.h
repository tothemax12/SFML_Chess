#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Piece.h"
#include "Pawn.h"

class Board
{
private:
    sf::Image boardImage;
    std::string boardString;

    //piece definitions
    Pawn testPawn1;
    Pawn testPawn2;

    std::vector<Piece> piecesCurrentlyOnBoard;


public:
    Board();
    ~Board();

    void printBoard();
    void overWriteBoardAtLocation(int cord, char thingOnSpace);
    std::vector<Piece>* getPiecesCurrentlyOnBoard();
};