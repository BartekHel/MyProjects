#pragma once

#include "UI.h"

class MainMenuSettings : public UI {
    sf::RenderWindow& window;

    std::vector<sf::Text> texts;
    std::vector<sf::CircleShape> buttons;
    std::vector<sf::RectangleShape> backgrounds;

    std::vector<std::vector<int>> var;
    std::vector<int> settings;
    int choice;

    std::vector<std::string> files;
    std::vector<std::string> directories;

    std::vector<sf::Text> directory_texts, files_texts;

    std::vector<sf::RectangleShape> background;
    std::string dir, path;
    int size;

    int mod;
    std::vector<int> win_siz;

public:
    MainMenuSettings(sf::RenderWindow& window);
    ~MainMenuSettings();

    void display();
    int events();
    bool displayStartSettings();
    void displayMapSettings();
    int loadMap();
    void loadDir();
    void loadFiles(const int i);
    bool displayOptions();
    void displayAuthor();
    bool confirmExit();
    void mode();
    void siz();

    std::vector<std::vector<int>> getSettings();
};