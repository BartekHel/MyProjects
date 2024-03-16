#include "Intersection.h"

Intersection::Intersection(const std::vector<int>& linkin, const std::pair<int, int>& position, std::mt19937& mt) : links(linkin), position(position) {
	red.loadFromFile("textures/red.png");
	yellow.loadFromFile("textures/yellow.png");
	green.loadFromFile("textures/green.png");

    setTexture(red, red_spr);
    setTexture(yellow, yellow_spr);
    setTexture(green, green_spr);

    std::uniform_real_distribution<float> dist1(1.0f, 7.0f);
    std::uniform_real_distribution<float> dist2(7.0f, 10.0f);

    sf::Sprite sprite1, sprite2;
    sf::Color col1, col2;
    bool is1, is2;
    int nr1, nr2;
    sprite1 = green_spr;
    nr1 = 1;
    is1 = false;
    sprite2 = red_spr;
    nr2 = 3;
    is2 = true;

    if (dist1(mt) > 6.0f) {
        sprite1 = red_spr;
        nr1 = 3;
        is1 = true;
        sprite2 = green_spr;
        nr2 = 1;
        is2 = false;
    }

    int last_elem = links.back();
    links.pop_back();
    links.insert(links.begin(), last_elem);
    
    sf::FloatRect bounds;
    sprite1.setPosition(sf::Vector2f((position.second + 2) * 50, (position.first + 2) * 50));
    lights.push_back(std::make_pair(sprite1, std::make_pair(nr1, nr1)));

    sf::RectangleShape block;
    block.setSize(sf::Vector2f(30.0f, 1.0f));
    block.setPosition(sprite1.getPosition() - sf::Vector2f(40.0f, 0.0f));
    blocks.push_back(std::make_pair(block, is1));

    sprite1.setPosition(sf::Vector2f((position.second - 1) * 50, (position.first - 1) * 50));
    bounds = sprite1.getLocalBounds();
    sprite1.setOrigin(bounds.width, bounds.height);
    sprite1.setRotation(180.0f);
    lights.push_back(std::make_pair(sprite1, std::make_pair(nr1, nr1)));

    block.setSize(sf::Vector2f(30.0f, 1.0f));
    block.setPosition(sprite1.getPosition() + sf::Vector2f(60.0f, 50.0f));
    blocks.push_back(std::make_pair(block, is1));

    sprite2.setPosition(sf::Vector2f((position.second + 2) * 50, (position.first - 1) * 50));
    bounds = sprite2.getLocalBounds();
    sprite2.setOrigin(bounds.width, bounds.height / 1000.0f);
    sprite2.setRotation(270.0f);
    lights.push_back(std::make_pair(sprite2, std::make_pair(nr2, nr2)));

    block.setSize(sf::Vector2f(1.0f, 30.0f));
    block.setPosition(sprite2.getPosition() + sf::Vector2f(0.0f, 60.0f));
    blocks.push_back(std::make_pair(block, is2));

    sprite2.setPosition(sf::Vector2f((position.second - 1) * 50, (position.first + 2) * 50));
    bounds = sprite2.getLocalBounds();
    sprite2.setOrigin(bounds.width / 1000.0f, bounds.height);
    sprite2.setRotation(90.0f);
    lights.push_back(std::make_pair(sprite2, std::make_pair(nr2, nr2)));

    block.setSize(sf::Vector2f(1.0f, 30.0f));
    block.setPosition(sprite2.getPosition() - sf::Vector2f(-50.0f, 40.0f));
    blocks.push_back(std::make_pair(block, is2));

    second_change = false;
    time = dist1(mt);
    max = dist2(mt);
}

Intersection::~Intersection() {

}

void Intersection::setTexture(sf::Texture& texture, sf::Sprite& sprite) {
    texture.setSmooth(true);

    float tile_size = 50.0f;
    sf::Vector2u texture_size = texture.getSize();
    float scale_x = static_cast<float>(tile_size) / texture_size.x;
    float scale_y = static_cast<float>(tile_size) / texture_size.y;

    sprite.setTexture(texture);
    sprite.setScale(scale_x, scale_y);
}

bool Intersection::update() {
    time += timer.getElapsedTime().asSeconds();
    timer.restart();

    if (time > max) {
        for (int i = 0; i < 4; ++i) {
            lights[i].second.first = 2;
            lights[i].first.setTexture(yellow);
        }

        time = 0;
        second_change = true;
        return true;
    }
    else if (second_change && time > 1.0f) {
        for (int i = 0; i < 4; ++i) {
            if (lights[i].second.second == 1) {
                lights[i].second.first = 3;
                lights[i].second.second = 3;
                lights[i].first.setTexture(red);
            }
            else if (lights[i].second.second == 3) {
                lights[i].second.first = 1;
                lights[i].second.second = 1;
                lights[i].first.setTexture(green);
            }
            setVisible(i);
        }

        time = 0;
        second_change = false; 
        return true;
    }

    return false;
}

sf::Sprite& Intersection::getLight(const int i) {
    return lights[i].first;
}

sf::RectangleShape& Intersection::getRect(const int i) {
    return blocks[i].first;
}

void Intersection::setVisible(const int i) {
    blocks[i].second = !blocks[i].second;
}

bool Intersection::isVisible(const int i) {
    return blocks[i].second;
}

int Intersection::isIndex(const int idx) {
    for (int i = 0; i < 4; ++i)
        if (links[i] == idx)
            return i;
    return -1;
}