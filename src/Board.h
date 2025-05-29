#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"
#include <cmath>
#include <fstream>

class PawnPromotionState {

    public:
        bool pieceNotSelected;

        //Piece Menu Textures and Sprites
        sf::Texture wPawnPromotionMenuTexture;
        sf::Texture bPawnPromotionMenuTexture;
        sf::Sprite pawnPromotionMenuSprite;

        sf::RenderWindow* window;
        Board* board;

        PawnPromotionState(Board* board, sf::Texture* bPawnPromotionMenuTexture, sf::Texture* wPawnPromotionMenuTexture);
        ~PawnPromotionState();

        Piece* getInstanceOfSelectedPiece(int selectedPieceCord, Piece* pieceToChange);
        int handleClickPawnPromotionState(int clickX, int clickY);
        void drawLoop(Piece* pawnBeingChanged, std::string* boardStrToChange);
};

class Board
{
private:
    sf::Texture* boardTexture;
    sf::Sprite boardSprite;
    sf::Sprite highlightSquareSprite;

    sf::Texture* wPawnTexture;
    sf::Texture* wRookTexture;
    sf::Texture* wKingTexture;
    sf::Texture* wQueenTexture;
    sf::Texture* wKnightTexture;
    sf::Texture* wBishopTexture;
    sf::Texture* wPawnPromotionMenuTexture; 

    sf::Texture* bPawnTexture;
    sf::Texture* bRookTexture;
    sf::Texture* bKingTexture;
    sf::Texture* bQueenTexture;
    sf::Texture* bKnightTexture;
    sf::Texture* bBishopTexture;
    sf::Texture* bPawnPromotionMenuTexture;

    // //piece definitions
    // Pawn testPawn1;
    // Pawn testPawn2;
    // //Pawn testPawn2;

    std::vector<Piece*>* piecesCurrentlyOnBoard;
    std::string boardString;

    std::vector<Piece*>* copyOfPiecesAfterMoveWasMade; 
    std::string copyofBoardStringAfterMoveWasMade;


public:
    std::vector<Animation> wKnightAnimations;
    std::vector<Animation> wQueenAnimations;
    std::vector<Animation> wPawnAnimations;
    std::vector<Animation> wBishopAnimations;
    std::vector<Animation> wRookAnimations;
    std::vector<Animation> wKingAnimations;

    //piece definitions
    //Pawn testPawn1;
    //Pawn testPawn2;
    //Pawn testPawn2;

    Board(
         sf::Texture* whiteWinsScreenTexture,
         sf::Texture* blackWinsScreenTexture,
         sf::Texture* boardTexture, 
         sf::Texture* highlightedSquareTexture, 
         sf::Texture* wPawnTexture,
         std::vector<Animation> wPawnAnimations,
         sf::Texture* wRookTexture,
         std::vector<Animation> wRookAnimations,
         sf::Texture* wKingTexture,
         std::vector<Animation> wKingAnimations,
         sf::Texture* wQueenTexture,
         std::vector<Animation> wQueenAnimations,
         sf::Texture* wKnightTexture,
         std::vector<Animation> wKnightAnimations,
         sf::Texture* wBishopTexture,
         std::vector<Animation> wBishopAnimations,
         sf::Texture* wPawnPromotionMenuTexture,
         sf::Texture* bPawnTexture, 
         sf::Texture* bRookTexture, 
         sf::Texture* bKingTexture, 
         sf::Texture* bQueenTexture,
         sf::Texture* bKnightTexture,
         sf::Texture* bBishopTexture,
         sf::Texture* bPawnPromotionMenuTexture,
         sf::RenderWindow* window);
    ~Board();
    void readInBoardFromFile();
    std::vector<Piece*>* initializePiecesOnBoardBasedOnBoardString(std::string boardString);

    void printBoard(std::string boardToPrint);
    void overWriteBoardAtLocation(int cord, char thingOnSpace);
    std::vector<Piece*>* getPiecesCurrentlyOnBoard();
    
    void drawBoard(sf::RenderWindow* window);
    void drawPiecesCurrentlyOnBoard(sf::RenderWindow* window);
    void drawHighlightedValidMoves(sf::RenderWindow* window, std::vector<int> validMoves);

    std::array<int, 2> convertStrIndexToBoardCords(int stringIdx);
    int convertBoardCordsToStringIndex(int x, int y);
    bool inRange(int val, int low, int high);

    std::string* getBoardStr();
    void setBoardStr(std::string strToAssign);

    std::string* getBoardCopyStr();
    void setBoardCopyStr(std::string strToAssign);
    void setCopyPieceVect(std::vector<Piece*>* ptrToPieceVect);
    std::vector<Piece*>* getCopyPieceVect();

    //takes in "Black" or "White" for team, and 0 (current real board), or 1 (copy board after a move was made) for which board to check
    std::vector<int> getAllCapturableSpacesForAGivenSide(std::string sideThatIsCapturingPieces, std::string boardToUse, std::vector<Piece*>* vectOfPiecesToUse);

    bool isKingCapturable(std::vector<int> vectOfAllCapturableLocations, std::string sideThatIsCapturingPieces, std::string whichBoardToCheck);
    bool sideIsInCheckMate(std::string side);

    sf::Texture* getPieceTexture(std::string pieceName, bool isOnWhiteTeam);

    sf::RenderWindow* window;
    PawnPromotionState pawnPromotionState;

    void freeVectorOfPieces(std::vector<Piece*>* vectOfPieces);
};