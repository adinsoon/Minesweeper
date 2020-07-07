#include "SFMLMenu.h"
#include <iostream>

SFMLMenu::SFMLMenu() {
    mainBar.loadFromFile("..\\icons\\mainBar.ico");
    lowBar.loadFromFile("..\\icons\\lower.ico");
    lowerBar.loadFromFile("..\\icons\\lowerBar.ico");
    sideBar.loadFromFile("..\\icons\\sideBar.ico");
    buttonA.loadFromFile("..\\icons\\buttonA.ico");
    buttonB.loadFromFile("..\\icons\\buttonB.ico");
    mainMode.loadFromFile("..\\icons\\mainMode.ico");
    sideMode.loadFromFile("..\\icons\\sideMode.ico");
    modeEasy.loadFromFile("..\\icons\\EASY.ico");
    modeNormal.loadFromFile("..\\icons\\NORMAL.ico");
    modeHard.loadFromFile("..\\icons\\HARD.ico");
    modeDebug.loadFromFile("..\\icons\\DEBUG.ico");
    icon.loadFromFile("..\\icons\\icon.png");

    menu.loadFromFile("..\\sounds\\menu.ogg");
}

void SFMLMenu::drawMenu() {
    constexpr int menu_height = 233;
    constexpr int menu_width = 358;
    bool changeScenery = false;     // MAIN MENU THEN CHANGE TO GAME MODE MENU
    bool closeWindow = false;

    sf::RenderWindow MenuWindow(sf::VideoMode(menu_width, menu_height), "Minesweeper");
    MenuWindow.setIcon(300, 300, icon.getPixelsPtr());
    while (MenuWindow.isOpen()) {
        sf::Event menuEvent{};
        while (MenuWindow.pollEvent(menuEvent)) {
            if (menuEvent.type == sf::Event::Closed) {
                MenuWindow.close();
                exit(0);
            } else if (!changeScenery) {
                ///////////////    MAIN MENU
                if (menuEvent.type == sf::Event::MouseButtonPressed) {
                    if (menuEvent.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(MenuWindow);
                        if (showButton[0].getGlobalBounds().contains(static_cast <sf::Vector2f>(mouse_pos))) {
                            sound.setBuffer(menu);
                            sound.play();
                            changeScenery = !changeScenery;
                        }
                    }
                }
            } else if (changeScenery) {
                ////////////     GAME MODES MENU
                if (menuEvent.type == sf::Event::MouseButtonPressed) {
                    if (menuEvent.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mouse_position = sf::Mouse::getPosition(MenuWindow);
                        if (showButton[2].getGlobalBounds().contains(static_cast <sf::Vector2f>(mouse_position))) {
                            height = 9;
                            width = 9;
                            mode = EASY;
                            closeWindow = true;
                        } else if (showButton[3].getGlobalBounds().contains(
                                static_cast <sf::Vector2f>(mouse_position))) {
                            height = 12;
                            width = 12;
                            mode = NORMAL;
                            closeWindow = true;
                        } else if (showButton[4].getGlobalBounds().contains(
                                static_cast <sf::Vector2f>(mouse_position))) {
                            height = 15;
                            width = 15;
                            mode = HARD;
                            closeWindow = true;
                        } else if (showButton[5].getGlobalBounds().contains(
                                static_cast <sf::Vector2f>(mouse_position))) {
                            height = 7;
                            width = 9;
                            mode = DEBUG;
                            closeWindow = true;
                        } else
                            closeWindow = false;
                        if (closeWindow) {
                            sound.setBuffer(menu);
                            sound.play();
                            MenuWindow.close();
                        }
                    }
                }
            }
        }
        //////////    MAIN MENU
        formatMainMenu(MenuWindow);
        /////////     DRAW GAME MODES
        if(changeScenery) {
            formatGameModes(MenuWindow);
        }
        MenuWindow.display();
    }
}


    //////     GETTERS SECTION
int SFMLMenu::getGameHeight() const {
    return height;
}

int SFMLMenu::getGameWidth() const {
    return width;
}

GameMode SFMLMenu::getGameMode() const {
    return mode;
}



void SFMLMenu::formatMainMenu(sf::RenderWindow &MenuWindow) {
    /////////////     MAIN MENU
    showBar[0].setTexture(mainBar);
    MenuWindow.clear(sf::Color::Blue);
    MenuWindow.draw(showBar[0]);
    //////////////////////////////////////////////
    showButton[0].setScale(0.35, 0.35);
    showButton[0].setPosition(120,174);
    showButton[0].setTexture(buttonA);
    MenuWindow.draw(showButton[0]);
    //////////////////////////////////////////////
    showBar[1].setTexture(lowerBar);
    showBar[1].setScale(0.35,0.35);
    showBar[1].setPosition(0,204);
    MenuWindow.draw(showBar[1]);
    //////////////////////////////////////////////
    showBar[2].setTexture(sideBar);
    showBar[2].setScale(0.35,0.35);
    showBar[2].setPosition(0,174);
    MenuWindow.draw(showBar[2]);
    showBar[2].setPosition(240,174);
    MenuWindow.draw(showBar[2]);

    //////     INTERACTIVE MAIN BUTTON
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(MenuWindow);
    if(showButton[0].getGlobalBounds().contains(static_cast <sf::Vector2f>(mouse_pos))){
        showButton[1].setTexture(buttonB);
        showButton[1].setScale(0.35,0.35);
        showButton[1].setPosition(120,174);
        MenuWindow.draw(showButton[1]);
    }
}

void SFMLMenu::formatGameModes(sf::RenderWindow &MenuWindow) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(MenuWindow);
    MenuWindow.clear(sf::Color::Black);
    ///////////     UPPER PART
    showBar[3].setTexture(mainMode);
    showBar[3].setScale(0.35, 0.35);
    MenuWindow.draw(showBar[3]);
    showBar[4].setTexture(sideMode);
    showBar[4].setScale(0.35, 0.34);
    showBar[4].setPosition(0, 89);
    MenuWindow.draw(showBar[4]);
    showBar[4].setPosition(271, 89);
    MenuWindow.draw(showBar[4]);

    ////////     EASY BUTTON
    showButton[2].setTexture(modeEasy);
    showButton[2].setTextureRect(sf::IntRect(0, 0, 512, 85));
    showButton[2].setScale(0.353, 0.35);
    showButton[2].setPosition(90, 89);
    MenuWindow.draw(showButton[2]);
    if (showButton[2].getGlobalBounds().contains(static_cast <sf::Vector2f>(mouse_pos))) {
        showButton[2].setTextureRect(sf::IntRect(0, 86, 512, 170));
        MenuWindow.draw(showButton[2]);
    }

    ///////     NORMAL BUTTON
    showButton[3].setTexture(modeNormal);
    showButton[3].setTextureRect(sf::IntRect(0, 5, 512, 85));
    showButton[3].setScale(0.353, 0.35);
    showButton[3].setPosition(90, 119);
    MenuWindow.draw(showButton[3]);
    if (showButton[3].getGlobalBounds().contains(static_cast <sf::Vector2f>(mouse_pos))) {
        showButton[3].setTextureRect(sf::IntRect(0, 86, 512, 170));
        MenuWindow.draw(showButton[3]);
    }

    /////////     HARD BUTTON
    showButton[4].setTexture(modeHard);
    showButton[4].setTextureRect(sf::IntRect(0, 0, 512, 85));
    showButton[4].setScale(0.353, 0.345);
    showButton[4].setPosition(90, 147);
    MenuWindow.draw(showButton[4]);
    if (showButton[4].getGlobalBounds().contains(static_cast <sf::Vector2f>(mouse_pos))) {
        showButton[4].setTextureRect(sf::IntRect(0, 86, 512, 170));
        MenuWindow.draw(showButton[4]);
    }

    //////////     DEBUG BUTTON
    showButton[5].setTexture(modeDebug);
    showButton[5].setTextureRect(sf::IntRect(0, 2, 512, 85));
    showButton[5].setScale(0.353, 0.353);
    showButton[5].setPosition(90, 176);
    MenuWindow.draw(showButton[5]);
    if (showButton[5].getGlobalBounds().contains(static_cast <sf::Vector2f>(mouse_pos))) {
        showButton[5].setTextureRect(sf::IntRect(0, 86, 512, 170));
        MenuWindow.draw(showButton[5]);
    }

    /////////     LOW BAR
    showButton[6].setTexture(lowBar);
    showButton[6].setScale(0.353, 0.34);
    showButton[6].setPosition(90, 205);
    MenuWindow.draw(showButton[6]);
}

