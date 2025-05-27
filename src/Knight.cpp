#include "Knight.h"
#include "Board.h"

Knight::Knight(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture) : 
Piece(board, pieceIcon, cord, pieceTexture)
{

}

std::vector<int> Knight::getBasicMoves() {
    std::vector<int> basicMoves;
    std::string boardStr = *board->getBoardStr();

    //assume all are valid, throw out the ones we don't want
    
    //upper left
    basicMoves.push_back(this->cord-17);

    //upper right
    basicMoves.push_back(this->cord-15);

    //down left
    basicMoves.push_back(this->cord+15);

    //down right
    basicMoves.push_back(this->cord+17);

    //left up
    basicMoves.push_back(this->cord-10);
    
    //left down
    basicMoves.push_back(this->cord+6);

    //right up
    basicMoves.push_back(this->cord-6);

    //right down
    basicMoves.push_back(this->cord+10);

    //mark the ones not on the board
    for (int i = 0; i < basicMoves.size(); i++)
    {
        if (!board->inRange(basicMoves.at(i), 0, 63)) {
            basicMoves.at(i) = -1;
        }
    }

    //if I am 1 space from the right, and that space is on the board, throw out the far 2 right
    if (board->inRange(this->cord+1, 0, 63) && onRightSideOfBoard(this->cord+1)) {
        basicMoves.at(6) = -1;
        basicMoves.at(7) = -1;
    }

    //if I am on the right, throw out all the right side spaces
    if (onRightSideOfBoard(this->cord)) {
        basicMoves.at(6) = -1;
        basicMoves.at(7) = -1;

        basicMoves.at(1) = -1;
        basicMoves.at(3) = -1;
    }

    //same for the left
    if (board->inRange(this->cord-1, 0, 63) && onLeftSideOfBoard(this->cord-1)) {
        basicMoves.at(4) = -1;
        basicMoves.at(5) = -1;
    }

    if (onLeftSideOfBoard(this->cord)) {
        basicMoves.at(4) = -1;
        basicMoves.at(5) = -1;

        basicMoves.at(0) = -1;
        basicMoves.at(2) = -1;
    }

    basicMoves = removeLocationsNotOnBoard(basicMoves);

    //mark the ones with pieces on them
    for (int i = 0; i < basicMoves.size(); i++)
    {
        if (boardStr.at(basicMoves.at(i)) != '0') {
            basicMoves.at(i) = -1;
        }
    }

    basicMoves = removeLocationsNotOnBoard(basicMoves);

    printf("basicMoves: \n");
    for (int i = 0; i < basicMoves.size(); i++)
    {
        printf("%d ", basicMoves.at(i));
    }
    printf("\nend of basicMoves\n");

    return basicMoves;
}

std::vector<int> Knight::getMyCapturableSpaces(std::string boardToCheck) {
    std::vector<int> capturableMoves;
    //std::string boardStr = *board->getBoardStr();
    std::string boardStr = boardToCheck;
    
    //assume all are valid, throw out the ones we don't want
    
    //upper left
    capturableMoves.push_back(this->cord-17);

    //upper right
    capturableMoves.push_back(this->cord-15);

    //down left
    capturableMoves.push_back(this->cord+15);

    //down right
    capturableMoves.push_back(this->cord+17);

    //left up
    capturableMoves.push_back(this->cord-10);
    
    //left down
    capturableMoves.push_back(this->cord+6);

    //right up
    capturableMoves.push_back(this->cord-6);

    //right down
    capturableMoves.push_back(this->cord+10);

    //mark the ones not on the board
    for (int i = 0; i < capturableMoves.size(); i++)
    {
        if (!board->inRange(capturableMoves.at(i), 0, 63)) {
            capturableMoves.at(i) = -1;
        }
    }

    //if I am 1 space from the right, and that space is on the board, throw out the far 2 right
    if (board->inRange(this->cord+1, 0, 63) && onRightSideOfBoard(this->cord+1)) {
        capturableMoves.at(6) = -1;
        capturableMoves.at(7) = -1;
    }

    //if I am on the right, throw out all the right side spaces
    if (onRightSideOfBoard(this->cord)) {
        capturableMoves.at(6) = -1;
        capturableMoves.at(7) = -1;

        capturableMoves.at(1) = -1;
        capturableMoves.at(3) = -1;
    }

    //same for the left
    if (board->inRange(this->cord-1, 0, 63) && onLeftSideOfBoard(this->cord-1)) {
        capturableMoves.at(4) = -1;
        capturableMoves.at(5) = -1;
    }

    if (onLeftSideOfBoard(this->cord)) {
        capturableMoves.at(4) = -1;
        capturableMoves.at(5) = -1;

        capturableMoves.at(0) = -1;
        capturableMoves.at(2) = -1;
    }

    capturableMoves = removeLocationsNotOnBoard(capturableMoves);

    //throw out the basic moves that do not have pieces on them
    //also throw out the spots without opponents on them
    for (int i = 0; i < capturableMoves.size(); i++)
    {
        if (boardStr.at(capturableMoves.at(i)) == '0' || !opponentIsOnSpace(boardStr.at(capturableMoves.at(i)))) {
            capturableMoves.at(i) = -1;
        }
    }

    capturableMoves = removeLocationsNotOnBoard(capturableMoves);

    printf("capturableMoves: \n");
    for (int i = 0; i < capturableMoves.size(); i++)
    {
        printf("%d ", capturableMoves.at(i));
    }
    printf("\nend of capturableMoves\n");

    return capturableMoves;
}

std::vector<int> Knight::getSpecialMoves() {
    std::vector<int> specialMoves;
    return specialMoves;
}

void Knight::preformSpecialMove(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy) {
    
}

std::vector<int> Knight::getValidMoves() {
    //brainstorming...
    //also need to confirm they are on the board.
    //okay these are the basic moves, but if any of them put the king
    //in check we need to throw them out.
    //additionally, the pawn can preform a special move, so we
    //also need to account for that.
    std::vector<int> validMoves;
    std::vector<int> basicMoves = getBasicMoves();
    std::vector<int> capturableSpaces = getMyCapturableSpaces(*board->getBoardStr());
    bool isKingInDangerIfMoveWasPreformed = false;

    //printf("valid moves size: %d \n", validMoves->size());
    for (int i = 0; i < basicMoves.size(); i++)
    {
        //printf("basic moves size: %d \n", basicMoves.size());
        //printf("i: %d \n", i);
        //printf("valid moves size: %d \n", validMoves->size());
        validMoves.emplace_back(basicMoves.at(i));
        //printf("valid moves size: %d \n", validMoves->size());
    }
    
    for (int i = 0; i < capturableSpaces.size(); i++)
    {
        //printf("capt spaces size: %d \n", capturableSpaces->size());
        //printf("i: %d \n", i);
        //printf("valid moves size: %d \n", validMoves->size());
        validMoves.emplace_back(capturableSpaces.at(i));
        //printf("valid moves size: %d \n", validMoves->size());
    }

    //need to remove the spaces that put the king in danger. that is not valid
    for (int i = validMoves.size()-1; i > -1; i--)
    {
        isKingInDangerIfMoveWasPreformed = isMoveValid(validMoves.at(i), getMyTeamString());
        if (isKingInDangerIfMoveWasPreformed) {
            validMoves.erase(validMoves.begin()+i);
        }
    }

    return validMoves;
}