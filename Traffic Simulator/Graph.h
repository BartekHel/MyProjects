#pragma once

#include <vector>
#include "Structs.h"

class Graph {

    std::vector<std::vector<int>> map;
    int rows, cols;

    std::vector<Connection> connections, entrances, exits;
    std::vector<std::pair<int, int>> intersections;
    std::vector<int> indexes;
    std::vector<std::vector<int>> links;

public:
    Graph() { };
    Graph(std::vector<std::vector<int>>& map);
    ~Graph();

    Vertex nearestVertex(const Vertex& point, int choice);
    void create();
    int getSize();
    std::pair<int, int> getRowCol();
    std::vector<std::vector<Connection>> getConnections();
    std::pair<int, int> getIntersection(const int i);
    int getIntersectionsNum();
    int getIdx(int i);
    std::vector<int> getLinks(int i);
    void clear();
};