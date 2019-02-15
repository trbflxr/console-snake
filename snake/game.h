#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H


#include <thread>
#include "board.h"
#include "snake.h"

#define SCORE_PTS 10

class Game final {
public:
    explicit Game(int boardSize);
    ~Game();

    void start();
    void stop();

    inline int getScore() const { return score; }
    inline bool isOver() const { return shouldStop; }

private:
    void moveFunc();
    static void moveFuncWrapper(void *data);

    void spawnFood();

private:
    Board *board;
    Snake *snake;

    Node *food;
    int score;

    bool shouldStop;

    std::thread *moveThread;
};

#endif //SNAKE_GAME_H
