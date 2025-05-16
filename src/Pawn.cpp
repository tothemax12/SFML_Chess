#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(Board *board, char pieceIcon, int cord, sf::Texture* pieceTexture) : 
Piece(board, pieceIcon, cord, pieceTexture)
{

}

Pawn::~Pawn()
{
}

std::vector<int>* Pawn::getBasicMoves() {
    std::vector<int>* validMoves = new std::vector<int>;
    std::string currentBoard = *board->getBoardCopyStr();

    bool isWhitePiece = isupper(this->pieceIcon);
    int offset = 8;
    if (isWhitePiece) {
        offset = -8;
    }
    
    if (isFirstTurn) {
        validMoves->push_back(cord+offset);
        validMoves->push_back(cord+2*offset);
    } else {
        validMoves->push_back(cord+offset);
        validMoves->push_back(-1);
    }


    //remove the spaces that are blocked by an opponent in front of the pawn
    //(can't capture forward)
    //std::string currentBoard = *currentBoardString;
    // for (int i = 0; i < validMoves->size(); i++) {
    //     if (currentBoard[validMoves->at(i)] != '0') {
    //         //also there is a piece in front of us, we can't capture that
    //         for(int j = i; j < validMoves->size(); j++) {
    //             validMoves->at(j) = -1;
    //         }
    //         //if we hit a piece we can't go beyond that piece
    //         break;
    //     }
    // }

    //remove the spaces that are blocked by an opponent in front of the pawn
    //case 1: both spaces are not on the board
    //do not need to be concerned about pieces blocking us
    if (!board->inRange(cord+offset, 0, 63) && !board->inRange(cord+2*offset, 0, 63)) {
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

    } else if (board->inRange(cord+offset, 0, 63) && !board->inRange(cord+2*offset, 0, 63)) {
        //if only the second above is off the board, check if first spot blocked
        int spotInFrontOfPawn = cord+offset;
        if (board->getBoardStr()->at(spotInFrontOfPawn) != '0') {
            //if the next spot in front of pawn
            //is taken, then throw out all the basic moves
            //we are blocked
    
            validMoves->at(0) = -1;
            validMoves->at(1) = -1;
        }
        validMoves = removeLocationsNotOnBoard(validMoves);
    } else if (board->inRange(cord+offset, 0, 63) && board->inRange(cord+2*offset, 0, 63)) {
        int spotInFrontOfPawn = cord+offset;
        int secondSpotInFrontOfPawn = cord+2*offset;
        if (board->getBoardStr()->at(spotInFrontOfPawn) != '0') {
            //if the next spot in front of pawn
            //is taken, then throw out all the basic moves
            //we are blocked
    
            validMoves->at(0) = -1;
            validMoves->at(1) = -1;
        }
    
        if (board->getBoardStr()->at(secondSpotInFrontOfPawn) != '0') {
            //only the second spot in front of
            //pawn is
            validMoves->at(1) = -1;
        }
        validMoves = removeLocationsNotOnBoard(validMoves);
    }
    return validMoves;
}

//getCapturableSpaces takes in a board string to be able to check other boards if a move to were
//potentially be made
std::vector<int>* Pawn::getMyCapturableSpaces(std::string boardToCheck) {
    std::vector<int>* capturableSpaces = new std::vector<int>;
    if (pieceIcon == 'P') {
        //ignore the right capturable square of pawn if on side of board
        if (!(cord == 7 || cord == 15 || cord == 23 || cord == 31 || cord == 39 || cord == 47 || cord == 55 || cord == 63)) {
            //if it's also a white piece ignore it
            if (((cord-7) >= 0 && (cord-7) <= 63) && !isupper(board->getBoardStr()->at(cord-7))) {
                capturableSpaces->push_back(cord-7);
            }
        }
        //if a pawn is on the right side of board, ignore the left one
        if (cord != 0 && cord % 8) {
            if (((cord-9) >= 0 && (cord-9) <= 63) && !isupper(board->getBoardStr()->at(cord-9))) {
                capturableSpaces->push_back(cord-9);
            }
        }
    } else {
        //if they are on the sides, do not add the val that goes off the board
        if (cord != 0 && cord % 8) {
            if (((cord+7) >= 0 && (cord+7) <= 63) && isupper(board->getBoardStr()->at(cord+7))) {
                capturableSpaces->push_back(cord+7);
            }
        }
            //if black pawn is on the right side of board, ignore the right capturable space cord
        if (!(cord == 7 || cord == 15 || cord == 23 || cord == 31 || cord == 39 || cord == 47 || cord == 55 || cord == 63)) {
            if (((cord+9) >= 0 && (cord+9) <= 63) && isupper(board->getBoardStr()->at(cord+9))) {
                capturableSpaces->push_back(cord+9);
            }
        }
    }

    //can't capture stuff if nothing is there
    std::string currentBoard = *board->getBoardStr();
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

bool Pawn::checkIfSpecialMoveCanBePreformed() {
    //en passant can be preformed if...
    //-capturing piece has moved exactly 3 spaces forward
        //keep a count of spaces the pawn moved 

    //-captured pawn must have moved 2 spaces on it's first turn,
    //landing right next to the capturing pawn
        //track a bool if they chose to move 2 spaces
        //captured pawn must be directly to the left or right of pawn

    //-the en passant must be preformed by capturing pawn on the 
    //turn right after the captured pawn moved
        //???

    return false;
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
    std::vector<int>* capturableSpaces = getMyCapturableSpaces(*board->getBoardStr());
    bool isKingInDangerIfMoveWasPreformed = false;

    //first check if we can even preform the special move,
    //if we can, than calculate that space and put a negative on it
    //to indicate it is a special move
    

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
    for (int i = validMoves->size()-1; i > -1; i--)
    {
        isKingInDangerIfMoveWasPreformed = isMoveValid(validMoves->at(i), getMyTeamString());
        if (isKingInDangerIfMoveWasPreformed) {
            validMoves->erase(validMoves->begin()+i);
        }
    }
    
    return validMoves;
}

// void Pawn::movePiece(int moveIndex, bool testMoveOnCopyBoard, std::string* boardStrToChange, std::vector<Piece*>* piecesVectToChange) {
//     //first handling checking the moves for validity
//     if (testMoveOnCopyBoard) {
//         //positive cord, just a normal move piece or move and capture a piece
//         if (moveIndex >= 0) {
//             //no capture involved, just moving the piece
//             if (boardStrToChange->at(moveIndex) == '0') {
//                 overWriteBoardStrAtIndex(boardStrToChange, moveIndex, this->pieceIcon);
//             } else {
//                 //for capturing a piece, just need to move the piece on the string and then remove the piece
//                 //from the piece array
//                 removePieceFromPieceVector(piecesVectToChange, moveIndex);
//                 overWriteBoardStrAtIndex(boardStrToChange, moveIndex, this->pieceIcon);
//             }
//         } else {//handle special move

//         }
//     }
// }