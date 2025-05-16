#include "Board.h"

Board::Board(sf::Texture* boardTexture, 
            sf::Texture* highlightedSquareTexture, 
            sf::Texture* wPawnTexture, 
            sf::Texture* wRookTexture,
            sf::Texture* wKingTexture, 
            sf::Texture* bPawnTexture, 
            sf::Texture* bRookTexture,
            sf::Texture* bKingTexture) : 
boardTexture(boardTexture),
boardSprite(*boardTexture),
highlightSquareSprite(*highlightedSquareTexture),
wPawnTexture(wPawnTexture),
wRookTexture(wRookTexture),
wKingTexture(wKingTexture),
bPawnTexture(bPawnTexture),
bRookTexture(bRookTexture),
bKingTexture(bKingTexture) 
//testPawn1('P', 47, wPawnTexture, &boardString),
//testPawn2('p', 31, bPawnTexture, &boardString)
{
    //boardTexture = sf::Texture("/home/max/SFML_Chess/res/chess_board.png");
    //boardSprite = sf::Sprite(boardTexture);
                //   "00000000
                //    00000000
                //    00000000
                //    00000000
                //    00000P00
                //    000000p0
                //    00000000
                //    00000000"
    
    //boardString = "pPpP00000000000000000000000000p0p0000ppP000000000000000000000000";
    //boardString = "00000000000000p0000000000000000000P00000000000000000000000000000";
    readInBoardFromFile();
    std::cout << boardString << " \n";
    piecesCurrentlyOnBoard = initializePiecesOnBoardBasedOnBoardString(boardString);

    highlightSquareSprite.setScale({.4, .4});
    highlightSquareSprite.setColor(sf::Color::Magenta);

    for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
        std::cout << "Memory Address: " << &piecesCurrentlyOnBoard->at(i) << "\n";
        std::cout << "cord : " << piecesCurrentlyOnBoard->at(i)->cord << "\n";
    }

    //testPawn1 = Pawn('P', 40, wPawnTexture);
    
    //piecesCurrentlyOnBoard.emplace_back(testPawn1);
    //piecesCurrentlyOnBoard.emplace_back(testPawn2);
}

Board::~Board()
{
}

void Board::readInBoardFromFile() {
    std::ifstream boardTextFile;
    std::string currentLine;
    boardTextFile.open("/home/max/SFML_Chess/res/boardString.txt");
    
    while(!boardTextFile.eof()) {
        getline(boardTextFile, currentLine);
        boardString += currentLine;
    }

    boardTextFile.close();
}

std::vector<Piece*>* Board::initializePiecesOnBoardBasedOnBoardString(std::string boardStr) {
    //Pawn::Pawn(char pieceIcon, int cord, sf::Texture* pieceTexture, std::string* currentBoardString) : 

    std::vector<Piece*>* piecesOnTheBoard = new std::vector<Piece*>;
    int* screenCords;
    for (int i = 0; i < boardString.size(); i++) {
        if (boardString[i] != '0') {
            //Pawn init
            if(boardString[i] == 'P') {
                Pawn* newPawn = new Pawn(this, 'P', i, wPawnTexture);
                
                //set the cord based on the index in the string arr
                screenCords = convertStrIndexToBoardCords(newPawn->cord);
                newPawn->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
                
                piecesOnTheBoard->emplace_back(newPawn);
            }
            if(boardString[i] == 'p') {
                Pawn* newPawn = new Pawn(this, 'p', i, bPawnTexture);

                screenCords = convertStrIndexToBoardCords(newPawn->cord);
                newPawn->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});

                piecesOnTheBoard->emplace_back(newPawn);
            }
            //end pawn init----------------------------------------------------------------------

            //rook init
            if(boardString[i] == 'R') {
                Rook* newRook = new Rook(this, 'R', i, wRookTexture);
                
                //set the cord based on the index in the string arr
                screenCords = convertStrIndexToBoardCords(newRook->cord);
                newRook->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
                
                piecesOnTheBoard->emplace_back(newRook);
            }
            if(boardString[i] == 'r') {
                Rook* newRook = new Rook(this, 'r', i, bRookTexture);

                screenCords = convertStrIndexToBoardCords(newRook->cord);
                newRook->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});

                piecesOnTheBoard->emplace_back(newRook);
            }
            if(boardString[i] == 'K') {
                King* newKing = new King(this, 'K', i, wKingTexture);
                
                //set the cord based on the index in the string arr
                screenCords = convertStrIndexToBoardCords(newKing->cord);
                newKing->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
                
                piecesOnTheBoard->emplace_back(newKing);
            }
            if(boardString[i] == 'k') {
                King* newKing = new King(this, 'k', i, bKingTexture);

                screenCords = convertStrIndexToBoardCords(newKing->cord);
                newKing->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});

                piecesOnTheBoard->emplace_back(newKing);
            }
            //end rook init------------------------------------------------------------------------
        }
    }

    return piecesOnTheBoard;
}

void Board::printBoard(std::string boardToPrint) {
    for(int i = 0; i < boardToPrint.size(); i++) {
        if (!(i%8) && (i != 0)) {
            printf("\n");
        }
        printf("%c ", boardToPrint[i]);
    }
}

void Board::overWriteBoardAtLocation(int cord, char thingOnSpace) {
    boardString[cord] = thingOnSpace;
}

std::vector<Piece*>* Board::getPiecesCurrentlyOnBoard() {
    return piecesCurrentlyOnBoard;
}

void Board::drawBoard(sf::RenderWindow* window) {
    window->draw(boardSprite);
}

void Board::drawPiecesCurrentlyOnBoard(sf::RenderWindow* window) {
    for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
        window->draw(piecesCurrentlyOnBoard->at(i)->pieceSprite);
    }
}

void Board::drawHighlightedValidMoves(sf::RenderWindow* window, std::vector<int>* validMoves) {
    int* screenCords;
    for (int i = 0; i < validMoves->size(); i++) {
        //get cords
        screenCords = convertStrIndexToBoardCords(validMoves->at(i));
        highlightSquareSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
        window->draw(highlightSquareSprite);
    }
}


int* Board::convertStrIndexToBoardCords(int stringIdx) {
    //0->63
	//spit out (x, y)
	
	int x = 0;
	int y = 0;

	for (int i = 0; i < 63; i++) {
		
		if (i == stringIdx) {
			break;
		}
		
		x += 80;
		
		if (x > 560) {
			x = 0;
			y += 80;
		}
	}
	int* cords = new int[2];
	cords[0] = x;
	cords[1] = y;
	return cords;
}

int Board::convertBoardCordsToStringIndex(int x, int y) {
    int strIndex = (floor((8*x)/640) + floor((8*y)/640) + 7*floor((8*y)/640)); 
    return strIndex;
}

//returns if true if val is in the range of [low, high], false otherwise
bool Board::inRange(int val, int low, int high) {
    return (val >= low && val <= high);    
}

std::vector<int>* Board::getAllCapturableSpacesForAGivenSide(std::string sideThatIsCapturingPieces, std::string boardToUse, std::vector<Piece*>* vectOfPiecesToUse) {
    std::vector<int>* allSpacesOfPiecesThatCanBeCaptured = new std::vector<int>;
    std::vector<int>* currentPiecesCapturableSpaces;
    std::vector<Piece*>* vectorOfRelaventPieces = vectOfPiecesToUse;
    if (sideThatIsCapturingPieces == "White") {
        for (int i = 0; i < vectorOfRelaventPieces->size(); i++) {
            //if there is a white piece, get the spaces it is currently able to capture
            if (isupper(vectorOfRelaventPieces->at(i)->pieceIcon)) {
                currentPiecesCapturableSpaces = vectorOfRelaventPieces->at(i)->getMyCapturableSpaces(boardToUse);
                //printf("size of currentPiecesCapturableSpaces: %d\n", currentPiecesCapturableSpaces->size());
                for (int j = 0; j < currentPiecesCapturableSpaces->size(); j++)
                {
                    allSpacesOfPiecesThatCanBeCaptured->push_back(currentPiecesCapturableSpaces->at(j));
                }
            }
        }
    } else if (sideThatIsCapturingPieces == "Black") {
        for (int i = 0; i < vectorOfRelaventPieces->size(); i++) {
            //if there is a black piece, get the spaces it is currently able to capture
            if (!isupper(vectorOfRelaventPieces->at(i)->pieceIcon)) {
                currentPiecesCapturableSpaces = vectorOfRelaventPieces->at(i)->getMyCapturableSpaces(boardToUse);
                for (int j = 0; j < currentPiecesCapturableSpaces->size(); j++)
                {
                    allSpacesOfPiecesThatCanBeCaptured->push_back(currentPiecesCapturableSpaces->at(j));
                }
            }
        }
    }

    return allSpacesOfPiecesThatCanBeCaptured;
}

bool Board::isKingCapturable(std::vector<int>* vectOfAllCapturableLocations, std::string sideThatIsCapturingPieces, std::string whichBoardToCheck) {
    
    std::string boardStrToCheck = whichBoardToCheck;
    // if (whichBoardToCheck == "Real") {
    //     boardStrToCheck.assign(this->boardString);
    // } else if (whichBoardToCheck == "Copy") {
    //     boardStrToCheck.assign(this->copyofBoardStringAfterMoveWasMade);
    // }
    
    
    std::string strOfCapturablePieceIcons;
    if (sideThatIsCapturingPieces == "Black") {
        for (int i = 0; i < vectOfAllCapturableLocations->size(); i++)
        {
            //if there is a white piece that can be captured, store it's pieceIcon
           if (isupper(boardStrToCheck[vectOfAllCapturableLocations->at(i)])) {
            strOfCapturablePieceIcons+=boardStrToCheck[vectOfAllCapturableLocations->at(i)];
           }
        }
    } else if (sideThatIsCapturingPieces == "White") {
        for (int i = 0; i < vectOfAllCapturableLocations->size(); i++)
        {
           if (islower(boardStrToCheck[vectOfAllCapturableLocations->at(i)])) {
            strOfCapturablePieceIcons+=boardStrToCheck[vectOfAllCapturableLocations->at(i)];
           }
        }
    }
    
    bool kingCanBeCaptured = false;
    if (strOfCapturablePieceIcons.size() > 0) {
        for (int i = 0; i < strOfCapturablePieceIcons.size(); i++)
        {
            if(strOfCapturablePieceIcons[i] == 'k' || strOfCapturablePieceIcons[i] == 'K') {
                kingCanBeCaptured = true;
                break;
            }
        }
    }

    return kingCanBeCaptured;
    //case,         criteria
    //if b and real, islower() && board
    //if b and copy
    //if w and real
    //if w and copy
}

std::string* Board::getBoardStr() {
    return &boardString;
}

void Board::setBoardStr(std::string strToAssign) {
    boardString.assign(strToAssign);
}

std::string* Board::getBoardCopyStr() {
    return &copyofBoardStringAfterMoveWasMade;
}

void Board::setBoardCopyStr(std::string strToAssign) {
    copyofBoardStringAfterMoveWasMade.assign(strToAssign);
}

void Board::setCopyPieceVect(std::vector<Piece*>* ptrToPieceVect) {
    copyOfPiecesAfterMoveWasMade = ptrToPieceVect;
}

std::vector<Piece*>* Board::getCopyPieceVect() {
    return copyOfPiecesAfterMoveWasMade;
}

bool Board::sideIsInCheckMate(std::string side) {
    //so at a high level, a team is in checkmate if there is
    //no move that a team can make that will result in the king not
    //not being in danger

    //go through all the pieces on the side trying to get out of check (potentially checkmate)
    //for each piece, get there current valid moves; we worked it out so that if a move results
    //in the king being in danger the move is not valid and not added to the list.
    
    //so if the list of ALL valid moves for every piece on a side is empty then we are in checkmate.
    std::vector<int> allValidMovesForASide;
    std::vector<int> currentPiecesValidMoves;
    bool isInCheckmate = false;
    std::string currentPiecesTeam;
    for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++)
    {
        currentPiecesTeam = piecesCurrentlyOnBoard->at(i)->getMyTeamString();
        if (currentPiecesTeam == side) {
            currentPiecesValidMoves = *piecesCurrentlyOnBoard->at(i)->getValidMoves();
            for (int j = 0; j < currentPiecesValidMoves.size(); j++) {
                allValidMovesForASide.push_back(currentPiecesValidMoves.at(j));
            }
        }
    }
    
    if (allValidMovesForASide.size() == 0) {
        isInCheckmate = true;
    }

    return isInCheckmate;
}