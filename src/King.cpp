#include "King.h"

King::King(Board* board, char pieceIcon, int cord, sf::Texture* pieceTexture) : 
Piece(board, pieceIcon, cord, pieceTexture)
{

}

King::~King() {

}

std::vector<int>* King::getBasicMoves() {
    std::vector<int>* validMoves = new std::vector<int>;

    //row above king
    validMoves->push_back(cord-7);
    validMoves->push_back(cord-8);
    validMoves->push_back(cord-9);

    //left and right of king
    validMoves->push_back(cord-1);
    validMoves->push_back(cord+1);

    //row below king
    validMoves->push_back(cord+7);
    validMoves->push_back(cord+8);
    validMoves->push_back(cord+9);

    validMoves = removeLocationsNotOnBoard(validMoves);

    return validMoves;
}


std::vector<int>* King::getValidMoves() {
    std::vector<int>* validMoves = getBasicMoves();
    return validMoves;
}

std::vector<int>* King::getMyCapturableSpaces() {
    return getBasicMoves();
}