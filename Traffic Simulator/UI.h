#pragma once

#include <SFML/Graphics.hpp>

class UI {
protected:
	sf::Font font;
	sf::Vector2i mouse_position;

public:
	virtual ~UI() { };
	void virtual display() = 0;
	int virtual events() = 0;
	std::vector<std::vector<int>> virtual getSettings() = 0;
};