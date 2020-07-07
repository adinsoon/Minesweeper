#ifndef MINESWEEPER_CONSOLEVIEW_H
#define MINESWEEPER_CONSOLEVIEW_H

#include "Board.h"

class ConsoleView {
    Board &board;
public:
    explicit ConsoleView(Board &b);
    void display();
};


#endif //MINESWEEPER_CONSOLEVIEW_H
