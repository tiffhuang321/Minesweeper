//
// Created by tiffh on 11/25/2024.
//

#include "Button.h"
#include "TextManager.h"


Button::Button(int rows, int cols) {
    Default = nullptr;
    x = rows;
    y = cols;
};
void Button::draw(sf::RenderWindow& window) const{
    window.draw(sprite);
}
bool Button::click(float x, float y) const{
    if (sprite.getGlobalBounds().contains(x, y)) {
        return true;
    }
    return false;
}

// Smile
Smile::Smile(int rows, int cols) : Button (rows, cols) {
    Default = TM("happy");
    win = TM("win");
    lose = TM("lose");

    x = ((rows/2.0) * 32) - 32;
    y = 32 * (cols+0.5);

    sprite.setTexture(*Default);
    sprite.setPosition(x, y);
}
bool Smile::click(float x, float y){
    if (sprite.getGlobalBounds().contains(x, y)) {
        sprite.setTexture(*Default);
        return true;
    }
    return false;
}
void Smile::setFace(const string& face_name) {
    if (face_name == "win") {
        sprite.setTexture(*win);
    }
    else if (face_name == "lose") {
        sprite.setTexture(*lose);
    }
}

// Debug
DebugButton::DebugButton(int rows, int cols) : Button(rows, cols) {
    Default = TM("debug");

    x = rows*32 - 304;
    y = 32 * (cols+0.5);
    sprite.setTexture(*Default);
    sprite.setPosition(x, y);
}

// Pause Button
PauseButton::PauseButton(int rows, int cols) : Button(rows, cols) {
    Default = TM("pause");
    pause = TM("play");
    clicked = false;

    x = rows*32 - 240;
    y = 32 * (cols+0.5);
    sprite.setTexture(*Default);
    sprite.setPosition(x, y);
}
void PauseButton::click() {
    if (sprite.getGlobalBounds().contains(x, y)) {
        if (!clicked) {
            sprite.setTexture(*pause);
            clicked = true;
        }
        else {
            sprite.setTexture(*Default);
            clicked = false;
        }

    }
}
bool PauseButton::getSprite(int x, int y) const{
    if (sprite.getGlobalBounds().contains(x, y)) {
        return true;
    }
    return false;
}
bool PauseButton::wasClicked() const {
    return clicked;
}
// Leaderboard
Leaderboard::Leaderboard(int rows, int cols) : Button(rows, cols) {
    Default = TM("leaderboard");
    ifstream file("files/leaderboard.txt");
    window_width = rows * 16; // 25 * 16
    window_height = cols * 16 + 50; // 16 * 16 + 50
    x = rows*32 -176;
    y = 32 * (cols+0.5);
    clicked = false;

    sprite.setTexture(*Default);
    sprite.setPosition(x, y);

    string name, time;

    while (getline(file, name, ',')) {
        getline(file, time);
        leaderboard.emplace_back(name, time);
    }


}
void Leaderboard::write_content() {
    content = "";

    for (int i = 0; i < 5; i++) {
        content += to_string(i+1) + ".\t" + leaderboard[i].first + "\t" + leaderboard[i].second + "\n\n";
    }
}
void Leaderboard::update(const string& name, const string& time) {
    // first find if existing names include the asterisk
    // remove
    for (int i = 0; i<leaderboard.size(); i++) {
        if (leaderboard[i].second.find('*')!=string::npos) {

            leaderboard[i].second.pop_back();
        }
    }

    // append the new score with asterisk
    leaderboard.emplace_back(time, " " + name + "*");
    // linear sort start
    for (int i = 1; i < leaderboard.size(); i++) {

        const pair<string, string> current = leaderboard[i];
        int j = i - 1;
        string str = leaderboard[i].first; // = i
        const int score = stoi(str.substr(0,2) + str.substr(3, 2));


        while (j>=0) {
            string str2 = leaderboard[j].first; // j = i-1
            const int temp = stoi(str2.substr(0,2) + str2.substr(3, 2));
            if (score >= temp) break;

            leaderboard[j+1] = leaderboard[j];
            j--;
        }
        leaderboard[j+1] = current;

    }
    ofstream file("files/leaderboard.txt");
    for (int i = 0; i < 5; i++) {
        if (leaderboard[i].second.find('*')!=string::npos) {
            file << leaderboard[i].first + "," + leaderboard[i].second.substr(0, leaderboard[i].second.size()-1) << endl;
        }
        else {
            file << leaderboard[i].first + "," + leaderboard[i].second << endl;
        }

    }

}

void Leaderboard::Window(Timer& timer, Board& board, PauseButton& pause) {

    sf::RenderWindow window;
    window.create(sf::VideoMode(window_width + 50, window_width), "Minesweeper Leaderboard");
    write_content();

    TextManager leaderboardText(sf::Color::White, "LEADERBOARD", 20, sf::Text::Bold);
    TextManager content(sf::Color::White, this->content, 18, sf::Text::Bold);

    leaderboardText.getText().setStyle(sf::Text::Bold | sf::Text::Underlined);
    leaderboardText.setText(window_width/2, window_height/2-120);
    content.setText(window_width/2, window_height/2+20);


    while (window.isOpen()) {

        sf::Event event;

        // close leaderboard
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                if (!board.Win() && !board.Lose() && !pause.wasClicked()) {
                    timer.Resume();
                    board.togglePause();
                }
                clicked = false;
                window.close();

            }
        }

        // Graphical Interface here
        window.clear(sf::Color::Blue);
        window.draw(leaderboardText.getText());
        window.draw(content.getText());
        window.display();
    }
}
bool Leaderboard::Open() const {

    return clicked;
}
void Leaderboard::click() {
    clicked = true;
}
void Leaderboard::getboard() {
    for (int i = 0; i < leaderboard.size(); i++) {
        cout << leaderboard[i].first << " " << leaderboard[i].second << endl;
    }
}
sf::Sprite& Leaderboard::getSprite() {
    return sprite;
}