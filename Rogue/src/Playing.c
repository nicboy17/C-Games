/**************************************************************************
 Student Name: Nick Major                Student Number: 0879292
 Date: 03/13/14                          Course Name: cis2500
 
 I have exclusive control over this submission via my password.
 By including this statement in this header comment, I certify that:
      1) I have read and understood the University policy on academic integrity;
      2) I have completed the Computing with Integrity Tutorial on Moodle; and
      3) I have achieved at least 80% in the Computing with Integrity Self Test.
 I assert that this work is my own. I have appropriately acknowledged any and all material
 (data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
 Furthermore, I certify that this assignment was prepared by me specifically for this course.
 ****************************************************************************/

#include "Structs.h"
#include "Playing.h"

//Handles player movement through array and collection of items
void playing(amount * draw, int x, int y, teleport * player)
{
    int xpos = 0;
    int ypos = 0;
    
    char userInput;
    
    userInput = getch();
    
    //gets user input for direction of player
    while (userInput != 'q')
    {
        //gets position of the cursor
        getyx (stdscr, ypos, xpos);
        
        //Direction depending on the key entered moves the cursor
        switch (userInput)
        {
            case UP:
                if (mvinch (ypos - 1, xpos) != '-' && mvinch (ypos - 1, xpos) != 'M' && mvinch (ypos - 1, xpos) != ' ')
                {
                    mvwprintw (stdscr, 0, 0, "                                          ");
                    ypos --;
                    
                    //Erases behind player
                    if (mvinch (ypos + 1, xpos) != '+' && mvinch (ypos + 1, xpos) != '%')
                    {
                        mvaddch (ypos + 1, xpos, '.');
                    }
                }
                break;
                
            case DOWN:
                if (mvinch (ypos + 1, xpos) != '-' && mvinch (ypos + 1, xpos) != 'M' && mvinch (ypos + 1, xpos) != ' ')
                {
                    mvwprintw (stdscr, 0, 0, "                                          ");
                    ypos ++;
                    
                    if (mvinch (ypos - 1, xpos) != '+' && mvinch (ypos - 1, xpos) != '%')
                    {
                        mvaddch (ypos - 1, xpos, '.');
                    }
                }
                break;
                
            case RIGHT:
                if (mvinch (ypos , xpos + 1) != '|' && mvinch (ypos, xpos + 1) != 'M' && mvinch (ypos, xpos + 1) != ' ')
                {
                    mvwprintw (stdscr, 0, 0, "                                          ");
                    xpos ++;
                    
                    if (mvinch (ypos, xpos - 1) != '+' && mvinch (ypos, xpos - 1) != '%')
                    {
                        mvaddch (ypos, xpos - 1, '.');
                    }
                }
                break;
                
            case LEFT:
                if (mvinch (ypos, xpos - 1) != '|' && mvinch (ypos, xpos - 1) != 'M' && mvinch (ypos, xpos + 1) != ' ')
                {
                    mvwprintw (stdscr, 0, 0, "                                          ");
                    xpos --;
                    if (mvinch (ypos, xpos + 1) != '+' && mvinch (ypos, xpos + 1) != '%')
                    {
                        mvaddch (ypos, xpos + 1, '.');
                    }
                }
                break;
            default:
                mvwprintw (stdscr, 0, 0, "use only w, s, a, d, to move and q to quit\n");
                break;
        }
        
        //Places hero
        if (mvinch (ypos, xpos) != '+' && mvinch (ypos, xpos) != '%' && mvinch (ypos, xpos) != '*' && mvinch (ypos, xpos) != '!' && mvinch (ypos, xpos) != '$' && mvinch (ypos, xpos) != ')')
        {
            mvaddch (ypos, xpos, '@');
        }
        
        //Teleportes hero to corner of the next room
        if (mvinch (ypos, xpos) == '+')
        {
            if (xpos < player->room1 && ypos < 23)
            {
                xpos = player->room1 + 4;
                ypos = 4;
                mvaddch (ypos, xpos, '@');
            }
            else if (xpos > player->room1 && xpos < player->room2 && ypos < 23)
            {
                xpos = player->room2 + 4;
                ypos = 4;
                mvaddch (ypos, xpos, '@');
            }
            else if (xpos > player->room2 && ypos < 23)
            {
                xpos = 4;
                ypos = 26;
                mvaddch (ypos, xpos, '@');
            }
            else if (xpos < player->room4 && ypos > 24)
            {
                xpos = player->room4 + 4;
                ypos = 26;
                mvaddch (ypos, xpos, '@');
            }
            else if (xpos > player->room4 && xpos < player->room5 && ypos > 24)
            {
                xpos = player->room5 + 4;
                ypos = 26;
                mvaddch (ypos, xpos, '@');
            }
            else if (xpos > player->room5 && ypos > 24)
            {
                xpos = 4;
                ypos = 4;
                mvaddch (ypos, xpos, '@');
            }
        }
        
        //Inventory tracker
        if (mvinch (ypos, xpos) == ')')
        {
            draw->weapons ++;
        }
        else if (mvinch (ypos, xpos) == '*')
        {
            draw->gold ++;
        }
        else if (mvinch (ypos, xpos) == '!')
        {
            draw->potions ++;
        }
        else if (mvinch (ypos, xpos) == '$')
        {
            draw->magic ++;
        }
        
        //moves cursor
        move (ypos, xpos);
        userInput = getch ();
    }
}

//sets up ncurses
void ncursesSetup()
{
    initscr();
    cbreak();
    noecho();
    start_color();
    refresh();
}
