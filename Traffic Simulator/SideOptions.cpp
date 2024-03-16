#include "SideOptions.h"

#include <regex>
#include <filesystem>
#include <fstream>

SideOptions::SideOptions(sf::RenderWindow& window) : window(window){
	font.loadFromFile("fonts/amatic.ttf");

	ret = 1;
	text_size = 30.0f;
	size = sf::Vector2f(200, 50);

	shift_left = sf::Vector2f(240, 20);
	shift_right = sf::Vector2f(20, 20);

	col1 = sf::Color(64, 64, 64);
	col2 = sf::Color(200, 200, 200);
	left_but.setFillColor(col1);

	left_text.setString("Zapisz mape");
	right_text.setString("Rozpocznij symulacje");

	thick = 5.0f;

	left_but.setSize(sf::Vector2f(size.x, size.y));

	right_but.setSize(sf::Vector2f(size.x, size.y));
	right_but.setFillColor(sf::Color(0, 128, 0));

	left_but.setOutlineColor(sf::Color::Black);
	left_but.setOutlineThickness(thick);

	right_but.setOutlineColor(sf::Color::Black);
	right_but.setOutlineThickness(thick);

	left_text.setFont(font);
	right_text.setFont(font);

	left_text.setCharacterSize(text_size);
	right_text.setCharacterSize(text_size);

	left_text.setFillColor(sf::Color::White);
	right_text.setFillColor(sf::Color::White);

	div_x = 2;
	div_y = 4;

	save_size = 0;
	std::string dir = std::filesystem::current_path().string();
	path = dir + "\\saves";
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
		for (const auto& entry : std::filesystem::directory_iterator(path))
			if (std::filesystem::is_directory(entry))
				++save_size;

	first = true;
}

SideOptions::SideOptions(sf::RenderWindow& window, bool second) : window(window) {
	font.loadFromFile("fonts/amatic.ttf");

	ret = 3;
	text_size = 70.0f;
	size = sf::Vector2f(150, 70);

	shift_left = sf::Vector2f(190, 20);
	shift_right = sf::Vector2f(20, 20);

	col1 = sf::Color(128, 0, 0);
	col2 = sf::Color(255, 0, 0);
	left_but.setFillColor(col1);

	left_text.setString("Stop");
	right_text.setString("Start");

	thick = 5.0f;

	left_but.setSize(sf::Vector2f(size.x, size.y));

	right_but.setSize(sf::Vector2f(size.x, size.y));
	right_but.setFillColor(sf::Color(0, 128, 0));

	left_but.setOutlineColor(sf::Color::Black);
	left_but.setOutlineThickness(thick);

	right_but.setOutlineColor(sf::Color::Black);
	right_but.setOutlineThickness(thick);

	left_text.setFont(font);
	right_text.setFont(font);

	left_text.setCharacterSize(text_size);
	right_text.setCharacterSize(text_size);

	left_text.setFillColor(sf::Color::White);
	right_text.setFillColor(sf::Color::White);

	div_x = 2;
	div_y = -10;
}

SideOptions::~SideOptions() {

}


int SideOptions::select() {
    sf::RectangleShape background(sf::Vector2f(100.0f, 40.0f));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(2.0f);
    background.setPosition(window.getSize().x / 4 + 180, window.getSize().y / 5 + 200);

    sf::RectangleShape confirm_button(sf::Vector2f(100.0f, 40.0f));
    confirm_button.setFillColor(sf::Color(50, 50, 50));
    confirm_button.setOutlineColor(sf::Color::White);
    confirm_button.setOutlineThickness(2.0f);
    confirm_button.setPosition(window.getSize().x / 4 + 180, window.getSize().y / 5 + 260);

	sf::RectangleShape back(sf::Vector2f(200.0f, 60.0f));
	back.setFillColor(sf::Color(50, 50, 50));
	back.setOutlineColor(sf::Color::White);
	back.setOutlineThickness(2.0f);
	back.setPosition(window.getSize().x / 4 + 130, window.getSize().y / 5 + 120);

	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(35);
	text.setString("Podaj   liczbe   aut");
	text.setPosition(back.getPosition().x + 20, back.getPosition().y + 5);

    sf::Text input_text;
    input_text.setFont(font);
    input_text.setFillColor(sf::Color::White);
    input_text.setOutlineColor(sf::Color::Black);
    input_text.setOutlineThickness(1.0f);
    input_text.setCharacterSize(24);
    input_text.setPosition(background.getPosition().x + 10, background.getPosition().y + 5);

	sf::Text confirm_text;
	confirm_text.setFont(font);
	confirm_text.setFillColor(sf::Color::White);
	confirm_text.setCharacterSize(24);
	confirm_text.setString("Potwierdz");
	confirm_text.setPosition(confirm_button.getPosition().x + 20, confirm_button.getPosition().y + 5);

    std::string user_in;
    bool editing = false;

    std::regex num_pat("[0-9]+");

    while (window.isOpen()) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (background.getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                        editing = true;
                        background.setFillColor(sf::Color(200, 200, 200));
                    }
                    else if (confirm_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                        background.setFillColor(sf::Color(50, 50, 50));

                        std::regex size_pat("^([1-9]|[1][0-9]|20)$");
                        if (user_in.empty() || !std::regex_search(user_in, size_pat))
                            background.setFillColor(sf::Color::Red);
                        else
							return std::stoi(user_in);
                    }
					else {
						editing = false;
						background.setFillColor(sf::Color(50, 50, 50));
					}
                }
            }
            else if (event.type == sf::Event::TextEntered) {
                if (editing) {
                    if (event.text.unicode == 8) {
                        if (!user_in.empty()) {
                            user_in.pop_back();
                            input_text.setString(user_in);
                        }
                    }
                    else if (user_in.size() < 11) {
                        std::string inputChar(1, static_cast<char>(event.text.unicode));
                        std::string updatedInputX = user_in + inputChar;

                        if (std::regex_match(updatedInputX, num_pat)) {
                            user_in = updatedInputX;
                            input_text.setString(user_in);
                        }
                    }
                }
            }
        }

        if (confirm_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            confirm_button.setFillColor(sf::Color(128, 128, 128));
        else
            confirm_button.setFillColor(sf::Color::Black);

        window.clear(sf::Color(60, 60, 179));
        window.draw(background);
        window.draw(confirm_button);
        window.draw(input_text);
        window.draw(confirm_text);
        window.draw(back);
        window.draw(text);
        window.display();
    }
}

int SideOptions::displayOptions(sf::Vector2f& pos, int zoomed)
{
	if (zoomed == 1) {
		const float sc = 0.9091;
		size.x *= sc;
		size.y *= sc;
		thick *= sc;
		text_size *= sc;
		shift_left.x *= sc;
		shift_left.y *= sc;
		shift_right.x *= sc;
		shift_right.y *= sc;

		cur_pos_left = pos - sf::Vector2f(size.x, size.y) - sf::Vector2f(shift_left.x, shift_left.y);
		cur_pos_right = pos - sf::Vector2f(size.x, size.y) - sf::Vector2f(shift_right.x, shift_right.y);

		left_text.setCharacterSize(text_size);
		right_text.setCharacterSize(text_size);

		left_but.setSize(size);
		left_but.setOutlineThickness(thick);
		right_but.setSize(size);
		right_but.setOutlineThickness(thick);
	}
	else if (zoomed == -1) {
		const float sc = 1.1;
		size.x *= sc;
		size.y *= sc;
		thick *= sc;
		text_size *= sc;
		shift_left.x *= sc;
		shift_left.y *= sc;
		shift_right.x *= sc;
		shift_right.y *= sc;

		cur_pos_left = pos - sf::Vector2f(size.x, size.y) - sf::Vector2f(shift_left.x, shift_left.y);
		cur_pos_right = pos - sf::Vector2f(size.x, size.y) - sf::Vector2f(shift_right.x, shift_right.y);

		left_text.setCharacterSize(text_size);
		right_text.setCharacterSize(text_size);

		left_but.setSize(size);
		left_but.setOutlineThickness(thick);
		right_but.setSize(size);
		right_but.setOutlineThickness(thick);
	}
	else {
		cur_pos_left = pos - sf::Vector2f(size.x, size.y) - sf::Vector2f(shift_left.x, shift_left.y);
		cur_pos_right = pos - sf::Vector2f(size.x, size.y) - sf::Vector2f(shift_right.x, shift_right.y);
	}

	left_but.setPosition(cur_pos_left);
	right_but.setPosition(cur_pos_right);

	left_text.setPosition(left_but.getPosition() + sf::Vector2f(text_size / div_x, text_size / div_y));
	right_text.setPosition(right_but.getPosition() + sf::Vector2f(text_size / div_x, text_size / div_y));

	mouse_position = sf::Mouse::getPosition(window);
	sf::Vector2f real_mouse_pos = window.mapPixelToCoords(mouse_position);

	window.draw(left_but);
	window.draw(right_but);

	window.draw(left_text);
	window.draw(right_text);

	if (left_but.getGlobalBounds().contains(real_mouse_pos)) {
		left_but.setFillColor(col2);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return ret;
	}
	else {
		left_but.setFillColor(col1);
	}

	if (right_but.getGlobalBounds().contains(real_mouse_pos)) {
		right_but.setFillColor(sf::Color(0, 255, 0));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return ret + 1;
	}
	else
		right_but.setFillColor(sf::Color(0, 128, 0));

	return 0;
}

void SideOptions::save(const std::vector<std::vector<int>>& maps) {
	if (first) {
		std::string nr = std::to_string(save_size + 1);
		filename = "\\Map" + nr;
		std::filesystem::create_directory(path + filename);
		first = false;
	}

	int size = 0;
	std::string save_path = path + filename;
	if (std::filesystem::exists(save_path) && std::filesystem::is_directory(save_path))
		for (const auto& entry : std::filesystem::directory_iterator(save_path))
			if (std::filesystem::is_regular_file(entry))
				++size;

	if (size == 0)
		save_name = path + filename + "\\save_" + "1" + ".txt";

	sf::RectangleShape background(sf::Vector2f(400.0f, 300.0f));
	background.setFillColor(sf::Color(50, 50, 50));
	background.setOutlineColor(sf::Color::White);
	background.setOutlineThickness(5.f);
	background.setPosition(window.getSize().x / 4 + 60, window.getSize().y / 5);

	sf::RectangleShape buttonsOption[2];
	for (int i = 0; i < 2; ++i) {
		buttonsOption[i].setSize(sf::Vector2f(200.f, 50.f));
		buttonsOption[i].setFillColor(sf::Color::Black);
		buttonsOption[i].setOutlineColor(sf::Color::White);
		buttonsOption[i].setOutlineThickness(2.f);
		buttonsOption[i].setPosition(background.getPosition() + sf::Vector2f(100.0f, 70.0f + i * 100.0f));
	}

	sf::Text options[2];
	for (int i = 0; i < 2; ++i) {
		options[i].setFont(font);
		options[i].setFillColor(sf::Color::White);
		options[i].setCharacterSize(24);
	}
	options[0].setString("Zapisz");
	options[0].setPosition(buttonsOption[0].getPosition() + sf::Vector2f(75.0f, 10.0f));
	options[1].setString("Nowy zapis");
	options[1].setPosition(buttonsOption[1].getPosition() + sf::Vector2f(65.0f, 10.0f));

	bool choice = true;
	while (choice) {
		mouse_position = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left)
					for (int i = 0; i < 3; ++i)
						if (buttonsOption[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y))
							switch (i) {
							case 0:
								choice = false;
								break;
							case 1:
								save_name = path + filename + "\\save_" + std::to_string(size + 1) + ".txt";
								choice = false;
								break;
							default:
								break;
							}

		window.clear(sf::Color(60, 60, 179));
		window.draw(background);

		for (int i = 0; i < 2; ++i) {
			if (buttonsOption[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y))
				buttonsOption[i].setFillColor(sf::Color(128, 128, 128));
			else
				buttonsOption[i].setFillColor(sf::Color::Black);
			window.draw(buttonsOption[i]);
			window.draw(options[i]);
		}
		window.display();
	}

	std::ofstream file(save_name);

	if (file.is_open()) {
		for (const auto& row : maps) {
			for (const auto& elem : row)
				file << elem << " ";
			file << "\n";
		}

		file.close();
	}
}