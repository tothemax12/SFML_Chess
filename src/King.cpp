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
    std::string boardStr = *board->getBoardStr();

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

    for (int i = 0; i < validMoves->size(); i++)
    {
        //if there is a piece on a move we can make, throw
        //it out. that is for capturable spaces to check
        if (boardStr[validMoves->at(i)] != '0') {
            validMoves->at(i) = -1;
        }
    }
    
    validMoves = removeLocationsNotOnBoard(validMoves);

    return validMoves;
}

std::vector<int>* King::getMyCapturableSpaces(std::string boardToCheck) {
    //we get the basic moves which are just valid spaces all around the king, it's not concerned
    //with if there is a piece in those spots
    std::vector<int>* capturableSpaces = new std::vector<int>;
    std::string myTeam = getMyTeamString();
    

    //begin with assuming all the spots are good
    //row above king
    capturableSpaces->push_back(cord-7);
    capturableSpaces->push_back(cord-8);
    capturableSpaces->push_back(cord-9);
    
    //left and right of king
    capturableSpaces->push_back(cord-1);
    capturableSpaces->push_back(cord+1);

    //row below king
    capturableSpaces->push_back(cord+7);
    capturableSpaces->push_back(cord+8);
    capturableSpaces->push_back(cord+9);

    //remove them based on where the middle cord is
    if(onLeftSideOfBoard(cord)) {
        //cord-9
        capturableSpaces->at(2) = -1;
        //cord-1
        capturableSpaces->at(3) = -1;
        //cord+7
        capturableSpaces->at(5) = -1;
    }

    if(onRightSideOfBoard(cord)) {
        //cord-7 
        capturableSpaces->at(0) = -1;
        //cord+1
        capturableSpaces->at(4) = -1;
        //cord+9
        capturableSpaces->at(7) = -1;
    }

    //middle cord on top row, remove the top row
    if (board->inRange(cord, 0, 7)) {
        //cord-7
        capturableSpaces->at(0) = -1;
        //cord-8
        capturableSpaces->at(1) = -1;
        //cord-9
        capturableSpaces->at(2) = -1;
    }

    //middle cord on bottom row
    if (board->inRange(cord, 56, 63)) {
        //cord+7
        capturableSpaces->at(5) = -1;
        //cord+8
        capturableSpaces->at(6) = -1;
        //cord+9
        capturableSpaces->at(7) = -1;
    }

    capturableSpaces = removeLocationsNotOnBoard(capturableSpaces);

    for (int i = 0; i < capturableSpaces->size(); i++)
    {
        //we do not care about empty spaces here
        if(boardToCheck[capturableSpaces->at(i)] == '0') {
            capturableSpaces->at(i) = -1;
        }
    }    

    capturableSpaces = removeLocationsNotOnBoard(capturableSpaces);

    for (int i = 0; i < capturableSpaces->size(); i++)
    {
        //if there is a piece on a move we can make
        if (boardToCheck[capturableSpaces->at(i)] != '0') {
            if (myTeam == "White") {
                if (!islower(boardToCheck[capturableSpaces->at(i)])) {
                    //this says, if, from the spots I collected around the me, a piece is on the opposite side as me, do nothing.

                    //what I meant to say was, if from the spot I collected around me, a piece is on my team, throw it out
                    capturableSpaces->at(i) = -1;
                }
            } else if (myTeam == "Black") {
                if (!isupper(boardToCheck[capturableSpaces->at(i)])) {
                    capturableSpaces->at(i) = -1;
                }
            }
        }
    }

    capturableSpaces = removeLocationsNotOnBoard(capturableSpaces);
    
    // printf("capturable spaces: \n");
    // for (int i = 0; i < capturableSpaces->size(); i++)
    // {
    //     std::cout << capturableSpaces->at(i) << "\n";
    //     //printf("valid moves size: %d \n", validMoves->size());
    //     //validMoves->emplace_back(capturableSpaces->at(i));
    //     //printf("valid moves size: %d \n", validMoves->size());
    // }
    // printf("end of capturable spaces\n");
    

    return capturableSpaces;
}

bool King::checkIfSpecialMoveCanBePreformed() {
    //check if it can castle
    return false;
}

std::vector<int>* King::getValidMoves() {
    std::vector<int>* validMoves = new std::vector<int>;
    std::vector<int>* basicMoves = getBasicMoves();
    std::vector<int>* capturableSpaces = getMyCapturableSpaces(*board->getBoardStr());    
    bool isKingInDangerIfMoveWasPreformed = false;

    for (int i = 0; i < basicMoves->size(); i++)
    {
        validMoves->emplace_back(basicMoves->at(i));        
    }
    
    for (int i = 0; i < capturableSpaces->size(); i++)
    {
        validMoves->emplace_back(capturableSpaces->at(i));
    }

    //need to remove the spaces that put the king in danger. that is not valid
    for (int i = validMoves->size()-1; i > -1; i--)
    {
        isKingInDangerIfMoveWasPreformed = isMoveValid(validMoves->at(i), getMyTeamString());
        if (isKingInDangerIfMoveWasPreformed) {
            validMoves->erase(validMoves->begin()+i);
        }
    }

    return validMoves;
}