//
// Created by tiffh on 11/26/2024.
//

#ifndef DIGITS_H
#define DIGITS_H

#include "TextureManager.h"
#include <chrono>

class Digits {
protected:
    map<int, sf::Sprite> digitMap; // map of all the individual digits
    sf::Texture* digitTexture;
    TextureManager TM;
    int x;
    int y;

public:
    Digits();
};

class Counter : private Digits {
    sf::Sprite sign;
    sf::Sprite digit1;
    sf::Sprite digit2;
    sf::Sprite digit3;

    int hundreds;
    int tens;
    int ones;
    bool negative;
public:
    Counter(int mineCount, int rows);
    void setCount(int mineCount);
    void draw(sf::RenderWindow& window) const;
};

class Timer: private Digits {
    bool paused;
    sf::Sprite minute1;
    sf::Sprite minute2;
    sf::Sprite second1;
    sf::Sprite second2;

    int minutes;
    int seconds;
    int cols;
    int rows;

    int dig1;
    int dig2;
    int dig3;
    int dig4;

    // taken from Timer demo
    chrono::steady_clock::time_point pauseTime;
    chrono::steady_clock::time_point unPausedTime;
    chrono::high_resolution_clock::time_point start_time;
    chrono::duration<int> elapsed_pause;
    chrono::duration<int> duration;
    int Time;

public:
    Timer(int cols, int rows);
    void setTime();
    void draw(sf::RenderWindow& window) const;
    string getTime() const;
    int totalTime();
    int getElapsed() const;
    void Pause();
    void Resume();
    void Reset();
    bool isPaused() const;

};
#endif //DIGITS_H
