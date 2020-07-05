#include <iostream>
#include "Board.h"

int main(){
    Board board(9, 7, DEBUG);
    board.debug_display();
    board.diagnostic_info();
    return 0;
}
