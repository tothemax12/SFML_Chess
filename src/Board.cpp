#include "Board.h"

Board::Board(sf::Texture* boardTexture, sf::Texture* wPawnTexture, sf::Texture* bPawnTexture) : 
boardTexture(boardTexture),
boardSprite(*boardTexture), 
wPawnTexture(wPawnTexture),
bPawnTexture(bPawnTexture) 
//testPawn1('P', 47, wPawnTexture, &boardString),
//testPawn2('p', 31, bPawnTexture, &boardString)
{
    //boardTexture = sf::Texture("/home/max/SFML_Chess/res/chess_board.png");
    //boardSprite = sf::Sprite(boardTexture);
                //   "00000000
                //    00000000
                //    00000000
                //    00000000
                //    00000P00
                //    000000p0
                //    00000000
                //    00000000"
    
    boardString = "pPpP00000000000000000000000000p0p0000ppP000000000000000000000000";
    piecesCurrentlyOnBoard = initializePiecesOnBoardBasedOnBoardString();
    //testPawn1 = Pawn('P', 40, wPawnTexture);
    
    //piecesCurrentlyOnBoard.emplace_back(testPawn1);
    //piecesCurrentlyOnBoard.emplace_back(testPawn2);
}

Board::~Board()
{
}

std::vector<Piece*>* Board::initializePiecesOnBoardBasedOnBoardString() {
    //Pawn::Pawn(char pieceIcon, int cord, sf::Texture* pieceTexture, std::string* currentBoardString) : 

    std::vector<Piece*>* piecesOnTheBoard = new std::vector<Piece*>;
    for (int i = 0; i < boardString.size(); i++) {
        if (boardString[i] != '0') {
            if(boardString[i] == 'P') {
                Pawn* newPawn = new Pawn('P', i, wPawnTexture, &boardString);
                piecesOnTheBoard->emplace_back(newPawn);
            }
            if(boardString[i] == 'p') {
                Pawn* newPawn = new Pawn('p', i, bPawnTexture, &boardString);
                piecesOnTheBoard->emplace_back(newPawn);
            }
        }
    }

    return piecesOnTheBoard;
}

void Board::printBoard() {
    for(int i = 0; i < boardString.size(); i++) {
        if (!(i%8) && (i != 0)) {
            printf("\n");
        }
        printf("%c ", boardString[i]);
    }
}

void Board::overWriteBoardAtLocation(int cord, char thingOnSpace) {
    boardString[cord] = thingOnSpace;
}

std::vector<Piece*>* Board::getPiecesCurrentlyOnBoard() {
    return piecesCurrentlyOnBoard;
}

void Board::drawBoard(sf::RenderWindow* window) {
    window->draw(boardSprite);
}

void Board::drawPiecesCurrentlyOnBoard(sf::RenderWindow* window) {
    for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
        window->draw(piecesCurrentlyOnBoard->at(i)->pieceSprite);
    }
}