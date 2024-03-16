#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "Car.h"

class Intersection {
	std::pair<int, int> position;

	sf::Texture green, yellow, red;
	sf::Sprite green_spr, yellow_spr, red_spr;

	std::vector<std::pair<sf::Sprite, std::pair<int, int>>> lights;

	std::vector<std::pair<sf::RectangleShape, bool>> blocks;
	std::vector<int> links;

	float time, max;
	sf::Clock timer;
	bool second_change = false;

public:
	Intersection() { };
	Intersection(const std::vector<int>& linkin, const std::pair<int, int>& position, std::mt19937& mt);
	~Intersection();

	void setTexture(sf::Texture& texture, sf::Sprite& sprite);
	bool update();
	sf::Sprite& getLight(const int i);
	sf::RectangleShape& getRect(const int i);
	void setVisible(const int i);
	bool isVisible(const int i);
	int isIndex(const int idx);
};