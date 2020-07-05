#include "Board.h"
#include <iostream>
#include <ctime>


Board::Board(int h, int w, GameMode m){
    if(h>50 || w>50 || h<1 || w<1){
        std::cerr << "Height or/and width value is too big or too small! Choose appropriate value between 1 to 50"
        << std::endl;
    }
    srand(time(NULL));
    height = h;
    width = w;
    mode = m;
    resetBoard();
    fillBoard(mode);
}

void Board::fillBoard(GameMode m) {
    countMinesToPut();
    int row = 0,col = 0;
    if(mode != DEBUG){
        for(int putBomb=0;putBomb<minesCount;++putBomb){
            row = rand()%height;
            col = rand()%width;
            if (board[row][col].hasMine) {
                putBomb--;
            }
            else {
                board[row][col].hasMine = true;
            }
        }
    }
    else{
        for(int putBomb=0;putBomb<width;++putBomb) {
            board[0][putBomb].hasMine = true;                    //horizontal
            board[putBomb+1][putBomb+1].hasMine = true;          //diagonal
            board[2*putBomb+2][0].hasMine = true;                //vertical
        }
    }
}

void Board::countMinesToPut() {
    if (mode == EASY) {
        minesCount = int(height * width * modeFactor.easyModeFactor);
    }
    if (mode == NORMAL) {
        minesCount = int(height * width * modeFactor.normalModeFactor);
    }
    if (mode == HARD) {
        minesCount = int(height * width * modeFactor.hardModeFactor);
    }
    if (mode == DEBUG) {
        // in DEBUG mode first row has bombs on each column
        // and every second row has bomb on its first column
        // and bomb is also on diagonal axis
        // note here: board[0][0] is count as "height" bomb
        for(int checkHere=0;checkHere<width;++checkHere) {
            if(isOnBoard(0,checkHere)) minesCount++;
            if(isOnBoard(checkHere+1,checkHere+1)) minesCount++;
            if(isOnBoard(2*checkHere+2,0)) minesCount++;
        }
    }
}

void Board::resetBoard() {
    for(int row=0;row<height;++row){
        for(int column=0;column<width;++column) {
            board[row][column].hasFlag = false;
            board[row][column].isRevealed = false;
            board[row][column].hasMine = false;
        }
    }
}

////////////////////////////////////
/////     SIMPLE GETTERS
int Board::getBoardWidth() const {
    return width;
}

int Board::getBoardHeight() const {
    return height;
}

int Board::getMineCount() const {
    return minesCount;
}

////////////////////////////////////
/////     BOOLEANS
bool Board::hasFlag(int row, int col) const {
    if (board[row][col].hasFlag)
        return true;
    else if (!isOnBoard(row,col))
        return false;
    else if (!board[row][col].hasFlag)
        return false;
    else if (isRevealed(row,col))
        return false;
    else
        return false;
}

bool Board::isRevealed(int row, int col) const {
    return (board[row][col].isRevealed);
}

bool Board::isOnBoard(int row, int col) const {
    return ((row>-1) && (row<getBoardHeight()) && (col>-1) && (col<getBoardWidth()));
}

bool Board::isFillable(int row, int col) const {
    return ((!board[row][col].hasMine) && (!board[row][col].hasFlag));
}

bool Board::isFirstMove() const {
    // return true if all fields are not revealed
    int fieldCheck = getBoardHeight()*getBoardWidth();
    int notRevealed = 0;
    for(int row=0;row<getBoardHeight();++row){
        for(int col=0;col<getBoardWidth();col++){
            if (!board[row][col].isRevealed)
                notRevealed++;
        }
    }
    return (fieldCheck == notRevealed);
}

////////////////////////////////////
/////     ACTIONS BY PLAYER
void Board::toggleFlag(int row, int col) {
    if (!isOnBoard(row,col)) {}
    else if (getGameState() == FINISHED_WIN || getGameState() == FINISHED_LOSS) {}
    else if (!board[row][col].isRevealed)
        board[row][col].hasFlag = !board[row][col].hasFlag;
    else if (board[row][col].isRevealed){}
}

void Board::revealField(int row, int col) {
    if (!isOnBoard(row,col)) {}
    else if (getGameState() == FINISHED_WIN || getGameState() == FINISHED_LOSS) {} // game is already finished
    else if (!board[row][col].isRevealed) {     // if it's everything OK with field
        // if its the first player action - move mine to another location, reveal field (not in DEBUG mode!)
        if (isFirstMove()) {                    // it means that game just started
            firstReveal(row, col);               // reveal field 3x3
            for(int x_row=-1;x_row<2;++x_row) {
                for (int y_col=-1;y_col<2;++y_col) {
                    if (countMinesAround(row+x_row,col+y_col) == 0)
                        floodFill(row+x_row,col+y_col);
                }
            }
        }
        else if (!board[row][col].hasMine) {
            board[row][col].isRevealed = true;
            if (countMinesAround(row, col) == 0)
                floodFill(row, col);
        }
        else if (board[row][col].hasMine) {
            board[row][col].isRevealed = true;
            state = FINISHED_LOSS;
        }
    }
}

////////////////////////////////////
/////     ACTIONS FOR TOGGLE/REVEAL
int Board::countMinesAround(int row, int col) const {
    int minesCountedAround=0;
    if (!board[row][col].isRevealed)
        return -1;
    else if (!isOnBoard(row,col))
        return -1;
    else if (row<0 || col<0)
        return -1;
    else {
        for(int x_row=-1;x_row<2;++x_row){
            for(int y_col=-1;y_col<2;++y_col){
                if (((row+x_row)<0) || ((col+y_col)<0)){}
                else if(board[row + x_row][col + y_col].hasMine)
                    minesCountedAround++;
            }
        }
    }
    return minesCountedAround;
}

void Board::firstReveal(int row, int col) {
    int countFirstRevealMines=0;
    for(int x_row=-1;x_row<2;++x_row) {
        for(int y_col=-1;y_col<2;++y_col) {
            if(isOnBoard(row+x_row,col+y_col)){
                if(board[row+x_row][col+y_col].hasMine)
                    countFirstRevealMines++;
                board[row+x_row][col+y_col].hasMine = false;
                board[row+x_row][col+y_col].isRevealed = true;
            }
        }
    }
    // relocate mines around revealed field
    for(int moveIt=0;moveIt<countFirstRevealMines;++moveIt) {
        int row_alt = rand()%height;
        int col_alt = rand()%width;
        if (board[row_alt][col_alt].hasMine)
            moveIt--;
        else {
            if(!board[row_alt][col_alt].isRevealed) {
                board[row_alt][col_alt].hasMine = true;
            }
        }
    }
}

void Board::floodFill(int row, int col) {
    // algorithm used to fill any free field around the revealed one
    // free means that field has no bombs as neighbours
    for(int x_row=-1;x_row<2;x_row++){
        for(int y_col=-1;y_col<2;y_col++){
            int temp_row = row+x_row;
            int temp_col = col+y_col;
            if (isOnBoard(temp_row,temp_col)){
                if(isFillable(temp_row,temp_col))
                    revealField(temp_row,temp_col);
            }
        }
    }
}

////////////////////////////////////
/////     COMPLEX GETTERS
GameState Board::getGameState() const {
    // WIN IF all mines were flagged and there are no flags on fields without mines, or
    // WIN IF all unrevealed fields have mines
    int rowHeight = getBoardHeight();
    int colWidth = getBoardWidth();
    int mines = getMineCount();
    int checkFields = ((rowHeight*colWidth)-mines);
    for (int row=0;row<height;++row) {
        for (int col=0;col<width;++col) {
            if (board[row][col].isRevealed && board[row][col].hasMine)
                return FINISHED_LOSS;
            else if(!board[row][col].hasMine && board[row][col].isRevealed)
                checkFields--;
        }
    }
    if(checkFields == 0)
        return FINISHED_WIN;
    else
        return RUNNING;
}

char Board::getFieldInfo(int row, int col) const {
    // used to show game in text mode in console
    if (!isOnBoard(row,col))    // if row or col is outside board
        return '#';
    else if (!board[row][col].isRevealed && board[row][col].hasFlag) // if the field is not revealed and has a flag
        return 'F';
    else if (!board[row][col].isRevealed && !board[row][col].hasFlag) // if the field is not revealed and does not have a flag
        return '_';
    else if (board[row][col].isRevealed && board[row][col].hasMine) // if the field is revealed and has mine
        return 'x';
    else if (board[row][col].isRevealed && countMinesAround(row,col) == 0) // if the field is revealed and has 0 mines around
        return ' ';
    else if (board[row][col].isRevealed && countMinesAround(row,col) != 0) { // if the field is revealed and has some mines around
        int chx = countMinesAround(row, col);
        return (chx+48);
    }
    return 0;
}

////////////////////////////////////
/////     DEBUG
void Board::debug_display() const {
    for(int row=0;row<height;++row){
        for(int col=0; col < width; ++col){
            if (board[row][col].hasMine)
                std::cout << "M";
            else
                std::cout << ".";
            if (board[row][col].isRevealed)
                std::cout << "o";
            else
                std::cout << ".";
            if (board[row][col].hasFlag)
                std::cout << "f  ";
            else
                std::cout << ".  ";
        }
        std::cout << std::endl;
    }
}

void Board::diagnostic_info() const {
    std::cout << "Height of the board: " << getBoardHeight() << std::endl;
    std::cout << "Width of the board: " << getBoardWidth() << std::endl;
    std::cout << "Mines on the board: " << getMineCount() << std::endl;
    std::cout << "Mode: " << mode << std::endl;
    std::cout << "State: " << getGameState() << std::endl;
}





