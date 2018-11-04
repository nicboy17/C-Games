/**************************************************************************
 Student Name: Nick Major                Student Number: 0879292
 Date: 01/16/14                          Course Name: cis2500
 
 I have exclusive control over this submission via my password.
 By including this statement in this header comment, I certify that:
      1) I have read and understood the University policy on academic integrity;
      2) I have completed the Computing with Integrity Tutorial on Moodle; and
      3) I have achieved at least 80% in the Computing with Integrity Self Test.
 I assert that this work is my own. I have appropriately acknowledged any and all material
 (data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
 Furthermore, I certify that this assignment was prepared by me specifically for this course.
 ****************************************************************************/

#include "obstruction.h"

int main()
{
    struct record * player1 = malloc(sizeof(struct record));
    player1->name = malloc(sizeof(char)*20);
    player1->win = 0;
    player1->lose = 0;
    
    struct record * player2 = malloc(sizeof(struct record));
    player2->name = malloc(sizeof(char)*20);
    player2->win = 0;
    player2->lose = 0;

    int x = 0;
    int row = 0;
    int coloumn = 0;
    
    ncurses ();
    setup(player1, player2, &x, &row, &coloumn);
    drawDots (row, coloumn);
    drawBoarder (row, coloumn);
    play(player1, player2, x, row, coloumn);
    
    refresh();
    endwin ();
    
    free(player1->name);
    free(player2->name);
    return 0;
}

void ncurses()
{
    //ncurses initialization
    initscr ();
    cbreak ();
    noecho ();
    start_color ();
    
    //Color Pairs
    init_pair (1, COLOR_GREEN, COLOR_BLACK);
    init_pair (2, COLOR_BLUE, COLOR_BLACK);
    init_pair (3, COLOR_RED, COLOR_BLACK);
    init_pair (4, COLOR_GREEN, COLOR_GREEN);
    init_pair (5, COLOR_BLACK, COLOR_BLACK);
    init_pair (6, COLOR_YELLOW, COLOR_BLACK);
}

void play (record * player1, record * player2, int x, int row, int coloumn)
{
    int game;
    int play;
    int xpos;
    int ypos;
    int turn;
    int y;
    int z;
    char userInput;
    
    xpos = 0;
    ypos = 0;
    game = 0;
    turn = 1;
    play = 1;
    
    read (player1, player2);
    
    text (player1, player2, row, coloumn);
    attron (COLOR_PAIR (2));
    mvwprintw (stdscr, 5, (coloumn*5) + coloumn + 12, "It is %s's turn", player1->name);
    attroff (COLOR_PAIR(2));
    
    move(4,7);
    
    //gets the direction from user keyboard
    userInput = getch ();
    
    while (userInput != 'q' && play == 1)
    {
        //gets position of the cursor
        getyx (stdscr, ypos, xpos);
        
        text (player1, player2, row, coloumn);
        
        //Depending on the key entered moves the cursor
        switch (userInput)
        {
            case UP:
                if (ypos - 4 >= 3)//These are the contstraints for the boards
                {
                    ypos = ypos - 4;
                    clearLine (row*3 + row + 4, 0);
                }
                break;
                
            case DOWN:
                if (ypos + 4 <= row*3 + row + 1)
                {
                    ypos = ypos + 4;
                    clearLine (row*3 + row + 4, 0);
                }
                break;
                
            case RIGHT:
                if (xpos + 6 <= coloumn*5 + coloumn + 3)
                {
                    xpos = xpos + 6;
                    clearLine (row*3 + row + 4, 0);
                }
                break;
                
            case LEFT:
                if (xpos - 6 >= 5)
                {
                    xpos = xpos - 6;
                    clearLine (row*3 + row + 4, 0);
                }
                break;
            case 'x':
            {
                if (mvinch(ypos, xpos) == '.')
                {
                    if (x == 0)
                    {
                        //fills in per color for each user turn
                        if (turn == 1)
                        {
                            attron (COLOR_PAIR (2));
                            fill (xpos, ypos, row, coloumn);
                            attroff (COLOR_PAIR (2));
                            attron (COLOR_PAIR (3));
                            mvwprintw (stdscr, 5, (coloumn*5) + coloumn + 12, "It is %s's turn", player2->name);
                            attroff (COLOR_PAIR (3));
                            refresh ();
                            turn = 2;
                        }
                        else if (turn == 2)
                        {
                            attron (COLOR_PAIR (3));
                            fill (xpos, ypos, row, coloumn);
                            attroff (COLOR_PAIR (3));
                            attron (COLOR_PAIR (2));
                            mvwprintw (stdscr, 5, (coloumn*5) + coloumn + 12, "It is %s's turn", player1->name);
                            attroff (COLOR_PAIR(2));
                            refresh ();
                            turn = 1;
                        }
                        x = 0;
                    }
                    else if (x == 1)
                    {
                        if (turn == 1)
                        {
                            clearLine (5, (coloumn*5) + coloumn + 12);
                            attron (COLOR_PAIR (2));
                            fill (xpos, ypos, row, coloumn);
                            attroff (COLOR_PAIR (2));
                            turn = 2;
                            game = checkGame(row, coloumn);
                            if (turn == 2 && game == 0)
                            {
                                attron (COLOR_PAIR (3));
                                computer(&y, &z, row, coloumn);
                                fill(z,y,row,coloumn);
                                attroff (COLOR_PAIR (3));
                                attron (COLOR_PAIR (2));
                                mvwprintw (stdscr, 5, (coloumn*5) + coloumn + 12, "It is %s's turn", player1->name);
                                attroff (COLOR_PAIR(2));
                                turn = 1;
                            }
                            x = 1;
                            refresh ();
                        }
                    }
                }
            }
            break;
            
            default:
                mvwprintw (stdscr, row*3 + row + 4, 6, "w, s, a, d, x to choose or q to quit\n");
            break;
        }

        game = checkGame(row, coloumn);
            
        if (game == 1)
        {
            if (turn == 2)
            {
                clearLine (5, (coloumn*5) + coloumn + 12);
                attron (COLOR_PAIR (2));
                mvwprintw (stdscr, 5, (coloumn*5) + coloumn + 12, "%s Won", player1->name);
                attroff (COLOR_PAIR (2));
                player1->win ++;
                player2->lose ++;
            }
            else if (turn == 1)
            {
                clearLine (5, (coloumn*5) + coloumn + 12);
                attron (COLOR_PAIR (3));
                mvwprintw (stdscr, 5, (coloumn*5) + coloumn + 12, "%s Won", player2->name);
                attroff (COLOR_PAIR (3));
                player2->win ++;
                player1->lose ++;
            }
            
            save(player1, player2);
            
            xpos = 7;
            ypos = 4;
            game = 0;
            turn = 1;
            
            playAgain(&play, &row, &coloumn);
            
            text (player1, player2, row, coloumn);
            
            attron (COLOR_PAIR (2));
            mvwprintw (stdscr, 5, (coloumn*5) + coloumn + 12, "It is %s's turn", player1->name);
            attroff (COLOR_PAIR(2));
            drawDots (row, coloumn);
            drawBoarder (row, coloumn);
        }
        if (play == 1)
        {
            //moves cursor
            move (ypos, xpos);
            userInput = getch ();
            refresh();
        }
    }
}

void setup (record * player1, record * player2, int * x, int * row, int * coloumn)
{
    int maxX;
    int maxY;
    getmaxyx(stdscr, maxY, maxX);
    maxY --;
    maxX --;
    
    echo ();
    char temp[20];
    
    mvprintw(0, 0, "Welcome to Obstruction");
    
    while ((temp[0] != 'n' || (temp[0] != 'n' && temp[1] != 'o')) && (temp[0] != 'y' || (temp[0] != 'y' && temp[1] != 'e' && temp[2] != 's')))
    {
        clearLine(1,0);
        mvprintw(1, 0, "  Are you playing by yourself?");
        move (1,31);
        scanw("%s", &temp);
    }
    
    if (temp[0] == 'n' || (temp[0] == 'n' && temp[1] == 'o'))
    {
        *x = 0;
        
        mvprintw(2, 0, "  Please enter Player 1 name:");
        move (2,30);
        scanw("%s", &temp);
        strcpy(player1->name, temp);
    
        mvprintw(3, 0, "  Please enter Player 2 name:");
        move (3,30);
        scanw("%s", &temp);
        strcpy(player2->name, temp);
        
    }
    else if (temp[0] == 'y' || (temp[0] == 'y' && temp[1] == 'e' && temp[2] == 's'))
    {
        *x = 1;
        
        mvprintw(2, 0, "  Please enter your name:");
        move (2,26);
        scanw("%s", &temp);
        strcpy(player1->name, temp);
        strcpy(player2->name, "automated");
    }
    
    while ((*row < 6 || *row > 10) && (*coloumn < 6 || *coloumn > 10))
    {
        if (*x == 0)
        {
            clearLine(4,0);
            mvprintw(4, 0, "  What dimensions would you like?");
            move (4,34);
            scanw("%dx%d", row, coloumn);
        }
        else if (*x == 1)
        {
            clearLine(3,0);
            mvprintw(3, 0, "  What dimensions would you like?");
            move (3,34);
            scanw("%dx%d", row, coloumn);
        }
    }
    
    clearLine(0,0);
    clearLine(1,0);
    clearLine(2,0);
    clearLine(3,0);
    clearLine(4,0);
    clearLine(5,0);
    noecho ();
}

void playAgain (int * t, int * row, int * coloumn)
{
    echo ();
    char temp[5];
    
    attron (COLOR_PAIR (5));
    for (int i = 0; i <= *row*3 + *row + 5; i ++)
    {
        for (int j = 0; j <= *coloumn*5 + *coloumn + 11; j ++)
        {
            mvaddch (i, j, ' ');
        }
    }
    attroff (COLOR_PAIR(5));
    
    mvprintw(0, 0, "Would you like to play again?");
    move (0,30);
    scanw("%s", &temp);
    
    *row = 0;
    *coloumn = 0;
    
    if ((temp[0] == 'y' && temp[1] == 'e' && temp[2] == 's') || (temp[0] == 'y'))
    {
        *t = 1;
        
        while ((*row < 6 || *row > 10) && (*coloumn < 6 || *coloumn > 10))
        {
            mvprintw(1, 0, "What dimensions would you like?");
            move (1,32);
            scanw("%dx%d", row, coloumn);
        }
    }
    else
    {
        *t = 2;
    }
    
    clearLine(0,0);
    clearLine(1,0);
    mvprintw(0, 16, "Obstruction");
    noecho ();
    move(4,7);
}

//This draws the boarder for the game
void drawBoarder (int row, int coloumn)
{
    //Clears around boarder
    attron (COLOR_PAIR (5));
    mvwprintw (stdscr, 0, 0, "                                                                                       ");
    mvwprintw (stdscr, 1, 0, "                                                                                       ");
    for (int i = 0; i <= (coloumn*5) + coloumn; i ++)
    {
        mvwprintw (stdscr, i, 0, "    ");
        mvwprintw (stdscr, i, (coloumn*5) + coloumn + 4, "      ");
    }
    mvwprintw (stdscr, (row*3) + row + 2, 0, "                                         ");
    mvwprintw (stdscr, (row*3) + row + 3, 0, "                                         ");
    mvwprintw (stdscr, (row*3) + row + 4, 0, "                                         ");
    mvwprintw (stdscr, (row*3) + row + 5, 0, "                                         ");
    mvwprintw (stdscr, (row*3) + row + 2, ((coloumn*5) + coloumn + 4)/2, "                                         ");
    mvwprintw (stdscr, (row*3) + row + 3, ((coloumn*5) + coloumn + 4)/2, "                                         ");
    mvwprintw (stdscr, (row*3) + row + 4, ((coloumn*5) + coloumn + 4)/2, "                                         ");
    mvwprintw (stdscr, (row*3) + row + 5, ((coloumn*5) + coloumn + 4)/2, "                                         ");
    attroff (COLOR_PAIR(5));
    
    attron (COLOR_PAIR (4));
    //Horizontal Rows
    for (int i = 2; i <= (row*3) + row + 2; i = i + 4)
    {
        for (int j = 4; j <= (coloumn*5) + coloumn + 4; j ++)
        {
            mvaddch (i, j, 'x');
        }
    }
    
    //Vertical Coloumns
    for (int i = 2; i <= (row*3) + row + 2; i ++)
    {
        for (int j = 4; j <= coloumn*5 + coloumn + 5; j = j + 6)
        {
            mvaddch(i, j, 'x');
        }
    }
    attroff (COLOR_PAIR (4));
    mvprintw(0, ((coloumn*5) + coloumn)/2, "Obstruction");
    
    refresh ();
}

//Draws the dots for user to select
void drawDots (int row, int coloumn)
{
    for (int i = 4; i <= row*4; i = i + 4)
    {
        for (int j = 7; j <= coloumn*6 + 6; j = j + 6)
        {
            mvaddch(i, j, '.');
        }
    }
    
    refresh ();
}

//Checks to see if the game is over
int checkGame (int row, int coloumn)
{
    int total = 0;
    int gameOver = 0;
    
    for (int j = 7; j <= coloumn*6 + 6; j = j + 6)
    {
        for (int i = 4; i <= row*4; i = i + 4)
        {
            if (mvinch(i, j) == '.')
            {
                total ++; //if there aren't any dots on the board the game is over
            }
        }
    }
    
    if (total > 0)
    {
        gameOver = 0;
    }
    else if (total == 0)
    {
        gameOver = 1;
    }
    
    return gameOver;
}

void computer (int * y, int * z, int row, int coloumn)
{
    int a;
    a = rand()%100;
    
    if (a < 50)
    {
        for (int j = 7; j <= coloumn*6 + 6; j = j + 6)
        {
            for (int i = 4; i <= row*4; i = i + 4)
            {
                if (mvinch(i, j) == '.')
                {
                    *y = i;
                    *z = j;
                    break;
                }
            }
        }
    }
    else if (a >= 50)
    {
        for (int i = 4; i <= row*4; i = i + 4)
        {
            for (int j = 7; j <= coloumn*6 + 6; j = j + 6)
            {
                if (mvinch(i, j) == '.')
                {
                    *y = i;
                    *z = j;
                    break;
                }
            }
        }
    }
    
}

void text (record * player1, record * player2, int row, int coloumn)
{
    mvprintw(0, ((coloumn*5) + coloumn)/2, "Obstruction");
    
    attron (COLOR_PAIR(2));
    mvprintw (2, (coloumn*5) + coloumn + 12,"Player 1 - %s", player1->name);
    mvprintw (9, (coloumn*5) + coloumn + 12,"Player 1: %d-%d", player1->win, player1->lose);
    attroff (COLOR_PAIR(2));
    
    attron (COLOR_PAIR(3));
    mvprintw (3, (coloumn*5) + coloumn + 12,"Player 2 - %s", player2->name);
    mvprintw (10, (coloumn*5) + coloumn + 12,"Player 2: %d-%d", player2->win, player2->lose);
    attroff (COLOR_PAIR(3));
    
    attron (COLOR_PAIR (6));
    mvprintw(8, (coloumn*5) + coloumn + 12, "Scoreboard");
    attroff (COLOR_PAIR (6));
}

// Fills the board with 'o's to mark the user space
void fill (int x, int y, int row, int coloumn)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    
    for (i = 0; i < 17; i ++)
    {
        for (j = 0; j < 11; j ++)
        {
            if ((mvinch(y + j - 5, x + i - 8)&A_COLOR) != COLOR_PAIR (2) && (mvinch(y + j - 5, x + i - 8)&A_COLOR) != COLOR_PAIR (3))
            {
                mvaddch (j + y - 5, i + x - 8, 'o');
            }
        }
    }
    //Draws the boarder back on the o's
    drawBoarder (row, coloumn);
    refresh ();
}

void read (record * player1, record * player2)
{
    FILE * file;
    file = fopen("assets/score.txt", "r");
    fscanf(file, "player 1: %d-%d", &player1->win, &player1->lose);
    fscanf(file, "player 2: %d-%d", &player2->win, &player2->lose);
    fclose(file);
}

void save (record * player1, record * player2)
{
    FILE * file;
    file = fopen("assets/score.txt", "w");
    fprintf(file, "player1: %d-%d\n", player1->win, player1->lose);
    fprintf(file, "player2: %d-%d", player2->win, player2->lose);
    fclose(file);
}

//Clears lines
void clearLine (int x, int y)
{
    mvwprintw (stdscr, x, y, "                                                ");
    refresh ();
}
