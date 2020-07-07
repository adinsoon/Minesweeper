#ifndef MINESWEEPER_MSGBOX_H
#define MINESWEEPER_MSGBOX_H

#include <SFML/Graphics.hpp>
#include "Board.h"

class MsgBox {
    sf::Image icon;
    sf::Font myFont;
    sf::Text info[3];
    sf::Texture button0;
    sf::Texture button1;
    sf::Texture buttonPLAY;
    sf::Sprite buttons[3];
    void drawIt(int scenario, sf::RenderWindow &window);
    void format();
public:
    MsgBox();
    void drawMsg(int scenario);

};


#endif //MINESWEEPER_MSGBOX_H
