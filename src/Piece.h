#pragma once
#include "iostream"
#include <vector>
//#include "Game.h"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Piece
{
public:
    char pieceIcon;
    int cord;
    bool isFirstTurn;
    std::string* currentBoardString;
    std::vector<Piece*>* piecesCurrentlyOnBoard; 

    Piece(char pieceIcon, int cord, sf::Texture* pieceTexture, std::string* currentBoardString, std::vector<Piece*>* piecesCurrentlyOnBoard);
    ~Piece();

    sf::Texture pieceTexture;
    sf::Sprite pieceSprite;

    //returns a list of just the basic moves a piece can make, not accounting for anything else
    virtual std::vector<int>* getBasicMoves();

    //returns a list of valid indexes a piece can move to, after accounting for spaces
    //that put the king in check, and special moves
    virtual std::vector<int>* getValidMoves();
    std::vector<int>* removeLocationsNotOnBoard(std::vector<int>* validMoves);
    virtual std::vector<int>* getCapturableSpaces();
    std::vector<int>* getAllCapturableSpacesForAGiveSide(std::string sideThatIsCapturingPieces);
    std::string* getAllPiecesThatCanBeCapturedBySide(std::string sideThatIsCapturingPieces);
    std::vector<Piece> getPiecesICanCapture(std::vector<Piece>* piecesCurrentlyOnBoard);
};