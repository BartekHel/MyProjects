#include "InGameSettings.h"

InGameSettings::InGameSettings(sf::RenderWindow& window) : window(window), texts(3), buttons(3) {
	font.loadFromFile("fonts/amatic.ttf");

    background.setSize(sf::Vector2f(400.0f, 400.0f));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(5.f);
    background.setPosition(window.getSize().x / 4 + 60, window.getSize().y / 5 - 30);

    for (int i = 0; i < 3; ++i) {
        buttons[i].setSize(sf::Vector2f(200.f, 50.f));
        buttons[i].setFillColor(sf::Color::Black);
        buttons[i].setOutlineColor(sf::Color::White);
        buttons[i].setOutlineThickness(2.f);
        buttons[i].setPosition(background.getPosition() + sf::Vector2f(100.0f, 70.0f + i * 100.0f));
    }

    for (int i = 0; i < 3; ++i) {
        texts[i].setFont(font);
        texts[i].setFillColor(sf::Color::White);
        texts[i].setCharacterSize(24);
    }
    texts[0].setString("Wroc");
    texts[0].setPosition(buttons[0].getPosition() + sf::Vector2f(83.0f, 10.0f));
    texts[1].setString("Menu glowne");
    texts[1].setPosition(buttons[1].getPosition() + sf::Vector2f(60.0f, 10.0f));
    texts[2].setString("Wyjdz");
    texts[2].setPosition(buttons[2].getPosition() + sf::Vector2f(80.0f, 10.0f));
}

InGameSettings::~InGameSettings() {

}

void InGameSettings::display() {
    mouse_position = sf::Mouse::getPosition(window);

    window.draw(background);
    for (int i = 0; i < 3; ++i) {
        const bool contains = buttons[i].getGlobalBounds().contains(mouse_position.x, mouse_position.y);
        if (contains)
            buttons[i].setFillColor(sf::Color(50, 50, 50));
        else
            buttons[i].setFillColor(sf::Color::Black);

        window.draw(buttons[i]);
        window.draw(texts[i]);
    }
}

int InGameSettings::events() {
    mouse_position = sf::Mouse::getPosition(window);

    std::vector<bool> contains = {
         buttons[0].getGlobalBounds().contains(mouse_position.x, mouse_position.y),
         buttons[1].getGlobalBounds().contains(mouse_position.x, mouse_position.y),
         buttons[2].getGlobalBounds().contains(mouse_position.x, mouse_position.y)
    };

    if (contains[0])
        return 0;
    else if (contains[1])
        return 3;
    else if (contains[2])
        if (confirmExit())
            window.close();

    return 1;
}

bool InGameSettings::confirmExit() {
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

std::vector<std::vector<int>> InGameSettings::getSettings() {
	std::vector<std::vector<int>> temp;
	return temp;
}