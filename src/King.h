#include "Piece.h"
//#include "Game.h"

class King : public Piece
{
private:
    /* data */
public:
    King(/* args */);
    ~King();
    
    std::vector<int>* getBasicMoves() override;
    std::vector<int>* getValidMoves() override;
    std::vector<int>* getCapturableSpaces() override;
};