#include "ConsoleView.h"
#include <iostream>

ConsoleView::ConsoleView(Board &b) : board(b) {

}

void ConsoleView::display() {
    for(int row=0;row<board.getBoardHeight();++row){
        for(int col=0;col<board.getBoardWidth();++col){
            std::cout << board.getFieldInfo(row,col) << "     ";
        }
        std::cout << std::endl;
    }
}
