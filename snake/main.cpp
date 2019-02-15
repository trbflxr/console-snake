#include "display.h"
#include "game.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    Display::init();

    Game game(20);

    Menu menu(&game);
    menu.showMenu();

    Display::shutdown();

    return 0;
}
