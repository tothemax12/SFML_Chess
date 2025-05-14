#include "Piece.h"
#include "Board.h"

Piece::Piece(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture) : 
pieceSprite(*pieceTexture)
{
	this->pieceIcon = pieceIcon;
	this->cord = cord;
	this->isFirstTurn = true;
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

std::vector<int>* Piece::getMyCapturableSpaces() {
    return nullptr;
}


//modifies the pointed to board based on the move index
void Piece::movePiece(int moveIndex, std::string* boardStrToChange) {
    //positive cord, just a normal move piece or move and capture a piece
    //if (moveIndex >= 0) {
        //no capture involved, just moving the piece
        if (boardStrToChange->at(moveIndex) == '0') {
            boardStrToChange->at(this->cord) = '0';
            boardStrToChange->at(moveIndex) = this->pieceIcon;

            //also need to update the piece vect
            //but if I just change me, the piece vector points to me,
            //so it will have the correct information
            this->cord = moveIndex;
            
            //can't forget to update the sprites location as well
            int* screenCords = board->convertStrIndexToBoardCords(this->cord);
            this->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});            
        } //else {//handle special move

    // }
    //}
}

bool Piece::isMoveValid(int moveCord) {
    bool isKingInDangerUhOh = false;

    //update the copy board string to the current games board so we can try
    //the move out and validate it
    //this should modify the board classes strings via pointer
    board->setBoardCopyStr(*board->getBoardStr());

    //init the copy piece vect based on the copyStr
    board->initializePiecesOnBoardBasedOnBoardString(*board->getBoardCopyStr());

    //move the piece and modify the copy board
    movePiece(moveCord, board->getBoardCopyStr());

    //get all the opponent teams capturable spaces
    //based on that copy board after move was made
    std::vector<int>* allCapturableSpotsForOpponentAfterMove = board->getAllCapturableSpacesForAGivenSide("Black", "Copy");

    //need to see if the king is in that list
    isKingInDangerUhOh = board->isKingCapturable(allCapturableSpotsForOpponentAfterMove, "Black", "Copy");
    
    return isKingInDangerUhOh;
}

bool Piece::onRightSideOfBoard(int cord) {
    return (cord == 7 || cord == 15 || cord == 23 || cord == 31 || cord == 39 || cord == 47 || cord == 55 || cord == 63);
}

bool Piece::onLeftSideOfBoard(int cord) {
    return (cord == 0 || !(cord % 8));
}