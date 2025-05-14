#include "Game.h"
#include "Piece.h"
#include "Pawn.h"
#include <SFML/Graphics.hpp>

sf::Texture boardTexture;
sf::Texture highlightedSquareTexture;

//white team textures
sf::Texture wPawnTexture;
sf::Texture wRookTexture;

//black team textures
sf::Texture bPawnTexture;
sf::Texture bRookTexture;


int main() {
    //int check = boardTexture.loadFromFile("//res//chess_board.png");
    //works int check1 = boardTexture.loadFromFile("/home/max/SFML_Chess/src/chess_board.png");
    int check1 = boardTexture.loadFromFile("/home/max/SFML_Chess/res/chess_board.png");
    int check2 = highlightedSquareTexture.loadFromFile("/home/max/SFML_Chess/res/white-pawn-svgrepo-com.png");
    
    int check3 = wPawnTexture.loadFromFile("/home/max/SFML_Chess/res/white-pawn-svgrepo-com.png");
    int wRookTextureLoadSuccess = wRookTexture.loadFromFile("/home/max/SFML_Chess/res/white-rook-svgrepo-com.png");

    int check4 = bPawnTexture.loadFromFile("/home/max/SFML_Chess/res/black-pawn-svgrepo-com.png");
    int bRookTextureLoadSuccess = bRookTexture.loadFromFile("/home/max/SFML_Chess/res/black-rook-svgrepo-com.png");

    //int check2 = boardTexture.loadFromFile("/res/chess_board.png");
    //int check3 = boardTexture.loadFromFile("\res\chess_board.png");

    Game game = Game(&boardTexture, &highlightedSquareTexture, &wPawnTexture, &wRookTexture, &bPawnTexture, &bRookTexture);
    game.draw();

    std::cout << "Hoopla\n";
    return 0;
}