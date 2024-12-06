#include <iostream>
#include <SFML/Graphics.hpp>

#include "Board.h"
#include "TextManager.h"
#include <cmath>
#include "Button.h"


using namespace std;

int main() {
    ifstream file("files/config.cfg");

    int col;
    int row;
    int mines;
    file >> col >> row >> mines;
    file.close();

    sf::RenderWindow window;

    int window_width = col*32;
    int window_height = row*32 + 100;
    window.create(sf::VideoMode(window_width, window_height) , "Minesweeper");

    // load welcome text
    string welcome = "WELCOME TO MINESWEEPER!";
    string enter = "Enter your name: ";
    string inputName = "|";

    TextManager enter_name(sf::Color::White, enter, 20, sf::Text::Bold);
    TextManager welcome_text(sf::Color::White, welcome, 24, sf::Text::Underlined);
    TextManager player_name(sf::Color::Yellow, inputName, 18, sf::Text::Bold);

    welcome_text.getText().setStyle(sf::Text::Bold|sf::Text::Underlined);
    welcome_text.setText(window_width/2, window_height/2-150);
    enter_name.setText(window_width/2, window_height/2-75);
    player_name.setText(window_width/2, window_height/2-45);

    //welcome window
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {


            if(event.type == sf::Event::Closed) {
                return 0;
            }
            // checking input
            if (event.type == sf::Event::TextEntered) {
                if (inputName.size() > 1 && event.text.unicode == 13) {
                    window.close();
                }
                if (event.text.unicode == '\b') {
                    if (inputName.length() != 1) {
                        inputName.erase(inputName.end()-2);
                    }
                }
                else if(event.text.unicode < 128 && event.text.unicode != 13
                    && inputName.size() < 11) {

                    if (isalpha(static_cast<char>(event.text.unicode))) {
                        inputName.insert(inputName.end()-1, static_cast<char>(event.text.unicode));
                    }

                }

                // refreshing the text and checking capitalization

                if (!inputName.empty()) {
                    inputName[0] = toupper(inputName[0]);
                    inputName[inputName.size()-1] = tolower(inputName[inputName.size()-1]);
                }
                player_name.getText().setString(inputName);

                // update the length of the name
                player_name.setText(window_width/2, window_height/2-45);
            }

        }

        // render
        window.clear(sf::Color::Blue);

        window.draw(welcome_text.getText());
        window.draw(enter_name.getText());
        window.draw(player_name.getText());

        window.display();
    }

    // game window

    sf::RenderWindow gamewindow;

    gamewindow.create(sf::VideoMode(window_width, window_height), "Minesweeper");
    Board board("files/config.cfg");
    Smile smiley(col, row);
    DebugButton buggy(col, row);
    PauseButton play_button(col, row);
    Leaderboard leaderboard(col, row);

    // counter & timer logic
    Counter counter(mines, row);
    Timer timer(col, row);

    while(gamewindow.isOpen()) {

        sf::Event event;

        while(gamewindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return 0;
            }

            // load the game


            if (event.type == sf::Event::MouseButtonPressed) {

                sf::Vector2i mouse = sf::Mouse::getPosition(gamewindow);
                Tile* selectedTile = board.getTile(mouse.x, mouse.y);

                // if a tile is clicked
                // if the leaderboard is selected
                if (leaderboard.getSprite().getGlobalBounds().contains(mouse.x, mouse.y)) {
                    leaderboard.click();
                    if (!board.isPaused() && !board.Win() && !board.Lose()) {
                        board.togglePause();
                    }
                    timer.Pause();

                }

                else if (selectedTile&& !board.isPaused() && !board.Win() && !board.Lose()) {

                    // left click
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                        selectedTile->click();
                        // board.revealTiles(); // debugging

                        // Lose condition
                        if (selectedTile->isMine() && !selectedTile->Flagged()) {
                            board.loseCondition();
                            smiley.setFace("lose");

                            timer.Pause();
                        }
                        // Win condition
                        else if (board.winCondition()) {
                            smiley.setFace("win");

                            timer.Pause();
                            leaderboard.update(inputName.substr(0, inputName.size()-1), timer.getTime());
                            leaderboard.click();
                        }
                    }
                    // right click
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        selectedTile->setFlag();
                    }

                }

                // if the reset button is clicked
                else if (smiley.click(mouse.x, mouse.y)) {
                    board.reset();
                    timer.Reset();
                    if (board.isPaused()) {
                        play_button.click();
                        board.togglePause();
                    }
                    if (board.isDebug()) {
                        board.toggleDebug();
                    }
                }

                // if the debug button is clicked
                else if (buggy.click(mouse.x, mouse.y) && !board.isPaused() && !board.Win() && !board.Lose()) {
                    board.toggleDebug();
                }

                // if the play button is clicked
                else if (play_button.getSprite(mouse.x, mouse.y) && !board.Lose() && !board.Win()) {
                    play_button.click();
                    board.togglePause();
                    if (board.isPaused()) {
                        timer.Pause();
                    }
                    else {
                        timer.Resume();
                    }

                }


                // update flag counter every click
                int mineNum = board.mineCount() - board.count_flags();
                counter.setCount(mineNum);
            }
            // interaction polling end
        }

        // display updating
        gamewindow.clear(sf::Color::White);
        // setting clock
        timer.setTime();

        // general game UI
        board.drawBoard(gamewindow);
        smiley.draw(gamewindow);
        buggy.draw(gamewindow);
        play_button.draw(gamewindow);
        leaderboard.draw(gamewindow);


        // digit/number UI
        counter.draw(gamewindow);
        timer.draw(gamewindow);
        gamewindow.display();

        if (leaderboard.Open()) {

            leaderboard.Window(timer, board, play_button);

        }

    }

    return 0;
}
