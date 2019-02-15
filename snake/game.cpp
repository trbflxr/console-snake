#include "display.h"
#include "game.h"


Game::Game(int boardSize)
    : score(0),
      shouldStop(false),
      moveThread(nullptr) {

    srand(static_cast<unsigned>(time(nullptr)));

    board = new Board(boardSize, boardSize * 2, this);
    snake = new Snake(this, board, {5, 5}, Direction::Right);
}

Game::~Game() {
    if (!shouldStop) {
        stop();
    }

    delete snake;
    delete board;
}

void Game::start() {
    score = 0;
    shouldStop = false;

    board->generate();
    snake->spawn();
	board->spawnFood();

    //repaint thread
    board->startRepaint();

    moveThread = new std::thread(moveFuncWrapper, this);

    int ch;
    while ((ch = Display::getChar()) != KEY_ESC) {
        switch (ch) {
            case KEY_ARROW_LEFT: {
                snake->changeDirection(Direction::Left);
                break;
            }
            case KEY_ARROW_RIGHT: {
                snake->changeDirection(Direction::Right);
                break;
            }
            case KEY_ARROW_UP: {
                snake->changeDirection(Direction::Up);
                break;
            }
            case KEY_ARROW_DOWN: {
                snake->changeDirection(Direction::Down);
                break;
            }
            default: break;
        }

        //game over pause
        if (ch == KEY_RETURN) {
            break;
        }
    }

    board->stopRepaint();
}

void Game::stop() {
    shouldStop = true;

    if (moveThread) {
        moveThread->detach();
        delete moveThread;
    }
}

void Game::moveFunc() {
    while (!shouldStop) {
        Display::sleep(200);

        const Node *h = snake->getNextHead();
        const point &p = h->pos;

        //bounds check
        if (p.x < 1 || p.x > board->getRows() ||
            p.y < 1 || p.y > board->getColumns()) {
            stop();
        }

        //self check
        if (h->type == NodeType::SnakeBody) {
            stop();
        }

        snake->move();
    }
}

void Game::moveFuncWrapper(void *data) {
    Game *g = static_cast<Game *>(data);
    g->moveFunc();
}
