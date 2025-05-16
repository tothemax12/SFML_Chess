#include "Game.h"
#include <iostream>

Game::Game(sf::Texture* boardTexture, 
           sf::Texture* highlightedSquareTexture, 
           sf::Texture* wPawnTexture, 
           sf::Texture* wRookTexture,
           sf::Texture* wKingTexture, 
           sf::Texture* bPawnTexture,
           sf::Texture* bRookTexture,
           sf::Texture* bKingTexture) : 
boardTexture(boardTexture),
highlightedSquareTexture(highlightedSquareTexture), 
wPawnTexture(wPawnTexture),
wRookTexture(wRookTexture),
wKingTexture(wKingTexture),
bPawnTexture(bPawnTexture),
bRookTexture(bRookTexture),
bKingTexture(bKingTexture), 
board(boardTexture, highlightedSquareTexture, wPawnTexture, wRookTexture, wKingTexture, bPawnTexture, bRookTexture, bKingTexture) 
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

    std::vector<int> validMoves;
    std::vector<Piece*>* piecesCurrentlyOnBoard = board.getPiecesCurrentlyOnBoard();
    int* weirdCord = &piecesCurrentlyOnBoard->at(0)->cord;
    std::vector<int>* currentCapturableSpacesForASide = board.getAllCapturableSpacesForAGivenSide("White", *board.getBoardStr(), board.getPiecesCurrentlyOnBoard());

    while(true) {
        window.clear();
        board.drawBoard(&window);
        board.drawPiecesCurrentlyOnBoard(&window);

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

            // for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
            //     //std::cout << "i: " << i << "\n";
            //     //std::cout << "ith piece cord: " << piecesCurrentlyOnBoard->at(i)->cord << "\n";
            //     //if there is a piece at the clicked square print the valid moves it can make
            //     if (piecesCurrentlyOnBoard->at(i)->cord == strIndex) {

            //         validMoves = piecesCurrentlyOnBoard->at(i)->getValidMoves();
            //         std::cout << "valid moves for " << piecesCurrentlyOnBoard->at(i)->pieceIcon << " :\n";
            //         for (int j = 0; j < validMoves->size(); j++) {
            //             std::cout << validMoves->at(j) << "\n";
            //         }
            //     }
            // }

            validMoves = handleClick(mouseX, mouseY);

            //board.printBoard(*board.getBoardStr());
        }

        // for (int i = 0; i < currentCapturableSpacesForASide->size(); i++)
        // {
        //     std::cout << "current capturable spaces for white team: " << currentCapturableSpacesForASide->at(i) << " \n";
        // }
        

        // if (validMoves != nullptr) {
        //     board.drawHighlightedValidMoves(&window, validMoves);
        //     //board.drawHighlightedValidMoves(&window, currentCapturableSpacesForASide);
        // }
        board.drawHighlightedValidMoves(&window, &validMoves);
        
        bool sideIsInCheckMate = false;
        sideIsInCheckMate = board.sideIsInCheckMate("White");
        std::cout << "White is in checkmate: " << sideIsInCheckMate << "\n";
        
        window.display();

        mouseX = -1;
        mouseY = -1;
        strIndex = -1;
    }
}



void Game::draw() {
    debugValidMoves();

    board.printBoard(*board.getBoardStr());
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


//when a click happens

//if a piece was not already clicked:

//What if we have a method that solely returns the validMoves 
//of a space when a click happens. If that space was empty return an
//empty list.

//t





// std::vector<int> Game::getValidMovesForClickedSpace(int mouseX, int mouseY) {
//     std::vector<int>* blankValidMoves;
//     std::vector<int>* validMovesOfClickedSpace;
//     int strIdxOfClick = board.convertBoardCordsToStringIndex(mouseX, mouseY);
//     std::vector<Piece*>* piecesCurrentlyOnBoard = board.getPiecesCurrentlyOnBoard();

//     bool pieceWasClicked = false;
//     for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
//         //std::cout << "i: " << i << "\n";
//         //std::cout << "ith piece cord: " << piecesCurrentlyOnBoard->at(i)->cord << "\n";
//         //if there is a piece at the clicked square print the valid moves it can make
//         if (piecesCurrentlyOnBoard->at(i)->cord == strIdxOfClick) {
//             pieceWasClicked = true;

//             validMovesOfClickedSpace = piecesCurrentlyOnBoard->at(i)->getValidMoves();

//             std::cout << "valid moves for " << piecesCurrentlyOnBoard->at(i)->pieceIcon << " :\n";
//             for (int j = 0; j < validMovesOfClickedSpace->size(); j++) {
//                 std::cout << validMovesOfClickedSpace->at(j) << "\n";
//             }

//             //hit the piece we clicked, we are done
//             break;
//         }
//     }

//     if (!pieceWasClicked) {
//         validMovesOfClickedSpace = blankValidMoves;
//     }

//     return *validMovesOfClickedSpace;
// }

//returns a pointer to a piece to the piece of the click
//if the user clicked a blank space return nullptr
Piece* Game::getPieceThatWasClicked(int mouseX, int mouseY) {
    Piece* pieceToReturn = nullptr;

    int strIdxOfClick = board.convertBoardCordsToStringIndex(mouseX, mouseY);
    std::vector<Piece*>* piecesCurrentlyOnBoard = board.getPiecesCurrentlyOnBoard();

    for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
        //std::cout << "i: " << i << "\n";
        //std::cout << "ith piece cord: " << piecesCurrentlyOnBoard->at(i)->cord << "\n";
        //if there is a piece at the clicked square print the valid moves it can make
        if (piecesCurrentlyOnBoard->at(i)->cord == strIdxOfClick) {

            pieceToReturn = piecesCurrentlyOnBoard->at(i);

            //hit the piece we clicked, we are done
            break;
        }
    }

    return pieceToReturn;
}

//maybe handleClick should return the valid moves of the clicked space, (empty if blank space)
//or if there was a piece already clicked, then proceed with the movement
std::vector<int> Game::handleClick(int mouseX, int mouseY) {
    std::vector<int> emptyListOfValidMoves;
    std::vector<int> validMovesToReturn;

    static Piece* clickedPiece = nullptr;
    std::vector<int>* clickedPiecesValidMoves;
    int strIdxOfClick = board.convertBoardCordsToStringIndex(mouseX, mouseY);

    //if a piece was previously clicked see if they clicked one of it's valid moves
    if (clickedPiece != nullptr) {
        //for clicked pieces valid moves
        std::vector<int>* piecesValidMoves = clickedPiece->getValidMoves();
        
        // std::cout << "Clicked piece's valid moves: ";
        // for (int i = 0; i < piecesValidMoves->size(); i++)
        // {
        //     std::cout << piecesValidMoves->at(i) << " ";
        // }
        //     std::cout << "\n";
        
        for (int i = 0; i < piecesValidMoves->size(); i++) {
            //if they clicked a valid move
            if (piecesValidMoves->at(i) == strIdxOfClick) {
                //begin that pieces move procedure (on the real board)
                clickedPiece->movePiece(piecesValidMoves->at(i), board.getBoardStr(), board.getPiecesCurrentlyOnBoard(), false);
                //printf("clicked a valid move location for the selected piece\n");

                clickedPiece = nullptr;
                validMovesToReturn = emptyListOfValidMoves;
            }
        }
        //if they didn't click a valid move,
        //get the piece of that new space and exit this function
        clickedPiece = getPieceThatWasClicked(mouseX, mouseY);
        if (clickedPiece == nullptr) {
            validMovesToReturn = emptyListOfValidMoves;
        } else {
            validMovesToReturn = *clickedPiece->getValidMoves();
        }
    } else {
        //get the information from the click
        clickedPiece = getPieceThatWasClicked(mouseX, mouseY);

        if (clickedPiece != nullptr) {
            clickedPiecesValidMoves = clickedPiece->getValidMoves();

            // std::cout << "Clicked piece's valid moves: ";
            // for (int i = 0; i < clickedPiecesValidMoves->size(); i++)
            // {
            //     std::cout << clickedPiecesValidMoves->at(i) << " ";
            // }

            //std::cout << "\n";
            validMovesToReturn = *clickedPiecesValidMoves;
        } else if (clickedPiece == nullptr) {
            validMovesToReturn = emptyListOfValidMoves;
        }
    }

    return validMovesToReturn;
}