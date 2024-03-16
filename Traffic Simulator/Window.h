#pragma once

#include <SFML/Graphics.hpp>

class Window {
	int width, height;
	const std::string title;
	sf::RenderWindow window;
	int i;

public:
	Window();
	Window(const int i);
	Window(const std::vector<int> siz);
	~Window();

	void change();
	sf::RenderWindow& getWindow();
};