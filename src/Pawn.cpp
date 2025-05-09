#include "Pawn.h"

Pawn::Pawn(char pieceIcon, int cord, sf::Texture* pieceTexture, std::string* currentBoardString, std::vector<Piece*>* piecesCurrentlyOnBoard) : 
Piece(pieceIcon, cord, pieceTexture, currentBoardString, piecesCurrentlyOnBoard)
{

}

Pawn::~Pawn()
{
}

std::vector<int>* Pawn::getBasicMoves() {
    std::vector<int>* validMoves = new std::vector<int>;
    std::string currentBoard = *currentBoardString;

    bool isWhitePiece = isupper(this->pieceIcon);
    int offset = 8;
    if (isWhitePiece) {
        offset = -1*8;
    }
    
    if (isFirstTurn) {
        validMoves->push_back(cord+offset);
        validMoves->push_back(cord+2*offset);
    } else {
        validMoves->push_back(cord+offset);
    }

    //remove the spaces that are blocked by an opponent in front of the pawn
    //(can't capture forward)
    //std::string currentBoard = *currentBoardString;
    for (int i = 0; i < validMoves->size(); i++) {
        if (currentBoard[validMoves->at(i)] != '0') {
            //also there is a piece in front of us, we can't capture that
            for(int j = i; j < validMoves->size(); j++) {
                validMoves->at(j) = -1;
            }
            //if we hit a piece we can't go beyond that piece
            break;
        }
    }

    printf("valid basic moves:\n");
    for (int i = 0; i < validMoves->size(); i++) {
        printf("%d\n", validMoves->at(i));
    }

    //remove out of bounds spots
    validMoves = removeLocationsNotOnBoard(validMoves);

    printf("valid basic moves:\n");
    for (int i = 0; i < validMoves->size(); i++) {
        printf("%d\n", validMoves->at(i));
    }
    
    return validMoves;
}

std::vector<int>* Pawn::getValidMoves() {
    //brainstorming...
    //also need to confirm they are on the board.
    //okay these are the basic moves, but if any of them put the king
    //in check we need to throw them out.
    //additionally, the pawn can preform a special move, so we
    //also need to account for that.
    std::vector<int>* validMoves = new std::vector<int>;
    std::vector<int>* basicMoves = getBasicMoves();
    std::vector<int>* capturableSpaces = getCapturableSpaces();

    //printf("valid moves size: %d \n", validMoves->size());
    for (int i = 0; i < basicMoves->size(); i++)
    {
        //printf("basic moves size: %d \n", basicMoves->size());
        printf("i: %d \n", i);
        //printf("valid moves size: %d \n", validMoves->size());
        validMoves->emplace_back(basicMoves->at(i));
        //printf("valid moves size: %d \n", validMoves->size());
        
    }
    
    for (int i = 0; i < capturableSpaces->size(); i++)
    {
        //printf("capt spaces size: %d \n", capturableSpaces->size());
        //printf("i: %d \n", i);
        //printf("valid moves size: %d \n", validMoves->size());
        validMoves->emplace_back(capturableSpaces->at(i));
        //printf("valid moves size: %d \n", validMoves->size());
    }

    //need to remove the spaces that put the king in danger. that is not valid

    return validMoves;
}

//getCapturableSpaces takes in a board string to be able to check other boards if a move to were
//potentially be made
std::vector<int>* Pawn::getCapturableSpaces() {
    std::vector<int>* capturableSpaces = new std::vector<int>;
    if (pieceIcon == 'P') {
        //ignore the right capturable square of pawn if on side of board
        if (!(cord == 7 || cord == 15 || cord == 23 || cord == 31 || cord == 39 || cord == 47 || cord == 55 || cord == 63)) {
            //if it's also a white piece ignore it
            if (((cord-7) >= 0 && (cord-7) <= 63) && !isupper(currentBoardString->at(cord-7))) {
                capturableSpaces->push_back(cord-7);
            }
        }
        //if a pawn is on the right side of board, ignore the left one
        if (cord != 0 && cord % 8) {
            if (((cord-9) >= 0 && (cord-9) <= 63) && !isupper(currentBoardString->at(cord-9))) {
                capturableSpaces->push_back(cord-9);
            }
        }
    } else {
        //if they are on the sides, do not add the val that goes off the board
        if (cord != 0 && cord % 8) {
            if (((cord+7) >= 0 && (cord+7) <= 63) && isupper(currentBoardString->at(cord+7))) {
                capturableSpaces->push_back(cord+7);
            }
        }
            //if black pawn is on the right side of board, ignore the right capturable space cord
        if (!(cord == 7 || cord == 15 || cord == 23 || cord == 31 || cord == 39 || cord == 47 || cord == 55 || cord == 63)) {
            if (((cord+9) >= 0 && (cord+9) <= 63) && isupper(currentBoardString->at(cord+9))) {
                capturableSpaces->push_back(cord+9);
            }
        }
    }

    //can't capture stuff if nothing is there
    std::string currentBoard = *currentBoardString;
    for (int i = 0; i < capturableSpaces->size(); i++) {
        if (currentBoard[capturableSpaces->at(i)] == '0') {
            capturableSpaces->at(i) = -1;
        }
    }

    capturableSpaces = removeLocationsNotOnBoard(capturableSpaces);
    
    printf("valid capturable spaces:\n");
    //printf("%c???", currentBoard[38]);
    for (int i = 0; i < capturableSpaces->size(); i++) {
        printf("%d\n", capturableSpaces->at(i));
    }

    return capturableSpaces;
}