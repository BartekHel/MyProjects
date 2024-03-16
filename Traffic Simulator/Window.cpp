#include "Window.h"

Window::Window() : width(1024), height(768), title("Traffic Simulator") {
	window.create(sf::VideoMode(width, height), title, sf::Style::Titlebar);
	window.setFramerateLimit(60);
}

Window::Window(const int i) : i(i), title("Traffic Simulator") {
	if (width == 0) {
		width = 1024;
		height = 768;
	}
	if (i == 10)
		window.create(sf::VideoMode(width, height), title, sf::Style::Titlebar);
	else 
		window.create(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
	window.setFramerateLimit(60);
}

Window::Window(const std::vector<int> siz) : width(siz[0]), height(siz[1]), title("Traffic Simulator") {
	window.create(sf::VideoMode(width, height), title, sf::Style::Titlebar);
	window.setFramerateLimit(60);
}

Window::~Window() {

}

sf::RenderWindow& Window::getWindow() {
	return window;
}