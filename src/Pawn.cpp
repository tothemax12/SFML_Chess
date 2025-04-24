#include "Pawn.h"

Pawn::Pawn(char pieceIcon, int cord)
{
    this->pieceIcon = pieceIcon;
    this->cord = cord;
}

Pawn::Pawn()
{

}

Pawn::~Pawn()
{
}

std::vector<int>* Pawn::getBasicMoves() {
    std::vector<int>* validMoves = new std::vector<int>;
    
    //White piece
    if (this->pieceIcon == 'p') {
        if (isFirstTurn) {
            validMoves->push_back(cord-8);
            validMoves->push_back(cord-16);
        } else {
            validMoves->push_back(cord-8);
        }
    }

    //Black piece
    if (this->pieceIcon == 'P') {
        if (isFirstTurn) {
            validMoves->push_back(cord+8);
            validMoves->push_back(cord+16);
        } else {
            validMoves->push_back(cord+8);
        }
    }

    validMoves = removeLocationsNotOnBoard(validMoves);

    return validMoves;
}

std::vector<int>* Pawn::getValidMoves() {
    //brainstorming...
    //also need to confirm they are on the board.
    //okay these are the basic moves, but if any of them put the king
    //in check we need to throw them out.
    //additionally, the pawn can preform a special move, so we
    //also need to account for that.
    std::vector<int>* validMoves = getBasicMoves();
    return validMoves;
}

std::vector<int>* Pawn::getCapturableSpaces() {
    std::vector<int>* capturableSpaces = new std::vector<int>;
    if (pieceIcon == 'P') {
        capturableSpaces->push_back(cord+7);
        capturableSpaces->push_back(cord+9);
    } else {
        capturableSpaces->push_back(cord-7);
        capturableSpaces->push_back(cord-9);
    }

    capturableSpaces = removeLocationsNotOnBoard(capturableSpaces);
    return capturableSpaces;
}