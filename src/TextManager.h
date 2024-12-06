//
// Created by tiffh on 11/16/2024.
//


#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class TextManager {
    sf::Font font;
    sf::Text text;


public:
    TextManager(sf::Color color, const string& message, int size, sf::Uint32 style) {
        font.loadFromFile("files/font.ttf");
        text.setFont(font);
        text.setString(message);
        text.setCharacterSize(size);
        text.setFillColor(color);
        text.setStyle(style);
    }
    void setText(float x, float y) {
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,
            textRect.top + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(x, y));
    }
    sf::Text& getText() {
        return text;
    }

};

#endif //TEXTMANAGER_H
