#include "Game.h"
#include <iostream>

Game::Game()
{
    board = "0000000000000000000000000000000000000000000000000000000000000000";
    testPawn1 = Pawn('p', 50);
    testPawn2 = Pawn('P', 41);
    piecesCurrentlyOnBoard = {testPawn1, testPawn2};
}

Game::~Game()
{
}

void Game::printBoard() {
    for(int i = 0; i < 65; i++) {
        if (!(i%8) && (i != 0)) {
            printf("\n");
        }
        printf("%c ", board[i]);
    }
}

void Game::overWriteBoardAtLocation(int cord, char thingOnSpace) {
    board[cord] = thingOnSpace;
}

std::vector<Piece>* Game::getPiecesCurrentlyOnBoard() {
    return &piecesCurrentlyOnBoard;
}
