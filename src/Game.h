#pragma once
#include <map>
#include "Board.h"
#include "Animation.h"
#include "SFML/Audio.hpp"

// class SoundPlayer {
//     //std::map<std::string, sf::Sound> soundMap;

//     sf::SoundBuffer soundBuffer;
//     sf::Sound currentSoundEffectPlaying;
//     //sf::Music currentSong;

//     void playSound(std::string soundID);
//     void stopSound();
//     SoundPlayer();
//     ~SoundPlayer();
// };

class Game
{
private:
    Board board;
    sf::RenderWindow window;
    sf::Texture* whiteWinsScreenTexture;
    sf::Texture* blackWinsScreenTexture;
    sf::Sprite whiteTeamWinsSprite;
    sf::Sprite blackTeamWinsSprite;

    sf::Texture* boardTexture;
    sf::Texture* highlightedSquareTexture;
    
    sf::Texture* wPawnTexture;
    std::vector<Animation> wPawnAnimations;
    sf::Texture* wRookTexture;
    std::vector<Animation> wRookAnimations;
    sf::Texture* wKingTexture;
    std::vector<Animation> wKingAnimations;
    sf::Texture* wQueenTexture;
    std::vector<Animation> wQueenAnimations;

    sf::Texture* wKnightTexture;
    std::vector<Animation> wKnightAnimations;
    sf::Texture* wBishopTexture;
    std::vector<Animation> wBishopAnimations;
    sf::Texture* wPawnPromotionMenuTexture;

    sf::Texture* bPawnTexture;
    sf::Texture* bRookTexture;
    sf::Texture* bKingTexture;
    sf::Texture* bQueenTexture;
    sf::Texture* bKnightTexture;
    sf::Texture* bBishopTexture;
    sf::Texture* bPawnPromotionMenuTexture;

public:
    Game(
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
         sf::Texture* bPawnPromotionMenuTexture);
    ~Game();
    void debugValidMoves();
    void drawWinnerInformation(bool whiteTeamWon);
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