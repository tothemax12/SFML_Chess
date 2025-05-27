#include "Game.h"
#include "Piece.h"
#include "Pawn.h"
#include <SFML/Graphics.hpp>

sf::Texture boardTexture;
sf::Texture highlightedSquareTexture;

//white team textures
sf::Texture wPawnTexture;
sf::Texture wRookTexture;
sf::Texture wKingTexture;
sf::Texture wQueenTexture;
sf::Texture wKnightTexture;
sf::Texture wBishopTexture;
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
    // int bPawnPromotionMenuTextureLoadSuccess = bPawnPromotionMenuTexture.loadFromFile("/home/max/SFML_Chess/res/pawnPromotionMenuBlack.png");
  
    int check1 = boardTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/board.png");
    int check2 = highlightedSquareTexture.loadFromFile("/home/max/SFML_Chess/res/white-pawn-svgrepo-com.png");
    
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

    int wBishopTextureLoadSuccess = wBishopTexture.loadFromFile("/home/max/SFML_Chess/res/white-bishop-svgrepo-com.png");
    int bBishopTextureLoadSuccess = bBishopTexture.loadFromFile("/home/max/SFML_Chess/res/mmbn-chess-assets/black-bishop.png");

    int wPawnPromotionMenuTextureLoadSuccess = wPawnPromotionMenuTexture.loadFromFile("/home/max/SFML_Chess/res/pawnPromotionMenuWhite.png");
    int bPawnPromotionMenuTextureLoadSuccess = bPawnPromotionMenuTexture.loadFromFile("/home/max/SFML_Chess/res/pawnPromotionMenuBlack.png");
    Game game = Game(&boardTexture, 
                     &highlightedSquareTexture, 
                     &wPawnTexture, 
                     &wRookTexture, 
                     &wKingTexture, 
                     &wQueenTexture,
                     &wKnightTexture,
                     &wBishopTexture,
                     &wPawnPromotionMenuTexture,
                     &bPawnTexture, 
                     &bRookTexture, 
                     &bKingTexture, 
                     &bQueenTexture,
                     &bKnightTexture,
                     &bBishopTexture,
                     &bPawnPromotionMenuTexture);
    //game.draw();
    game.playGame();

    std::cout << "Hoopla\n";
    return 0;
}