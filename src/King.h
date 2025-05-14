#include "Piece.h"
//#include "Game.h"

class King : public Piece
{
private:
    /* data */
public:
    King(Board* board, char pieceIcon, int cord, sf::Texture* pieceTexture);
    ~King();
    
    std::vector<int>* getBasicMoves() override;
    std::vector<int>* getValidMoves() override;
    std::vector<int>* getMyCapturableSpaces() override;
};