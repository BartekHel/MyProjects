#include "Car.h"

#include <iostream>

Car::Car(Graph& graph, std::mt19937& mt) : graph(graph) {
    texture.loadFromFile("textures/car.png");

    texture.setSmooth(true);
    sf::Vector2u texture_size = texture.getSize();
    float scale_x = static_cast<float>(25) / texture_size.x;
    float scale_y = static_cast<float>(40) / texture_size.y;

    car.first.setTexture(texture);
    car.first.setScale(scale_x, scale_y);
    car.second.second.setSize(sf::Vector2f(40.0f, 40.0f));
    car.second.first.setSize(sf::Vector2f(40.0f, 10.0f));

    speed = 10.0f;

    std::uniform_int_distribution<int> dist(0, graph.getSize());

    int i1 = dist(mt);
    int o1 = i1;
    while (o1 == i1)
        o1 = dist(mt);

    algorithm = Dijkstra(graph);

    dest = algorithm.getEnd(o1);
    auto Converter = [](const std::pair<int, int>& p) {
        return sf::Vector2f(static_cast<float>(p.first), static_cast<float>(p.second));
    };
    position = Converter(algorithm.getPos(i1));
    position.x *= 50.0f;
    position.y *= 50.0f;

    position += sf::Vector2f(25, 25);

    idx = graph.getIdx(i1);
    goal = algorithm.getStart(i1);
    setDestination(goal);

    idx_change = false;
}

Car::~Car() {

}

void Car::setDestination(std::pair<int, int> goal) {
    destination.x = goal.first * 50.0f;
    destination.y = goal.second * 50.0f;
    direction.x = direction.y = 0;

    if (std::abs(destination.y - position.y) < std::abs(destination.x - position.x)) {
        if (destination.x > position.x) {
            direction.x = 1;
            rotation = 90.0f;
        }
        else {
            direction.x = -1;
            rotation = 270.0f;
        }
    }
    else {
        if (destination.y > position.y) {
            direction.y = 1;
            rotation = 180.0f;
        }
        else {
            direction.y = -1;
            rotation = 0.0f;
        }
    }

    car.first.setRotation(rotation);
    car.second.second.setRotation(rotation);
    car.second.first.setRotation(rotation);

    sf::FloatRect bounds = car.first.getLocalBounds();
    car.first.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    bounds = car.second.second.getLocalBounds();
    car.second.second.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    car.second.first.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    sf::Vector2f current = car.first.getPosition();
    sf::Vector2f trans_vector = position - current;
    car.first.move(trans_vector);
    car.second.second.move(trans_vector);
    car.second.first.move(trans_vector);
}

void Car::moveAfter() {
    car.first.setPosition(position.x, position.y);
    car.second.second.setPosition(car.first.getPosition() - sf::Vector2f(5.0f * direction.x, 5.0f * direction.y));
    car.second.first.setPosition(car.first.getPosition() + sf::Vector2f(10.0f * direction.x, 10.0f * direction.y));
}

bool Car::update(const float dt) {
    int adj = (direction.x == 1 || direction.y == 1) ? 50.0f : 0.0f;

    if (direction.y == 0 && std::abs(destination.x + adj - position.x) < 30.0f || direction.x == 0 && std::abs(destination.y + adj - position.y) < 30.0f) {
        if (goal.first == dest.first && goal.second == dest.second)
            return 0;
        else {
            goal = algorithm.algorithm(goal);
            setDestination(goal);
            idx = -1;
            idx_change = true;
            if (goal.first == 0 && goal.second == 0)
                return 0;
        }
    }
    else if (idx_change) {
        idx = algorithm.getIdx();
        idx_change = false;
    }
    else {
        if (goal.first == dest.first && goal.second == dest.second)
            idx = -1;
        position += sf::Vector2f(direction.x * speed * dt, direction.y * speed * dt);
    }

    return 1;
}

int Car::checkCollision(Car* car2) {
    sf::FloatRect bounds1 = car.second.second.getGlobalBounds();
    sf::FloatRect bounds2 = car2->getCar().second.first.getGlobalBounds();

    sf::FloatRect bounds3 = car.second.first.getGlobalBounds();
    sf::FloatRect bounds4 = car2->getCar().second.second.getGlobalBounds();

    if (bounds1.intersects(bounds2))
        return 1;
    else if (bounds4.intersects(bounds3))
        return 2;
    return 0;
}

bool Car::checkCollision(const sf::RectangleShape& rect) {
    sf::FloatRect bounds1 = car.second.first.getGlobalBounds();
    sf::FloatRect bounds2 = rect.getGlobalBounds();
    sf::FloatRect bounds3 = car.second.second.getGlobalBounds();

    if (bounds1.intersects(bounds2) && !bounds2.intersects(bounds3))
        return true;
    return false;
}

void Car::stop() {
    speed = 0.0f;
}

void Car::move() {
    speed = 300.0f;
}

int Car::getIndex() {
    return idx;
}

std::pair<sf::Sprite, std::pair<sf::RectangleShape, sf::RectangleShape>>& Car::getCar() {
    return car;
}