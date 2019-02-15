#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H


#include "point.h"

class Board;

enum class NodeType {
    HBorder,
    VBorder,
    SnakeHead,
    SnakeBody,
    Food,
    Void
};

struct Node {
    Node(NodeType type, const point &pos)
        : type(type),
          pos(pos) {}

    NodeType type;
    point pos;
};


#endif //SNAKE_NODE_H
