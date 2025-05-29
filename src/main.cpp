#include "Game.h"
#include "Piece.h"
#include "Pawn.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"

sf::Texture boardTexture;
sf::Texture highlightedSquareTexture;

sf::Texture whiteWinsScreenTexture;
sf::Texture blackWinsScreenTexture;

sf::Texture explosionAnimationSpriteSheet;
Animation explosionAnimation;

//white team textures
sf::Texture wPawnTexture;
sf::Texture wPawnAttackAnimationSpriteSheet;
Animation wPawnAttackAnimation;

sf::Texture wRookTexture;
sf::Texture wRookAttackAnimationSpriteSheet;
Animation wRookAttackAnimation;

sf::Texture wKingTexture;
sf::Texture wKingAttackAnimationSpriteSheet;
Animation wKingAttackAnimation;

sf::Texture wQueenTexture;
sf::Texture wQueenAttackAnimationSpriteSheet;
Animation wQueenAttackAnimation;

sf::Texture wKnightTexture;
sf::Texture wKnightAttackAnimationSpriteSheet;
Animation wKnightAttackAnimation;

sf::Texture wBishopTexture;
sf::Texture wBishopAttackAnimationSpriteSheet;
Animation wBishopAttackAnimation;

sf::Texture wPawnPromotionMenuTexture;

//black team textures
sf::Texture bPawnTexture;
sf::Texture bRookTexture;
sf::Texture bKingTexture;
sf::Texture bQueenTexture;
sf::Texture bKnightTexture;
sf::Texture bBishopTexture;
sf::Texture bPawnPromotionMenuTexture;


int main() {
    bool megamanBattleNetworkAssets = true;

    // int check1 = boardTexture.loadFromFile("/home/max/SFML_Chess/res/chess_board.png");
    // int check2 = highlightedSquareTexture.loadFromFile("/home/max/SFML_Chess/res/white-pawn-svgrepo-com.png");
    
    // int check3 = wPawnTexture.loadFromFile("/home/max/SFML_Chess/res/white-pawn-svgrepo-com.png");

    // int check4 = bPawnTexture.loadFromFile("/home/max/SFML_Chess/res/black-pawn-svgrepo-com.png");

    // int wRookTextureLoadSuccess = wRookTexture.loadFromFile("/home/max/SFML_Chess/res/white-rook-svgrepo-com.png");
    // int bRookTextureLoadSuccess = bRookTexture.loadFromFile("/home/max/SFML_Chess/res/black-rook-svgrepo-com.png");

    // int wKingTextureLoadSuccess = wKingTexture.loadFromFile("/home/max/SFML_Chess/res/white-king-svgrepo-com.png");
    // int bKingTextureLoadSuccess = bKingTexture.loadFromFile("/home/max/SFML_Chess/res/black-king-svgrepo-com.png");

    // int wQueenTextureLoadSuccess = wQueenTexture.loadFromFile("/home/max/SFML_Chess/res/white-queen-svgrepo-com.png");
    // int bQueenTextureLoadSuccess = bQueenTexture.loadFromFile("/home/max/SFML_Chess/res/black-queen-svgrepo-com.png");

    // int wKnightTextureLoadSuccess = wKnightTexture.loadFromFile("/home/max/SFML_Chess/res/white-knight-svgrepo-com.png");
    // int bKnightTextureLoadSuccess = bKnightTexture.loadFromFile("/home/max/SFML_Chess/res/black-knight-svgrepo-com.png");

    // int wBishopTextureLoadSuccess = wBishopTexture.loadFromFile("/home/max/SFML_Chess/res/white-bishop-svgrepo-com.png");
    // int bBishopTextureLoadSuccess = bBishopTexture.loadFromFile("/home/max/SFML_Chess/res/black-bishop-svgrepo-com.png");

    // int wPawnPromotionMenuTextureLoadSuccess = wPawnPromotionMenuTexture.loadFromFile("/home/max/SFML_Chess/res/pawnPromotionMenuWhite.png");
    // int bPawnPromotionMenuTextureLoadSuccess = bPawnPromotionMenuTexture.loadFromFile("/home/max/SFML_Chess/res/pawnPromotionMenuBlack.png")
    int whiteTeamWinsTexture = whiteWinsScreenTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/white-team-wins.png");
    int blackTeamWinsTexture = blackWinsScreenTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/black-team-wins.png");

    int check1 = boardTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/board.png");
    int check2 = highlightedSquareTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/moveOptionTexture.png");

    sf::Texture textureOfCurrentAnimation = highlightedSquareTexture;
    sf::Sprite spriteOfCurrentAnimation(textureOfCurrentAnimation);
    
    int check3 = wPawnTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/white-pawn.png");

    int check4 = bPawnTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/black-pawn.png");

    int wRookTextureLoadSuccess = wRookTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/white-rook.png");
    int bRookTextureLoadSuccess = bRookTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/black-rook.png");

    int wKingTextureLoadSuccess = wKingTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/white-king.png");
    int bKingTextureLoadSuccess = bKingTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/black-king.png");

    int wQueenTextureLoadSuccess = wQueenTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/white-queen.png");
    int bQueenTextureLoadSuccess = bQueenTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/black-queen.png");

    int wKnightTextureLoadSuccess = wKnightTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/white-knight.png");
    int bKnightTextureLoadSuccess = bKnightTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/black-knight.png");

    int wBishopTextureLoadSuccess = wBishopTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/white-bishop.png");
    int bBishopTextureLoadSuccess = bBishopTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/black-bishop.png");

    int wPawnPromotionMenuTextureLoadSuccess = wPawnPromotionMenuTexture.loadFromFile("/home/max/SFML_Chess/res/pawnPromotionMenuWhite.png");
    int bPawnPromotionMenuTextureLoadSuccess = bPawnPromotionMenuTexture.loadFromFile("/home/max/SFML_Chess/res/pawnPromotionMenuBlack.png");

    //game.draw();

    //sf::Texture attackAnimationSpriteSheet;
    int explosionAnimationLoad = explosionAnimationSpriteSheet.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/explosion-animation.png");
    explosionAnimation = Animation(&spriteOfCurrentAnimation, &explosionAnimationSpriteSheet);

    int b = wPawnAttackAnimationSpriteSheet.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/attack_animations/wPawn-Attack.png");
    wPawnAttackAnimation = Animation(&spriteOfCurrentAnimation, &wPawnAttackAnimationSpriteSheet);
    std::vector<Animation> wPawnAttackAnimations = {wPawnAttackAnimation, explosionAnimation};

    int a = wRookAttackAnimationSpriteSheet.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/attack_animations/wRook-Attack.png");
    wRookAttackAnimation = Animation(&spriteOfCurrentAnimation, &wRookAttackAnimationSpriteSheet);
    std::vector<Animation> wRookAttackAnimations = {wRookAttackAnimation, explosionAnimation};

    int c = wKingAttackAnimationSpriteSheet.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/attack_animations/wKing-Attack.png");
    wKingAttackAnimation = Animation(&spriteOfCurrentAnimation, &wKingAttackAnimationSpriteSheet);
    std::vector<Animation> wKingAttackAnimations = {wKingAttackAnimation, explosionAnimation};

    int testLoad = wKnightAttackAnimationSpriteSheet.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/attack_animations/white-knight-attack-animation.png");
    wKnightAttackAnimation = Animation(&spriteOfCurrentAnimation, &wKnightAttackAnimationSpriteSheet);
    std::vector<Animation> wKnightAnimations = {wKnightAttackAnimation, explosionAnimation};
    
    int testLoad1 = wQueenAttackAnimationSpriteSheet.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/attack_animations/white-queen-attack-animation.png");
    wQueenAttackAnimation = Animation(&spriteOfCurrentAnimation, &wQueenAttackAnimationSpriteSheet);
    std::vector<Animation> wQueenAnimations = {wQueenAttackAnimation, explosionAnimation};

    int testLoad2 = wBishopAttackAnimationSpriteSheet.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/attack_animations/wbishop-attack.png");
    wBishopAttackAnimation = Animation(&spriteOfCurrentAnimation, &wBishopAttackAnimationSpriteSheet);
    std::vector<Animation> wBishopAnimations = {wBishopAttackAnimation, explosionAnimation};

    Game game = Game(
                     &whiteWinsScreenTexture,
                     &blackWinsScreenTexture,
                     &boardTexture, 
                     &highlightedSquareTexture, 
                     &wPawnTexture,
                     wPawnAttackAnimations, 
                     &wRookTexture,
                     wRookAttackAnimations,
                     &wKingTexture,
                     wKingAttackAnimations,
                     &wQueenTexture,
                     wQueenAnimations,
                     &wKnightTexture,
                     wKnightAnimations,
                     &wBishopTexture,
                     wBishopAnimations, 
                     &wPawnPromotionMenuTexture,
                     &bPawnTexture, 
                     &bRookTexture, 
                     &bKingTexture, 
                     &bQueenTexture,
                     &bKnightTexture,
                     &bBishopTexture,
                     &bPawnPromotionMenuTexture);

    game.playGame();
    
    // Animation attackAnimation(&wKnightAttackAnimationSpriteSheet);
    // sf::RenderWindow testWindow = sf::RenderWindow(sf::VideoMode({640, 640}), "SFML works!");
    // attackAnimation.currentFrame.setPosition({150, 50});

    // int currentFrame = 7;
    // while(true) {
    //     attackAnimation.setCurrentFrame(currentFrame);
        
    //     testWindow.clear();
    //     testWindow.draw(attackAnimation.currentFrame);
    //     testWindow.display();

    //     currentFrame--;
    //     if(!currentFrame) {
    //         currentFrame = 7;
    //     }
        
    //     sf::sleep(sf::milliseconds(100));
    // }


    std::cout << "Hoopla\n";
    return 0;
}