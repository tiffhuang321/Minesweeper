//
// Created by tiffh on 11/15/2024.
//

#pragma once

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H



#include <unordered_map>
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;



class TextureManager {
    unordered_map<string, sf::Texture> textures;
    sf::Texture tileHidden;
    sf::Texture tileReveal;
    sf::Texture mine;
    sf::Texture flag;
    sf::Texture number1;
    sf::Texture number2;
    sf::Texture number3;
    sf::Texture number4;
    sf::Texture number5;
    sf::Texture number6;
    sf::Texture number7;
    sf::Texture number8;
    sf::Texture number9;
    sf::Texture happy;
    sf::Texture win;
    sf::Texture lose;
    sf::Texture debug;
    sf::Texture pause;
    sf::Texture play;
    sf::Texture leaderboard;
    sf::Texture digits;
public:
    TextureManager() {
        tileHidden.loadFromFile("images/tile_hidden.png");
        tileReveal.loadFromFile("images/tile_revealed.png");
        mine.loadFromFile("images/mine.png");
        flag.loadFromFile("images/flag.png");
        number1.loadFromFile("images/number_1.png");
        number2.loadFromFile("images/number_2.png");
        number3.loadFromFile("images/number_3.png");
        number4.loadFromFile("images/number_4.png");
        number5.loadFromFile("images/number_5.png");
        number6.loadFromFile("images/number_6.png");
        number7.loadFromFile("images/number_7.png");
        number8.loadFromFile("images/number_8.png");
        happy.loadFromFile("images/face_happy.png");
        win.loadFromFile("images/face_win.png");
        lose.loadFromFile("images/face_lose.png");
        debug.loadFromFile("images/debug.png");
        pause.loadFromFile("images/pause.png");
        play.loadFromFile("images/play.png");
        leaderboard.loadFromFile("images/leaderboard.png");
        digits.loadFromFile("images/digits.png");

        textures["T_Hidden"] = tileHidden;
        textures["T_Reveal"] = tileReveal;
        textures["Mine"] = mine;
        textures["Flag"] = flag;
        textures["Number1"] = number1;
        textures["Number2"] = number2;
        textures["Number3"] = number3;
        textures["Number4"] = number4;
        textures["Number5"] = number5;
        textures["Number6"] = number6;
        textures["Number7"] = number7;
        textures["Number8"] = number8;
        textures["happy"] = happy;
        textures["win"] = win;
        textures["lose"] = lose;
        textures["debug"] = debug;
        textures["pause"] = pause;
        textures["play"] = play;
        textures["leaderboard"] = leaderboard;
        textures["digits"] = digits;

    }
    sf::Texture* operator()(const string& name) {
        return &textures[name];
        }

    // set up sprites in the class and return pointers to them, just like the texture
    // set the pos so it can be redrawn in a diff location?
};

// NOTE: careful with the texture manager...
#endif //TEXTUREMANAGER_H