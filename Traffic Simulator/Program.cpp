#include "Program.h"
#include "Scheme.h"
#include "Map.h"
#include "MainMenuSettings.h"
#include "InGameSettings.h"
#include "MenuControl.h"
#include "MapControl.h"
#include "CarControl.h"

#include <atomic>

std::atomic<bool> stop(false);

Program::Program() {
    window = new Window;

    view = window->getWindow().getView();
    prev_zoom = zoom = 1.0f;
    view.zoom(zoom);
    base_view = view;
    window->getWindow().setView(view);
    speed = 30.0f;

    ui = new MainMenuSettings(window->getWindow());
    control = std::make_unique<MenuControl>(ui);

    settings_open = 1;
    is_pressed = false;

    Program::setSet();
}

Program::~Program() {
    delete buttons;
    delete map;
    delete ui;
    delete window;
    Program::destruct();
}

void Program::destruct() {
    stop = true;
    for (auto& thread : car_threads)
        thread.second.join();
    car_threads.clear();
    for (const auto& ptr : cars)
        delete ptr;
    cars.clear();
    for (const auto& ptr : intersections)
        delete ptr;
    graph.clear();
    intersections.clear();
}

void Program::setSet() {
    start = false;
    show = false;
    sec_faze = false;
    time = sf::Time::Zero;
}

bool Program::is_running() {
    return window->getWindow().isOpen();
}

void Program::events() {
    while (window->getWindow().pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->getWindow().close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape && !settings_open) {
                start = false;
                settings_open = 1;
                ui = new InGameSettings(window->getWindow());
                control = std::make_unique<MenuControl>(ui);
                tmp = view;
                view = base_view;
                window->getWindow().setView(view);
            }
            else if (event.key.code == sf::Keyboard::Tilde)
                show = show ? false : true;
            break;
        case sf::Event::MouseWheelScrolled:
            if (!settings_open) {
                const float z = event.mouseWheelScroll.delta;

                if (z > 0) {
                    zoom *= 1.1f;
                    zoomed = 1;
                }
                else if (z < 0) {
                    zoom /= 1.1f;
                    zoomed = -1;
                }
                else
                    zoomed = 0;

                view.zoom(prev_zoom / zoom);
                prev_zoom = zoom;
                window->getWindow().setView(view);
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
                if (settings_open) {
                    settings_open = ui->events();

                    if (!settings_open)
                        Program::settingsClosed();
                    else
                        Program::settingsOpen();
                }
                else {
                    is_pressed = true;
                    change = 1;
                }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                is_pressed = true;
                change = 3;
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (!settings_open && event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right) {
                is_pressed = false;
                map->functions(2);
            }
            break;
        default:
            continue;
        }
    }

    if (!settings_open) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            view.move(0.0f, -speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            view.move(0.0f, speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            view.move(-speed, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            view.move(speed, 0.0f);
        window->getWindow().setView(view);
    }
}

void Program::settingsOpen() {
    if (settings_open == 3) {
        delete ui;
        ui = new MainMenuSettings(window->getWindow());
        control = std::make_unique<MenuControl>(ui);

        if (sec_faze)
            Program::destruct();
    }
    else if (settings_open > 9 && settings_open < 20) {
        delete window;
        window = new Window(settings_open);
        settings_open = 1;
    }
    else if (settings_open >= 1000) {
        std::vector<int> siz;
        siz.push_back(settings_open);
        settings_open = ui->events();
        siz.push_back(settings_open);
        delete window;
        window = new Window(siz);
        settings_open = 1;
    }
}

void Program::settingsClosed() {
    const int size = ui->getSettings().size();

    if (size != 0) {
        delete map;

        if (size == 1) {
            std::vector<int> size = ui->getSettings()[0];
            map = new Scheme(window->getWindow(), size);
        }
        else {
            std::vector<int> size;
            std::vector<std::vector<int>> roads = ui->getSettings();
            size.push_back(roads[0].size());
            size.push_back(roads.size());
            map = new Scheme(window->getWindow(), size);
            map->setRoads(roads);
        }

        map_sprite = map->getMap();
        view = base_view;
        window->getWindow().setView(view);
        Program::setSet();
        delete buttons;
        buttons = new SideOptions(window->getWindow());
        stop = false;
        control = std::make_unique<MapControl>(this);
    }
    else {
        if (settings_open == 3)
            stop = true;
        else {
            control = std::make_unique<CarControl>(this);
            view = tmp;
            window->getWindow().setView(view);
        }
    }

    delete ui;
}

void carThreadFun(Car* car, std::vector<Intersection*>& intersections, std::map<Car*, std::pair<bool, bool>> can_move, std::vector<Car*>& cars) {
    while (car->update(0)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        const int idx = car->getIndex();

        for (int j = 0; j < intersections.size(); ++j) {
            int check = intersections[j]->isIndex(idx);
            if (check != -1 && intersections[j]->isVisible(check) && car->checkCollision(intersections[j]->getRect(check))) {
                can_move[car].first = false;
                break;
            }
            else
                can_move[car].first = true;
        }

        can_move[car].second = true;
        for (int j = 0; j < cars.size(); ++j) {
            if (car != cars[j] && idx == cars[j]->getIndex() && car->checkCollision(cars[j])) {
                if (car->checkCollision(cars[j]) == 1)
                    can_move[cars[j]].second = false;
                else
                    can_move[car].second = false;
                break;
            }
            else
                can_move[cars[j]].second = true;
        }

        if (!can_move[car].first || !can_move[car].second)
            car->stop();
        else {
            car->move();
            car->moveAfter();
        }

        if (stop)
            break;
    }
}

void Program::render(std::mt19937& mt) {
    window->getWindow().clear(sf::Color(60, 60, 179));

    dt = clock.restart();
    pos = view.getCenter() + sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2);

    if (is_pressed) {
        map->functions(change);
        change = 0;
    }

    control->renderView(mt);

    window->getWindow().display();
}

void Program::renderProgram(std::mt19937& mt) {
    float dt_sec = dt.asSeconds();

    if (start) {
        time += dt;

        for (int i = 0; i < cars.size(); ++i) {
            if (!cars[i]->update(dt_sec)) {
                car_threads[cars[i]].join();
                car_threads.erase(cars[i]);
                delete cars[i];
                cars.erase(cars.begin() + i);
                --i;
            }
        }

        if (cars.size() != n_cars && time >= sf::seconds(1.0) || cars.empty()) {
            Car* car = new Car(graph, mt);
            cars.push_back(car);
            can_move.emplace(car, std::make_pair(true, true));
            car_threads[car] = std::thread(carThreadFun, car, std::ref(intersections), std::ref(can_move), std::ref(cars));
            time = sf::Time::Zero;
        }

        int size2 = intersections.size();
        for (int i = 0; i < size2; ++i)
            intersections[i]->update();
    }

    Program::display();

    const int choice = buttons->displayOptions(pos, zoomed);
    start = (choice == 3) ? false : ((choice == 4) ? true : start);
}

void Program::display() {
    const int size1 = cars.size();
    for (int i = 0; i < size1; ++i) {
        if (show) {
            window->getWindow().draw(cars[i]->getCar().second.first);
            window->getWindow().draw(cars[i]->getCar().second.second);
        }
        window->getWindow().draw(cars[i]->getCar().first);
    }

    const int size2 = intersections.size();
    for (int i = 0; i < size2; ++i)
        for (int j = 0; j < 4; ++j) {
            if (show && intersections[i]->isVisible(j))
                window->getWindow().draw(intersections[i]->getRect(j));
            window->getWindow().draw(intersections[i]->getLight(j));
        }
}

void Program::buttonsShow(std::mt19937& mt) {
    window->getWindow().draw(map_sprite);

    const int choice = buttons->displayOptions(pos, zoomed);

    if (choice == 1) {
        std::vector<std::vector<int>> maps = map->getRoads();
        sf::View temp_view = view;
        view = base_view;
        window->getWindow().setView(view);
        buttons->save(maps);
        view = temp_view;
        window->getWindow().setView(view);
    }
    else if (choice == 2 && map->check()) {
        delete map;
        map = new Map;
        map_sprite = map->getMap();
        start = false;
        sec_faze = true;
        view = base_view;
        window->getWindow().setView(view);
        delete buttons;
        buttons = new SideOptions(window->getWindow(), true);
        n_cars = buttons->select();

        std::vector<std::vector<int>> maps = map->getRoads();
        graph = Graph(maps);
        const int size = graph.getIntersectionsNum();

        for (int i = 0; i < size; ++i) {
            Intersection* intersection = new Intersection(graph.getLinks(i), graph.getIntersection(i), mt);
            intersections.push_back(intersection);
        }

        control = std::make_unique<CarControl>(this);
    }

    zoomed = 0;
}