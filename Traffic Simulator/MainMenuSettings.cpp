#include "MainMenuSettings.h"
#include <windows.h>
#include <regex>
#include <filesystem>
#include <fstream>

MainMenuSettings::MainMenuSettings(sf::RenderWindow& window) : window(window), texts(4), buttons(3), backgrounds(4) {
    font.loadFromFile("fonts/amatic.ttf");

    const sf::Vector2u window_size = window.getSize();
    const float center_x = window_size.x / 2.0f;

    buttons[2].setFillColor(sf::Color(139, 0, 0));
    buttons[1].setFillColor(sf::Color(128, 128, 0));
    buttons[0].setFillColor(sf::Color(0, 100, 0));

    for (int i = 0; i < 3; ++i) {
        buttons[i].setRadius(60);
        buttons[i].setPointCount(14);
        buttons[i].setOutlineColor(sf::Color::Black);
        buttons[i].setOutlineThickness(5.0f);
        buttons[i].setPosition(center_x - 60, 250 + i * 150.0f);

        backgrounds[i].setSize(sf::Vector2f(135.0f, 144.0f));
        backgrounds[i].setPosition(buttons[i].getPosition() - sf::Vector2f(9.0f, 15.0f));
        backgrounds[i].setFillColor(sf::Color::Black);
        backgrounds[i].setOutlineColor(sf::Color(32, 32, 32));
        backgrounds[i].setOutlineThickness(3.0f);

        texts[i].setFont(font);
        texts[i].setCharacterSize(30);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setOutlineThickness(3.0f);
        texts[i].setOrigin(texts[i].getGlobalBounds().width / 2, texts[i].getGlobalBounds().height / 2);
        texts[i].setPosition(buttons[i].getPosition() + sf::Vector2f(17.0f, 40.0f));
    }

    backgrounds[3].setSize(sf::Vector2f(20.0f, 85.0f));
    backgrounds[3].setPosition(buttons[2].getPosition() + sf::Vector2f(50.0f, 135.0f));
    backgrounds[3].setFillColor(sf::Color::Black);
    backgrounds[3].setOutlineColor(sf::Color(32, 32, 32));
    backgrounds[3].setOutlineThickness(3.0f);

    texts[2].setPosition(buttons[2].getPosition() + sf::Vector2f(35.0f, 40.0f));

    texts[3].setFont(font);
    texts[3].setCharacterSize(100);
    texts[3].setOutlineColor(sf::Color::Black);
    texts[3].setOutlineThickness(5.0f);
    texts[3].setOrigin(texts[0].getGlobalBounds().width / 2, texts[0].getGlobalBounds().height / 2);
    texts[3].setPosition(window_size.x / 4 + 25, 60);
    texts[3].setFillColor(sf::Color::White);

    texts[0].setString("Rozpocznij");
    texts[1].setString("Ustawienia");
    texts[2].setString("Wyjdz");
    texts[3].setString("Traffic   Simulator");

    choice = -1;
    mod = 0;
};

MainMenuSettings::~MainMenuSettings() { };

void MainMenuSettings::display() {
    mouse_position = sf::Mouse::getPosition(window);

    window.draw(texts[3]);
    window.draw(backgrounds[3]);
    for (int i = 0; i < 3; ++i) {
        const bool contains = backgrounds[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y);
        if (contains) {
            backgrounds[i].setFillColor(sf::Color(50, 50, 50));
            buttons[2].setFillColor(sf::Color::Red);
            buttons[1].setFillColor(sf::Color::Yellow);
            buttons[0].setFillColor(sf::Color::Green);
        }
        else {
            buttons[2].setFillColor(sf::Color(139, 0, 0));
            buttons[1].setFillColor(sf::Color(128, 128, 0));
            buttons[0].setFillColor(sf::Color(0, 100, 0));
            backgrounds[i].setFillColor(sf::Color::Black);
        }
        window.draw(backgrounds[i]);
        window.draw(buttons[i]);
        window.draw(texts[i]);
    }
}

int MainMenuSettings::events() {
    mouse_position = sf::Mouse::getPosition(window);

    if (win_siz.size() != 0 && win_siz[0] == -1) {
        int tmp = win_siz[1];
        win_siz.clear();
        return tmp;
    }

    std::vector<bool> contains = {
         backgrounds[0].getGlobalBounds().contains(mouse_position.x, mouse_position.y),
         backgrounds[1].getGlobalBounds().contains(mouse_position.x, mouse_position.y),
         backgrounds[2].getGlobalBounds().contains(mouse_position.x, mouse_position.y)
    };

    if (contains[0]) {
        if (MainMenuSettings::displayStartSettings())
            return 0;
    }
    else if (contains[1]) {
        MainMenuSettings::displayOptions();
        if (mod > 1) {
            int tmp = mod;
            mod = 0;
            return tmp;
        }
        else if (win_siz.size() != 0) {
            int tmp = win_siz[0];
            win_siz[0] = -1;
            return tmp;
        }

    }
    else if (contains[2])
        if (confirmExit())
            window.close();

    return 1;
}

bool MainMenuSettings::displayStartSettings() {
    sf::RectangleShape background(sf::Vector2f(400.0f, 400.0f));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(5.f);
    background.setPosition(window.getSize().x / 4 + 60, window.getSize().y / 5 - 30);

    sf::RectangleShape buttonsOption[3];
    for (int i = 0; i < 3; ++i) {
        buttonsOption[i].setSize(sf::Vector2f(200.f, 50.f));
        buttonsOption[i].setFillColor(sf::Color::Black);
        buttonsOption[i].setOutlineColor(sf::Color::White);
        buttonsOption[i].setOutlineThickness(2.f);
        buttonsOption[i].setPosition(background.getPosition() + sf::Vector2f(100.0f, 70.0f + i * 100.0f));
    }

    sf::Text options[3];
    for (int i = 0; i < 3; ++i) {
        options[i].setFont(font);
        options[i].setFillColor(sf::Color::White);
        options[i].setCharacterSize(24);
    }
    options[0].setString("Nowa mapa");
    options[0].setPosition(buttonsOption[0].getPosition() + sf::Vector2f(65.0f, 10.0f));
    options[1].setString("Wczytaj");
    options[1].setPosition(buttonsOption[1].getPosition() + sf::Vector2f(70.0f, 10.0f));
    options[2].setString("Wroc");
    options[2].setPosition(buttonsOption[2].getPosition() + sf::Vector2f(80.0f, 10.0f));

    while (true) {
        mouse_position = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                    for (int i = 0; i < 3; ++i)
                        if (buttonsOption[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            switch (i) {
                            case 0:
                                MainMenuSettings::displayMapSettings();
                                return 1;
                                break;
                            case 1:
                                if(MainMenuSettings::loadMap())
                                    return 1;
                                break;
                            case 2:
                                return 0;
                                break;
                            default:
                                break;
                            }

        window.clear(sf::Color(60, 60, 179));
        window.draw(background);
        for (int i = 0; i < 3; ++i) {
            if (buttonsOption[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                buttonsOption[i].setFillColor(sf::Color(128, 128, 128));
            else
                buttonsOption[i].setFillColor(sf::Color::Black);
            window.draw(buttonsOption[i]);
            window.draw(options[i]);
        }
        window.display();
    }
}

void MainMenuSettings::displayMapSettings() {
    sf::RectangleShape background_x(sf::Vector2f(100.0f, 40.0f));
    background_x.setFillColor(sf::Color(50, 50, 50));
    background_x.setOutlineColor(sf::Color::White);
    background_x.setOutlineThickness(2.0f);
    background_x.setPosition(window.getSize().x / 4 + 120, window.getSize().y / 5 + 200);

    sf::RectangleShape background_y(sf::Vector2f(100.0f, 40.0f));
    background_y.setFillColor(sf::Color(50, 50, 50));
    background_y.setOutlineColor(sf::Color::White);
    background_y.setOutlineThickness(2.0f);
    background_y.setPosition(window.getSize().x / 4 + 240, window.getSize().y / 5 + 200);

    sf::RectangleShape confirm_button(sf::Vector2f(100.0f, 40.0f));
    confirm_button.setFillColor(sf::Color(50, 50, 50));
    confirm_button.setOutlineColor(sf::Color::White);
    confirm_button.setOutlineThickness(2.0f);
    confirm_button.setPosition(window.getSize().x / 4 + 180, window.getSize().y / 5 + 260);

    sf::RectangleShape background(sf::Vector2f(450.0f, 60.0f));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(2.0f);
    background.setPosition(window.getSize().x / 4 + 10, window.getSize().y / 5 + 120);

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(35);
    text.setString("Podaj   rozmiary   mapy   (szerokosc,   wysokosc)");
    text.setPosition(background.getPosition().x + 20, background.getPosition().y + 5);

    sf::Text input_text_x;
    input_text_x.setFont(font);
    input_text_x.setFillColor(sf::Color::White);
    input_text_x.setOutlineColor(sf::Color::Black);
    input_text_x.setOutlineThickness(1.0f);
    input_text_x.setCharacterSize(24);
    input_text_x.setPosition(background_x.getPosition().x + 10, background_x.getPosition().y + 5);

    sf::Text input_text_y;
    input_text_y.setFont(font);
    input_text_y.setFillColor(sf::Color::White);
    input_text_y.setOutlineColor(sf::Color::Black);
    input_text_y.setOutlineThickness(1.0f);
    input_text_y.setCharacterSize(24);
    input_text_y.setPosition(background_y.getPosition().x + 10, background_y.getPosition().y + 5);

    sf::Text confirm_text;
    confirm_text.setFont(font);
    confirm_text.setFillColor(sf::Color::White);
    confirm_text.setCharacterSize(24);
    confirm_text.setString("Potwierdz");
    confirm_text.setPosition(confirm_button.getPosition().x + 20, confirm_button.getPosition().y + 5);

    std::string user_in_x, user_in_y;
    bool editing_x = false;
    bool editing_y = false;
    bool good1 = true;
    bool good2 = true;
    std::regex num_pat("[0-9]+");

    while (true) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (background_x.getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                        editing_x = true;
                        editing_y = false;
                        background_x.setFillColor(sf::Color(200, 200, 200));
                        background_y.setFillColor(sf::Color(50, 50, 50));
                    }
                    else if (background_y.getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                        editing_y = true;
                        editing_x = false;
                        background_y.setFillColor(sf::Color(200, 200, 200));
                        background_x.setFillColor(sf::Color(50, 50, 50));
                    }
                    else if (confirm_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                        background_x.setFillColor(sf::Color(50, 50, 50));
                        background_y.setFillColor(sf::Color(50, 50, 50));

                        std::regex size_pat("^([5-9]|[1-4][0-9]|50)$");
                        if (user_in_x.empty() || !std::regex_search(user_in_x, size_pat)) {
                            background_x.setFillColor(sf::Color::Red);
                            good1 = false;
                        }
                        else 
                            good1 = true;
                        if (user_in_y.empty() || !std::regex_search(user_in_y, size_pat)) {
                            background_y.setFillColor(sf::Color::Red);
                            good2 = false;
                        }
                        else
                            good2 = true;
   
                        if (good1 && good2) {
                            settings.push_back(std::stoi(user_in_x));
                            settings.push_back(std::stoi(user_in_y));
                            return;
                        }
                    }
                    else {
                        editing_y = false;
                        editing_x = false;
                        background_x.setFillColor(sf::Color(50, 50, 50));
                        background_y.setFillColor(sf::Color(50, 50, 50));
                    }
                }
            }
            else if (event.type == sf::Event::TextEntered) {
                if (editing_x) {
                    if (event.text.unicode == 8) {
                        if (!user_in_x.empty()) {
                            user_in_x.pop_back();
                            input_text_x.setString(user_in_x);
                        }
                    }
                    else if (user_in_x.size() < 11) {
                        std::string inputChar(1, static_cast<char>(event.text.unicode));
                        std::string updatedInputX = user_in_x + inputChar;

                        if (std::regex_match(updatedInputX, num_pat)) {
                            user_in_x = updatedInputX;
                            input_text_x.setString(user_in_x);
                        }
                    }
                }
                if (editing_y) {
                    if (event.text.unicode == 8) {
                        if (!user_in_y.empty()) {
                            user_in_y.pop_back();
                            input_text_y.setString(user_in_y);
                        }
                    }
                    else if (user_in_y.size() < 11) {
                        std::string inputChar(1, static_cast<char>(event.text.unicode));
                        std::string updatedInputY = user_in_y + inputChar;

                        if (std::regex_match(updatedInputY, num_pat)) {
                            user_in_y = updatedInputY;
                            input_text_y.setString(user_in_y);
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
        window.draw(background_x);
        window.draw(background_y);
        window.draw(confirm_button);
        window.draw(input_text_x);
        window.draw(input_text_y);
        window.draw(confirm_text);
        window.draw(background);
        window.draw(text);
        window.display();
    }
}

void MainMenuSettings::loadDir() {
    dir = std::filesystem::current_path().string();
    path = dir + "\\saves";

    directories.clear();
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            std::string name = entry.path().filename().string();
            directories.push_back(name);
        }
    }

    std::sort(directories.begin(), directories.end(), [](const std::string& a, const std::string& b) {
        std::string name_a = a.substr(3);
        std::string name_b = b.substr(3);

        int num_a = std::stoi(name_a);
        int num_b = std::stoi(name_b);

        return num_a < num_b;
        });

    size = directories.size();
    background.clear();
    background.resize(size);

    int x;
    for (int i = 0; i < size; ++i) {
        if (i % 8 == 0)
            x = 2;
        background[i].setSize(sf::Vector2f(200.0f, 60.0f));
        background[i].setFillColor(sf::Color(50, 50, 50));
        background[i].setOutlineColor(sf::Color::White);
        background[i].setOutlineThickness(2.0f);
        background[i].setPosition(window.getSize().x / 4 + 150, 65.0f * x);
        ++x;
    }

    int idx = 0;
    directory_texts.clear();
    for (const auto& dir : directories) {
        sf::Text text(dir, font);
        text.setCharacterSize(50.0f);
        text.setPosition(background[idx].getPosition().x + 70.0f, background[idx].getPosition().y + 1.0f);
        directory_texts.push_back(text);
        ++idx;
    }
}

void MainMenuSettings::loadFiles(const int i) {
    path = dir + "\\saves\\" + directories[i];

    files.clear();
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::string name = entry.path().filename().string();
            name = name.substr(0, name.size() - 4);
            files.push_back(name);
        }
    }

    std::sort(files.begin(), files.end(), [](const std::string& a, const std::string& b) {
        std::string name_a = a.substr(5);
        std::string name_b = b.substr(5);

        int num_a = std::stoi(name_a);
        int num_b = std::stoi(name_b);

        return num_a < num_b;
        });

    size = files.size();
    background.clear();
    background.resize(size);

    int x;
    for (int i = 0; i < size; ++i) {
        if (i % 8 == 0)
            x = 2;
        background[i].setSize(sf::Vector2f(200.0f, 60.0f));
        background[i].setFillColor(sf::Color(50, 50, 50));
        background[i].setOutlineColor(sf::Color::White);
        background[i].setOutlineThickness(2.0f);
        background[i].setPosition(window.getSize().x / 4 + 150, 65.0f * x);
        ++x;
    }

    int idx = 0;
    files_texts.clear();
    for (const auto& fil : files) {
        sf::Text text(fil, font);
        text.setCharacterSize(50.0f);
        text.setPosition(background[idx].getPosition().x + 60.0f, background[idx].getPosition().y + 1.0f);
        files_texts.push_back(text);
        ++idx;
    }
}

int MainMenuSettings::loadMap() {
    MainMenuSettings::loadDir();

    if (size == 0)
        return 0;

    sf::RectangleShape prev, next, back;

    prev.setSize(sf::Vector2f(200.0f, 60.0f));
    prev.setFillColor(sf::Color(20, 20, 20));
    prev.setOutlineColor(sf::Color::White);
    prev.setOutlineThickness(2.0f);
    prev.setPosition(window.getSize().x / 4 + 150, 65.0f);

    next.setSize(sf::Vector2f(200.0f, 60.0f));
    next.setFillColor(sf::Color(20, 20, 20));
    next.setOutlineColor(sf::Color::White);
    next.setOutlineThickness(2.0f);
    next.setPosition(window.getSize().x / 4 + 150, 65.0f * 10);

    back.setSize(sf::Vector2f(200.0f, 60.0f));
    back.setFillColor(sf::Color(20, 20, 20));
    back.setOutlineColor(sf::Color::White);
    back.setOutlineThickness(2.0f);
    back.setPosition(window.getSize().x / 1.25, window.getSize().y / 1.1);

    sf::Text prev_text, next_text, back_text;

    prev_text.setFont(font);
    prev_text.setString("Poprzednie");
    prev_text.setCharacterSize(50.0f);
    prev_text.setPosition(prev.getPosition().x + 30.0f, prev.getPosition().y);

    next_text.setFont(font);
    next_text.setString("Nastepne");
    next_text.setCharacterSize(50.0f);
    next_text.setPosition(next.getPosition().x + 45.0f, next.getPosition().y);

    back_text.setFont(font);
    back_text.setString("Wroc");
    back_text.setCharacterSize(50.0f);
    back_text.setPosition(back.getPosition().x + 70.0f, back.getPosition().y);

    int start, stop;
    start = 0;
    if (size > 8)
        stop = 8;
    else
        stop = size;

    int num1 = size;
    int num2;
    bool released = false;
    while (true) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (back.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        if (choice == -1)
                            return 0;
                        else {
                            choice = -1;
                            MainMenuSettings::loadDir();

                            start = 0;
                            if (size > 8)
                                stop = 8;
                            else
                                stop = size;
                        }
                    for (int i = start; i < stop; ++i) {
                        if (background[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y) && background[i].getFillColor() != sf::Color::Red) {
                            if (choice == -1) {
                                choice = i;

                                MainMenuSettings::loadFiles(choice);

                                num2 = size;
                                start = 0;
                                if (size > 8)
                                    stop = 8;
                                else
                                    stop = size;
                            }
                            else if (released) {
                                path = dir + "\\saves\\" + directories[choice] + "\\" + files[i] + ".txt";

                                std::ifstream file(path);

                                if (file.is_open()) {
                                    std::string line;

                                    while (std::getline(file, line)) {
                                        std::vector<int> inner;
                                        std::istringstream iss(line);
                                        int value;

                                        while (iss >> std::ws >> value) {
                                            inner.push_back(value);
                                        }

                                        var.push_back(inner);
                                    }
                                    file.close();
                                }

                                return 1;
                            }
                        }
                    }

                    if (start != 0 && prev.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        stop = start;
                        start = start - 8;
                    }
                    else if (size > 8 && next.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        start = stop;
                        stop = start;
                        while (stop < size && stop % 7 != 0)
                            ++stop;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    for (int i = start; i < stop; ++i) {
                        if (background[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            background[i].setFillColor(sf::Color::Red);
                            if (choice == -1) {
                                directory_texts[i].setString("Usuniete");
                                directory_texts[i].setPosition(background[i].getPosition().x + 45.0f, background[i].getPosition().y + 1.0f);
                                std::string path = dir + "\\saves";
                                std::string name = path + "\\" + directories[i];
                                std::filesystem::remove_all(name);

                                --num1;
                                if (num1 == 0)
                                    return 0;
                            }
                            else {
                                files_texts[i].setString("Usuniete");
                                files_texts[i].setPosition(background[i].getPosition().x + 45.0f, background[i].getPosition().y + 1.0f);
                                std::string name = path + "\\" + files[i]  + ".txt";
                                std::filesystem::remove(name);

                                --num2;
                                if (num2 == 0) {
                                    files_texts.clear();
                                    files.clear();

                                    choice = -1;
                                    MainMenuSettings::loadDir();

                                    start = 0;
                                    if (size > 8)
                                        stop = 8;
                                    else
                                        stop = size;
                                }
                            }
                        }
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left)
                    released = true;
        }

        if (size == 0) {
            choice = -1;
            MainMenuSettings::loadDir();

            start = 0;
            if (size > 8)
                stop = 8;
            else
                stop = size;
        }

        window.clear(sf::Color(60, 60, 179));

        if (choice == -1) {
            for (int i = start; i < stop; ++i) {
                if (background[i].getFillColor() != sf::Color::Red) {
                    if (background[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        background[i].setFillColor(sf::Color::Black);
                    else
                        background[i].setFillColor(sf::Color(50, 50, 50));
                }

                window.draw(background[i]);
                window.draw(directory_texts[i]);
            }

            if (prev.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                prev.setFillColor(sf::Color(150, 150, 150));
            else
                prev.setFillColor(sf::Color(20, 20, 20));
            if (next.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                next.setFillColor(sf::Color(150, 150, 150));
            else
                next.setFillColor(sf::Color(20, 20, 20));

            if (start != 0) {
                window.draw(prev);
                window.draw(prev_text);
            }
            if (size > 8) {
                window.draw(next);
                window.draw(next_text);
            }
        }
        else {
            for (int i = start; i < stop; ++i) {
                if (background[i].getFillColor() != sf::Color::Red) {
                    if (background[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        background[i].setFillColor(sf::Color::Black);
                    else
                        background[i].setFillColor(sf::Color(50, 50, 50));
                }

                window.draw(background[i]);
                window.draw(files_texts[i]);
            }

            if (prev.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                prev.setFillColor(sf::Color(150, 150, 150));
            else
                prev.setFillColor(sf::Color(20, 20, 20));
            if (next.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                next.setFillColor(sf::Color(150, 150, 150));
            else
                next.setFillColor(sf::Color(20, 20, 20));

            if (start != 0) {
                window.draw(prev);
                window.draw(prev_text);
            }
            if (size > 8) {
                window.draw(next);
                window.draw(next_text);
            }
        }

        if (back.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            back.setFillColor(sf::Color(150, 150, 150));
        else
            back.setFillColor(sf::Color(20, 20, 20));

        window.draw(back);
        window.draw(back_text);

        window.display();
    }

    return 1;
}

bool MainMenuSettings::displayOptions() {
    sf::RectangleShape background(sf::Vector2f(400.0f, 500.0f));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(5.f);
    background.setPosition(window.getSize().x / 4 + 60, window.getSize().y / 5 - 30);

    sf::RectangleShape buttonsOption[4];
    for (int i = 0; i < 4; ++i) {
        buttonsOption[i].setSize(sf::Vector2f(200.f, 50.f));
        buttonsOption[i].setFillColor(sf::Color::Black);
        buttonsOption[i].setOutlineColor(sf::Color::White);
        buttonsOption[i].setOutlineThickness(2.f);
        buttonsOption[i].setPosition(background.getPosition() + sf::Vector2f(100.0f, 70.0f + i * 100.0f));
    }

    sf::Text options[4];
    for (int i = 0; i < 4; ++i) {
        options[i].setFont(font);
        options[i].setFillColor(sf::Color::White);
        options[i].setCharacterSize(24);
    }
    options[0].setString("Tryb okna");
    options[0].setPosition(buttonsOption[0].getPosition() + sf::Vector2f(70.0f, 10.0f));
    options[1].setString("Rozmiar okna");
    options[1].setPosition(buttonsOption[1].getPosition() + sf::Vector2f(55.0f, 10.0f));
    options[2].setString("Autorzy");
    options[2].setPosition(buttonsOption[2].getPosition() + sf::Vector2f(75.0f, 10.0f));
    options[3].setString("Wroc");
    options[3].setPosition(buttonsOption[3].getPosition() + sf::Vector2f(85.0f, 10.0f));

    while (true) {
        mouse_position = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                    for (int i = 0; i < 4; ++i)
                        if (buttonsOption[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            switch (i) {
                            case 0:
                                MainMenuSettings::mode();
                                if (mod > 1)
                                    return 1;
                                break;
                            case 1:
                                MainMenuSettings::siz();
                                if (win_siz.size() != 0)
                                    return 1;
                                break;
                            case 2:
                                if (mod)
                                    mod = 0;
                                else
                                    MainMenuSettings::displayAuthor();
                                break;
                            case 3:
                                return 1;
                                break;
                            default:
                                break;
                            }

        window.clear(sf::Color(60, 60, 179));
        window.draw(background);
        for (int i = 0; i < 4; ++i) {
            if (buttonsOption[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                buttonsOption[i].setFillColor(sf::Color(128, 128, 128));
            else
                buttonsOption[i].setFillColor(sf::Color::Black);
            window.draw(buttonsOption[i]);
            window.draw(options[i]);
        }
        window.display();
    }
}

void MainMenuSettings::mode() {
    sf::RectangleShape background(sf::Vector2f(400.0f, 400.0f));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(5.f);
    background.setPosition(window.getSize().x / 4 + 60, window.getSize().y / 5 - 30);

    sf::RectangleShape buttonsOption[3];
    for (int i = 0; i < 3; ++i) {
        buttonsOption[i].setSize(sf::Vector2f(200.f, 50.f));
        buttonsOption[i].setFillColor(sf::Color::Black);
        buttonsOption[i].setOutlineColor(sf::Color::White);
        buttonsOption[i].setOutlineThickness(2.f);
        buttonsOption[i].setPosition(background.getPosition() + sf::Vector2f(100.0f, 70.0f + i * 100.0f));
    }

    sf::Text options[3];
    for (int i = 0; i < 3; ++i) {
        options[i].setFont(font);
        options[i].setFillColor(sf::Color::White);
        options[i].setCharacterSize(24);
    }

    options[0].setString("Okno");
    options[0].setPosition(buttonsOption[0].getPosition() + sf::Vector2f(80.0f, 10.0f));
    options[1].setString("Pelen ekran");
    options[1].setPosition(buttonsOption[1].getPosition() + sf::Vector2f(65.0f, 10.0f));
    options[2].setString("Wroc");
    options[2].setPosition(buttonsOption[2].getPosition() + sf::Vector2f(80.0f, 10.0f));

    mod = 0;
    while (!mod) {
        mouse_position = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                    for (int i = 0; i < 4; ++i)
                        if (buttonsOption[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                            switch (i) {
                            case 0:
                                mod = 10;
                                break;
                            case 1:
                                mod = 11;
                                break;
                            default:
                                mod = 1;
                                break;
                            }

        window.clear(sf::Color(60, 60, 179));
        window.draw(background);
        for (int i = 0; i < 3; ++i) {
            if (buttonsOption[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                buttonsOption[i].setFillColor(sf::Color(128, 128, 128));
            else
                buttonsOption[i].setFillColor(sf::Color::Black);

            window.draw(buttonsOption[i]);
            window.draw(options[i]);
        }
        window.display();
    }
}

void MainMenuSettings::siz() {
    sf::RectangleShape background_x(sf::Vector2f(100.0f, 40.0f));
    background_x.setFillColor(sf::Color(50, 50, 50));
    background_x.setOutlineColor(sf::Color::White);
    background_x.setOutlineThickness(2.0f);
    background_x.setPosition(window.getSize().x / 4 + 120, window.getSize().y / 5 + 200);

    sf::RectangleShape background_y(sf::Vector2f(100.0f, 40.0f));
    background_y.setFillColor(sf::Color(50, 50, 50));
    background_y.setOutlineColor(sf::Color::White);
    background_y.setOutlineThickness(2.0f);
    background_y.setPosition(window.getSize().x / 4 + 240, window.getSize().y / 5 + 200);

    sf::RectangleShape confirm_button(sf::Vector2f(100.0f, 40.0f));
    confirm_button.setFillColor(sf::Color(50, 50, 50));
    confirm_button.setOutlineColor(sf::Color::White);
    confirm_button.setOutlineThickness(2.0f);
    confirm_button.setPosition(window.getSize().x / 4 + 180, window.getSize().y / 5 + 260);

    sf::RectangleShape background(sf::Vector2f(450.0f, 60.0f));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(2.0f);
    background.setPosition(window.getSize().x / 4 + 10, window.getSize().y / 5 + 120);

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(35);
    text.setString("Podaj   rozmiary   okna   (szerokosc,   wysokosc)");
    text.setPosition(background.getPosition().x + 20, background.getPosition().y + 5);

    sf::Text input_text_x;
    input_text_x.setFont(font);
    input_text_x.setFillColor(sf::Color::White);
    input_text_x.setOutlineColor(sf::Color::Black);
    input_text_x.setOutlineThickness(1.0f);
    input_text_x.setCharacterSize(24);
    input_text_x.setPosition(background_x.getPosition().x + 10, background_x.getPosition().y + 5);

    sf::Text input_text_y;
    input_text_y.setFont(font);
    input_text_y.setFillColor(sf::Color::White);
    input_text_y.setOutlineColor(sf::Color::Black);
    input_text_y.setOutlineThickness(1.0f);
    input_text_y.setCharacterSize(24);
    input_text_y.setPosition(background_y.getPosition().x + 10, background_y.getPosition().y + 5);

    sf::Text confirm_text;
    confirm_text.setFont(font);
    confirm_text.setFillColor(sf::Color::White);
    confirm_text.setCharacterSize(24);
    confirm_text.setString("Potwierdz");
    confirm_text.setPosition(confirm_button.getPosition().x + 20, confirm_button.getPosition().y + 5);

    std::string user_in_x, user_in_y;
    bool editing_x = false;
    bool editing_y = false;
    bool good1 = true;
    bool good2 = true;
    std::regex num_pat("[0-9]+");

    while (true) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (background_x.getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                        editing_x = true;
                        editing_y = false;
                        background_x.setFillColor(sf::Color(200, 200, 200));
                        background_y.setFillColor(sf::Color(50, 50, 50));
                    }
                    else if (background_y.getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                        editing_y = true;
                        editing_x = false;
                        background_y.setFillColor(sf::Color(200, 200, 200));
                        background_x.setFillColor(sf::Color(50, 50, 50));
                    }
                    else if (confirm_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                        background_x.setFillColor(sf::Color(50, 50, 50));
                        background_y.setFillColor(sf::Color(50, 50, 50));

                        std::regex size_pat("^(1000|[1][0-4][0-9][0-9]|1500)$");
                        if (!std::regex_search(user_in_x, size_pat)) {
                            background_x.setFillColor(sf::Color::Red);
                            good1 = false;
                        }
                        else
                            good1 = true;
                        if (!std::regex_search(user_in_y, size_pat)) {
                            background_y.setFillColor(sf::Color::Red);
                            good2 = false;
                        }
                        else
                            good2 = true;

                        if (user_in_x.empty() || user_in_y.empty()) {
                            if (user_in_x.empty() && !user_in_y.empty())
                                good1 = false;
                            else if (!user_in_x.empty() && user_in_y.empty())
                                good2 = false;
                            else if (user_in_x.empty() && user_in_y.empty()) {
                                good1 = true;
                                good2 = true;
                            }
                        }

                        if (good1 && good2) {
                            if (!user_in_x.empty() && !user_in_y.empty()) {
                                win_siz.push_back(std::stoi(user_in_x));
                                win_siz.push_back(std::stoi(user_in_y));
                            }
                            return;
                        }
                    }
                    else {
                        editing_y = false;
                        editing_x = false;
                        background_x.setFillColor(sf::Color(50, 50, 50));
                        background_y.setFillColor(sf::Color(50, 50, 50));
                    }
                }
            }
            else if (event.type == sf::Event::TextEntered) {
                if (editing_x) {
                    if (event.text.unicode == 8) {
                        if (!user_in_x.empty()) {
                            user_in_x.pop_back();
                            input_text_x.setString(user_in_x);
                        }
                    }
                    else if (user_in_x.size() < 11) {
                        std::string inputChar(1, static_cast<char>(event.text.unicode));
                        std::string updatedInputX = user_in_x + inputChar;

                        if (std::regex_match(updatedInputX, num_pat)) {
                            user_in_x = updatedInputX;
                            input_text_x.setString(user_in_x);
                        }
                    }
                }
                if (editing_y) {
                    if (event.text.unicode == 8) {
                        if (!user_in_y.empty()) {
                            user_in_y.pop_back();
                            input_text_y.setString(user_in_y);
                        }
                    }
                    else if (user_in_y.size() < 11) {
                        std::string inputChar(1, static_cast<char>(event.text.unicode));
                        std::string updatedInputY = user_in_y + inputChar;

                        if (std::regex_match(updatedInputY, num_pat)) {
                            user_in_y = updatedInputY;
                            input_text_y.setString(user_in_y);
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
        window.draw(background_x);
        window.draw(background_y);
        window.draw(confirm_button);
        window.draw(input_text_x);
        window.draw(input_text_y);
        window.draw(confirm_text);
        window.draw(background);
        window.draw(text);
        window.display();
    }
}

void MainMenuSettings::displayAuthor() {
    sf::RectangleShape background(sf::Vector2f(300.0f, 200.0f));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(5.f);
    background.setPosition(window.getSize().x / 3 + 10, window.getSize().y / 3 + 30);

    sf::RectangleShape button;
    button.setSize(sf::Vector2f(200.f, 50.f));
    button.setFillColor(sf::Color::Black);
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(2.f);
    button.setPosition(background.getPosition() + sf::Vector2f(50.0f, 110.0f));

    sf::Text options[3];
    for (int i = 0; i < 3; ++i) {
        options[i].setFont(font);
        options[i].setFillColor(sf::Color::White);
        options[i].setCharacterSize(24);
    }
    options[0].setCharacterSize(35);
    options[0].setString("Autor:");
    options[0].setPosition(background.getPosition() + sf::Vector2f(40.0f, 40.0f));
    options[1].setCharacterSize(35);
    options[1].setFillColor(sf::Color::Blue);
    options[1].setOutlineColor(sf::Color::White);
    options[1].setOutlineThickness(3.0f);
    options[1].setString("Bartosz   Helinski");
    options[1].setPosition(background.getPosition() + sf::Vector2f(115.0f, 40.0f));
    options[2].setString("Wroc");
    options[2].setPosition(button.getPosition() + sf::Vector2f(85.0f, 10.0f));

    while (true) {
        mouse_position = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                    if (button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        return;

        window.clear(sf::Color(60, 60, 179));
        window.draw(background);
        if (button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            button.setFillColor(sf::Color(128, 128, 128));
        else
            button.setFillColor(sf::Color::Black);
        window.draw(button);
        for (int i = 0; i < 3; ++i)
            window.draw(options[i]);
        window.display();
    }
}

bool MainMenuSettings::confirmExit() {
    sf::RectangleShape dialog(sf::Vector2f(450.0f, 200.0f));
    dialog.setFillColor(sf::Color(128, 128, 128));
    dialog.setOutlineThickness(3.0f);
    dialog.setOutlineColor(sf::Color::Black);
    dialog.setPosition(window.getSize().x / 4 + 30, window.getSize().y / 3 + 25);

    sf::Text text("Czy na pewno chcesz wyjsc?", font, 50);
    text.setFillColor(sf::Color::Black);
    text.setPosition(dialog.getPosition() + sf::Vector2f(60.0f, 30.0f));

    sf::RectangleShape yesButton(sf::Vector2f(150.0f, 50.0f));
    yesButton.setFillColor(sf::Color::Green);
    yesButton.setOutlineThickness(2.f);
    yesButton.setOutlineColor(sf::Color::Black);
    yesButton.setPosition(dialog.getPosition() + sf::Vector2f(50.0f, 110.0f));

    sf::RectangleShape noButton(sf::Vector2f(150.0f, 50.0f));
    noButton.setFillColor(sf::Color::Red);
    noButton.setOutlineThickness(2.f);
    noButton.setOutlineColor(sf::Color::Black);
    noButton.setPosition(dialog.getPosition() + sf::Vector2f(250.0f, 110.0f));

    sf::Text yesText("Tak", font, 35);
    yesText.setFillColor(sf::Color::Black);
    yesText.setPosition(dialog.getPosition() + sf::Vector2f(110.0f, 112.0f));

    sf::Text noText("Nie", font, 35);
    noText.setFillColor(sf::Color::Black);
    noText.setPosition(dialog.getPosition() + sf::Vector2f(310.0f, 112.0f));

    while (true) {
        mouse_position = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                    if (yesButton.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        return true;
                    else if (noButton.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
                        return false;

        window.draw(dialog);
        window.draw(text);

        if (yesButton.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            yesButton.setFillColor(sf::Color::Yellow);
        else if (noButton.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            noButton.setFillColor(sf::Color::Yellow);
        else {
            yesButton.setFillColor(sf::Color::Green);
            noButton.setFillColor(sf::Color::Red);
        }

        window.draw(yesButton);
        window.draw(noButton);
        window.draw(yesText);
        window.draw(noText);
        window.display();
    }
}

std::vector<std::vector<int>>MainMenuSettings::getSettings() {
    if (settings.size() != 0)
        var.push_back(settings);
    return var;
}