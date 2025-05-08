#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Piece.h"
#include "Pawn.h"

class Board
{
private:
    sf::Texture* boardTexture;
    sf::Sprite boardSprite;
    std::string boardString;
    sf::Texture* wPawnTexture;
    sf::Texture* bPawnTexture;


    // //piece definitions
    // Pawn testPawn1;
    // Pawn testPawn2;
    // //Pawn testPawn2;

    std::vector<Piece*>* piecesCurrentlyOnBoard;

public:
    //piece definitions
    //Pawn testPawn1;
    //Pawn testPawn2;
    //Pawn testPawn2;

    Board(sf::Texture* boardTexture, sf::Texture* wPawnTexture, sf::Texture* bPawnTexture);
    ~Board();
    std::vector<Piece*>* initializePiecesOnBoardBasedOnBoardString();


    void printBoard();
    void overWriteBoardAtLocation(int cord, char thingOnSpace);
    std::vector<Piece*>* getPiecesCurrentlyOnBoard();
    
    void drawBoard(sf::RenderWindow* window);
    void drawPiecesCurrentlyOnBoard(sf::RenderWindow* window);
};