#pragma once
#include "iostream"
#include <vector>
//#include "Game.h"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Board;

class Piece
{
public:
    Board *board;
    char pieceIcon;
    int cord;
    bool isFirstTurn;

    Piece(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture);
    ~Piece();

    sf::Texture pieceTexture;
    sf::Sprite pieceSprite;

    //returns a list of just the basic moves a piece can make, not accounting for anything else
    virtual std::vector<int>* getBasicMoves();

    //returns a list of valid indexes a piece can move to, after accounting for spaces
    //that put the king in check, and special moves
    virtual std::vector<int>* getValidMoves();
    std::vector<int>* removeLocationsNotOnBoard(std::vector<int>* validMoves);
    virtual std::vector<int>* getMyCapturableSpaces();

    void movePiece(int moveIndex, std::string* boardStrToChange);
    bool isMoveValid(int moveCord);

    bool onRightSideOfBoard(int cord);
    bool onLeftSideOfBoard(int cord);
};