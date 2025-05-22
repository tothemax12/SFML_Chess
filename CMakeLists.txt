cmake_minimum_required(VERSION 3.28)
project(Chess LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
src/Game.h
src/Game.cpp

src/Piece.h
src/Piece.cpp 

src/Pawn.h
src/Pawn.cpp

src/Rook.h
src/Rook.cpp

src/King.h
src/King.cpp

src/Queen.h
src/Queen.cpp

src/Knight.h
src/Knight.cpp

src/Bishop.h
src/Bishop.cpp

src/Board.h
src/Board.cpp
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)