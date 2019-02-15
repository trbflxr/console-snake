#ifndef SNAKE_BOARD_H
#define SNAKE_BOARD_H


#include <thread>
#include <vector>
#include "node.h"
#include "point.h"

#define HBORDER_CHAR '-'
#define VBORDER_CHAR '|'
#define SNAKE_HEAD_CHAR 'x'
#define SNAKE_BODY_CHAR 'o'
#define FOOD_CHAR '*'
#define VOID_CHAR ' '

#define REPAINT_INTERVAL 100


class Game;

class Board final {
public:
    explicit Board(int rows, int columns, Game *game);
    ~Board();

    void generate() const;

    void startRepaint();
    void stopRepaint();

    void addNode(NodeType type, const point &pos) const;
    NodeType getNodeType(const point &pos) const;

    Node *getNode(const point &pos) const;

    point getRandomPoint() const;

    inline int getRows() const { return rows; }
    inline int getColumns() const { return columns; }

private:
    void autoPaintFunc();
    static void autoPaintFuncWrapper(void *data);

    void draw();

private:
    Game *game;

    int rows;
    int columns;

    //should it be a 2d array?
    std::vector<Node*> nodes;

    bool repaint;
    std::thread *repaintThread;
};


#endif //SNAKE_BOARD_H
