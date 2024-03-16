#pragma once

#include <SFML/Graphics.hpp>
#include "MapSetUp.h"

class Map : public MapSetUp {
    std::vector<std::vector<int>> roads;

public:
    Map();
    ~Map();

    void setRoads();
    void setMapSprite();
    sf::Texture& select_texture(const int choice);
    std::vector<std::vector<int>> getRoads();
    void setRoads(std::vector<std::vector<int>> roads) { };

    void functions(const int change);
    bool check();
};