#include "Rook.h"
#include "Board.h"

Rook::Rook(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture, std::vector<Animation> listOfAnimations) : 
Piece(board, pieceIcon, cord, pieceTexture, listOfAnimations)
{

}

std::vector<int> Rook::getBasicMoves() {
    std::vector<int> basicMoves;
    std::string boardStr = *board->getBoardStr();

    //right direction, go to the right until it wraps back to the left
    bool initiallyOnLS = onLeftSideOfBoard(cord);
    int i = cord;
    if (initiallyOnLS) {
        i++;
    };
    for (; !onLeftSideOfBoard(i) && board->inRange(i, 0, 63); i++)
    {
        //the spot where we started is not valid
        if (i == cord) {
            continue;
        }

        //we are blocked, handle capture spaces in other method
        if (boardStr.at(i) != '0') {
            break;
        }

        basicMoves.push_back(i);
    }

    bool initiallyOnRS = onRightSideOfBoard(cord);
    i = cord;
    if (initiallyOnRS) {
        i--;
    };
    //left direction, stop when we wrap back to the right side
    for (; !onRightSideOfBoard(i) && board->inRange(i, 0, 63); i--)
    {
        //the spot where we started is not valid
        if (i == cord) {
            continue;
        }

        //we are blocked, handle capture spaces in other method
        if (boardStr.at(i) != '0') {
            break;
        }

        basicMoves.push_back(i);
    }
    
    //upward direction
    for (int i = cord; board->inRange(i, 0, 63); i-=8)
    {
        if (i == cord) {
            continue;
        }

        if (boardStr.at(i) != '0') {
            break;
        }

        basicMoves.push_back(i);
    }

    //downward direction
    for (int i = cord; board->inRange(i, 0, 63); i+=8)
    {
        if (i == cord) {
            continue;
        }

        if (boardStr.at(i) != '0') {
            break;
        }

        basicMoves.push_back(i);
    }
    
    
    return basicMoves;
}

std::vector<int> Rook::getMyCapturableSpaces(std::string boardToCheck) {
    std::vector<int> capturableMoves;
    //std::string boardStr = *board->getBoardStr();
    std::string boardStr = boardToCheck;

    if (this->pieceIcon == 'R') {
        //right direction, go to the right until it wraps back to the left
        bool initiallyOnLS = onLeftSideOfBoard(cord);
        int i = cord;
        if (initiallyOnLS) {
            i++;
        };
        for (; !onLeftSideOfBoard(i) && board->inRange(i, 0, 63); i++)
        {
            //the spot where we started is not valid
            if (i == cord) {
                continue;
            }

            //we hit something
            if (boardStr.at(i) != '0') {
                //only if it is on the opponents team do we add it
                if (islower(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }

                //either way, we hit something, so we are still done.
                break;
            }
        }

        bool initiallyOnRS = onRightSideOfBoard(cord);
        i = cord;
        if (initiallyOnRS) {
            i--;
        };
        //left direction, stop when we wrap back to the right side
        for (; !onRightSideOfBoard(i) && board->inRange(i, 0, 63); i--)
        {
            //the spot where we started is not valid
            if (i == cord) {
                continue;
            }
            
            //we hit something
            if (boardStr.at(i) != '0') {
                //only if it is on the opponents team do we add it
                if (islower(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }

                //either way, we hit something, so we are still done.
                break;
            }
        }
        
        //upward direction
        for (int i = cord; board->inRange(i, 0, 63); i-=8)
        {
            if (i == cord) {
                continue;
            }

            //we hit something
            if (boardStr.at(i) != '0') {
                //only if it is on the opponents team do we add it
                if (islower(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }

                //either way, we hit something, so we are still done.
                break;
            }
        }

        //downward direction
        for (int i = cord; board->inRange(i, 0, 63); i+=8)
        {
            if (i == cord) {
                continue;
            }

            //we hit something
            if (boardStr.at(i) != '0') {
                //only if it is on the opponents team do we add it
                if (islower(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }

                //either way, we hit something, so we are still done.
                break;
            }
        }
    }


    if (this->pieceIcon == 'r') {
        //right direction, go to the right until it wraps back to the left
        bool initiallyOnLS = onLeftSideOfBoard(cord);
        int i = cord;
        if (initiallyOnLS) {
            i++;
        };
        for (; !onLeftSideOfBoard(i) && board->inRange(i, 0, 63); i++)
        {
            //the spot where we started is not valid
            if (i == cord) {
                continue;
            }

            //we hit something
            if (boardStr.at(i) != '0') {
                //only if it is on the opponents team do we add it
                if (isupper(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }

                //either way, we hit something, so we are still done.
                break;
            }
        }

        bool initiallyOnRS = onRightSideOfBoard(cord);
        i = cord;
        if (initiallyOnRS) {
            i--;
        };
        //left direction, stop when we wrap back to the right side
        for (; !onRightSideOfBoard(i) && board->inRange(i, 0, 63); i--)
        {
            //the spot where we started is not valid
            if (i == cord) {
                continue;
            }
            
            //we hit something
            if (boardStr.at(i) != '0') {
                //only if it is on the opponents team do we add it
                if (isupper(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }

                //either way, we hit something, so we are still done.
                break;
            }
        }
        
        //upward direction
        for (int i = cord; board->inRange(i, 0, 63); i-=8)
        {
            if (i == cord) {
                continue;
            }

            //we hit something
            if (boardStr.at(i) != '0') {
                //only if it is on the opponents team do we add it
                if (isupper(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }

                //either way, we hit something, so we are still done.
                break;
            }
        }

        //downward direction
        for (int i = cord; board->inRange(i, 0, 63); i+=8)
        {
            if (i == cord) {
                continue;
            }

            //we hit something
            if (boardStr.at(i) != '0') {
                //only if it is on the opponents team do we add it
                if (isupper(boardStr.at(i))) {
                    capturableMoves.push_back(i);
                }

                //either way, we hit something, so we are still done.
                break;
            }
        }
    }
    
    return capturableMoves;
}

std::vector<int> Rook::getSpecialMoves() {
    std::vector<int> specialMoves;
    return specialMoves;
}

void Rook::preformSpecialMove(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy) {
    
}

std::vector<int> Rook::getValidMoves() {
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