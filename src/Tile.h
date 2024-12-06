//
// Created by tiffh on 11/6/2024.
//

#ifndef TILE_H
#define TILE_H



#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using namespace std;

// Using an enum to track state.
// Enums rename integers, so "Up" will be replaced by '0' when the code compiles, and "Down" will be replaced with '1'
enum TileState {
    Up,
    Down
};

class Tile {
    // Store pointers to texture to avoid storing a copy (it can get very expensive very quickly!)
    TextureManager TM;
    const sf::Texture* hidden;
    const sf::Texture* reveal;

    sf::Sprite sprite;
    TileState state;

    vector<Tile*> adjacentTiles;
    int adjacentMines;
    bool has_mine = false;
    bool flagged = false;  // flag each tile once the player wins


public:

    Tile(const sf::Texture* up_texture, const sf::Texture* down_texture, int x, int y);
    sf::Sprite& get_sprite();
    void click();
    bool isMine() const;
    bool isRevealed() const;
    void setMine();
    vector<Tile*>& AdjacentTiles();
    int& AdjacentMines();
    bool Flagged() const;
    void setFlag();
    void reset();
};

#endif //TILE_H