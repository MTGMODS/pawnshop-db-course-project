#ifndef MENU_H
#define MENU_H

#include "Pawnshop.h"

class Menu {
private:
    Pawnshop& pawnshop;
    void userGuide() const;
public:
    Menu(Pawnshop& p);
    void displayMenu();
};

#endif
