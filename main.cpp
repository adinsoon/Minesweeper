#include <iostream>
#include "Board.h"
#include "ConsoleView.h"
#include "ConsoleController.h"
#include "SFMLView.h"
#include "SFMLController.h"
#include "SFMLMenu.h"

int main(){
    SFMLMenu menu;
    menu.drawMenu();
    Board board(menu.getGameHeight(), menu.getGameWidth(), menu.getGameMode());
    SFMLView view(board);
    SFMLController ctrl(board,view);
    ctrl.play();

    return 0;
}
