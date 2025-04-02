#include "Menu.h"
#include "Pawnshop.h"

int main() {

    Pawnshop pawnshop;

    Menu menu(pawnshop);
    menu.displayMenu();

    return 0;
}
