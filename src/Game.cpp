#include "Game.h"
#include <iostream>

Game::Game(sf::Texture* boardTexture, sf::Texture* highlightedSquareTexture, sf::Texture *wPawnTexture, sf::Texture *bPawnTexture) : 
boardTexture(boardTexture),
highlightedSquareTexture(highlightedSquareTexture), 
wPawnTexture(wPawnTexture),
bPawnTexture(bPawnTexture), 
board(boardTexture, highlightedSquareTexture, wPawnTexture, bPawnTexture) 
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
    
    int mouseX = -1;
    int mouseY = -1;
    int strIndex = -1;

    std::vector<int>* validMoves = nullptr;
    std::vector<Piece *>* piecesCurrentlyOnBoard = board.getPiecesCurrentlyOnBoard();
    int* weirdCord = &piecesCurrentlyOnBoard->at(0)->cord;
    std::vector<int>* currentCapturableSpacesForASide = piecesCurrentlyOnBoard->at(1)->getAllCapturableSpacesForAGiveSide("Black");

    while(true) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            } else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                mouseX = mouseButtonPressed->position.x;
                mouseY = mouseButtonPressed->position.y;

                std::cout << "Mouse cords " << mouseX << " " << mouseY << "\n";
                std::cout << "String index " << strIndex << "\n";
                strIndex = board.convertBoardCordsToStringIndex(mouseX, mouseY);

                //printf("%d", strIndex);
            }
        }

        if (mouseX > -1 && mouseY > -1) {
            //get validMoves of clicked piece
            // for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
            //     printf("icon of pieces in array: %c\n", piecesCurrentlyOnBoard->at(i)->pieceIcon);
            //     printf("cord of pieces in array: %d\n", piecesCurrentlyOnBoard->at(i)->cord);
            // }

            for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
                //std::cout << "i: " << i << "\n";
                //std::cout << "ith piece cord: " << piecesCurrentlyOnBoard->at(i)->cord << "\n";
                //if there is a piece at the clicked square print the valid moves it can make
                if (piecesCurrentlyOnBoard->at(i)->cord == strIndex) {

                    validMoves = piecesCurrentlyOnBoard->at(i)->getValidMoves();
                    std::cout << "valid moves for " << piecesCurrentlyOnBoard->at(i)->pieceIcon << " :\n";
                    for (int j = 0; j < validMoves->size(); j++) {
                        std::cout << validMoves->at(j) << "\n";
                    }
                }
            }
        }

        window.clear();
        board.drawBoard(&window);
        board.drawPiecesCurrentlyOnBoard(&window);

        for (int i = 0; i < currentCapturableSpacesForASide->size(); i++)
        {
            std::cout << "current capturable spaces for white team: " << currentCapturableSpacesForASide->at(i) << " \n";
        }
        

        if (validMoves != nullptr) {
            //board.drawHighlightedValidMoves(&window, validMoves);
            board.drawHighlightedValidMoves(&window, currentCapturableSpacesForASide);
        }
        window.display();

        mouseX = -1;
        mouseY = -1;
        strIndex = -1;
    }
}



void Game::draw() {
    debugValidMoves();

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