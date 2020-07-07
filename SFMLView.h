#ifndef MINESWEEPER_SFMLVIEW_H
#define MINESWEEPER_SFMLVIEW_H

#include "Board.h"
#include <SFML/Graphics.hpp>

class SFMLView {
    Board &board;
    // index means number of the bombs in the neighbourhood (from 0 to 8) and the last one is if field is unrevealed
    sf::Texture field[10];
    sf::Texture flag;
    sf::Texture bomb;
    sf::Sprite showIt;
    // regular size of each cell on the board
    const int cell = 40;
public:
    explicit SFMLView(Board &b);
    void drawBoard(sf::RenderWindow &win);
};


#endif //MINESWEEPER_SFMLVIEW_H
