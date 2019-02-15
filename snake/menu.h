#ifndef SNAKE_MENU_H
#define SNAKE_MENU_H


class Game;

class Menu final {
public:
    explicit Menu(Game *game);

    void showMenu();

private:
    void drawButton(int row, int column, int index, const char *text) const;

    void action();

    void about();
    void score();

private:
    Game *game;

    int selected;
};


#endif //SNAKE_MENU_H
