#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

//from curses.h
#define ATTR_REVERSE        0x00200000

#define WHITE               0x00
#define RED                 0x01
#define GREEN               0x02

#define KEY_RETURN          0x0a
#define KEY_ESC             0x1b
#define KEY_BACK            0x08

#define KEY_ARROW_UP        0x03
#define KEY_ARROW_DOWN      0x02
#define KEY_ARROW_LEFT      0x04
#define KEY_ARROW_RIGHT     0x05

#define DISPLAY_BUFFER_SIZE 1024

class Display {
public:
    static void init();
    static void shutdown();

    static void draw(int row, int column, const char *fmt, ...);
    static void draw(char c, int row, int column);
    static void clear();
    static void refresh();

    static char getChar();

    static void pushColor(int color);
    static void popColor(int color);

    static void pushAttribute(int a);
    static void popAttribute(int a);

    static void sleep(int time); //move this??

private:
    static bool colorSupport;
};


#endif //SNAKE_DISPLAY_H
