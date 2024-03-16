#pragma once

struct Vertex {
    int x, y;

    Vertex() { }
    Vertex(int x, int y) : x(x), y(y) { }
};

struct Connection {
    Vertex source, destin;
    int dist;

    Connection(Vertex& source, Vertex& destin) : source(source), destin(destin) {
        dist = abs(destin.x - source.x + destin.y - source.y);
    }
};