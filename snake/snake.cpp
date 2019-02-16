#include "snake.h"
#include "game.h"
#include "board.h"


Snake::Snake(Game *game, Board *board, const point &tailPos, Direction direction)
    : game(game),
      board(board),
      startPos(tailPos),
      startDirection(direction),
      direction(direction),
      head(nullptr) { }

void Snake::spawn() {
    body.clear();

    nextDirection.clear();
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
    if (nextDirection.size() < 2 && Snake::direction != direction) {
        nextDirection.push_back(direction);
    }
}

void Snake::move() {
    bool moved = false;

    std::lock_guard<std::mutex> guard(mutex);

    //this needed for "sharp turns"
    //when pressed arrow down and arrow left
    //snake do this:
    //
    //   ooo
    //    xo
    //
    //initial direction: right

    for (auto &&d : nextDirection) {
        if (checkDirection(d)) {
            direction = d;
            moveInternal();
            moved = true;
        }
    }

    if (!moved) {
        moveInternal();
    }
    nextDirection.clear();
}

void Snake::moveInternal() {
    Node *nextHead = getNextHead();
    if (nextHead->type == NodeType::Food) {
        eat(nextHead);
        game->addScore(SCORE_PTS);
        board->spawnFood();
        return;
    }

    if (nextHead->type == NodeType::Border || nextHead->type == NodeType::SnakeBody) {
        nextHead->type = NodeType::SnakeHit;
        game->stop();
        return;
    }

    //swap back and front body pieces
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
    //it's locked already in move method
    //food node is now snakes head
    Node *newHead = food;
    newHead->type = NodeType::SnakeHead;

    head->type = NodeType::SnakeBody;

    body.push_front(newHead);

    head = newHead;
}

bool Snake::checkDirection(Direction d) const {
    return !(d == Direction::Left && direction == Direction::Right ||
        d == Direction::Right && direction == Direction::Left ||
        d == Direction::Up && direction == Direction::Down ||
        d == Direction::Down && direction == Direction::Up);
}
