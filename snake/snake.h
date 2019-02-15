#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H


#include <deque>
#include <mutex>
#include "point.h"
#include "node.h"

class Board;

enum class Direction {
    Left,
    Right,
    Up,
    Down
};

class Snake final {
public:
    explicit Snake(Board *board, const point &tailPos, Direction direction);

    void spawn();

    void changeDirection(Direction direction);

    void move();

    Node *getNextHead() const;

    void eat(Node *food);

private:
    Board *board;
    const point startPos;
    const Direction startDirection;
    Direction direction;

    //this will be deleted by board
    Node *head;
    std::deque<Node*> body;

    std::mutex mutex;
};


#endif // SNAKE_SNAKE_H
