#include "ConsoleController.h"
#include <iostream>

ConsoleController::ConsoleController(Board &b, ConsoleView &v): board(b), view(v) {

}

void ConsoleController::play() {
    int option,row_cord,col_cord;
    do{
        view.display();
        std::cout << "Choose the action from the list below [1/2]: " << std::endl;
        std::cout << "1. Reveal the field [Type '1'] " << std::endl;
        std::cout << "2. Toggle on/off the flag [Type '2'] " << std::endl;
        std::cin >> option;
        do{
            std::cout << "Enter the number of row from 1 to " << board.getBoardHeight() << ": " << std::endl;
            std::cin >> row_cord;
        } while(row_cord > board.getBoardHeight() || row_cord < 0);
        do{
            std::cout << "Enter the number of column from 1 to " << board.getBoardWidth() << ": " << std::endl;
            std::cin >> col_cord;
        } while(col_cord > board.getBoardWidth() || col_cord < 0);
        if(option == 1){
            board.revealField(row_cord,col_cord);
        }
        else if(option == 2){
            board.toggleFlag(row_cord,col_cord);
        }
        else{
            std::cout << "Invalid action. Please try again. " << std::endl;
        }
    } while (board.getGameState() == RUNNING);

    if(board.getGameState() == FINISHED_WIN){
        std::cout << "Congratulations. You won! " << std::endl;
    }
    else if(board.getGameState() == FINISHED_LOSS){
        std::cout << "You lost. " << std::endl;
    }
}
