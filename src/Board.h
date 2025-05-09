#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Piece.h"
#include "Pawn.h"
#include <cmath>
#include <fstream>

class Board
{
private:
    sf::Texture* boardTexture;
    sf::Sprite boardSprite;
    sf::Sprite highlightSquareSprite;
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

    Board(sf::Texture* boardTexture, sf::Texture* highlightedSquareTexture, sf::Texture* wPawnTexture, sf::Texture* bPawnTexture);
    ~Board();
    std::vector<Piece*>* initializePiecesOnBoardBasedOnBoardString();


    void printBoard();
    void overWriteBoardAtLocation(int cord, char thingOnSpace);
    std::vector<Piece*>* getPiecesCurrentlyOnBoard();
    
    void drawBoard(sf::RenderWindow* window);
    void drawPiecesCurrentlyOnBoard(sf::RenderWindow* window);
    void drawHighlightedValidMoves(sf::RenderWindow* window, std::vector<int>* validMoves);

    int* convertStrIndexToBoardCords(int stringIdx);
    int convertBoardCordsToStringIndex(int x, int y);
    bool inRange(int val, int low, int high);

    void readInBoardFromFile();
};