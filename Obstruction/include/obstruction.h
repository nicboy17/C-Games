#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

//When user enters character the corresponding happens to the cursor
#define UP	    'w'
#define DOWN	's'
#define LEFT    'a'
#define RIGHT   'd'

typedef struct record
{
    char * name;
    int win;
    int lose;
}record;

void ncurses();
void drawBoarder();           //Draws the Boarder of the game
void clearLine(int x, int y); //Clears lines
void fill(int x, int y, int row, int coloumn);      //fills in the board from players moves
void drawDots(int row, int coloumn);              //Draws the dots to be selected
int checkGame(int row, int coloumn);              //Checks the game to see if it is over
void play(record * player1, record * player2, int x, int row, int coloumn);
void setup(record * player1, record * player2, int * x, int * row, int * coloumn);
void playAgain(int * t, int * row, int * coloumn);
void computer(int * y, int * z, int row, int coloumn);
void text (record * player1, record * player2, int row, int coloumn);
void read (record * player1, record * player2);
void save (record * player1, record * player2);
