#pragma once
#include "iostream"
#include <vector>
//#include "Game.h"
#include <string>
#include <vector>
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Board;

class Piece
{
public:
    Board *board;
    char pieceIcon;
    int cord;
    bool hasNotMoved;

    Piece(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture, std::vector<Animation> listOfAnimations);
    ~Piece();

    std::vector<Animation> listOfAnimations;

    sf::Texture pieceTexture;
    sf::Sprite pieceSprite;

    //returns a list of just the basic moves a piece can make, not accounting for anything else
    virtual std::vector<int> getBasicMoves() = 0;

    //returns a list of valid indexes a piece can move to, after accounting for spaces
    //that put the king in check, and special moves
    virtual std::vector<int> getValidMoves() = 0;
    virtual std::vector<int> getMyCapturableSpaces(std::string boardToCheck) = 0;
    virtual std::vector<int> getSpecialMoves();

    std::vector<int> removeLocationsNotOnBoard(std::vector<int> validMoves);
    virtual void preformSpecialMove(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy);

    void movePiece(int currentGameTurn, int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy);
    bool isMoveValid(int moveCord, std::string whichTeam);

    bool onRightSideOfBoard(int cord);
    bool onLeftSideOfBoard(int cord);

    std::string getMyTeamString();
    std::string getOpponentsTeamString();
    bool opponentIsOnSpace(char boardSpace);

    virtual void updatePiecesInformation(int currentGameTurn);
};