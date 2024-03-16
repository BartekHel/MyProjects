#pragma once

#include "UI.h"

class InGameSettings : public UI {
	sf::RenderWindow& window;

	std::vector<sf::Text> texts;
	std::vector<sf::RectangleShape> buttons;
	sf::RectangleShape background;

public:
	InGameSettings(sf::RenderWindow& window);
	~InGameSettings();

	void display();
	int events();
	bool confirmExit();
	std::vector<std::vector<int>> getSettings();
};