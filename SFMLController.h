#ifndef MINESWEEPER_SFMLCONTROLLER_H
#define MINESWEEPER_SFMLCONTROLLER_H

#include "Board.h"
#include "SFMLView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MsgBox.h"

class SFMLController {
    Board &board;
    SFMLView &view;
    MsgBox messageBox;
    // regular size of each cell on the board
    const int cell = 40;
    // small window icon
    sf::Image icon;
    sf::Sound sound;
    sf::SoundBuffer reveal_voice;
    sf::SoundBuffer toggle_voice;
    sf::SoundBuffer win;
    sf::SoundBuffer lost;
    void gameHandler(sf::RenderWindow &window, bool &toDraw);
    void setTitle(std::string &titleType);
public:
    SFMLController(Board &b, SFMLView &v);
    void play();
};


#endif //MINESWEEPER_SFMLCONTROLLER_H
