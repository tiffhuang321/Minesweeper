//
// Created by tiffh on 11/27/2024.
//
#include "Digits.h"

Digits::Digits() {

    x=0;
    y=0;
    digitTexture = TM("digits");


    for (int i = 0; i < 11; i++) {
        sf::Sprite sprite;
        sprite.setTexture(*digitTexture);
        sf::IntRect rect(i*21, 0, 21, 32);
        // sf::Sprite sprite = digits;
        // sprite.setTextureRect(rect);
        sprite.setTextureRect(rect);

        digitMap.emplace(i, sprite);
    }

}

// Counter
Counter::Counter(int mineCount, int rows) {
    hundreds = 0;
    tens = 0;
    ones = 0;
    negative = false;
    setCount(mineCount);
    // cols = 25
    // rows = 16
    x = 33;
    y = 32*(rows+0.5) + 16;

    digit1 = digitMap[hundreds];
    digit2 = digitMap[tens];
    digit3 = digitMap[ones];

    sign = digitMap[10];
    sign.setPosition(x-21, y);
    digit1.setPosition(x, y);
    digit2.setPosition(x+21, y);
    digit3.setPosition(x+42, y);


}
void Counter::setCount(int mineCount) {
    if (mineCount < 0) {
        negative = true;
    }
    else {
        negative = false;
    }
    int count = abs(mineCount);
    hundreds = count/100;
    tens = (count/10) % 10;
    ones = count%10;

    digit1 = digitMap[hundreds];
    digit2 = digitMap[tens];
    digit3 = digitMap[ones];

    sign.setPosition(x-21, y);
    digit1.setPosition(x, y);
    digit2.setPosition(x+21, y);
    digit3.setPosition(x+42, y);

}
void Counter::draw(sf::RenderWindow& window) const{
    window.draw(digit1);
    window.draw(digit2);
    window.draw(digit3);
    if (negative) {
        window.draw(sign);
    }
}

// Timer
Timer::Timer(int cols, int rows) {
    pauseTime = chrono::steady_clock::now();
    unPausedTime = chrono::steady_clock::now();
    start_time = chrono::high_resolution_clock::now();
    elapsed_pause = chrono::duration_cast<chrono::duration<int>>(chrono::steady_clock::now() - pauseTime);
    duration = chrono::duration_cast<chrono::duration<int>>(chrono::high_resolution_clock::now() - start_time);
    Time = duration.count();
    paused = false;
    minutes = 0;
    seconds = 0;
    dig1 = dig2 = dig3 = dig4 = 0;
    this->cols = cols;
    this->rows = rows;

    minute1 = digitMap[0];
    minute2 = digitMap[0];
    second1 = digitMap[0];
    second2 = digitMap[0];
    minute1.setPosition(cols*32-97, 32*(rows+0.5)+16);
    minute2.setPosition(cols*32-97+21, 32*(rows+0.5)+16);
    second1.setPosition(cols*32-54, 32*(rows+0.5)+16);
    second2.setPosition(cols*32-54+21, 32*(rows+0.5)+16);
}
void Timer::setTime() {
    totalTime();
    minutes = Time/60;
    seconds = Time%60;

    dig1 = minutes/10;
    dig2 = minutes%10;
    dig3 = seconds/10;
    dig4 = seconds%10;

    if (!paused) {
        minute1 = digitMap[dig1];
        minute2 = digitMap[dig2];
        second1 = digitMap[dig3];
        second2 = digitMap[dig4];
    }

    minute1.setPosition(cols*32-97, 32*(rows+0.5)+16);
    minute2.setPosition(cols*32-97+21, 32*(rows+0.5)+16);
    second1.setPosition(cols*32-54, 32*(rows+0.5)+16);
    second2.setPosition(cols*32-54+21, 32*(rows+0.5)+16);

}
void Timer::draw(sf::RenderWindow& window) const{
    window.draw(minute1);
    window.draw(minute2);
    window.draw(second1);
    window.draw(second2);
}
string Timer::getTime() const{
    string time = to_string(dig1) + to_string(dig2) + ":"
    + to_string(dig3) + to_string(dig4);
    return time;
}
int Timer::totalTime() {
    duration = chrono::duration_cast<chrono::duration<int>>(chrono::high_resolution_clock::now() - start_time);
    Time = duration.count() - elapsed_pause.count();

    return Time;
}
int Timer::getElapsed() const {
    return elapsed_pause.count();
}
void Timer::Pause() {
    paused = true;
    pauseTime = chrono::steady_clock::now();

}
void Timer::Resume() {
    paused = false;
    unPausedTime = chrono::steady_clock::now();
    elapsed_pause += chrono::duration_cast<chrono::duration<int>>(unPausedTime - pauseTime);
    // elapsed_pause should == 0 if resumed without pause
}
void Timer::Reset() {
    paused = false;
    pauseTime = chrono::steady_clock::now();
    start_time = chrono::high_resolution_clock::now();
    elapsed_pause = chrono::duration_cast<chrono::duration<int>>(chrono::steady_clock::now() - pauseTime);
}
bool Timer::isPaused() const {
    return paused;
}