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

    sf::Texture* bPawnTexture;
    sf::Texture* bRookTexture;
    

public:
    Game(sf::Texture* boardTexture, sf::Texture* highlightedSquareTexture, sf::Texture* wPawnTexture, sf::Texture *wRookTexture, sf::Texture* bPawnTexture, sf::Texture *bRookTexture);
    ~Game();
    void debugValidMoves();
    void draw();

    std::vector<int> getValidMovesForClickedSpace(int mouseX, int mouseY);
    Piece* getPieceThatWasClicked(int mouseX, int mouseY);
    std::vector<int> handleClick(int mouseX, int mouseY);
};
