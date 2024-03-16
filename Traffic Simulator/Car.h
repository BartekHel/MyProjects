#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <random>

#include "Dijkstra.h"
#include "Graph.h"

class Car {
	sf::Texture texture;
	std::pair<sf::Sprite, std::pair<sf::RectangleShape, sf::RectangleShape>> car;

	Graph graph;
	Dijkstra algorithm;

	sf::Vector2f position, destination;
	sf::Vector2i direction;

	std::pair<int, int> goal, dest;

	float speed, rotation;

	int idx;
	bool idx_change;

public:
	Car(Graph& graph, std::mt19937& mt);
	~Car();

	void setDestination(std::pair<int, int> goal);
	void moveAfter();
	bool update(const float dt);
	int checkCollision(Car* car2);
	bool checkCollision(const sf::RectangleShape& rect);
	void stop();
	void move();
	int getIndex();
	std::pair<sf::Sprite, std::pair<sf::RectangleShape, sf::RectangleShape>>& getCar();
};