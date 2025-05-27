#include "King.h"
#include "Board.h"

King::King(Board* board, char pieceIcon, int cord, sf::Texture* pieceTexture) : 
Piece(board, pieceIcon, cord, pieceTexture)
{

}

King::~King() {

}

std::vector<int> King::getBasicMoves() {
    std::vector<int> basicMoves;
    std::string boardStr = *board->getBoardStr();

    //begin with assuming all the spots are good
    //row above king
    basicMoves.push_back(cord-7);
    basicMoves.push_back(cord-8);
    basicMoves.push_back(cord-9);
    
    //left and right of king
    basicMoves.push_back(cord-1);
    basicMoves.push_back(cord+1);

    //row below king
    basicMoves.push_back(cord+7);
    basicMoves.push_back(cord+8);
    basicMoves.push_back(cord+9);

    //remove them based on where the middle cord is
    if(onLeftSideOfBoard(cord)) {
        //cord-9
        basicMoves.at(2) = -1;
        //cord-1
        basicMoves.at(3) = -1;
        //cord+7
        basicMoves.at(5) = -1;
    }

    if(onRightSideOfBoard(cord)) {
        //cord-7 
        basicMoves.at(0) = -1;
        //cord+1
        basicMoves.at(4) = -1;
        //cord+9
        basicMoves.at(7) = -1;
    }

    //middle cord on top row, remove the top row
    if (board->inRange(cord, 0, 7)) {
        //cord-7
        basicMoves.at(0) = -1;
        //cord-8
        basicMoves.at(1) = -1;
        //cord-9
        basicMoves.at(2) = -1;
    }

    //middle cord on bottom row
    if (board->inRange(cord, 56, 63)) {
        //cord+7
        basicMoves.at(5) = -1;
        //cord+8
        basicMoves.at(6) = -1;
        //cord+9
        basicMoves.at(7) = -1;
    }

    basicMoves = removeLocationsNotOnBoard(basicMoves);

    for (int i = 0; i < basicMoves.size(); i++)
    {
        //if there is a piece on a move we can make, throw
        //it out. that is for capturable spaces to check
        if (boardStr[basicMoves.at(i)] != '0') {
            basicMoves.at(i) = -1;
        }
    }
    
    basicMoves = removeLocationsNotOnBoard(basicMoves);

    return basicMoves;
}

std::vector<int> King::getMyCapturableSpaces(std::string boardToCheck) {
    //we get the basic moves which are just valid spaces all around the king, it's not concerned
    //with if there is a piece in those spots
    std::vector<int> capturableSpaces;
    std::string myTeam = getMyTeamString();
    

    //begin with assuming all the spots are good
    //row above king
    capturableSpaces.push_back(cord-7);
    capturableSpaces.push_back(cord-8);
    capturableSpaces.push_back(cord-9);
    
    //left and right of king
    capturableSpaces.push_back(cord-1);
    capturableSpaces.push_back(cord+1);

    //row below king
    capturableSpaces.push_back(cord+7);
    capturableSpaces.push_back(cord+8);
    capturableSpaces.push_back(cord+9);

    //remove them based on where the middle cord is
    if(onLeftSideOfBoard(cord)) {
        //cord-9
        capturableSpaces.at(2) = -1;
        //cord-1
        capturableSpaces.at(3) = -1;
        //cord+7
        capturableSpaces.at(5) = -1;
    }

    if(onRightSideOfBoard(cord)) {
        //cord-7 
        capturableSpaces.at(0) = -1;
        //cord+1
        capturableSpaces.at(4) = -1;
        //cord+9
        capturableSpaces.at(7) = -1;
    }

    //middle cord on top row, remove the top row
    if (board->inRange(cord, 0, 7)) {
        //cord-7
        capturableSpaces.at(0) = -1;
        //cord-8
        capturableSpaces.at(1) = -1;
        //cord-9
        capturableSpaces.at(2) = -1;
    }

    //middle cord on bottom row
    if (board->inRange(cord, 56, 63)) {
        //cord+7
        capturableSpaces.at(5) = -1;
        //cord+8
        capturableSpaces.at(6) = -1;
        //cord+9
        capturableSpaces.at(7) = -1;
    }

    capturableSpaces = removeLocationsNotOnBoard(capturableSpaces);

    for (int i = 0; i < capturableSpaces.size(); i++)
    {
        //we do not care about empty spaces here
        if(boardToCheck[capturableSpaces.at(i)] == '0') {
            capturableSpaces.at(i) = -1;
        }
    }    

    capturableSpaces = removeLocationsNotOnBoard(capturableSpaces);

    for (int i = 0; i < capturableSpaces.size(); i++)
    {
        //if there is a piece on a move we can make
        if (boardToCheck[capturableSpaces.at(i)] != '0') {
            if (myTeam == "White") {
                if (!islower(boardToCheck[capturableSpaces.at(i)])) {
                    //this says, if, from the spots I collected around the me, a piece is on the opposite side as me, do nothing.

                    //what I meant to say was, if from the spot I collected around me, a piece is on my team, throw it out
                    capturableSpaces.at(i) = -1;
                }
            } else if (myTeam == "Black") {
                if (!isupper(boardToCheck[capturableSpaces.at(i)])) {
                    capturableSpaces.at(i) = -1;
                }
            }
        }
    }

    capturableSpaces = removeLocationsNotOnBoard(capturableSpaces);
    
    // printf("capturable spaces: \n");
    // for (int i = 0; i < capturableSpaces.size(); i++)
    // {
    //     std::cout << capturableSpaces.at(i) << "\n";
    //     //printf("valid moves size: %d \n", validMoves.size());
    //     //validMoves.emplace_back(capturableSpaces.at(i));
    //     //printf("valid moves size: %d \n", validMoves.size());
    // }
    // printf("end of capturable spaces\n");
    

    return capturableSpaces;
}

//determines if the king can castle and returns the negative of the cords it will
//end up at
std::vector<int> King::getSpecialMoves() {
    //check if it can castle

    //the king can castle to the left or right if...
    //1. the king and the rook it is going to castle with
    //haven't moved. 
    //2. there are no pieces between the king and the rook
    //it is going to castle with

    std::vector<int> specialMoves;
    std::string boardStr = *board->getBoardStr();
    std::vector<Piece*> pieceVect = *board->getPiecesCurrentlyOnBoard();
    bool canCastleLeft = false;
    bool canCastleRight = false;

    specialMoves.push_back(-1);
    specialMoves.push_back(-1);

    // bool correctIcon;
    // bool spacesAreEmpty;
    // bool pieceIsRook;
    // bool pieceIsFourToTheLeft;
    // bool rookHasNotMoved;

    //if we haven't moved
    if (this->hasNotMoved) {
        for (int i = 0; i < pieceVect.size(); i++) {

            // correctIcon = pieceVect.at(i)->pieceIcon == 'R';
            // pieceIsFourToTheLeft = pieceVect.at(i)->cord == this->cord-4;
            // rookHasNotMoved = pieceVect.at(i)->hasNotMoved;

            if (
                isupper(pieceVect.at(i)->pieceIcon) &&
                pieceVect.at(i)->pieceIcon == 'R' && 
                pieceVect.at(i)->cord == this->cord-4 && 
                pieceVect.at(i)->hasNotMoved &&
                boardStr.at(this->cord-1) == '0' &&
                boardStr.at(this->cord-2) == '0' &&
                boardStr.at(this->cord-3) == '0') {

                canCastleLeft = true;
            }

            if (
                isupper(pieceVect.at(i)->pieceIcon) &&
                pieceVect.at(i)->pieceIcon == 'R' && 
                pieceVect.at(i)->cord == this->cord+3 && 
                pieceVect.at(i)->hasNotMoved &&
                boardStr.at(this->cord+1) == '0' &&
                boardStr.at(this->cord+2) == '0') {
        
                canCastleRight = true;
            }

            if (
                islower(pieceVect.at(i)->pieceIcon) &&
                pieceVect.at(i)->pieceIcon == 'r' && 
                pieceVect.at(i)->cord == this->cord-4 && 
                pieceVect.at(i)->hasNotMoved &&
                boardStr.at(this->cord-1) == '0' &&
                boardStr.at(this->cord-2) == '0' &&
                boardStr.at(this->cord-3) == '0') {

                canCastleLeft = true;
            }

            if (
                islower(pieceVect.at(i)->pieceIcon) &&
                pieceVect.at(i)->pieceIcon == 'r' && 
                pieceVect.at(i)->cord == this->cord+3 && 
                pieceVect.at(i)->hasNotMoved &&
                boardStr.at(this->cord+1) == '0' &&
                boardStr.at(this->cord+2) == '0') {
        
                canCastleRight = true;
            }
        }
    
        //these work for black or white king
        if (canCastleLeft) {
            specialMoves.at(0) = -1*(this->cord - 2);
        }
        
        if (canCastleRight) {
            specialMoves.at(1) = -1*(this->cord + 2);
        }

        //need to process the locations a bit different here
        //we will mark the specials by -cord to indicate that a special move will
        //be preformed
        for (int i = specialMoves.size()-1; i > -1; i--)
        {
            if (specialMoves.at(i) == -1) {
                specialMoves.erase(specialMoves.begin()+i);
            }
        }
    }

    for (int i = specialMoves.size()-1; i > -1; i--)
    {
        if (specialMoves.at(i) == -1) {
            specialMoves.erase(specialMoves.begin()+i);
        }
    }

    return specialMoves;
}

void King::preformSpecialMove(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy) {
    int realMoveCord = -1*moveIndex;
    std::string myTeam = getMyTeamString();

    Piece* kingToUpdate;
    Piece* rookToUpdate;
    Piece* currentPiece;
    std::array<int, 2> screenCords;
    bool leftCastle = false;
    bool rightCastle = false;

    if (realMoveCord == 62 || realMoveCord == 6) {
        rightCastle = true;
    }

    if (realMoveCord == 58 || realMoveCord == 2) {
        leftCastle = true;
    }

    //only can move to 62 or 58 for white and for black
        //modifying the string-----------------------------

        //remove king
        boardStrToChange->at(this->cord) = '0';

        if (rightCastle) {//preform right castle
            //move king
            boardStrToChange->at(this->cord+2) = this->pieceIcon;
        } else if (leftCastle) {
            boardStrToChange->at(this->cord-2) = this->pieceIcon;
        }

        //put rook in new spot
        if (myTeam == "White") {
            if (rightCastle) {
                boardStrToChange->at(this->cord+1) = 'R';
            } else if (leftCastle) {
                boardStrToChange->at(this->cord-1) = 'R';
            }
        } else {
            if (rightCastle) {
                boardStrToChange->at(this->cord+1) = 'r';
            } else if (leftCastle) {
                boardStrToChange->at(this->cord-1) = 'r';   
            }
        }

        //overwrite old rook spot
        if (rightCastle) {
            boardStrToChange->at(this->cord+3) = '0';
        } else if (leftCastle) {
            boardStrToChange->at(this->cord-4) = '0';
        }
        // board->printBoard(*boardStrToChange);
        // printf("\n");
        //end of string modification-----------------------------------------------------


        //update the king and rook cord/sprites------------------------------------------
        for (int i = 0; i < pieceVectorToChange->size(); i++)
        {
            currentPiece = pieceVectorToChange->at(i);
            if (currentPiece->cord == this->cord) {
                kingToUpdate = currentPiece;
            }
            
            if (rightCastle) {
                if (currentPiece->cord == this->cord+3) {
                    rookToUpdate = currentPiece;
                }
            } else if (leftCastle) {
                if (currentPiece->cord == this->cord-4) {
                    rookToUpdate = currentPiece;
                }
            }
        }
        
        if (rightCastle) {
            rookToUpdate->cord = this->cord + 1;
        } else if (leftCastle) {
            rookToUpdate->cord = this->cord - 1;
        }
        screenCords = board->convertStrIndexToBoardCords(rookToUpdate->cord);
        rookToUpdate->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
        rookToUpdate->hasNotMoved = false;

        if (rightCastle) {
            kingToUpdate->cord = this->cord + 2;
        } else if (leftCastle) {
            kingToUpdate->cord = this->cord - 2;
        }
        screenCords = board->convertStrIndexToBoardCords(kingToUpdate->cord);
        kingToUpdate->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
        kingToUpdate->hasNotMoved = false;
        //end of sprite updating----------------------------------------------------------
}

std::vector<int> King::getValidMoves() {
    std::vector<int> validMoves;
    std::vector<int> basicMoves = getBasicMoves();
    std::vector<int> capturableSpaces = getMyCapturableSpaces(*board->getBoardStr());    
    std::vector<int> specialMoves = getSpecialMoves();
    
    bool isKingInDangerIfMoveWasPreformed = false;

    for (int i = 0; i < basicMoves.size(); i++)
    {
        validMoves.emplace_back(basicMoves.at(i));        
    }
    
    for (int i = 0; i < capturableSpaces.size(); i++)
    {
        validMoves.emplace_back(capturableSpaces.at(i));
    }

    printf("special moves:\n");
    for (int i = 0; i < specialMoves.size(); i++)
    {
        printf("%d", specialMoves.at(i));
        validMoves.emplace_back(specialMoves.at(i));
    }
    printf("\n\n");


    //need to remove the spaces that put the king in danger. that is not valid
    for (int i = validMoves.size()-1; i > -1; i--)
    {
        isKingInDangerIfMoveWasPreformed = isMoveValid(validMoves.at(i), getMyTeamString());
        if (isKingInDangerIfMoveWasPreformed) {
            validMoves.erase(validMoves.begin()+i);
        }
    }

    printf("total valid moves:\n");
    for (int i = 0; i < validMoves.size(); i++)
    {
        printf("%d ", validMoves.at(i));
    }
    printf("\n\n");

    return validMoves;
}