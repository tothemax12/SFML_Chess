#include "Board.h"

PawnPromotionState::PawnPromotionState(Board* board, sf::Texture* bPawnPromotionMenuTexture, sf::Texture* wPawnPromotionMenuTexture) :
wPawnPromotionMenuTexture(*wPawnPromotionMenuTexture),
bPawnPromotionMenuTexture(*bPawnPromotionMenuTexture),
pawnPromotionMenuSprite(*wPawnPromotionMenuTexture),
board(board)
{
    pieceNotSelected = true;
    pawnPromotionMenuSprite.setPosition({(float)160, (float)240});
}

PawnPromotionState::~PawnPromotionState() {

}

Piece* PawnPromotionState::getInstanceOfSelectedPiece(int selectedPieceCord, Piece* pieceToChange) {
    Piece* pieceToReturn = nullptr;
    bool onWhiteTeam = isupper(pieceToChange->pieceIcon);
    switch (selectedPieceCord)
    {
    case 26:
        if (onWhiteTeam) {
            Bishop* newBishop = new Bishop(board, 'B', pieceToChange->cord, board->getPieceTexture("Bishop", onWhiteTeam));
            pieceToReturn = dynamic_cast<Bishop*>(newBishop);
        } else {
            Bishop* newBishop = new Bishop(board, 'b', pieceToChange->cord, board->getPieceTexture("Bishop", onWhiteTeam));
            pieceToReturn = dynamic_cast<Bishop*>(newBishop);
        }
        break;
    case 27:
        if (onWhiteTeam) {
            Knight* newKnight = new Knight(board, 'N', pieceToChange->cord, board->getPieceTexture("Knight", onWhiteTeam));
            pieceToReturn = dynamic_cast<Knight*>(newKnight);
        } else {
            Knight* newKnight = new Knight(board, 'n', pieceToChange->cord, board->getPieceTexture("Knight", onWhiteTeam));
            pieceToReturn = dynamic_cast<Knight*>(newKnight);
        }
        break;
    case 28:
        if (onWhiteTeam) {
            Queen* newQueen = new Queen(board, 'Q', pieceToChange->cord, board->getPieceTexture("Queen", onWhiteTeam));
            pieceToReturn = dynamic_cast<Queen*>(newQueen);
        } else {
            Queen* newQueen = new Queen(board, 'q', pieceToChange->cord, board->getPieceTexture("Queen", onWhiteTeam));
            pieceToReturn = dynamic_cast<Queen*>(newQueen);
        }
        break;
    case 29:
        if (onWhiteTeam) {
            Rook* newRook = new Rook(board, 'R', pieceToChange->cord, board->getPieceTexture("Rook", onWhiteTeam));
            pieceToReturn = dynamic_cast<Rook*>(newRook);
        } else {
            Rook* newRook = new Rook(board, 'r', pieceToChange->cord, board->getPieceTexture("Rook", onWhiteTeam));
            pieceToReturn = dynamic_cast<Rook*>(newRook);
        }
        break;
    default:
        break;
    }

    if(pieceToReturn != nullptr) {
        pieceToReturn->hasNotMoved = false;
    }

    return pieceToReturn;
}


int PawnPromotionState::handleClickPawnPromotionState(int clickX, int clickY) {
    int strIdxOfClickedPiece = -1;
    int strIdxOfClick = 0;

    strIdxOfClick = board->convertBoardCordsToStringIndex(clickX, clickY);
    if (strIdxOfClick == 26 ||
        strIdxOfClick == 27 ||
        strIdxOfClick == 28 ||
        strIdxOfClick == 29) {
            strIdxOfClickedPiece = strIdxOfClick;
        }

    // switch (strIdxOfClick) {
    //     case 26:

    // }
    return strIdxOfClickedPiece;
}

void PawnPromotionState::drawLoop(Piece* pawnBeingChanged, std::string* boardStrToChange) {
    int mouseX = -1;
    int mouseY = -1;
    int clickedPieceCord = -1;
    Piece* pieceSelected = nullptr;

    //set the correct menu texture for the sprite
    if (isupper(pawnBeingChanged->pieceIcon)) {
        pawnPromotionMenuSprite.setTexture(wPawnPromotionMenuTexture);
    } else {
        pawnPromotionMenuSprite.setTexture(bPawnPromotionMenuTexture);
    }
    
    while (pieceNotSelected) {
        board->window->clear();
        board->drawBoard(board->window);
        board->drawPiecesCurrentlyOnBoard(board->window);
        board->window->draw(pawnPromotionMenuSprite);

        //handle input
        while (const std::optional event = board->window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                board->window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    board->window->close();
            } else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                mouseX = mouseButtonPressed->position.x;
                mouseY = mouseButtonPressed->position.y;

                std::cout << "Mouse cords " << mouseX << " " << mouseY << "\n";
                std::cout << "String index " << clickedPieceCord << "\n";
                //clickedPieceCord = board->convertBoardCordsToStringIndex(mouseX, mouseY);
                //printf("%d", strIndex);
                clickedPieceCord = handleClickPawnPromotionState(mouseX, mouseY);
            }
        }

        if (mouseX > -1 && mouseY > -1) {
            if (clickedPieceCord != -1) {
                pieceSelected = getInstanceOfSelectedPiece(clickedPieceCord, pawnBeingChanged);

                //overwrite stuff

                //put selection on the board by overwriting pawn
                delete pawnBeingChanged;

                //printf('pawn cord: %d', )                
                pawnBeingChanged = pieceSelected;

                std::vector<Piece*>* piecesCurrentlyOnBoard = board->getPiecesCurrentlyOnBoard();
                for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++)
                {
                    if (piecesCurrentlyOnBoard->at(i)->cord == pawnBeingChanged->cord)  {   
                        printf("icon of piece we changed: %c\n", piecesCurrentlyOnBoard->at(i)->pieceIcon);
                    }

                    if (piecesCurrentlyOnBoard->at(i)->cord == pawnBeingChanged->cord)  {   
                        piecesCurrentlyOnBoard->at(i) = pawnBeingChanged;
                        printf("icon of piece we changed: %c\n", piecesCurrentlyOnBoard->at(i)->pieceIcon);
                    }
                }
                

                board->overWriteBoardAtLocation(pawnBeingChanged->cord, pawnBeingChanged->pieceIcon);

                std::array<int, 2> newSpritePosition = board->convertStrIndexToBoardCords(pawnBeingChanged->cord);
                pawnBeingChanged->pieceSprite.setPosition({(float)newSpritePosition[0],(float)newSpritePosition[1]});
                
                //draw the new piece to the window
                //board->drawPiecesCurrentlyOnBoard(board->window);
                 
                board->printBoard(*board->getBoardStr());
                pieceNotSelected = false;
            }
        }

        board->window->display();
    }

    pieceNotSelected = true;
}

Board::Board(sf::Texture* boardTexture, 
            sf::Texture* highlightedSquareTexture, 
            sf::Texture* wPawnTexture, 
            sf::Texture* wRookTexture,
            sf::Texture* wKingTexture, 
            sf::Texture* wQueenTexture, 
            sf::Texture* wKnightTexture,
            sf::Texture* wBishopTexture,
            sf::Texture* wPawnPromotionMenuTexture,
            sf::Texture* bPawnTexture, 
            sf::Texture* bRookTexture,
            sf::Texture* bKingTexture,
            sf::Texture* bQueenTexture,
            sf::Texture* bKnightTexture,
            sf::Texture* bBishopTexture,
            sf::Texture* bPawnPromotionMenuTexture,
            sf::RenderWindow* window) : 
boardTexture(boardTexture),
boardSprite(*boardTexture),
highlightSquareSprite(*highlightedSquareTexture),
wPawnTexture(wPawnTexture),
wRookTexture(wRookTexture),
wKingTexture(wKingTexture),
wQueenTexture(wQueenTexture),
wKnightTexture(wKnightTexture),
wBishopTexture(wBishopTexture),
wPawnPromotionMenuTexture(wPawnPromotionMenuTexture),
bPawnTexture(bPawnTexture),
bRookTexture(bRookTexture),
bKingTexture(bKingTexture),
bQueenTexture(bQueenTexture),
bKnightTexture(bKnightTexture),
bBishopTexture(bBishopTexture),
bPawnPromotionMenuTexture(bPawnPromotionMenuTexture),
window(window),
pawnPromotionState(this, bPawnPromotionMenuTexture, wPawnPromotionMenuTexture) 
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

    //pawnPromotionState = PawnPromotionState(window, this, bPawnTexture);
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
    std::array<int, 2> screenCords;
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
            //end rook init------------------------------------------------------------------------

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

            if(boardString[i] == 'Q') {
                Queen* newQueen = new Queen(this, 'Q', i, wQueenTexture);
                
                //set the cord based on the index in the string arr
                screenCords = convertStrIndexToBoardCords(newQueen->cord);
                newQueen->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
                
                piecesOnTheBoard->emplace_back(newQueen);
            }
            if(boardString[i] == 'q') {
                Queen* newQueen = new Queen(this, 'q', i, bQueenTexture);

                screenCords = convertStrIndexToBoardCords(newQueen->cord);
                newQueen->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});

                piecesOnTheBoard->emplace_back(newQueen);
            }

            if(boardString[i] == 'N') {
                Knight* newKnight = new Knight(this, 'N', i, wKnightTexture);
                
                //set the cord based on the index in the string arr
                screenCords = convertStrIndexToBoardCords(newKnight->cord);
                newKnight->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
                
                piecesOnTheBoard->emplace_back(newKnight);
            }
            if(boardString[i] == 'n') {
                Knight* newKnight = new Knight(this, 'n', i, bKnightTexture);

                screenCords = convertStrIndexToBoardCords(newKnight->cord);
                newKnight->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});

                piecesOnTheBoard->emplace_back(newKnight);
            }

            if(boardString[i] == 'B') {
                Bishop* newBishop = new Bishop(this, 'B', i, wBishopTexture);
                
                //set the cord based on the index in the string arr
                screenCords = convertStrIndexToBoardCords(newBishop->cord);
                newBishop->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
                
                piecesOnTheBoard->emplace_back(newBishop);
            }
            if(boardString[i] == 'b') {
                Bishop* newBishop = new Bishop(this, 'b', i, bBishopTexture);

                screenCords = convertStrIndexToBoardCords(newBishop->cord);
                newBishop->pieceSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});

                piecesOnTheBoard->emplace_back(newBishop);
            }
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

void Board::drawHighlightedValidMoves(sf::RenderWindow* window, std::vector<int> validMoves) {
    std::array<int, 2> screenCords;
    for (int i = 0; i < validMoves.size(); i++) {
        //draw the special moves for the player too
        if (validMoves.at(i) < 0) {
            screenCords = convertStrIndexToBoardCords(-1*validMoves.at(i));
        } else {
        //get cords
            screenCords = convertStrIndexToBoardCords(validMoves.at(i));
        }
        highlightSquareSprite.setPosition({(float)screenCords[0], (float)screenCords[1]});
        window->draw(highlightSquareSprite);
    }
}


std::array<int, 2> Board::convertStrIndexToBoardCords(int stringIdx) {
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
	std::array<int, 2> cords;
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

std::vector<int> Board::getAllCapturableSpacesForAGivenSide(std::string sideThatIsCapturingPieces, std::string boardToUse, std::vector<Piece*>* vectOfPiecesToUse) {
    std::vector<int> allSpacesOfPiecesThatCanBeCaptured;
    std::vector<int> currentPiecesCapturableSpaces;
    std::vector<Piece*>* vectorOfRelaventPieces = vectOfPiecesToUse;
    if (sideThatIsCapturingPieces == "White") {
        for (int i = 0; i < vectorOfRelaventPieces->size(); i++) {
            //if there is a white piece, get the spaces it is currently able to capture
            if (isupper(vectorOfRelaventPieces->at(i)->pieceIcon)) {
                currentPiecesCapturableSpaces = vectorOfRelaventPieces->at(i)->getMyCapturableSpaces(boardToUse);
                //printf("size of currentPiecesCapturableSpaces: %d\n", currentPiecesCapturableSpaces->size());
                for (int j = 0; j < currentPiecesCapturableSpaces.size(); j++)
                {
                    allSpacesOfPiecesThatCanBeCaptured.push_back(currentPiecesCapturableSpaces.at(j));
                }
            }
        }
    } else if (sideThatIsCapturingPieces == "Black") {
        for (int i = 0; i < vectorOfRelaventPieces->size(); i++) {
            //if there is a black piece, get the spaces it is currently able to capture
            if (!isupper(vectorOfRelaventPieces->at(i)->pieceIcon)) {
                currentPiecesCapturableSpaces = vectorOfRelaventPieces->at(i)->getMyCapturableSpaces(boardToUse);
                for (int j = 0; j < currentPiecesCapturableSpaces.size(); j++)
                {
                    allSpacesOfPiecesThatCanBeCaptured.push_back(currentPiecesCapturableSpaces.at(j));
                }
            }
        }
    }

    return allSpacesOfPiecesThatCanBeCaptured;
}

bool Board::isKingCapturable(std::vector<int> vectOfAllCapturableLocations, std::string sideThatIsCapturingPieces, std::string whichBoardToCheck) {
    
    std::string boardStrToCheck = whichBoardToCheck;
    // if (whichBoardToCheck == "Real") {
    //     boardStrToCheck.assign(this->boardString);
    // } else if (whichBoardToCheck == "Copy") {
    //     boardStrToCheck.assign(this->copyofBoardStringAfterMoveWasMade);
    // }
    
    
    std::string strOfCapturablePieceIcons;
    if (sideThatIsCapturingPieces == "Black") {
        for (int i = 0; i < vectOfAllCapturableLocations.size(); i++)
        {
            //if there is a white piece that can be captured, store it's pieceIcon
           if (isupper(boardStrToCheck[vectOfAllCapturableLocations.at(i)])) {
            strOfCapturablePieceIcons+=boardStrToCheck[vectOfAllCapturableLocations.at(i)];
           }
        }
    } else if (sideThatIsCapturingPieces == "White") {
        for (int i = 0; i < vectOfAllCapturableLocations.size(); i++)
        {
           if (islower(boardStrToCheck[vectOfAllCapturableLocations.at(i)])) {
            strOfCapturablePieceIcons+=boardStrToCheck[vectOfAllCapturableLocations.at(i)];
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
            currentPiecesValidMoves = piecesCurrentlyOnBoard->at(i)->getValidMoves();
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

sf::Texture* Board::getPieceTexture(std::string pieceName, bool isOnWhiteTeam) {
    sf::Texture* textureToReturn = wPawnPromotionMenuTexture;

    if(pieceName == "Rook") {
        if (isOnWhiteTeam) {
            textureToReturn = wRookTexture;
        } else {
            textureToReturn = bRookTexture;
        }
    } else if(pieceName == "Bishop") {
        if (isOnWhiteTeam) {
            textureToReturn = wBishopTexture;
        } else {
            textureToReturn = bBishopTexture;
        }
    } else if(pieceName == "Knight") {
        if (isOnWhiteTeam) {
            textureToReturn = wKnightTexture;
        } else {
            textureToReturn = bKnightTexture;
        }
    } else if(pieceName == "Queen") {
        if (isOnWhiteTeam) {
            textureToReturn = wQueenTexture;
        } else {
            textureToReturn = bQueenTexture;
        }
    }
    
    return textureToReturn;
}

void Board::freeVectorOfPieces(std::vector<Piece*>* vectOfPieces) {
    for (int i = 0; i < vectOfPieces->size(); i++)
    {
        delete vectOfPieces->at(i);
    }
    delete vectOfPieces;
}
