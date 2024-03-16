#pragma once

#include <SFML/Graphics.hpp>

class SideOptions {
    sf::RenderWindow& window;

    sf::Vector2i mouse_position;

    sf::Color col1, col2;
    sf::Font font;
    sf::Text left_text, right_text;
    sf::RectangleShape left_but, right_but;
    sf::Vector2f size, shift_left, shift_right, cur_pos_left, cur_pos_right;
    float thick, text_size;
    int ret, div_x, div_y, save_size;
    bool first;
    std::string filename, path, save_name;

public:
    SideOptions(sf::RenderWindow& window);
    SideOptions(sf::RenderWindow& window, bool second);
    ~SideOptions();

    int displayOptions(sf::Vector2f& pos, int zoomed);
    int select();
    void save(const std::vector<std::vector<int>>& maps);
};