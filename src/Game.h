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
    sf::Texture* bPawnTexture;
    

public:
    Game(sf::Texture* boardTexture, sf::Texture* highlightedSquareTexture, sf::Texture* wPawnTexture, sf::Texture* bPawnTexture);
    ~Game();
    void debugValidMoves();
    void draw();
};
