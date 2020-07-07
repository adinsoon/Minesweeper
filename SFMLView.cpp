#include "SFMLView.h"

SFMLView::SFMLView(Board &b) : board(b){
    field[0].loadFromFile("..\\icons\\field0.ico");
    field[1].loadFromFile("..\\icons\\field1.ico");
    field[2].loadFromFile("..\\icons\\field2.ico");
    field[3].loadFromFile("..\\icons\\field3.ico");
    field[4].loadFromFile("..\\icons\\field4.ico");
    field[5].loadFromFile("..\\icons\\field5.ico");
    field[6].loadFromFile("..\\icons\\field6.ico");
    field[7].loadFromFile("..\\icons\\field7.ico");
    field[8].loadFromFile("..\\icons\\field8.ico");
    field[9].loadFromFile("..\\icons\\pole.ico");
    flag.loadFromFile("..\\icons\\flaga.ico");
    bomb.loadFromFile("..\\icons\\mina.ico");
}

void SFMLView::drawBoard(sf::RenderWindow &win) {
    for(int row=0;row<board.getBoardHeight();++row){
        for(int col=0;col<board.getBoardWidth();++col){
            showIt.setScale(0.3,0.3);
            showIt.setPosition(0+cell*col,0+cell*row);
            if(board.getFieldInfo(row,col) == '_'){
                showIt.setTexture(field[9]);
            }
            else if(board.getFieldInfo(row,col) == 'F'){
                showIt.setTexture(flag);
            }
            else if(board.getFieldInfo(row,col) == 'x'){
                showIt.setTexture(bomb);
            }
            else if(board.getFieldInfo(row,col) == ' '){
                showIt.setTexture(field[0]);
            }
            else if(board.getFieldInfo(row,col) == '1'){
                showIt.setTexture(field[1]);
            }
            else if(board.getFieldInfo(row,col) == '2'){
                showIt.setTexture(field[2]);
            }
            else if(board.getFieldInfo(row,col) == '3'){
                showIt.setTexture(field[3]);
            }
            else if(board.getFieldInfo(row,col) == '4'){
                showIt.setTexture(field[4]);
            }
            else if(board.getFieldInfo(row,col) == '5'){
                showIt.setTexture(field[5]);
            }
            else if(board.getFieldInfo(row,col) == '6'){
                showIt.setTexture(field[6]);
            }
            else if(board.getFieldInfo(row,col) == '7'){
                showIt.setTexture(field[7]);
            }
            else if(board.getFieldInfo(row,col) == '8'){
                showIt.setTexture(field[8]);
            }
            win.draw(showIt);
        }
    }
}
