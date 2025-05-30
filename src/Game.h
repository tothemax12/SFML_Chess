#pragma once
#include <map>
#include "Board.h"
#include "Animation.h"
#include <queue>
#include "SFML/Audio.hpp"
#include <ctime>
#include <cstdlib>

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

class MainMenuState {
    private:
        sf::Texture face1Texture;
        sf::Texture face2Texture;
        sf::Texture face3Texture;
        sf::Texture face4Texture;
        sf::Texture face5Texture;
        sf::Texture face6Texture;
        sf::Texture face7Texture;
        sf::Texture face8Texture;
        sf::Texture face9Texture;
        sf::Texture face10Texture;
        sf::Texture face11Texture;

        sf::Sprite face1Sprite;
        sf::Sprite face2Sprite;
        sf::Sprite face3Sprite;
        sf::Sprite face4Sprite;
        sf::Sprite face5Sprite;
        sf::Sprite face6Sprite;
        sf::Sprite face7Sprite;
        sf::Sprite face8Sprite;
        sf::Sprite face9Sprite;
        sf::Sprite face10Sprite;
        sf::Sprite face11Sprite;
        std::array<sf::Sprite, 11> arrayOfSprites = {face1Sprite,
                                                     face2Sprite,
                                                     face3Sprite,
                                                     face4Sprite,
                                                     face5Sprite,
                                                     face6Sprite,
                                                     face7Sprite,
                                                     face8Sprite,
                                                     face9Sprite,
                                                     face10Sprite,
                                                     face11Sprite};
        std::vector<sf::Sprite> leftSideSprites;
        std::vector<sf::Sprite> rightSideSprites;


        sf::Texture mainMenuLogoTexture;
        sf::Texture mainMenuBackGroundTexture;

        sf::Sprite mainMenuLogoImageSprite;
        sf::Sprite mainMenuBackGroundImageSprite;
        sf::Music mainMenuMusic;
        sf::RenderWindow* window;
        // std::array<sf::Texture, 10> collectionOfFaceTextures;
        // std::array<sf::Sprite, 10> spritesOnLeftSide;
        // std::array<sf::Sprite, 10> spritesOnRightSide;

        bool stateIsActive;

    public:
        MainMenuState(sf::RenderWindow* window);
        ~MainMenuState();
        void drawSides();
        void moveSides();
        void cycleImages();
        void handleInput();
        void draw();

};

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
    sf::RenderWindow* getWindow();
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