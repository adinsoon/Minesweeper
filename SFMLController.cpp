#include "SFMLController.h"
#include <string>

SFMLController::SFMLController(Board &b, SFMLView &v) : board(b), view(v) {
    // GameWindow.setVerticalSyncEnabled(true); //or
    // GameWindow.setFramerateLimit(30);
    icon.loadFromFile("..\\icons\\icon.png");
    reveal_voice.loadFromFile("..\\sounds\\revealfield.ogg");
    toggle_voice.loadFromFile("..\\sounds\\toggleflag.ogg");
    win.loadFromFile("..\\sounds\\win.ogg");
    lost.loadFromFile("..\\sounds\\lost.ogg");
}

void SFMLController::play() {
    std::string titleType;
    int scr_height = board.getBoardHeight()*cell;
    int scr_width = board.getBoardWidth()*cell;
    bool shouldDraw = true;

    setTitle(titleType);

    sf::RenderWindow GameWindow(sf::VideoMode(scr_width,scr_height), titleType);
    GameWindow.setIcon(300,300,icon.getPixelsPtr());

    while(GameWindow.isOpen()){
        sf::Event e;
        while(GameWindow.pollEvent(e)){
            if((e.type == sf::Event::Closed) ||
                (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)){
                if(board.getGameState() == RUNNING) {
                    messageBox.drawMsg(0);
                }
                else if(board.getGameState() == FINISHED_WIN ||
                    board.getGameState() == FINISHED_LOSS){
                    GameWindow.close();
                }
            }
            else if(e.type == sf::Event::MouseButtonPressed){
                int width, height;
                height = e.mouseButton.x / cell;
                width = e.mouseButton.y / cell;
                if(e.mouseButton.button == sf::Mouse::Left){
                    board.revealField(width,height);
                    sound.setBuffer(reveal_voice);
                    sound.play();
                }
                else if(e.mouseButton.button == sf::Mouse::Right){
                    board.toggleFlag(width,height);
                    sound.setBuffer(toggle_voice);
                    sound.play();
                }
            }
        }
        GameWindow.clear(sf::Color::Black);
        view.drawBoard(GameWindow);
        GameWindow.display();
        gameHandler(GameWindow, shouldDraw);
    }
}

void SFMLController::gameHandler(sf::RenderWindow &window, bool &toDraw) {
    if(board.getGameState() == FINISHED_WIN){
        while(toDraw) {
            window.close();
            sound.setBuffer(win);
            sound.play();
            messageBox.drawMsg(1);
            toDraw = false;
        }
    }
    else if(board.getGameState() == FINISHED_LOSS){
        while(toDraw){
            window.close();
            sound.setBuffer(lost);
            sound.play();
            messageBox.drawMsg(2);
            toDraw = false;
        }
    }
}

void SFMLController::setTitle(std::string &titleType) {
    if(board.getGameMode() == EASY)
        titleType = "Minesweeper: EASY ";
    else if(board.getGameMode() == NORMAL)
        titleType = "Minesweeper: NORMAL ";
    else if(board.getGameMode() == HARD)
        titleType = "Minesweeper: HARD ";
    else if(board.getGameMode() == DEBUG)
        titleType = "Minesweeper: DEBUG ";

    titleType = titleType + std::to_string(board.getBoardHeight()) + "x"
                 + std::to_string(board.getBoardWidth()) + "  " + std::to_string(board.getMineCount()) + "mines";
}
