#pragma once

#include "Window.h"
#include "MapSetUp.h"
#include "UI.h"
#include "Car.h"
#include "Graph.h"
#include "Intersection.h"
#include "SideOptions.h"
#include "Control.h"

#include <random>
#include <thread>

class Program {
	Window* window;
	sf::Event event;

	MapSetUp* map;
	sf::Sprite map_sprite;

	sf::View view, base_view, tmp;

	float zoom;
	float prev_zoom;

	float speed;

	UI* ui;
	int settings_open;
	bool sec_faze;
	int zoomed;

	Graph graph;

	int n_cars;
	std::vector<Car*> cars;
	std::map<Car*, std::pair<bool, bool>> can_move;

	std::map<Car*, std::thread> car_threads;

	std::vector<Intersection*> intersections;
	bool started;

	SideOptions* buttons;

	sf::Clock clock;
	sf::Time time, dt;

	bool is_pressed, start, show;
	int change;

	std::unique_ptr<Control> control;

	sf::Vector2f pos;

public:
	Program();
	~Program();

	void destruct();
	void setSet();

	void settingsOpen();
	void settingsClosed();

	bool is_running();
	void events();

	void render(std::mt19937& mt);
	void renderProgram(std::mt19937& mt);
	void display();
	void buttonsShow(std::mt19937& mt);
};