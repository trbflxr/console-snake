#include "board.h"
#include "display.h"
#include "game.h"


Board::Board(int rows, int columns, Game *game)
    : game(game),
      rows(rows),
      columns(columns),
      repaint(false),
      repaintThread(nullptr) {

    //fill board
    for (int i = 0; i < rows + 2; ++i) {
        for (int j = 0; j < columns + 2; ++j) {
            nodes.push_back(new Node(NodeType::Void, {i, j}));
        }
    }
}

Board::~Board() {
    if (repaint) {
        stopRepaint();
    }

    for (auto &&n : nodes) {
        delete n;
    }
}

void Board::generate() const {
    for (int i = 0; i < rows + 2; ++i) {
        for (int j = 0; j < columns + 2; ++j) {
            Node *n = getNode({j, i});
            if (i == 0 || i == rows + 1 || j == 0 || j == columns + 1) {
                n->type = NodeType::Border;
            } else {
                n->type = NodeType::Void;
            }
        }
    }
}

void Board::draw() {
    int color = 0;
    for (auto &&n : nodes) {
        int ch;
        switch (n->type) {
            case NodeType::Border: {
                color = WHITE;
                ch = BORDER_CHAR;
                break;
            }
            case NodeType::SnakeHead: {
                color = GREEN;
                ch = SNAKE_HEAD_CHAR;
                break;
            }
            case NodeType::SnakeBody: {
                color = GREEN;
                ch = SNAKE_BODY_CHAR;
                break;
            }
            case NodeType::SnakeHit: {
                color = YELLOW;
                ch = SNAKE_HIT_CHAR;
                break;
            }
            case NodeType::Food: {
                color = RED;
                ch = FOOD_CHAR;
                break;
            }
            default: //fall trough
            case NodeType::Void: {
                ch = VOID_CHAR;
                break;
            }
        }

        Display::pushColor(color);
        Display::draw(ch, n->pos.x, n->pos.y);
        Display::popColor(color);
    }

    Display::draw(3, columns + 5, "Score: %i", game->getScore());
    if (game->isOver()) {
        Display::pushColor(RED);
        Display::pushAttribute(ATTR_REVERSE);
        Display::draw(4, columns + 5, "Game over. Press 'Enter' to continue.");
        Display::popAttribute(ATTR_REVERSE);
        Display::popColor(RED);
    }
}

void Board::startRepaint() {
    repaint = true;
    repaintThread = new std::thread(autoPaintFuncWrapper, this);
}

void Board::stopRepaint() {
    repaint = false;

    if (repaintThread) {
        repaintThread->join();
        delete repaintThread;
    }
}

void Board::addNode(NodeType type, const point &pos) const {
    getNode(pos)->type = type;
}

NodeType Board::getNodeType(const point &pos) const {
    return getNode(pos)->type;
}

Node *Board::getNode(const point &pos) const {
    //+2 cuz borders | -
    const int p = pos.y * (columns + 2) + pos.x;
    return nodes[p];
}

point Board::getRandomPoint() const {
    point p;
    p.y = rand() % rows + 1;
    p.x = rand() % columns + 1;

    //fixme
    //not the best solution but it fine for now
    while (getNodeType(p) != NodeType::Void) {
        p.y = rand() % rows + 1;
        p.x = rand() % columns + 1;
    }
    return p;
}

void Board::spawnFood() const {
    const point &p = getRandomPoint();
    Node *f = getNode(p);
    f->type = NodeType::Food;
}

void Board::autoPaintFunc() {
    while (repaint) {
        Display::sleep(REPAINT_INTERVAL);
        Display::clear();
        draw();
        Display::refresh();
    }
}

void Board::autoPaintFuncWrapper(void *data) {
    Board *b = static_cast<Board *>(data);
    b->autoPaintFunc();
}
