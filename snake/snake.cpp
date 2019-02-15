#include "snake.h"
#include "board.h"

Snake::Snake(Board *board, const point &tailPos, Direction direction)
    : board(board),
      startPos(tailPos),
      startDirection(direction),
      direction(direction),
      head(nullptr) { }

void Snake::spawn() {
    body.clear();

    direction = startDirection;

    //create snake
    head = board->getNode(startPos);
    head->type = NodeType::SnakeBody;
    body.push_front(head);

    Node *b0 = getNextHead();
    b0->type = NodeType::SnakeBody;
    head = b0;
    body.push_front(head);

    Node *b1 = getNextHead();
    b1->type = NodeType::SnakeHead;
    head = b1;
    body.push_front(head);
}

void Snake::changeDirection(Direction direction) {
    if (direction == Direction::Left && Snake::direction == Direction::Right ||
        direction == Direction::Right && Snake::direction == Direction::Left ||
        direction == Direction::Up && Snake::direction == Direction::Down ||
        direction == Direction::Down && Snake::direction == Direction::Up) {
        return;
    }

    Snake::direction = direction;
}

void Snake::move() {
    std::lock_guard<std::mutex> guard(mutex);

    //"swap" back and front snake body piece
    Node *nextHead = getNextHead();
    nextHead->type = NodeType::SnakeHead;

    head->type = NodeType::SnakeBody;

    body.push_front(nextHead);

    Node *empty = body.back();
    body.pop_back();
    empty->type = NodeType::Void;

    head = nextHead;
}

Node *Snake::getNextHead() const {
    switch (direction) {
        case Direction::Left: return board->getNode({head->pos.y - 1, head->pos.x});
        case Direction::Right: return board->getNode({head->pos.y + 1, head->pos.x});
        case Direction::Up: return board->getNode({head->pos.y, head->pos.x - 1});
        case Direction::Down: return board->getNode({head->pos.y, head->pos.x + 1});
        default: return nullptr;
    }
}

void Snake::eat(Node *food) {
    std::lock_guard<std::mutex> guard(mutex);

    //food node is now snakes head
    Node *newHead = food;
    newHead->type = NodeType::SnakeHead;

    head->type = NodeType::SnakeBody;

    body.push_front(newHead);

    head = newHead;
}
