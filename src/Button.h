//
// Created by tiffh on 11/16/2024.
//


#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <fstream>
#include "Digits.h"
#include "Board.h"

using namespace std;

class Button {
protected:
    sf::Texture* Default;
    sf::Sprite sprite;
    TextureManager TM;
    int x;
    int y;

public:
    Button(int rows, int cols);
    void draw(sf::RenderWindow& window) const;
    bool click(float x, float y) const;
};

class Smile : public Button {
    sf::Texture* win;
    sf::Texture* lose;
public:
    Smile(int rows, int cols);
    bool click(float x, float y);
    void setFace(const string& face_name);
};

class DebugButton : public Button {
public:
    DebugButton(int rows, int cols);

};

class PauseButton : public Button {
    sf::Texture* pause;
    bool clicked;
public:
    PauseButton(int rows, int cols);
    void click();
    bool getSprite(int x, int y) const;
    bool wasClicked() const;

};

class Leaderboard : public Button {
    int window_width;
    int window_height;
    vector<pair<string, string>> leaderboard;
    string content;
    bool clicked;

public:
    Leaderboard(int rows, int cols);
    sf::Sprite& getSprite();
    void update(const string& name, const string& time);
    void write_content();
    void Window(Timer& timer, Board& board, PauseButton& pause);
    bool Open() const;
    void click();
    void getboard();
};

#endif //BUTTON_H
