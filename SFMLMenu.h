#ifndef MINESWEEPER_SFMLMENU_H
#define MINESWEEPER_SFMLMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Board.h"
#include "SFMLView.h"

class SFMLMenu {
    sf::Texture mainBar;
    sf::Texture lowBar;
    sf::Texture lowerBar;
    sf::Texture sideBar;
    sf::Texture buttonA;
    sf::Texture buttonB;
    sf::Texture mainMode;
    sf::Texture sideMode;
    sf::Texture modeEasy;
    sf::Texture modeNormal;
    sf::Texture modeHard;
    sf::Texture modeDebug;
    sf::Image icon;
    sf::Sprite showBar[10];
    sf::Sprite showButton[10];
    sf::SoundBuffer menu;
    sf::Sound sound;
    int height;
    int width;
    GameMode mode;
    void formatMainMenu(sf::RenderWindow &MenuWindow);
    void formatGameModes(sf::RenderWindow &MenuWindow);
public:
    SFMLMenu();
    void drawMenu();
    int getGameHeight() const;
    int getGameWidth() const;
    GameMode getGameMode() const;
};


#endif //MINESWEEPER_SFMLMENU_H
