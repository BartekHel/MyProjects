#include "Graph.h"

#include <algorithm>
#include <ranges>

Graph::Graph(std::vector<std::vector<int>>& map) : map(map) {
    rows = map.size();
    cols = map[0].size();

    Graph::create();

    std::vector<Connection> temp;
    std::ranges::copy(std::views::filter(connections, [](const Connection& connection) { return connection.dist == 1; }), back_inserter(temp));
    connections.erase(std::ranges::remove_if(connections, [](const Connection& connection) { return connection.dist == 1;}).begin(), connections.end());

    int ent_size = entrances.size();
    int con_size = connections.size();

    int size = getIntersectionsNum();
    links.resize(size, std::vector<int>(4));
    std::vector<std::pair<int, int>> pos(4);
    for (int i = 0; i < size; ++i) {
        const int x = intersections[i].second;
        const int y = intersections[i].first;
        pos[0] = std::make_pair(x, y);
        pos[2] = std::make_pair(x, y + 1);
        pos[3] = std::make_pair(x + 1, y + 1);
        pos[1] = std::make_pair(x + 1, y);

        for (int j = 0; j < 4; ++j) {
            links[i][j] = -1;
            for (int k = 0; k < entrances.size(); ++k) {
                const auto& temp = entrances[k].destin;
                if (pos[j].first == temp.x && pos[j].second == temp.y)
                    links[i][j] = k + con_size;
            }
            for (int k = 0; k < con_size; ++k) {
                const auto& temp = connections[k].destin;
                if (pos[j].first == temp.x && pos[j].second == temp.y)
                    links[i][j] = k;
            }
        }
    }

    connections.insert(connections.end(), temp.begin(), temp.end());

    std::vector<std::pair<Connection, int>> idx;
    for (int i = 0; i < ent_size; ++i)
        idx.push_back(std::make_pair(entrances[i], i));

    for (int i = 0; i < idx.size(); ++i)
        indexes.push_back(idx[i].second + con_size);
}

Graph::~Graph() {

}

Vertex Graph::nearestVertex(const Vertex& point, int choice) {
    const int y = point.x;
    const int x = point.y;
    Vertex nearest(0, 0);

    switch (choice) {
    case 1:
        for (int i = y - 1; i >= 0; --i)
            if (map[x][i] == 5 || map[x][i] == 1) {
                nearest = Vertex(i, x);
                break;
            }
        break;
    case 2:
        for (int i = y + 1; i < cols; ++i)
            if (map[x][i] == 5 || map[x][i] == 2) {
                nearest = Vertex(i, x);
                break;
            }
        break;
    case 3:
        for (int i = x + 1; i < rows; ++i)
            if (map[i][y] == 5 || map[i][y] == 3) {
                nearest = Vertex(y, i);
                break;
            }
        break;
    case 4:
        for (int i = x - 1; i >= 0; --i)
            if (map[i][y] == 5 || map[i][y] == 4) {
                nearest = Vertex(y, i);
                break;
            }
        break;
    }

    return nearest;
}

void Graph::create() {
    int rows1 = rows - 1;
    int cols1 = cols - 1;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] != 0) {
                Vertex entry_point(j, i);

                if (map[i][j] == 5 && map[i + 1][j + 1] == 5) {
                    intersections.push_back(std::make_pair(i, j));
                    Vertex nearest_inter(j, i + 1);
                    Vertex tmp = nearest_inter;
                    connections.emplace_back(entry_point, nearest_inter);
                    nearest_inter = nearestVertex(entry_point, 1);
                    if (nearest_inter.x != 0 || nearest_inter.y != 0)
                        if (map[nearest_inter.y][nearest_inter.x] == 5)
                            connections.emplace_back(entry_point, nearest_inter);

                    entry_point = tmp;
                    nearest_inter = Vertex(j + 1, i + 1);
                    tmp = nearest_inter;
                    connections.emplace_back(entry_point, nearest_inter);
                    nearest_inter = nearestVertex(entry_point, 3);
                    if (nearest_inter.x != 0 || nearest_inter.y != 0)
                        if (map[nearest_inter.y][nearest_inter.x] == 5)
                            connections.emplace_back(entry_point, nearest_inter);

                    entry_point = tmp;
                    nearest_inter = Vertex(j + 1, i);
                    tmp = nearest_inter;
                    connections.emplace_back(entry_point, nearest_inter);
                    nearest_inter = nearestVertex(entry_point, 2);
                    if (nearest_inter.x != 0 || nearest_inter.y != 0)
                        if (map[nearest_inter.y][nearest_inter.x] == 5)
                            connections.emplace_back(entry_point, nearest_inter);

                    entry_point = tmp;
                    nearest_inter = Vertex(j, i);
                    tmp = nearest_inter;
                    connections.emplace_back(entry_point, nearest_inter);
                    nearest_inter = nearestVertex(entry_point, 4);
                    if (nearest_inter.x != 0 || nearest_inter.y != 0)
                        if (map[nearest_inter.y][nearest_inter.x] == 5)
                            connections.emplace_back(entry_point, nearest_inter);

                    ++j;
                }
                else {
                    if (i == 0) {
                        Vertex nearest_inter = nearestVertex(entry_point, 3);
                        if (nearest_inter.x != 0 || nearest_inter.y != 0) {
                            if (map[i][j] == 3) {
                                entrances.emplace_back(entry_point, nearest_inter);
                                Vertex exit_point(entry_point.x + 1, entry_point.y);
                                Vertex exit_inter(nearest_inter.x + 1, nearest_inter.y);
                                exits.emplace_back(exit_inter, exit_point);
                            }
                        }
                    }
                    else if (i == rows1) {
                        Vertex nearest_inter = nearestVertex(entry_point, 4);
                        if (nearest_inter.x != 0 || nearest_inter.y != 0) {
                            if (map[i][j] == 4) {
                                entrances.emplace_back(entry_point, nearest_inter);
                                Vertex exit_point(entry_point.x - 1, entry_point.y);
                                Vertex exit_inter(nearest_inter.x - 1, nearest_inter.y);
                                exits.emplace_back(exit_inter, exit_point);
                            }
                        }
                    }
                    else if (j == 0) {
                        Vertex nearest_inter = nearestVertex(entry_point, 2);
                        if (nearest_inter.x != 0 || nearest_inter.y != 0) {
                            if (map[i][j] == 2) {
                                entrances.emplace_back(entry_point, nearest_inter);
                                Vertex exit_point(entry_point.x, entry_point.y - 1);
                                Vertex exit_inter(nearest_inter.x, nearest_inter.y - 1);
                                exits.emplace_back(exit_inter, exit_point);
                            }
                        }
                    }
                    else if (j == cols1) {
                        Vertex nearest_inter = nearestVertex(entry_point, 1);
                        if (nearest_inter.x != 0 || nearest_inter.y != 0) {
                            if (map[i][j] == 1) {
                                entrances.emplace_back(entry_point, nearest_inter);
                                Vertex exit_point(entry_point.x, entry_point.y + 1); 
                                Vertex exit_inter(nearest_inter.x, nearest_inter.y + 1);
                                exits.emplace_back(exit_inter, exit_point);
                            }
                        }
                    }
                }
            }
        }
    }
}

int Graph::getSize() {
    return entrances.size() - 1;
}

std::pair<int, int> Graph::getRowCol() {
    return std::make_pair(rows, cols);
}

std::vector<std::vector<Connection>> Graph::getConnections() {
    std::vector<std::vector<Connection>> temp;
    temp.push_back(connections);
    temp.push_back(entrances);
    temp.push_back(exits);
    return temp;
}

std::pair<int, int> Graph::getIntersection(const int i) {
    return intersections[i];
}

int Graph::getIntersectionsNum() {
    return intersections.size();
}

int Graph::getIdx(int i) {
    return indexes[i];
}

std::vector<int> Graph::getLinks(int i) {
    return links[i];
}

void Graph::clear() {
    map.clear();
    rows = 0;
    cols = 0;
    connections.clear();
    entrances.clear();
    exits.clear();
    intersections.clear();
    indexes.clear();
    links.clear();
}