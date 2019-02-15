#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <curses.h>
#include "display.h"


bool Display::colorSupport = false;

void Display::init() {
    //init console "screen"
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();

    if (has_colors()) {
        colorSupport = true;
    }

    //add some colors
    if (colorSupport) {
        start_color();

		init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
        init_pair(RED, COLOR_RED, COLOR_BLACK);
        init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    }
}

void Display::shutdown() {
    endwin();
}

void Display::draw(int row, int column, const char *fmt, ...) {
    char *args;
    char str[DISPLAY_BUFFER_SIZE];

    va_start(args, fmt);
    if (_vsnprintf_s(str, sizeof(str), _TRUNCATE, fmt, args) == -1) {
        str[sizeof(str) - 1] = '\0';
    }
    va_end(args);

    mvaddstr(row, column, str);
}

void Display::draw(char c, int row, int column) {
    mvaddch(row, column, c);
}

void Display::clear() {
    ::clear();
}

void Display::refresh() {
    ::refresh();
}

char Display::getChar() {
    return getch();
}

void Display::pushColor(int color) {
    if (colorSupport) {
        attron(COLOR_PAIR(color));
    }
}

void Display::popColor(int color) {
    if (colorSupport) {
        attroff(COLOR_PAIR(color));
    }
}

void Display::pushAttribute(int a) {
    attron(a);
}

void Display::popAttribute(int a) {
    attroff(a);
}

void Display::sleep(int time) {
    Sleep(time);
}
