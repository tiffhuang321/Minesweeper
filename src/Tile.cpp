//
// Created by tiffh on 11/15/2024.
//

#include "Tile.h"
using namespace std;


// Pass textures by reference and store by pointer to avoid copying the textures.
// Pass x and y to indicate where on the screen the tile should appear
Tile::Tile(const sf::Texture* up_texture, const sf::Texture* down_texture, int x, int y) {
    hidden = up_texture;
    reveal = down_texture;
    this->sprite = sf::Sprite(*up_texture);

    this->state = Up;
    adjacentMines = 0;

    sprite.setPosition(x, y);

}
sf::Sprite& Tile::get_sprite() {
    return sprite;
}

void Tile::click() {
    if (!flagged) {
        sprite.setTexture(*reveal);
        state = Down;

        // if the tile has adjacent mines then don't click adj tiles
        if (adjacentMines == 0 && !has_mine) {
            // if this tile does not have adj mines and is not a mine, then try clicking adj tiles
            // with the same check:
            for (Tile* tile : adjacentTiles) {
                if (tile->state == Up) {
                    tile->click();
                }
            }

        }
    }


}
bool Tile::isMine() const{
    return has_mine;
}
void Tile::setMine() {
    has_mine = true;
}
bool Tile::isRevealed() const {
    return state;
}
vector<Tile*>& Tile::AdjacentTiles() {
    return adjacentTiles;
}
int& Tile::AdjacentMines() {
    return adjacentMines;
}
bool Tile::Flagged() const{
    return flagged;
}
void Tile::setFlag() {

    // updates each time the user sets/unsets a flag
    if (state == Up) {
        if (flagged) {flagged = false;}
        else {flagged = true;}
    }

}
void Tile::reset() {
    has_mine = false;
    flagged = false;
    adjacentMines = 0;
    if (state == Down) {
        state = Up;
        sprite.setTexture(*hidden);
    }
}