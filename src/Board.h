//
// Created by tiffh on 11/15/2024.
//

#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <set>
#include <vector>
#include "TextureManager.h"

using namespace std;


class Board {
    int rows;
    int cols;
    int mines;
    int flags;

    int revealed_Tiles;
    TextureManager TM;
    vector<vector<Tile>> tiles;
    set<pair<int, int>> mineCoord;

    bool paused = false;
    bool debug_on = false;
    bool win = false;
    bool lose = false;


public:
    explicit Board(const string& fileName);
    void drawBoard(sf::RenderWindow& window);
    bool tileSelected(int x, int y) const;
    Tile* getTile(int x, int y);
    //void revealMines(sf::RenderWindow& window);
    void revealTiles();
    void flag_mines();
    void reset();
    void setAdjacentMines();
    void debug(sf::RenderWindow& window);
    bool Win() const;
    bool Lose() const;
    int mineCount() const;
    int count_flags();
    void togglePause();
    void toggleDebug();
    bool isPaused() const;
    bool isDebug() const;
    bool winCondition();
    void loseCondition();

};

#endif //BOARD_H
