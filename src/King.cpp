#include "King.h"
#include "Board.h"

King::King(Board* board, char pieceIcon, int cord, sf::Texture* pieceTexture) : 
Piece(board, pieceIcon, cord, pieceTexture)
{

}

King::~King() {

}

std::vector<int>* King::getBasicMoves() {
    std::vector<int>* validMoves = new std::vector<int>;

    //begin with assuming all the spots are good
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

    //remove them based on where the middle cord is
    if(onLeftSideOfBoard(cord)) {
        //cord-9
        validMoves->at(2) = -1;
        //cord-1
        validMoves->at(3) = -1;
        //cord+7
        validMoves->at(5) = -1;
    }

    if(onRightSideOfBoard(cord)) {
        //cord-7 
        validMoves->at(0) = -1;
        //cord+1
        validMoves->at(4) = -1;
        //cord+9
        validMoves->at(7) = -1;
    }

    //middle cord on top row, remove the top row
    if (board->inRange(cord, 0, 7)) {
        //cord-7
        validMoves->at(0) = -1;
        //cord-8
        validMoves->at(1) = -1;
        //cord-9
        validMoves->at(2) = -1;
    }

    //middle cord on bottom row
    if (board->inRange(cord, 56, 63)) {
        //cord+7
        validMoves->at(5) = -1;
        //cord+8
        validMoves->at(6) = -1;
        //cord+9
        validMoves->at(7) = -1;
    }

    validMoves = removeLocationsNotOnBoard(validMoves);

    std::string* currentBoardstr = board->getBoardStr();
    //remove the valid spaces of our team mates, can't capture them
    for (int i = 0; i < validMoves->size(); i++)
    {
        if (currentBoardstr->at(validMoves->at(i)) != '0') {
            if (isupper(this->pieceIcon)) {
                if (isupper(currentBoardstr->at(validMoves->at(i)))) {
                    validMoves->at(i) = -1;
                }
            } else if (islower(this->pieceIcon)) {
                if (islower(currentBoardstr->at(validMoves->at(i)))) {
                    validMoves->at(i) = -1;
                }
            }
        }
    }

    validMoves = removeLocationsNotOnBoard(validMoves);

    return validMoves;
}

std::vector<int>* King::getMyCapturableSpaces(std::string boardToCheck) {
    return getBasicMoves();
}

bool King::checkIfSpecialMoveCanBePreformed() {
    //check if it can castle
    return false;
}

std::vector<int>* King::getValidMoves() {
    std::vector<int>* validMoves = getBasicMoves();
    return validMoves;
}