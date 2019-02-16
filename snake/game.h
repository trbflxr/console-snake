#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H


#include <thread>
#include "board.h"
#include "snake.h"

#define SCORE_PTS 10

class Game final {
public:
    explicit Game(int boardSize, int frameDelay);
    ~Game();

    void start();
    void stop();

    inline void addScore(int pts) { score += pts; }
    inline int getScore() const { return score; }
    inline bool isOver() const { return shouldStop; }

private:
    void moveFunc() const;
    static void moveFuncWrapper(void *data);
    
private:
    Board *board;
    Snake *snake;

	int frameDelay;
    int score;

    bool shouldStop;

    std::thread *moveThread;
};

#endif //SNAKE_GAME_H
