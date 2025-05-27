#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture) : 
Piece(board, pieceIcon, cord, pieceTexture)
{

}

std::vector<int> Bishop::getBasicMoves() {
    std::vector<int> basicMoves;
    std::string boardStr = *board->getBoardStr();
    
    //upward right diagonal
    if(!onRightSideOfBoard(this->cord)) {
        for (int i = cord; board->inRange(i, 0, 63); i-=7)
        {
            if (i == cord) {
                continue;
            }

            if (boardStr.at(i) != '0') {
                break;
            }

            if(onRightSideOfBoard(i)) {
                //can't go up and diagonal more if we hit the side
                basicMoves.push_back(i);
                break;
            }

            basicMoves.push_back(i);
        }
    }

    //downward left diagonal
    if(!onLeftSideOfBoard(this->cord)) {
        for (int i = cord; board->inRange(i, 0, 63); i+=7)
        {
            if (i == cord) {
                continue;
            }

            if (boardStr.at(i) != '0') {
                break;
            }

            if(onLeftSideOfBoard(i)) {
                //can't go up and diagonal more if we hit the side
                basicMoves.push_back(i);
                break;
            }

            basicMoves.push_back(i);
        }
    }

    //upward left diagonal
    if(!onLeftSideOfBoard(this->cord)) {
        for (int i = cord; board->inRange(i, 0, 63); i-=9)
        {
            if (i == cord) {
                continue;
            }

            if (boardStr.at(i) != '0') {
                break;
            }

            if(onLeftSideOfBoard(i)) {
                //can't go up and diagonal more if we hit the side
                basicMoves.push_back(i);
                break;
            }

            basicMoves.push_back(i);
        }
    }

    //downward right diagonal
    if(!onRightSideOfBoard(this->cord)) {
        for (int i = cord; board->inRange(i, 0, 63); i+=9)
        {
            if (i == cord) {
                continue;
            }

            if (boardStr.at(i) != '0') {
                break;
            }

            if(onRightSideOfBoard(i)) {
                //can't go up and diagonal more if we hit the side
                basicMoves.push_back(i);
                break;
            }

            basicMoves.push_back(i);
        }
    }

    return basicMoves;
}

std::vector<int> Bishop::getMyCapturableSpaces(std::string boardToCheck) {
    std::vector<int> capturableMoves;
    //std::string boardStr = *board->getBoardStr();
    std::string boardStr = boardToCheck;
    
    //upward right diagonal
    if(!onRightSideOfBoard(this->cord)) {
        for (int i = cord; board->inRange(i, 0, 63); i-=7)
        {
            if (i == cord) {
                continue;
            }

            //we hit something
            if (boardStr.at(i) != '0') {
                if (opponentIsOnSpace(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }
                break;
            }

            if (onRightSideOfBoard(i)) {
                break;
            }
        }
    }

    //upward left diagonal
    if(!onLeftSideOfBoard(this->cord)) {
        for (int i = cord; board->inRange(i, 0, 63); i-=9)
        {
            if (i == cord) {
                continue;
            }

            //we hit something
            if (boardStr.at(i) != '0') {
                if (opponentIsOnSpace(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }
                break;
            }

            if (onLeftSideOfBoard(i)) {
                break;
            }
        }
    }

    //downward right diagonal
    if(!onRightSideOfBoard(this->cord)) {
        for (int i = cord; board->inRange(i, 0, 63); i+=9)
        {
            if (i == cord) {
                continue;
            }

            //we hit something
            if (boardStr.at(i) != '0') {
                if (opponentIsOnSpace(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }
                break;
            }

            if (onRightSideOfBoard(i)) {
                break;
            }
        }
    }

    //downward left diagonal
    if(!onLeftSideOfBoard(this->cord)) {
        for (int i = cord; board->inRange(i, 0, 63); i+=7)
        {
            if (i == cord) {
                continue;
            }

            //we hit something
            if (boardStr.at(i) != '0') {
                if (opponentIsOnSpace(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }
                break;
            }

            if (onLeftSideOfBoard(i)) {
                break;
            }
        }
    }

    return capturableMoves;
}

std::vector<int> Bishop::getSpecialMoves() {
    std::vector<int> specialMoves;
    return specialMoves;
}

void Bishop::preformSpecialMove(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy) {
    
}

std::vector<int> Bishop::getValidMoves() {
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
        //printf("basic moves size: %d \n", basicMoves->size());
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