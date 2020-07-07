#include "MsgBox.h"
#include <string>

MsgBox::MsgBox() {
    icon.loadFromFile("..\\icons\\icon.png");
    myFont.loadFromFile("..\\font\\arial.ttf");

    button0.loadFromFile("..\\icons\\yes.ico");
    button1.loadFromFile("..\\icons\\no.ico");
    buttonPLAY.loadFromFile("..\\icons\\playagain.ico");

    format();
}

void MsgBox::drawMsg(int scenario) {
    constexpr int msg_height = 80;
    constexpr int msg_width = 300;

    std::string msgType;
    if (scenario == 0)
        msgType = "Exit";
    else if (scenario == 1)
        msgType = "Success!";
    else if (scenario == 2)
        msgType = "Fail!";

    sf::RenderWindow msg(sf::VideoMode(msg_width, msg_height), msgType);
    msg.setIcon(300,300,icon.getPixelsPtr());
    while (msg.isOpen()) {
        sf::Event ev{};
        while (msg.pollEvent(ev)) {
            if ((ev.type == sf::Event::Closed) ||
                (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)) {
                if (scenario != 0)   // IF GAME IS FINISHED
                    msg.close();
            } else if (ev.type == sf::Event::MouseButtonPressed) {
                if (ev.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(msg);
                    if (scenario == 0) {
                        ////////     CLICK YES
                        if (buttons[0].getGlobalBounds().contains(static_cast <sf::Vector2f>(mouse_pos))) {
                            msg.close();
                            exit(0);
                        }
                            ////////     CLICK NO
                        else if (buttons[1].getGlobalBounds().contains(static_cast <sf::Vector2f>(mouse_pos))) {
                            msg.close();
                        }
                    }
                    if (scenario == 1 || scenario == 2) {
                        /////////     CLICK OK     ///////
                        if (buttons[2].getGlobalBounds().contains(static_cast <sf::Vector2f>(mouse_pos))) {
                            msg.close();
                        }
                    }
                }
            }
        }
        msg.clear(sf::Color(192,192,192));
        drawIt(scenario,msg);
        msg.display();
    }
}

void MsgBox::format() {
    info[0].setString("Are you sure you want to quit?");
    info[1].setString("Congratulations! You won.");
    info[2].setString("Unlucky! You lost.");
}

void MsgBox::drawIt(int scenario, sf::RenderWindow &window) {
    if(scenario == 0){
        /////////     ARE YOU SURE YOU WANT TO QUIT?
        info[scenario].setFont(myFont);
        info[scenario].setFillColor(sf::Color::Black);
        info[scenario].setCharacterSize(20);
        info[scenario].setPosition(10,10);
        //////////////////     YES BUTTON
        buttons[0].setTexture(button0);
        buttons[0].setScale(0.35,0.35);
        buttons[0].setPosition(30,50);
        window.draw(buttons[0]);
        /////////////////     NO BUTTON
        buttons[1].setTexture(button1);
        buttons[1].setScale(0.35,0.35);
        buttons[1].setPosition(200,50);
        window.draw(buttons[1]);
    }
    if(scenario == 1 || scenario ==2){
        ////////     WIN OR LOSS
        info[scenario].setFont(myFont);
        info[scenario].setFillColor(sf::Color::Black);
        info[scenario].setCharacterSize(20);
        if(scenario == 1)
            info[scenario].setPosition(30,10);
        else
            info[scenario].setPosition(70,10);
        /////////     OK BUTTON
        buttons[2].setTexture(buttonPLAY);
        buttons[2].setScale(0.35,0.35);
        buttons[2].setPosition(0,50);
        window.draw(buttons[2]);
    }
    window.draw(info[scenario]);
}
