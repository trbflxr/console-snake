#include "menu.h"
#include "display.h"
#include "game.h"


Menu::Menu(Game *game)
    : game(game),
      selected(0) { }

void Menu::showMenu() {
    int key = 0;
    Display::clear();

    while (key != KEY_RETURN) {
        Display::draw(3, 3, "SNAKE GAME");
        Display::draw(4, 3, "==================");

        drawButton(5, 3, 0, "START");
        drawButton(6, 3, 1, "ABOUT");
        drawButton(7, 3, 2, "EXIT");

        key = Display::getChar();
        if (key == KEY_ARROW_UP) {
            selected--;
        } else if (key == KEY_ARROW_DOWN) {
            selected++;
        } else if (key == KEY_ESC) {
            return;
        }
        if (selected == 3) {
            selected = 0;
        }
        if (selected == -1) {
            selected = 2;
        }
    }

    action();
}

void Menu::drawButton(int row, int column, int index, const char *text) const {
    if (selected == index) {
        Display::pushColor(RED);
    }
    Display::draw(row, column, text);
    if (selected == index) {
        Display::popColor(RED);
    }
}

void Menu::action() {
    if (selected == 0) {
        game->start();
        score();
    } else if (selected == 1) {
        about();
    } else {
        //exit
    }
}

void Menu::about() {
    int key = 0;
    Display::clear();

    while (key != KEY_ESC && key != KEY_BACK) {
        Display::draw(3, 3, "SNAKE GAME");
        Display::draw(4, 3, "==================");
        Display::pushColor(RED);
        Display::draw(5, 3, "Tut doljno bit opesaniye igri...");
        Display::draw(6, 3, "No ego net xD");
        Display::popColor(RED);
        Display::draw(7, 3, "==================");
        Display::draw(8, 3, "ESC \\ BACKSPACE - BACK");
        key = Display::getChar();
    }

    showMenu();
}

void Menu::score() {
    int key = 0;
    Display::clear();

    while (key != KEY_ESC && key != KEY_BACK && key != KEY_RETURN) {
        Display::draw(3, 3, "SNAKE GAME");
        Display::draw(4, 3, "==================");
        Display::draw(5, 3, "SCORE: %i", game->getScore());
        Display::draw(6, 3, "==================");
        Display::draw(7, 3, "ESC \\ BACKSPACE - BACK");
        Display::draw(8, 3, "ENTER - RESTART");
        key = Display::getChar();
    }

    if (key == KEY_RETURN) {
        selected = 0;
        action();
        return;
    }

    showMenu();
}
