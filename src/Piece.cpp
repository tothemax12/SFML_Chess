#include "Piece.h"

Piece::Piece(char pieceIcon, int cord)
{
    this->pieceIcon = pieceIcon;
    this->cord = cord;
}

Piece::Piece()
{
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

std::vector<int>* Piece::removeLocationsNotOnBoard(std::vector<int>* validMoves) {
    //remove vals off board
    for(int i = 0; i < validMoves->size(); i++) {
        if (!(validMoves->at(i) >= 0 && validMoves->at(i) <= 64)) {
            validMoves->erase(validMoves->begin()+i);
        }
    }

    return validMoves;
}

std::vector<int>* Piece::getCapturableSpaces() {
    return nullptr;
}

Piece* Piece::getPiecesICanCapture(std::vector<Piece>* piecesCurrentlyOnBoard) {
        //need to account for the diagonal spaces and special move, not just getBasicMoves in this case
        std::vector<int>* validMoves = getCapturableSpaces();
        std::vector<Piece>* piecesOnBoard = piecesCurrentlyOnBoard;
        Piece* arrayOfPiecesWeCanCapture = new Piece[validMoves->size()];
    
        int capturablePieceCount = 0;
        for (int i = 0; i < piecesOnBoard->size(); i++) {
            for (int j = 0; j < validMoves->size(); j++) {
                //we can go to that space, put it in the array
                if (validMoves->at(j) == piecesOnBoard->at(i).cord) {
                    if (
                          (islower(this->pieceIcon) && isupper(piecesOnBoard->at(i).pieceIcon))
                        ||(islower(this->pieceIcon) && isupper(piecesOnBoard->at(i).pieceIcon))
                    ) {
                        arrayOfPiecesWeCanCapture[capturablePieceCount] = piecesOnBoard->at(i);
                        capturablePieceCount++;
                    }
                }
            }
        }
    
        //we are done with this
        delete validMoves;
        
        return arrayOfPiecesWeCanCapture;
}
