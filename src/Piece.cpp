#include "Piece.h"

Piece::Piece(char pieceIcon, int cord, sf::Texture* pieceTexture, std::string* currentBoardString) : pieceSprite(*pieceTexture)
{
	this->pieceIcon = pieceIcon;
	this->cord = cord;
	this->isFirstTurn = true;
    this->currentBoardString = currentBoardString;

    //set the cord based on the index in the string arr
    int* screenCords = convertStrIndexToBoardCords(cord);
    pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
    
    //scale down the piece sprite a bit
    pieceSprite.setScale({.4, .4});

    delete screenCords;
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

int* Piece::convertStrIndexToBoardCords(int stringIdx) {
    //0->63
	//spit out (x, y)
	
	int x = 0;
	int y = 0;

	for (int i = 0; i < 63; i++) {
		
		if (i == stringIdx) {
			break;
		}
		
		x += 80;
		
		if (x > 560) {
			x = 0;
			y += 80;
		}
	}
	int* cords = new int[2];
	cords[0] = x;
	cords[1] = y;
	return cords;
}
