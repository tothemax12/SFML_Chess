#pragma once
#include <SFML/Graphics.hpp>

class Board;

//ultimately I want each piece to have an attack animation and a teleport animation
class Animation
{
private:

public:
    int numberOfFrames;

    //texture of whole animation
    sf::Texture* animationSpriteSheet;
    sf::Sprite* currentFrameSprite;

    Animation(sf::Sprite* ptrToAnimationSprite, sf::Texture* animationSpriteSheet);
    Animation();
    ~Animation();
    void setCurrentFrame(int frameNumber);
    void playAnimation(sf::RenderWindow* window, std::array<int, 2> locationToPlayAnimation, Board board);
};
