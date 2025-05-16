#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"
#include <cmath>
#include <fstream>

class Board
{
private:
    sf::Texture* boardTexture;
    sf::Sprite boardSprite;
    sf::Sprite highlightSquareSprite;

    sf::Texture* wPawnTexture;
    sf::Texture* wRookTexture;
    sf::Texture* wKingTexture;

    sf::Texture* bPawnTexture;
    sf::Texture* bRookTexture;
    sf::Texture* bKingTexture;

    // //piece definitions
    // Pawn testPawn1;
    // Pawn testPawn2;
    // //Pawn testPawn2;

    std::vector<Piece*>* piecesCurrentlyOnBoard;
    std::string boardString;

    std::vector<Piece*>* copyOfPiecesAfterMoveWasMade; 
    std::string copyofBoardStringAfterMoveWasMade;

public:
    //piece definitions
    //Pawn testPawn1;
    //Pawn testPawn2;
    //Pawn testPawn2;

    Board(sf::Texture* boardTexture, 
          sf::Texture* highlightedSquareTexture, 
          sf::Texture* wPawnTexture, 
          sf::Texture* wRookTexture,
          sf::Texture* wKingTexture, 
          sf::Texture* bPawnTexture, 
          sf::Texture* bRookTexture,
          sf::Texture* bKingTexture);
    ~Board();
    void readInBoardFromFile();
    std::vector<Piece*>* initializePiecesOnBoardBasedOnBoardString(std::string boardString);

    void printBoard(std::string boardToPrint);
    void overWriteBoardAtLocation(int cord, char thingOnSpace);
    std::vector<Piece*>* getPiecesCurrentlyOnBoard();
    
    void drawBoard(sf::RenderWindow* window);
    void drawPiecesCurrentlyOnBoard(sf::RenderWindow* window);
    void drawHighlightedValidMoves(sf::RenderWindow* window, std::vector<int>* validMoves);

    int* convertStrIndexToBoardCords(int stringIdx);
    int convertBoardCordsToStringIndex(int x, int y);
    bool inRange(int val, int low, int high);

    std::string* getBoardStr();
    void setBoardStr(std::string strToAssign);

    std::string* getBoardCopyStr();
    void setBoardCopyStr(std::string strToAssign);
    void setCopyPieceVect(std::vector<Piece*>* ptrToPieceVect);
    std::vector<Piece*>* getCopyPieceVect();

    //takes in "Black" or "White" for team, and 0 (current real board), or 1 (copy board after a move was made) for which board to check
    std::vector<int>* getAllCapturableSpacesForAGivenSide(std::string sideThatIsCapturingPieces, std::string boardToUse, std::vector<Piece*>* vectOfPiecesToUse);

    bool isKingCapturable(std::vector<int>* vectOfAllCapturableLocations, std::string sideThatIsCapturingPieces, std::string whichBoardToCheck);
    bool sideIsInCheckMate(std::string side);
};