#pragma once

class MapSetUp {
protected:
    int map_size_x, map_size_y, tile_size;

    std::vector<sf::Texture> textures;
    std::vector<sf::Sprite> map;
    sf::RenderTexture map_texture;
    sf::Sprite map_sprite;

    static std::vector<std::vector<int>> is_road;

    sf::Vector2i mouse_position;

public:
    virtual ~MapSetUp() {};

    void virtual setMapSprite() = 0;
    void virtual functions(const int change) = 0;
    bool virtual check() = 0;
    sf::Sprite& getMap() { return map_sprite; }
    std::vector<std::vector<int>> virtual getRoads() = 0;
    void virtual setRoads(std::vector<std::vector<int>> roads) = 0;
};