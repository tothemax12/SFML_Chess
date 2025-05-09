#include "Piece.h"

Piece::Piece(char pieceIcon, int cord, sf::Texture* pieceTexture, std::string* currentBoardString, std::vector<Piece*>* piecesCurrentlyOnBoard) : 
pieceSprite(*pieceTexture)
{
	this->pieceIcon = pieceIcon;
	this->cord = cord;
	this->isFirstTurn = true;
    this->currentBoardString = currentBoardString;
    this->piecesCurrentlyOnBoard = piecesCurrentlyOnBoard;
    
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

std::vector<int>* Piece::getCapturableSpaces() {
    return nullptr;
}

std::vector<int>* Piece::getAllCapturableSpacesForAGiveSide(std::string sideThatIsCapturingPieces) {
    std::vector<int>* allSpacesOfPiecesThatCanBeCaptured = new std::vector<int>;
    std::vector<int>* currentPiecesCapturableSpaces;
        
    if (sideThatIsCapturingPieces == "White") {
        for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
            //if there is a white piece, get the spaces it is currently able to capture
            if (isupper(piecesCurrentlyOnBoard->at(i)->pieceIcon)) {
                currentPiecesCapturableSpaces = piecesCurrentlyOnBoard->at(i)->getCapturableSpaces();
                for (int j = 0; j < currentPiecesCapturableSpaces->size(); j++)
                {
                    allSpacesOfPiecesThatCanBeCaptured->push_back(currentPiecesCapturableSpaces->at(j));
                }
            }
        }
    } else if (sideThatIsCapturingPieces == "Black") {
        for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
            //if there is a black piece, get the spaces it is currently able to capture
            if (!isupper(piecesCurrentlyOnBoard->at(i)->pieceIcon)) {
                currentPiecesCapturableSpaces = piecesCurrentlyOnBoard->at(i)->getCapturableSpaces();
                for (int j = 0; j < currentPiecesCapturableSpaces->size(); j++)
                {
                    allSpacesOfPiecesThatCanBeCaptured->push_back(currentPiecesCapturableSpaces->at(j));
                }
            }
        }
    }

    return allSpacesOfPiecesThatCanBeCaptured;
}

//returns a pointer to a string containing the icons of all oppnent piece icons that can be captured by a given side
std::string* Piece::getAllPiecesThatCanBeCapturedBySide(std::string sideThatIsCapturingPieces) {
    std::string piecesThatCanBeCaptured = "";
    std::vector<int>* allSpacesOfPiecesThatCanBeCaptured;

    //grab a list of all the spaces on the board that contain pieces that the requested side can capture
    allSpacesOfPiecesThatCanBeCaptured = getAllCapturableSpacesForAGiveSide("White");

    printf("all capturable spaces for white side:\n");
    for (int i = 0; i < allSpacesOfPiecesThatCanBeCaptured->size(); i++)
    {
        printf("%d\n", allSpacesOfPiecesThatCanBeCaptured->at(i));
    }

    allSpacesOfPiecesThatCanBeCaptured = getAllCapturableSpacesForAGiveSide("Black");

    printf("all capturable spaces for white side:\n");
    for (int i = 0; i < allSpacesOfPiecesThatCanBeCaptured->size(); i++)
    {
        printf("%d\n", allSpacesOfPiecesThatCanBeCaptured->at(i));
    }

    return nullptr;
}

std::vector<Piece> Piece::getPiecesICanCapture(std::vector<Piece>* piecesCurrentlyOnBoard) {
        //need to account for the diagonal spaces and special move, not just getBasicMoves in this case
        std::vector<int>* validMoves = getCapturableSpaces();
        std::vector<Piece>* piecesOnBoard = piecesCurrentlyOnBoard;
        //Piece* arrayOfPiecesWeCanCapture = new Piece[validMoves->size()];
        std::vector<Piece> piecesWeCanCapture;

        int capturablePieceCount = 0;
        for (int i = 0; i < piecesOnBoard->size(); i++) {
            for (int j = 0; j < validMoves->size(); j++) {
                //we can go to that space, put it in the array
                if (validMoves->at(j) == piecesOnBoard->at(i).cord) {
                    if (
                          (islower(this->pieceIcon) && isupper(piecesOnBoard->at(i).pieceIcon))
                        ||(islower(this->pieceIcon) && isupper(piecesOnBoard->at(i).pieceIcon))
                    ) {
                        piecesWeCanCapture.emplace_back(piecesOnBoard->at(i));
                        capturablePieceCount++;
                    }
                }
            }
        }
    
        //we are done with this
        delete validMoves;
        
        return piecesWeCanCapture;
}