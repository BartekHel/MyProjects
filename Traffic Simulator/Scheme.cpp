#include "Scheme.h"

std::vector<std::vector<int>> MapSetUp::is_road;

Scheme::Scheme(sf::RenderWindow& window, std::vector<int>& settings) : window(window) {
	tile_size = 100;
    map_size_x = settings[0];
    map_size_y = settings[1];

    is_road = std::vector<std::vector<int>>(map_size_y, std::vector<int>(map_size_x, 0));

    for (int i = 0; i < map_size_y; ++i)
        for (int j = 0; j < map_size_x; ++j)
            is_road[i][j] = 0;

    sf::Texture texture;
    texture.loadFromFile("textures/grass3.jpg");
	textures.push_back(texture);
    texture.loadFromFile("textures/crossv2.jpg");
    textures.push_back(texture);
    texture.loadFromFile("textures/nograss.jpg");
    textures.push_back(texture);
    texture.loadFromFile("textures/nocross.jpg");
    textures.push_back(texture);
    texture.loadFromFile("textures/grassenable.jpg");
    textures.push_back(texture);
    texture.loadFromFile("textures/cross.jpg");
    textures.push_back(texture);

    for (int i = 0; i < 6; ++i)
        textures[i].setSmooth(true);

    Scheme::setMapSprite();

    idx = base_idx = -1;

    num1 = 0, num2 = 0;
    was = false;
}

Scheme::~Scheme() {

}

void Scheme::setMapSprite() {
    map.resize(map_size_y * map_size_x);

    for (int i = 0; i < map_size_y; ++i)
        for (int j = 0; j < map_size_x; ++j) {
            sf::Sprite& tile = map[i * map_size_x + j];

            const sf::Vector2u texture_size = textures[0].getSize();
            const float scale_x = static_cast<float>(tile_size) / texture_size.x;
            const float scale_y = static_cast<float>(tile_size) / texture_size.y;
            tile.setScale(scale_x, scale_y);
                
            tile.setTexture(textures[0]);
            tile.setPosition(j * tile_size, i * tile_size);
        }

    Scheme::setSprite();
}

void Scheme::setSprite() {
    map_texture.create(tile_size * map_size_x, tile_size * map_size_y);

    for (int i = 0; i < map_size_y; ++i)
        for (int j = 0; j < map_size_x; ++j)
            map_texture.draw(map[i * map_size_x + j]);

    map_texture.display();
    map_sprite.setTexture(map_texture.getTexture());
}

void Scheme::functions(const int change) {
    mouse_position = sf::Mouse::getPosition(window);

    sf::Vector2f world_position = window.mapPixelToCoords(mouse_position);
    int x, y;

    if (world_position.x < 0 || world_position.y < 0)
        x = map_size_x;
    else {
        x = static_cast<int>(world_position.x) / tile_size;
        y = static_cast<int>(world_position.y) / tile_size;
    }

    if (change == 2 && base_idx != -1) {
        texture = &textures[4];

        for (int i = 0; i < map_size_x; ++i) {
            const int index = base_idx / map_size_x * map_size_x + i;
            if (map[index].getTexture() == texture)
                map[index].setTexture(textures[0]);
            else if (map[index].getTexture() == &textures[5])
                map[index].setTexture(textures[1]);
        }
        for (int i = 0; i < map_size_y; ++i) {
            const int index = i * map_size_x + base_idx % map_size_x;
            if (map[index].getTexture() == texture)
                map[index].setTexture(textures[0]);
            else if (map[index].getTexture() == &textures[5])
                map[index].setTexture(textures[1]);
        }

        Scheme::setSprite();
    }
    else if (x < map_size_x && y < map_size_y) {
        idx = y * map_size_x + x;
        sf::Sprite& tile = map[idx];
        const sf::Vector2u texture_size = textures[0].getSize();
        const float scale_x = static_cast<float>(tile_size) / texture_size.x;
        const float scale_y = static_cast<float>(tile_size) / texture_size.y;
        tile.setScale(scale_x, scale_y);

        if (base_idx % map_size_x == idx % map_size_x || base_idx / map_size_x == idx / map_size_x) {
            if (texture == &textures[0] || texture == &textures[2])
                tile.setTexture(textures[1]);
            else
                tile.setTexture(textures[0]);
        }

        if (change == 1) {
            base_idx = idx;

            texture = &textures[0];
            for (int i = 0; i < map_size_x; ++i) {
                const int index = base_idx / map_size_x * map_size_x + i;
                sf::Sprite& tile_temp = map[index];
                if (tile_temp.getTexture() == texture)
                    tile_temp.setTexture(textures[4]);
            }
            for (int i = 0; i < map_size_y; ++i) {
                const int index = i * map_size_x + base_idx % map_size_x;
                sf::Sprite& tile_temp = map[index];
                if (tile_temp.getTexture() == texture)
                    map[index].setTexture(textures[4]);
            }
        }
        else if (change == 3) {
            base_idx = idx;

            texture = &textures[1];
            for (int i = 0; i < map_size_x; ++i) {
                const int index = base_idx / map_size_x * map_size_x + i;
                sf::Sprite& tile_temp = map[index];
                if (tile_temp.getTexture() == texture)
                    tile_temp.setTexture(textures[5]);
            }
            for (int i = 0; i < map_size_y; ++i) {
                const int index = i * map_size_x + base_idx % map_size_x;
                sf::Sprite& tile_temp = map[index];
                if (tile_temp.getTexture() == texture)
                    tile_temp.setTexture(textures[5]);
            }
        }

        Scheme::setSprite();
    }
}

bool Scheme::check() {
    bool good = true;
    for (int i = 0; i < map_size_y; ++i)
        for (int j = 0; j < map_size_x; ++j) {
            sf::Sprite& tile = map[i * map_size_x + j];
            const sf::Texture* texture = tile.getTexture();

            if (texture == &textures[1] || texture == &textures[2]) {
                is_road[i][j] = 1;
                if (i != 0 && i != map_size_y - 1 && j != 0 && j != map_size_x - 1)
                    good = false;
            }
            else
                is_road[i][j] = 0;
        }
    good = good ? false : true;

    if (!good)
        for (int i = 0; i < map_size_x; ++i)
            is_road[map_size_y / 2][i] = -1;

    checkLineHor();
    checkLineVer();

    const sf::Vector2u texture_size = textures[0].getSize();
    float scale_x = static_cast<float>(tile_size) / texture_size.x;
    float scale_y = static_cast<float>(tile_size) / texture_size.y;

    for (int i = 0; i < map_size_y; ++i) {
        for (int j = 0; j < map_size_x; ++j) {
            sf::Sprite& tile = map[i * map_size_x + j];
            tile.setScale(scale_y, scale_x);
            tile.setPosition(j * tile_size, i * tile_size);

            if (is_road[i][j] == 0)
                tile.setTexture(textures[0]);
            else if (is_road[i][j] == 1) {
                tile.setTexture(textures[2]);
                good = false;
            }
            else if (is_road[i][j] == 3) {
                tile.setTexture(textures[1]);
            }
            else if (is_road[i][j] == -1) {
                tile.setTexture(textures[3]);
                good = false;
            }
        }
    }

    if (good)
        for (int i = 0; i < map_size_y; ++i)
            for (int j = 0; j < map_size_x; ++j)
                if (is_road[i][j] == 3)
                    is_road[i][j] = 1;

    Scheme::setSprite();
    return good;
}

void Scheme::checkLineHor() {
    std::vector<std::pair<int, int>> rows;

    int size = map_size_y;
    for (int i = 0; i < size; ++i) {
        int num = 0;
        if (is_road[i][0] == 1 || is_road[i][map_size_x - 1] == 1) {
            for (int j = 0; j < map_size_x; ++j) {
                if (is_road[i][j] == 1)
                    ++num;
            }
        }
        rows.push_back(std::make_pair(0, num));
    }

    size = rows.size() - 1;
    for (int i = 1; i < size; ++i) {
        int idx = 1, max = 0;
        for (int t = 1; t < size; ++t) {
            if (rows[t].first == 0 && rows[t].second > max) {
                max = rows[t].second;
                idx = t;
            }
        }
        
        if (rows[idx - 1].first != 1 && rows[idx + 1].first != 1 && max > 0) {
            for (int j = 0; j < map_size_x; ++j) {
                if (is_road[idx][j] != 1 && is_road[idx][j] != -1)
                    is_road[idx][j] = -1;
                else
                    is_road[idx][j] = 3;
            }
            rows[idx].first = 1;
        }
        else {
            rows[idx].first = 2;
        }
    }
}

void Scheme::checkLineVer() {
    std::vector<std::pair<int, int>> cols;

    int size = map_size_x;
    for (int i = 0; i < size; ++i) {
        int num = 0;
        if (is_road[0][i] == 1 || is_road[map_size_y - 1][i] == 1) {
            for (int j = 0; j < map_size_y; ++j) {
                if (is_road[j][i] == 1)
                    ++num;
            }
        }
        cols.push_back(std::make_pair(0, num));
    }

    size = cols.size() - 1;
    for (int i = 1; i < size; ++i) {
        int idx = 1, max = 0;
        for (int t = 1; t < size; ++t) {
            if (cols[t].first == 0 && cols[t].second > max) {
                max = cols[t].second;
                idx = t;
            }
        }

        if (cols[idx - 1].first != 1 && cols[idx + 1].first != 1 && max > 0) {
            for (int j = 0; j < map_size_y; ++j) {
                if (is_road[j][idx] != 1 && is_road[j][idx] != 3)
                    is_road[j][idx] = -1;
                else
                    is_road[j][idx] = 3;
            }
            cols[idx].first = 1;
        }
        else {
            cols[idx].first = 2;
        }
    }
}

std::vector<std::vector<int>> Scheme::getRoads() {
    for (int i = 0; i < map_size_y; ++i)
        for (int j = 0; j < map_size_x; ++j) {
            sf::Sprite& tile = map[i * map_size_x + j];
            const sf::Texture* texture = tile.getTexture();

            if (texture == &textures[1] || texture == &textures[2])
                is_road[i][j] = 1;
            else
                is_road[i][j] = 0;
        }

    return is_road;
}

void Scheme::setRoads(std::vector<std::vector<int>> roads) {
    is_road = roads;

    const sf::Vector2u texture_size = textures[0].getSize();
    float scale_x = static_cast<float>(tile_size) / texture_size.x;
    float scale_y = static_cast<float>(tile_size) / texture_size.y;

    for (int i = 0; i < map_size_y; ++i)
        for (int j = 0; j < map_size_x; ++j) {
            sf::Sprite& tile = map[i * map_size_x + j];
            tile.setScale(scale_y, scale_x);
            tile.setPosition(j * tile_size, i * tile_size);

            if (is_road[i][j] == 0)
                tile.setTexture(textures[0]);
            else if (is_road[i][j] == 1)
                tile.setTexture(textures[1]);
        }

    Scheme::setSprite();
}