#include "Dijkstra.h"

Dijkstra::Dijkstra(Graph& graph) : graph(graph) {
    rows = graph.getRowCol().first;
    cols = graph.getRowCol().second;

    connections = graph.getConnections()[0];
    entrances = graph.getConnections()[1];
    exits = graph.getConnections()[2];

    idx = -1;
}

Dijkstra::~Dijkstra() {

}

std::pair<int, int> Dijkstra::getPos(const int i) {
    std::pair<int, int> begin;

    begin.first = entrances[i].source.x;
    begin.second = entrances[i].source.y;

    return begin;
}

std::pair<int, int> Dijkstra::getStart(const int i) {
    std::pair<int, int> begin;

    begin.first = entrances[i].destin.x;
    begin.second = entrances[i].destin.y;

    return begin;
}

std::pair<int, int> Dijkstra::getEnd(const int o) {
    std::pair<int, int> finish;

    finish.first = exits[o].destin.x;
    finish.second = exits[o].destin.y;

    out = o;
    end.x = exits[o].source.x;
    end.y = exits[o].source.y;

    return finish;
}

std::pair<int, int> Dijkstra::algorithm(std::pair<int, int> position) {
    start.x = position.first;
    start.y = position.second;

    if (start.x == end.x && start.y == end.y)
        return std::make_pair(exits[out].destin.x, exits[out].destin.y);

    std::vector<std::vector<int>> distances(cols, std::vector<int>(rows, 999));
    std::vector<std::vector<Vertex>> previous(cols, std::vector<Vertex>(rows));
    std::vector<std::vector<int>> road_num(cols, std::vector<int>(rows));

    auto compare = [](const std::pair<Vertex, int>& a, const std::pair<Vertex, int>& b) {
        return a.second > b.second;
    };
    std::priority_queue<std::pair<Vertex, int>, std::vector<std::pair<Vertex, int>>, decltype(compare)> queue(compare);

    distances[start.x][start.y] = 0;
    queue.push(std::make_pair(start, 0));

    while (!queue.empty()) {
        Vertex current = queue.top().first;
        queue.pop();

        if (current.x == end.x && current.y == end.y)
            break;

        for (int i = 0; i < connections.size(); ++i) {
            const auto& connection = connections[i];
            if (connection.source.x == current.x && connection.source.y == current.y) {
                int new_dist = distances[current.x][current.y] + connection.dist;

                if (new_dist < distances[connection.destin.x][connection.destin.y]) {
                    distances[connection.destin.x][connection.destin.y] = new_dist;
                    previous[connection.destin.x][connection.destin.y] = current;
                    queue.push(std::make_pair(connection.destin, new_dist));

                    if (connection.dist == 1)
                        road_num[connection.destin.x][connection.destin.y] = -1;
                    else
                        road_num[connection.destin.x][connection.destin.y] = i;
                }
            }
        }
    }

    Vertex current = end;
    std::pair<int, int> path;

    while (current.x != start.x || current.y != start.y) {
        if (current.x < 0)
            return std::make_pair(0, 0);
        path = std::make_pair(current.x, current.y);
        idx = road_num[current.x][current.y];
        current = previous[current.x][current.y];
    }

    return path;
}

int Dijkstra::getIdx() {
    return idx;
}