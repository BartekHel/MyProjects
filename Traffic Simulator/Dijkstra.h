#pragma once

#include <queue>

#include "Graph.h"
#include "Structs.h"

class Dijkstra {
    Graph graph;

    int rows, cols, out, idx;

    Vertex start, end;

    std::vector<Connection> connections, entrances, exits;

public:
    Dijkstra() { };
    Dijkstra(Graph& graph);
    ~Dijkstra();

    std::pair<int, int> getPos(const int i);
    std::pair<int, int> getStart(const int i);
    std::pair<int, int> getEnd(const int o);
    std::pair<int, int> algorithm(std::pair<int, int> position);
    int getIdx();
};