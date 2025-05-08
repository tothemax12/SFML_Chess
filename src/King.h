#include "Piece.h"
//#include "Game.h"

class King : public Piece
{
private:
    /* data */
public:
    King(char pieceIcon, int cord, sf::Texture* pieceTexture, std::string* currentBoardString);
    ~King();
    
    std::vector<int>* getBasicMoves() override;
    std::vector<int>* getValidMoves() override;
    std::vector<int>* getCapturableSpaces() override;
};