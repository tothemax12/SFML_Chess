#include "Game.h"
#include <iostream>

Game::Game(sf::Texture* boardTexture, sf::Texture *wPawnTexture, sf::Texture *bPawnTexture) : 
boardTexture(boardTexture), 
wPawnTexture(wPawnTexture),
bPawnTexture(bPawnTexture), 
board(boardTexture, wPawnTexture, bPawnTexture) 
{
    window = sf::RenderWindow(sf::VideoMode({640, 640}), "SFML works!");
}

Game::~Game()
{
}

//need a visual tool to debug the spaces (validMoves) the pieces can move or I am going
//to go bonkers bananas
void Game::debugValidMoves() {
//I want to be able to display a board with some pieces
//click a piece on the board and have the square that are valid highlighted
    while(true) {
        window.clear();
        board.drawBoard(&window);
        board.drawPiecesCurrentlyOnBoard(&window);
        window.display();
    }
}



void Game::draw() {
    board.printBoard();
    // std::vector<int>* validMoves = board.testPawn1.getValidMoves();

    // printf("valid moves: \n");
    // for (int i = 0; i < validMoves->size(); i++)
    // {
    //     printf("%d \n", validMoves->at(i));
    // }
    

    while(true) {
        window.clear();
        board.drawBoard(&window);
        board.drawPiecesCurrentlyOnBoard(&window);
        window.display();
    }
}