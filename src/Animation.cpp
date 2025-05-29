#include "Animation.h"
#include "Board.h"
Animation::Animation(sf::Sprite* ptrToAnimationSprite, sf::Texture* animationSpriteSheet) :
animationSpriteSheet(animationSpriteSheet),
currentFrameSprite(ptrToAnimationSprite)
{

}

Animation::Animation():
animationSpriteSheet(nullptr),
currentFrameSprite(nullptr)
{

}

Animation::~Animation() {
    
}

void Animation::setCurrentFrame(int frameNumber) { 
    sf::IntRect currentFrameRect({(frameNumber*70), 0}, {70, 80});
    currentFrameSprite->setTextureRect(currentFrameRect);
}

void Animation::playAnimation(sf::RenderWindow* window, std::array<int, 2> locationToPlayAnimation, Board board) {
    currentFrameSprite->setTexture(*animationSpriteSheet);
    currentFrameSprite->setPosition({locationToPlayAnimation[0], locationToPlayAnimation[1]});

    int currentFrame = 7;
    while(currentFrame != 0) {
        setCurrentFrame(currentFrame);
        
        window->clear();
        board.drawBoard(window);
        board.drawPiecesCurrentlyOnBoard(window);
        window->draw(*currentFrameSprite);
        window->display();

        currentFrame--;
        sf::sleep(sf::milliseconds(80));
    }
}