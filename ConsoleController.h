#ifndef MINESWEEPER_CONSOLECONTROLLER_H
#define MINESWEEPER_CONSOLECONTROLLER_H

#include "Board.h"
#include "ConsoleView.h"

class ConsoleController {
    Board &board;
    ConsoleView &view;
public:
    ConsoleController(Board &b, ConsoleView &v);
    void play();
};


#endif //MINESWEEPER_CONSOLECONTROLLER_H
