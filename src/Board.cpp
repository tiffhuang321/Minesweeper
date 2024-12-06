//
// Created by tiffh on 11/15/2024.
//

#include "Board.h"
#include <cmath>
#include <fstream>
#include <random>
#include <set>
Board::Board(const string& fileName) {
    ifstream file(fileName);
    string c;
    string r;
    string m;
    flags = 0;

    getline(file, r);
    getline(file, c);
    getline(file, m);

    rows = stoi(r);
    cols = stoi(c);
    mines = stoi(m);
    file.close();

    revealed_Tiles = 0;
    tiles.resize(rows);

    for (int x = 0; x < rows; x++) {
        tiles[x].reserve(cols);
        for (int y = 0; y < cols; y++) {
            // x and y correspond to where on the screen the top-left corner of the tile sprite should be
            // x = row, y = column
            // each tile contains its own information & sprite
            tiles[x].emplace_back(TM("T_Hidden"),
                TM("T_Reveal"),
                x*32, y*32);
        }
    }


    random_device randrow;
    random_device randcolumn;
    uniform_int_distribution<int> dist(0, rows-1);
    uniform_int_distribution<int> dist2(0, cols-1);

    // generating mines
    while (mineCoord.size() != mines) {
        int rrow = dist(randrow);
        int rcolumn = dist2(randcolumn);
        if (mineCoord.insert({rrow, rcolumn}).second) {
            tiles[rrow][rcolumn].setMine();
        }
    }

    // setting up neighboring Tiles after everything else is set
    int rowX[] = {-1, -1, -1 , 0, 0, 1, 1, 1};
    int colY[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            for (int n = 0; n<8 ; n++) {
                if (rowX[n] + i >= 0 && rowX[n]+i < rows) {      // if column plus everything within the array is within the valid range
                    if (colY[n] + j >= 0 && colY[n]+j < cols) {  // if row is within the valid range
                        tiles[i][j].AdjacentTiles().push_back(&tiles[rowX[n] + i][colY[n] + j]); // pass the memory address of the target tiles
                    }
                }
            }
            // finish assigning adjacent tiles

            // count the number of adjacent mines
        }
    }
    setAdjacentMines();
    // Adjacent tiles setup end

}

void Board::drawBoard(sf::RenderWindow& window) {

    // drawing tile : match to size of the vector
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            const float XPOS = tiles[x][y].get_sprite().getPosition().x;
            const float YPOS = tiles[x][y].get_sprite().getPosition().y;

            window.draw(tiles[x][y].get_sprite());
            if (debug_on && !paused) {
                sf::Sprite debugMine;
                debugMine.setTexture(*TM("Mine"));
                if (tiles[x][y].isMine()) {
                    debugMine.setPosition(XPOS, YPOS);
                    window.draw(debugMine);
                }
            }
            if (paused) {
                sf::Sprite pause;
                pause.setTexture(*TM("T_Reveal"));
                pause.setPosition(XPOS, YPOS);
                window.draw(pause);

            }
            if (!paused && !debug_on) {
                string state;

                // drawing flags
                if (tiles[x][y].Flagged() && !tiles[x][y].isRevealed()) {
                    state = "Flag";
                }

                // drawing mines
                else if (tiles[x][y].isMine() && tiles[x][y].isRevealed()) {
                    state = "Mine";
                }

                // drawing nums
                else if (!tiles[x][y].isMine() && tiles[x][y].isRevealed() && tiles[x][y].AdjacentMines() > 0) {
                    state = "Number" + to_string(tiles[x][y].AdjacentMines());
                }

                if (!state.empty()) {
                    sf::Sprite tileState;
                    tileState.setPosition(XPOS, YPOS);
                    tileState.setTexture(*TM(state));

                    window.draw(tileState);
                }

            } // normal mode

            // lose
            if (lose) {
                sf::Sprite mine;
                mine.setTexture(*TM("Mine"));

                if (tiles[x][y].isMine()) {
                    tiles[x][y].click();
                    mine.setPosition(XPOS, YPOS);
                    if (tiles[x][y].Flagged()) {
                        window.draw(mine);
                    }

                }
            }

        }
    }


}
bool Board::tileSelected(int x, int y) const{
    if (x < rows && y < cols) {
        return true;
    }
    return false;
}

Tile* Board::getTile(int x, int y) {
    int row = floor(x / 32);
    int col = floor(y / 32);

    if (tileSelected(row, col)) {
        return &tiles[row][col];
    }
    return nullptr;
}
// void Board::revealMines(sf::RenderWindow& window) {
//     sf::Sprite mine;
//     mine.setTexture(*TM("Mine"));
//
//     auto it = mineCoord.begin();
//     for(it; it!=mineCoord.end(); ++it) {
//         tiles[it->first][it->second].click();
//         mine.setPosition(it->first * 32, it->second *32);
//
//         if (tiles[it->first][it->second].Flagged()) {
//
//             cout << "mine" << endl;
//             window.draw(mine);
//             // tiles[it->first][it->second].setFlag();
//         }
//     }
// }
void Board::loseCondition(){
    lose = true;
}
void Board::revealTiles() {
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            if (!tiles[x][y].isMine() && !tiles[x][y].isRevealed()) {
                tiles[x][y].click();
            }
        }
    }
}
void Board::flag_mines() {
    for (auto m : mineCoord) {
        if (!tiles[m.first][m.second].Flagged()) {
            tiles[m.first][m.second].setFlag();
        }
    }
    flags = mines;
}
void Board::setAdjacentMines() {
    for (int x=0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            if (tiles[x][y].isMine()) {
                for (Tile* t : tiles[x][y].AdjacentTiles()) {
                    t->AdjacentMines() += 1;
                }
            }
        }
    }
}

bool Board::Win() const{
    return win;
}
bool Board::Lose() const {
    return lose;
}
void Board::reset() {
    random_device randrow;
    random_device randcolumn;
    uniform_int_distribution<int> dist(0, rows-1);
    uniform_int_distribution<int> dist2(0, cols-1);
    // reset tiles
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            tiles[x][y].reset();
        }
    }
    // clear mines
    mineCoord.clear();
    while (mineCoord.size() != mines) {
        int rrow = dist(randrow);
        int rcolumn = dist2(randcolumn);
        if (mineCoord.insert({rrow, rcolumn}).second) {
            tiles[rrow][rcolumn].setMine();
        }
    }
    setAdjacentMines();
    revealed_Tiles = 0;
    win = false;
    lose = false;


}
void Board::debug(sf::RenderWindow& window) {
    sf::Sprite mine;
    mine.setTexture(*TM("Mine"));

    for (auto m : mineCoord) {
        Tile& t = tiles[m.first][m.second];
        if (!t.isRevealed()) {
            mine.setPosition(m.first*32, m.second*32);
            window.draw(mine);
        }

    }
}
int Board::mineCount() const {
    return mines;
}
int Board::count_flags() {
    flags = 0;
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            if (tiles[x][y].Flagged()) {
                flags+=1;
            }
        }
    }
    return flags;
}
void Board::togglePause() {
    if (paused) {
        paused = false;
    }
    else {
        paused = true;
    }
}
void Board::toggleDebug() {
    if (debug_on) {
        debug_on = false;
    }
    else {
        debug_on = true;
    }
}
bool Board::isDebug() const {
    return debug_on;
}
bool Board::isPaused() const {
    return paused;
}
bool Board::winCondition() {
    revealed_Tiles = 0;
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            if (tiles[x][y].isRevealed()) {
                revealed_Tiles += 1;
            }
        }
    }
    if (revealed_Tiles == (cols*rows-mines)) {

        flag_mines();
        win = true;
        return true;
    }
    return false;
}
