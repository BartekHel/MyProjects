#pragma once

#include <SFML/Graphics.hpp>
#include "MapSetUp.h"

class Scheme : public MapSetUp {
	sf::RenderWindow& window;

	const sf::Texture* texture;
	int base_idx, idx;

	std::vector<int> good;
	int num1, num2;
	bool was;

public:
	Scheme(sf::RenderWindow& window, std::vector<int>& settings);
	~Scheme();

	void setMapSprite();
	void setSprite();

	void functions(const int change);
	bool check();

	void checkLineHor();
	void checkLineVer();

	std::vector<std::vector<int>> getRoads();
	void setRoads(std::vector<std::vector<int>> roads);
};