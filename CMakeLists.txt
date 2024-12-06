cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(minesweeper)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Users/tiffh/CLionProjects/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(minesweeper main.cpp
        Tile.h
        Board.h
        TextureManager.h
        Board.cpp
        Tile.cpp
        TextManager.h
        Button.h
        Button.cpp
        Digits.h
        Digits.cpp
)
target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio)