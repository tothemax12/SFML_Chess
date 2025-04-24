#pragma once
#include "iostream"
#include <vector>
//#include "Game.h"

class Piece
{
public:
    char pieceIcon;
    int cord;

    Piece(char pieceIcon, int cord);
    Piece();
    ~Piece();


    //returns a list of just the basic moves a piece can make, not accounting for anything else
    virtual std::vector<int>* getBasicMoves();

    //returns a list of valid indexes a piece can move to, after accounting for spaces
    //that put the king in check, and special moves
    virtual std::vector<int>* getValidMoves();
    std::vector<int>* removeLocationsNotOnBoard(std::vector<int>* validMoves);
    virtual std::vector<int>* getCapturableSpaces();
    Piece* getPiecesICanCapture(std::vector<Piece>* piecesCurrentlyOnBoard);
};