#pragma once
#include "Board.h"

class Game
{
private:
    Board board;
    sf::RenderWindow window;
    sf::Texture* boardTexture;
    sf::Texture* highlightedSquareTexture;
    
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

public:
    Game(sf::Texture* boardTexture, 
         sf::Texture* highlightedSquareTexture, 
         sf::Texture* wPawnTexture, 
         sf::Texture* wRookTexture, 
         sf::Texture* wKingTexture, 
         sf::Texture* wQueenTexture,
         sf::Texture* wKnightTexture,
         sf::Texture* wBishopTexture,
         sf::Texture* wPawnPromotionMenuTexture,
         sf::Texture* bPawnTexture, 
         sf::Texture* bRookTexture, 
         sf::Texture* bKingTexture, 
         sf::Texture* bQueenTexture,
         sf::Texture* bKnightTexture,
         sf::Texture* bBishopTexture,
         sf::Texture* bPawnPromotionMenuTexture);
    ~Game();
    void debugValidMoves();
    void draw(std::vector<int> validMovesOfClickedPiece);

    std::vector<int> getValidMovesForClickedSpace(int mouseX, int mouseY);
    Piece* getPieceThatWasClicked(int mouseX, int mouseY);
    std::vector<int> handleClick(int mouseX, int mouseY);

    //stuff related to actually playing the game
    int turnCount = 0;
    bool whiteTurn = true;
    bool currentPlayerIsInCheckmate = false;
    std::string currentTeam = "White";
    std::array<int, 2> checkInput();

    std::vector<int> getValidMovesOfClickedPiece(Piece* clickedPiece);
    int playerClickedAValidMoveLocation(std::vector<int> validMoves, int strIdxOfClick);
    void checkIfCorrectTeamAndMovePiece(Piece* clickedPiece, int clickedValidSpace);
    std::vector<int> handleClickGame(int mouseX, int mouseY);
    int playGame();
};