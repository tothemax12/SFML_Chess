#include "Game.h"
#include <iostream>

// void SoundPlayer::playSound(std::string soundID) {

// }

// void SoundPlayer::stopSound() {

// }

// SoundPlayer::SoundPlayer()
// {
//     soundBuffer.loadFromFile("sound path");
//     currentSoundEffectPlaying.setBuffer(soundBuffer);
// }

// SoundPlayer::~SoundPlayer() {

// }
MainMenuState::MainMenuState(sf::RenderWindow* window) : 
face1Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/aqua-man-face.png"),
face2Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/b-king-face.png"),
face3Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/elec-man-face.png"),
face4Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/enemy-face.png"),
face5Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/guts-man-face.png"),
face6Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/mega-man-face.png"),
face7Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/proto-man-face.png"),
face8Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/roll-face.png"),
face9Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/slash-man-face.png"),
face10Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/white-pawn-face.png"),
face11Texture("/home/max/SFML_Chess/res/mmbn-chess-assets/bass-face.png"),
face1Sprite(face1Texture),
face2Sprite(face2Texture),
face3Sprite(face3Texture),
face4Sprite(face4Texture),
face5Sprite(face5Texture),
face6Sprite(face6Texture),
face7Sprite(face7Texture),
face8Sprite(face8Texture),
face9Sprite(face9Texture),
face10Sprite(face10Texture),
face11Sprite(face11Texture),

mainMenuBackGroundTexture("/home/max/SFML_Chess/res/mmbn-chess-assets/main-menu-background.png"),
mainMenuLogoTexture("/home/max/SFML_Chess/res/mmbn-chess-assets/main-menu-logo.png"),
mainMenuMusic(sf::Music("/home/max/SFML_Chess/res/mmbn-chess-assets/4-hometown-101soundboards.mp3")),
mainMenuBackGroundImageSprite(mainMenuBackGroundTexture),
mainMenuLogoImageSprite(mainMenuLogoTexture)
{   
    this->window = window;
    stateIsActive = true;

    //init the queues by putting random sprites in it
    srand(time(0));
    int randNum = rand() % arrayOfSprites.size();
    int lastRandNum = randNum;
    int numOfSprites = 7;
    for (int i = 0; i < numOfSprites+1; i++) {
        while(randNum == lastRandNum) {
            randNum = rand() % arrayOfSprites.size();
        }
        lastRandNum = randNum;

        leftSideSprites.push_back(arrayOfSprites[randNum]);
    }

    for (int i = 0; i < numOfSprites+1; i++) {
        while(randNum == lastRandNum) {
            randNum = rand() % arrayOfSprites.size();
        }
        lastRandNum = randNum;
        
        rightSideSprites.push_back(arrayOfSprites[randNum]);
    }

    int y = 10;
    for (int i = 0; i < numOfSprites+1; i++) {
        leftSideSprites.at(i).setPosition({10, y});
        rightSideSprites.at(i).setPosition({535, y});
        y+=125;
    }

    // for (int i = 0; i < arrayOfSprites.size(); i++) {
    //     arrayOfSprites.at(i).setPosition({10, y});
    //     //window->draw(*leftSideSprites[i]);
    //     //window->draw(*rightSideSprites[i]);
    //     y += 15;
    // }

}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::moveSides() {
    
    for (int i = 0; i < leftSideSprites.size(); i++) {
        leftSideSprites.at(i).setPosition({(leftSideSprites.at(i).getPosition().x), (leftSideSprites.at(i).getPosition().y+1)});
        rightSideSprites.at(i).setPosition({(rightSideSprites.at(i).getPosition().x), (rightSideSprites.at(i).getPosition().y-1)});

    }

    // for (int i = 0; i < rightSideSprites.size(); i++) {
    //     rightSideSprites.at(i).setPosition({(rightSideSprites.at(i).getPosition().x), (rightSideSprites.at(i).getPosition().y-1)});
    // }
}

void MainMenuState::drawSides() {
    for (int i = 0; i < leftSideSprites.size(); i++) {
        window->draw(leftSideSprites[i]);
        window->draw(rightSideSprites[i]);
        //window->draw(arrayOfSprites[i]);
    }

    // for (int i = 0; i < rightSideSprites.size(); i++) {
    //     //window->draw(*leftSideSprites[i]);
    //     window->draw(*rightSideSprites[i]);
    // }
}

void MainMenuState::cycleImages() {
    srand(time(0));
    int randNum = rand() % arrayOfSprites.size();
    for (int i = 0; i < leftSideSprites.size(); i++) {
        if (leftSideSprites.at(i).getPosition().y+114 == 754) {
            leftSideSprites.erase(leftSideSprites.begin()+i);

            leftSideSprites.push_back(arrayOfSprites[randNum]);
            
            leftSideSprites.at(leftSideSprites.size()-1).setPosition({10, -114});
            break;
        }
    } 

    for (int i = 0; i < rightSideSprites.size(); i++) {
        if (rightSideSprites.at(i).getPosition().y == -114) {
            rightSideSprites.erase(rightSideSprites.begin()+i);

            rightSideSprites.push_back(arrayOfSprites[randNum]);
            
            rightSideSprites.at(rightSideSprites.size()-1).setPosition({535, 755});
            break;
        }
    } 
}

void MainMenuState::handleInput() 
{
    //handle input
    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window->close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            stateIsActive = false;
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window->close();
        } else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            stateIsActive = false;
        }
    }
}

void MainMenuState::draw()
{
    mainMenuMusic.play();

    while (stateIsActive) {
        handleInput();
        window->draw(mainMenuBackGroundImageSprite);
        drawSides();
        window->draw(mainMenuLogoImageSprite);
        window->display();
        moveSides();
        cycleImages();
        sf::sleep(sf::milliseconds(10));
    }

    mainMenuMusic.stop();
    stateIsActive = true;
}


Game::Game(
         sf::Texture* whiteWinsScreenTexture,
         sf::Texture* blackWinsScreenTexture,
         sf::Texture* boardTexture, 
         sf::Texture* highlightedSquareTexture, 
         sf::Texture* wPawnTexture,
         std::vector<Animation> wPawnAnimations,
         sf::Texture* wRookTexture,
         std::vector<Animation> wRookAnimations,
         sf::Texture* wKingTexture,
         std::vector<Animation> wKingAnimations,
         sf::Texture* wQueenTexture,
         std::vector<Animation> wQueenAnimations,
         sf::Texture* wKnightTexture,
         std::vector<Animation> wKnightAnimations,
         sf::Texture* wBishopTexture,
         std::vector<Animation> wBishopAnimations,
         sf::Texture* wPawnPromotionMenuTexture,
         sf::Texture* bPawnTexture, 
         sf::Texture* bRookTexture, 
         sf::Texture* bKingTexture, 
         sf::Texture* bQueenTexture,
         sf::Texture* bKnightTexture,
         sf::Texture* bBishopTexture,
         sf::Texture* bPawnPromotionMenuTexture) : 
whiteTeamWinsSprite(*whiteWinsScreenTexture),
blackTeamWinsSprite(*blackWinsScreenTexture),
boardTexture(boardTexture),
highlightedSquareTexture(highlightedSquareTexture), 
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
window(sf::RenderWindow(sf::VideoMode({640, 640}), "SFML works!")),
board(whiteWinsScreenTexture,
    blackWinsScreenTexture,
    boardTexture, 
      highlightedSquareTexture, 
      wPawnTexture, 
      wPawnAnimations,
      wRookTexture, 
      wRookAnimations,
      wKingTexture, 
      wKingAnimations,
      wQueenTexture,
      wQueenAnimations,
      wKnightTexture,
      wKnightAnimations,
      wBishopTexture,
      wBishopAnimations,
      wPawnPromotionMenuTexture, 
      bPawnTexture, 
      bRookTexture, 
      bKingTexture, 
      bQueenTexture,
      bKnightTexture,
      bBishopTexture,
      bPawnPromotionMenuTexture, 
      &(this->window))
{
    //window = sf::RenderWindow(sf::VideoMode({640, 640}), "SFML works!");
}

Game::~Game()
{

}

sf::RenderWindow* Game::getWindow() {
    sf::RenderWindow* windowPtr = &window;
    return windowPtr;
}


//need a visual tool to debug the spaces (validMoves) the pieces can move or I am going
//to go bonkers bananas
void Game::debugValidMoves() {
//I want to be able to display a board with some pieces
//click a piece on the board and have the square that are valid highlighted
    
    int mouseX = -1;
    int mouseY = -1;
    int strIndex = -1;

    std::vector<int> validMoves;
    std::vector<Piece*>* piecesCurrentlyOnBoard = board.getPiecesCurrentlyOnBoard();
    int* weirdCord = &piecesCurrentlyOnBoard->at(0)->cord;
    std::vector<int> currentCapturableSpacesForASide = board.getAllCapturableSpacesForAGivenSide("White", *board.getBoardStr(), board.getPiecesCurrentlyOnBoard());

    while(true) {
        window.clear();
        board.drawBoard(&window);
        board.drawPiecesCurrentlyOnBoard(&window);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            } else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                mouseX = mouseButtonPressed->position.x;
                mouseY = mouseButtonPressed->position.y;

                std::cout << "Mouse cords " << mouseX << " " << mouseY << "\n";
                std::cout << "String index " << strIndex << "\n";
                strIndex = board.convertBoardCordsToStringIndex(mouseX, mouseY);

                //printf("%d", strIndex);
            }
        }

        if (mouseX > -1 && mouseY > -1) {

            validMoves = handleClick(mouseX, mouseY);

            //board.printBoard(*board.getBoardStr());
        }

        // for (int i = 0; i < currentCapturableSpacesForASide->size(); i++)
        // {
        //     std::cout << "current capturable spaces for white team: " << currentCapturableSpacesForASide->at(i) << " \n";
        // }
        

        // if (validMoves != nullptr) {
        //     board.drawHighlightedValidMoves(&window, validMoves);
        //     //board.drawHighlightedValidMoves(&window, currentCapturableSpacesForASide);
        // }
        board.drawHighlightedValidMoves(&window, validMoves);
        
        bool sideIsInCheckMate = false;
        sideIsInCheckMate = board.sideIsInCheckMate("White");
        std::cout << "White is in checkmate: " << sideIsInCheckMate << "\n";
        
        window.display();

        mouseX = -1;
        mouseY = -1;
        strIndex = -1;
    }
}

void Game::drawWinnerInformation(bool whiteTeamWon) {
    if (whiteTeamWon) {
        window.clear();
        board.drawBoard(&window);
        board.drawPiecesCurrentlyOnBoard(&window);
        window.draw(whiteTeamWinsSprite);
        window.display();
    } else {
        window.clear();
        board.drawBoard(&window);
        board.drawPiecesCurrentlyOnBoard(&window);
        window.draw(blackTeamWinsSprite);
        window.display();
    }
}

void Game::draw(std::vector<int> validMovesOfClickedPiece) {
    //debugValidMoves();

    //board.printBoard(*board.getBoardStr());
    // std::vector<int>* validMoves = board.testPawn1.getValidMoves();

    // printf("valid moves: \n");
    // for (int i = 0; i < validMoves->size(); i++)
    // {
    //     printf("%d \n", validMoves->at(i));
    // }
    
    window.clear();
    board.drawBoard(&window);
    board.drawPiecesCurrentlyOnBoard(&window);
    board.drawHighlightedValidMoves(&window, validMovesOfClickedPiece);
    window.display();
}

//returns a pointer to a piece to the piece of the click
//if the user clicked a blank space return nullptr
Piece* Game::getPieceThatWasClicked(int mouseX, int mouseY) {
    Piece* pieceToReturn = nullptr;

    int strIdxOfClick = board.convertBoardCordsToStringIndex(mouseX, mouseY);
    std::vector<Piece*>* piecesCurrentlyOnBoard = board.getPiecesCurrentlyOnBoard();

    for (int i = 0; i < piecesCurrentlyOnBoard->size(); i++) {
        //std::cout << "i: " << i << "\n";
        //std::cout << "ith piece cord: " << piecesCurrentlyOnBoard->at(i)->cord << "\n";
        //if there is a piece at the clicked square print the valid moves it can make
        if (piecesCurrentlyOnBoard->at(i)->cord == strIdxOfClick) {

            pieceToReturn = piecesCurrentlyOnBoard->at(i);

            //hit the piece we clicked, we are done
            break;
        }
    }

    return pieceToReturn;
}

//maybe handleClick should return the valid moves of the clicked space, (empty if blank space)
//or if there was a piece already clicked, then proceed with the movement
//this function is for debugging moving the pieces around
std::vector<int> Game::handleClick(int mouseX, int mouseY) {
    std::vector<int> emptyListOfValidMoves;
    std::vector<int> validMovesToReturn;

    static Piece* clickedPiece = nullptr;
    std::vector<int> clickedPiecesValidMoves;
    int strIdxOfClick = board.convertBoardCordsToStringIndex(mouseX, mouseY);
    int displayedValidMove;

    //if a piece was previously clicked see if they clicked one of it's valid moves
    if (clickedPiece != nullptr) {
        //for clicked pieces valid moves
        std::vector<int> piecesValidMoves = clickedPiece->getValidMoves();
        
        
        for (int i = 0; i < piecesValidMoves.size(); i++) {
            //if they clicked a valid move

            //might be negative for a special move
            displayedValidMove = abs(piecesValidMoves.at(i));
            if (displayedValidMove == strIdxOfClick) {
                //clickedPiece->movePiece(piecesValidMoves->at(i), board.getBoardStr(), board.getPiecesCurrentlyOnBoard(), false);

                //begin that pieces move procedure (on the real board)
                clickedPiece->movePiece(turnCount, piecesValidMoves.at(i), board.getBoardStr(), board.getPiecesCurrentlyOnBoard(), false);
                //printf("clicked a valid move location for the selected piece\n");

                clickedPiece = nullptr;
                validMovesToReturn = emptyListOfValidMoves;
                //return validMovesToReturn;
            }
        }
        //if they didn't click a valid move,
        //get the piece of that new space and exit this function
        clickedPiece = getPieceThatWasClicked(mouseX, mouseY);
        if (clickedPiece == nullptr) {
            validMovesToReturn = emptyListOfValidMoves;
        } else {
            validMovesToReturn = clickedPiece->getValidMoves();
        }
    } else {
        //get the information from the click
        clickedPiece = getPieceThatWasClicked(mouseX, mouseY);

        if (clickedPiece != nullptr) {
            clickedPiecesValidMoves = clickedPiece->getValidMoves();
            validMovesToReturn = clickedPiecesValidMoves;
        } else if (clickedPiece == nullptr) {
            validMovesToReturn = emptyListOfValidMoves;
        }
    }

    return validMovesToReturn;
}

//returns a list of valid moves based on the clicked space
std::vector<int> Game::getValidMovesOfClickedPiece(Piece* clickedPiece) {
    std::vector<int> validMovesOfClickedPiece;
    
    if (clickedPiece != nullptr) {
        validMovesOfClickedPiece = clickedPiece->getValidMoves();
    }

    return validMovesOfClickedPiece;
}

//returns the strIndex of the valid move that was clicked, otherwise
//returns -1 if it was not a valid space
int Game::playerClickedAValidMoveLocation(std::vector<int> validMoves, int strIdxOfClick) {
    int idxOfClickedValidMove = -1;
    int displayedValidMove;

    for (int i = 0; i < validMoves.size(); i++) {
        //if they clicked a valid move

        //might be negative for a special move
        displayedValidMove = abs(validMoves.at(i));
        if (displayedValidMove == strIdxOfClick) {
            idxOfClickedValidMove = validMoves.at(i);
        }
    }

    return idxOfClickedValidMove;
}

void Game::checkIfCorrectTeamAndMovePiece(Piece* clickedPiece, int clickedValidSpace) {
    if (whiteTurn && isupper(clickedPiece->pieceIcon) || !whiteTurn && islower(clickedPiece->pieceIcon)) {
        clickedPiece->movePiece(turnCount, clickedValidSpace, board.getBoardStr(), board.getPiecesCurrentlyOnBoard(), false);

        whiteTurn = !whiteTurn;

        if (whiteTurn) {
            currentTeam = "White";
        } else {
            currentTeam = "Black";
        }

        turnCount++;
    }    
}

std::vector<int> Game::handleClickGame(int mouseX, int mouseY) {
    std::vector<int> emptyListOfValidMoves;
    std::vector<int> validMovesToReturn;

    static Piece* clickedPiece = nullptr;
    std::vector<int> clickedPiecesValidMoves;
    int strIdxOfClick = board.convertBoardCordsToStringIndex(mouseX, mouseY);

    //if a piece was previously clicked see if they clicked one of it's valid moves
    if (clickedPiece != nullptr) {

        // //ensure the correct teams piece was clicked
        // if (!(whiteTurn && isupper(clickedPiece->pieceIcon) || !whiteTurn && islower(clickedPiece->pieceIcon))) {
        //     clickedPiece = nullptr;
        // }

        int clickedValidSpace;
        //for clicked pieces valid moves
        std::vector<int> piecesValidMoves = clickedPiece->getValidMoves();
        clickedValidSpace = playerClickedAValidMoveLocation(piecesValidMoves, strIdxOfClick);
        
        if (clickedValidSpace != -1) {
            checkIfCorrectTeamAndMovePiece(clickedPiece, clickedValidSpace);

            //completed move for that piece, reset for the next time
            clickedPiece = nullptr;
            validMovesToReturn = emptyListOfValidMoves;
        } else {
            //if they didn't click a valid move,
            //get the piece of that new space and exit this function
            clickedPiece = getPieceThatWasClicked(mouseX, mouseY);

            if (clickedPiece != nullptr && !(whiteTurn && isupper(clickedPiece->pieceIcon) || !whiteTurn && islower(clickedPiece->pieceIcon))) {
                clickedPiece = nullptr;
            }

            if (clickedPiece == nullptr) {
                validMovesToReturn = emptyListOfValidMoves;
            } else {
                validMovesToReturn = clickedPiece->getValidMoves();
            }

        }
    } else {//if a piece was not clicked previously
        //get the information from the click
        clickedPiece = getPieceThatWasClicked(mouseX, mouseY);
        
        if (clickedPiece != nullptr && !(whiteTurn && isupper(clickedPiece->pieceIcon) || !whiteTurn && islower(clickedPiece->pieceIcon))) {
            clickedPiece = nullptr;
        }

        //return the list of valid moves for the new clicked piece? why
        if (clickedPiece != nullptr) {
            clickedPiecesValidMoves = clickedPiece->getValidMoves();
            validMovesToReturn = clickedPiecesValidMoves;
        } else if (clickedPiece == nullptr) {
            validMovesToReturn = emptyListOfValidMoves;
        }
    }

    return validMovesToReturn;
}

std::array<int, 2> Game::checkInput() {
    std::array<int, 2> clickCords = {-1, -1};

      while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                clickCords[0] = -999;
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                    clickCords[0] = -999;
                }
            } else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                clickCords[0] = mouseButtonPressed->position.x;
                clickCords[1] = mouseButtonPressed->position.y;
            }
        }

    return clickCords;
}

int Game::playGame() {
    std::array<int, 2> clickCords = {-1, -1};
    std::vector<int> validMovesOfClickedPiece;
    bool whiteTeamWon = false;

    while(!currentPlayerIsInCheckmate) {
        clickCords = checkInput();

        if (clickCords[0] != -1) {
           validMovesOfClickedPiece = handleClickGame(clickCords[0], clickCords[1]);
        }

        if (clickCords[0] == -999 && clickCords[1] == -1) {
            return -1;
        }

        currentPlayerIsInCheckmate = board.sideIsInCheckMate(currentTeam);

        draw(validMovesOfClickedPiece);
    }

    if (currentTeam == "Black") {
        whiteTeamWon = true;
    } else {
        whiteTeamWon = false;
    }

    //end game loop
    while(true) {
        clickCords = checkInput();
        drawWinnerInformation(whiteTeamWon);
    }

    return -1;
}