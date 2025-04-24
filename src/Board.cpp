#include "Board.h"

Board::Board()
{
    boardString = "0000000000000000000000000000000000000000000000000000000000000000";
    // testPawn1 = Pawn('p', 50);
    // testPawn2 = Pawn('P', 41);
    piecesCurrentlyOnBoard = {testPawn1, testPawn2};
}

Board::~Board()
{
}

void Board::printBoard() {
    for(int i = 0; i < 65; i++) {
        if (!(i%8) && (i != 0)) {
            printf("\n");
        }
        printf("%c ", boardString[i]);
    }
}

void Board::overWriteBoardAtLocation(int cord, char thingOnSpace) {
    boardString[cord] = thingOnSpace;
}

std::vector<Piece>* Board::getPiecesCurrentlyOnBoard() {
    return &piecesCurrentlyOnBoard;
}