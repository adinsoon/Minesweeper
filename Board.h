#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

// quick set
enum GameMode {DEBUG, EASY, NORMAL, HARD};
enum GameState {RUNNING, FINISHED_WIN, FINISHED_LOSS};

// each field represents one or more of these
struct Field {
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

// each mode except debug has its own mines factor
struct ModeFactor {
    double easyModeFactor = 0.1;
    double normalModeFactor = 0.2;
    double hardModeFactor = 0.3;
};

class Board {
    // allocating 50x50 board
    Field board[50][50];
    ModeFactor modeFactor;
    int height=0;
    int width=0;
    int minesCount=0;
    GameMode mode;
    GameState state;
    void countMinesToPut();
    // put bombs on board according to selected mode
    void fillBoard(GameMode &m);
    // prepare clean board ready to fill
    void resetBoard();
public:
    // generate a width*height sized board with the number of mines that depend on GameMode:
    // - EASY   - 10% of game fields with mines (random)
    // - NORMAL - 20% of game fields with mines (random)
    // - HARD   - 30% of game fields with mines (random)
    // - DEBUG  - predefined mine layout
    Board(int h, int w, GameMode m);

    // simple getters - return appropriate values (passed to or calculated in constructor)
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    GameMode getGameMode() const;

    // return true if the field at (row,col) position was marked with flag
    // return false if any of the following is true:
    // - row or col is outside board
    // - there is no flag on the field
    // - field was already revealed
    bool hasFlag(int row, int col) const;

    // return true if the field was revealed
    bool isRevealed(int row, int col) const;

    // return true if the field is on board
    bool isOnBoard(int row, int col) const;

    // return true if countMines(int row, int col) for this field equals 0
    bool isFillable(int row,int col) const;

    // return true if its the first player action
    bool isFirstMove()const;

    // count mines around (x,y) position
    // if the field at (x,y) was not revealed - return -1
    // if either x or y is outside board      - return -1
    // otherwise - return mine count around this field
    // Examples for DEBUG layout (assuming the field is already revealed)
    // - countMines(0,1) should return 4
    // - countMines(9,2) should return 0
    // - countMines(1,2) should return 3
    // - countMines(7,6) should return 1
    int countMinesAround(int row, int col) const; // including [x][y] field

    // if the field at (x,y) was not revealed - change flag status for this field
    // Do nothing if any of the following is true
    // - field was already revealed
    // - either x or y is outside board
    // - game is already finished
    void toggleFlag(int row, int col);

    // try to reveal the field at (row,col)
    // Do nothing if any of the following is true
    // - field was already revealed
    // - either row or col is outside board
    // - game is already finished
    // - there is a flag on the field
    //
    // If the field was not revealed and there is no mine on it - reveal it
    // If the field was not revealed and there is a mine on it:
    // - if its the first player action - move mine to another location, reveal field (not in DEBUG mode!)
    void revealField(int row, int col);

    // - if its the first player action - move mine to another location, reveal field 3x3 (not in DEBUG mode!)
    void firstReveal(int row, int col);

    // reveal another fields around if their mines counted equals 0
    void floodFill(int row, int col);

    // return current game state:
    // - FINISHED_LOSS - if the player revealed field with mine
    // - FINISHED_WIN - if the player won the game:
    // --- all mines were flagged and there are no flags on fields without mines, or
    // --- all unrevealed fields have mines
    // - RUNNING - if the game is not yet finished
    GameState getGameState() const;

    // convenience function - returns useful information about field in one function call
    // if col or row is outside board                         - return '#' character
    // if the field is not revealed and has a flag            - return 'F' character
    // if the field is not revealed and does not have a flag  - return '_' (underscore) character
    // if the field is revealed and has mine                  - return 'col' character
    // if the field is revealed and has 0 mines around        - return ' ' (space) character
    // if the field is revealed and has some mines around     - return '1' ... '8' (number of mines as a digit)
    char getFieldInfo(int row, int col) const;

    void debug_display() const;
    void diagnostic_info() const;
};


#endif //MINESWEEPER_BOARD_H
