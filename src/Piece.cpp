#include "Piece.h"
#include "Board.h"

Piece::Piece(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture) : 
pieceSprite(*pieceTexture)
{
	this->pieceIcon = pieceIcon;
	this->cord = cord;
	this->hasNotMoved = true;
    this->board = board;
    //scale down the piece sprite a bit
    //pieceSprite.setScale({.4, .4});
}

Piece::~Piece()
{
}

std::vector<int>* Piece::getBasicMoves() {
    return nullptr;
}

std::vector<int>* Piece::getValidMoves() {
    return nullptr;
}

//this function is for removing invalid locations from valid locations arr
std::vector<int>* Piece::removeLocationsNotOnBoard(std::vector<int>* validMoves) {
    //remove vals off board
    for(int i = validMoves->size()-1; i > -1; i--) {
        if (!(validMoves->at(i) >= 0 && validMoves->at(i) <= 63)) {
            validMoves->erase(validMoves->begin()+i);
        }
    }

    return validMoves;
}

std::vector<int>* Piece::getMyCapturableSpaces(std::string boardToCheck) {
    return nullptr;
}

std::vector<int>* Piece::getSpecialMoves() {
    return nullptr;
}

void Piece::preformSpecialMove(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy) {

}


//modifies the pointed to board based on the move index
//also need to modify the pieceVector as then we can get the capturable moves based on that
void Piece::movePiece(int moveIndex, std::string* boardStrToChange, std::vector<Piece*>* pieceVectorToChange, bool isCopy) {
    //positive cord, just a normal move piece or move and capture a piece
    if (moveIndex >= 0) {
        //no capture involved, just moving the piece
        if (boardStrToChange->at(moveIndex) == '0') {
            boardStrToChange->at(this->cord) = '0';
            boardStrToChange->at(moveIndex) = this->pieceIcon;


            if (isCopy) {//we are modifying the copy to preform the move
                for (int i = 0; i < pieceVectorToChange->size(); i++)
                {
                 if (pieceVectorToChange->at(i)->cord == this->cord) {
                    pieceVectorToChange->at(i)->cord = moveIndex;
                 }   
                }
            } else {//real move, just change the real thing

                //also need to update the piece vect
                //but if I just change me, the piece vector points to me,
                //so it will have the correct information
                this->cord = moveIndex;
                
                //can't forget to update the sprites location as well
                int* screenCords = board->convertStrIndexToBoardCords(this->cord);
                this->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});

                //remember to update the pieces stuff
                this->hasNotMoved = false;

                //if this piece is a pawn and we just moved to the end of
                //the board, we need to promote the pawn, I think we can do it here
                if ((this->pieceIcon == 'P' && board->inRange(this->cord, 0, 7)) || (this->pieceIcon == 'p' && (board->inRange(this->cord, 56, 63)))) {
                    board->pawnPromotionState.drawLoop(this, board->getBoardStr());
                }
            }

        }  else if (boardStrToChange->at(moveIndex) != '0') {
            //handling if a piece is going to capture another piece
            boardStrToChange->at(this->cord) = '0';
            boardStrToChange->at(moveIndex) = this->pieceIcon;

            //same as just moving, but we need to remove the piece that was
            //captured from the piece vect
            std::vector<Piece*>* piecesCurrentlyOnBoard = pieceVectorToChange;
            for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++)
            {
                if (piecesCurrentlyOnBoard->at(i)->cord == moveIndex) {
                    piecesCurrentlyOnBoard->erase(piecesCurrentlyOnBoard->begin()+i);
                    break;
                }
            }

            if (isCopy) {//we are modifying the copy to preform the move
                for (int i = 0; i < pieceVectorToChange->size(); i++)
                {
                 if (pieceVectorToChange->at(i)->cord == this->cord) {
                    pieceVectorToChange->at(i)->cord = moveIndex;
                 }   
                }
            } else {
                //also need to update the piece vect
                //but if I just change me, the piece vector points to me,
                //so it will have the correct information
                this->cord = moveIndex;
                
                
                //can't forget to update the sprites location as well
                int* screenCords = board->convertStrIndexToBoardCords(this->cord);
                this->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});


                //remember to update the pieces stuff
                this->hasNotMoved = false;

                //if this piece is a pawn and we just moved to the end of
                //the board, we need to promote the pawn, I think we can do it here
                if ((this->pieceIcon == 'P' && board->inRange(this->cord, 0, 7)) || (this->pieceIcon == 'p' && (board->inRange(this->cord, 56, 63)))) {
                    board->pawnPromotionState.drawLoop(this, board->getBoardStr());
                }
            }
        }
    } else {
        //move was < 0, handle special move seperately
        this->preformSpecialMove(moveIndex, boardStrToChange, pieceVectorToChange, isCopy);
        board->printBoard(*board->getBoardStr());
        printf("\n");
    }
}

bool Piece::isMoveValid(int moveCord, std::string whichTeam) {
    bool isKingInDangerUhOh = false;
    std::vector<Piece*>* copyPieceVect;
    std::string myOpponent = getOpponentsTeamString();

    //update the copy board string to the current games board so we can try
    //the move out and validate it
    //this should modify the board classes strings via pointer
    board->setBoardCopyStr(*board->getBoardStr());

    //init the copy piece vect based on the copyStr
    copyPieceVect = board->initializePiecesOnBoardBasedOnBoardString(*board->getBoardCopyStr());
    board->setCopyPieceVect(copyPieceVect);

    //move the piece and modify the copy board
    movePiece(moveCord, board->getBoardCopyStr(), copyPieceVect, true);

    // std::cout << "Board str: \n";
    // board->printBoard(*board->getBoardStr());
    // printf("\n");

    // std::cout << "Board Copy str: \n";
    // board->printBoard(*board->getBoardCopyStr());
    // printf("\n");

    //get all the opponent teams capturable spaces
    //based on that copy board after move was made
    std::vector<int>* allCapturableSpotsForOpponentAfterMove = board->getAllCapturableSpacesForAGivenSide(myOpponent, *board->getBoardCopyStr(), board->getCopyPieceVect());

    // std::cout << "\ncapturable spaces on copy board after move:  " << "\n";
    // for (int i = 0; i < allCapturableSpotsForOpponentAfterMove->size(); i++)
    // {
    //     std::cout << allCapturableSpotsForOpponentAfterMove->at(i);
    // }
    // printf("\n");

    //need to see if the king is in that list
    isKingInDangerUhOh = board->isKingCapturable(allCapturableSpotsForOpponentAfterMove, myOpponent, *board->getBoardCopyStr());
    
    //std::cout << "king in danger: " << isKingInDangerUhOh << "\n";
    //std::cout << "when I go to: " << moveCord << "\n";

    return isKingInDangerUhOh;
}

bool Piece::onRightSideOfBoard(int cord) {
    return (cord == 7 || cord == 15 || cord == 23 || cord == 31 || cord == 39 || cord == 47 || cord == 55 || cord == 63);
}

bool Piece::onLeftSideOfBoard(int cord) {
    return (cord == 0 || !(cord % 8));
}

std::string Piece::getMyTeamString() {
    std::string myTeam;
    return islower(this->pieceIcon) ? myTeam = "Black" : myTeam = "White";
}

std::string Piece::getOpponentsTeamString() {
    std::string opponent;
    return islower(this->pieceIcon) ? opponent = "White" : opponent = "Black";
}

bool Piece::opponentIsOnSpace(char boardSpace) {
    bool isOpponent = false;

    if (boardSpace != '0' && isupper(this->pieceIcon) && islower(boardSpace)) {
        isOpponent = true;
    }

    if (boardSpace != '0' && islower(this->pieceIcon) && isupper(boardSpace)) {
        isOpponent = true;
    }

    return isOpponent;
}