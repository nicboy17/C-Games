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
#include "Draw.h"

//Draws the room from the parsed data
void drawRoom (room * rooms, int * totalRow, int * totalColoumn, int * num, amount * quantity)
{
    int x = 0;
    int y = 0;
    
    int rows = 0;
    int coloumns = 0;
    
    int door = 0;
    
    int i = 0;
    int j = 0;
    
    char * token;
    
    if (*num < 3)
    {
        *totalRow = 3;
        *totalColoumn = *totalColoumn + 3;
    }
    else if (*num == 3)
    {
        *totalRow = 25;
        *totalColoumn = 3;
    }
    else if (*num > 3)
    {
        *totalRow = 25;
        *totalColoumn = *totalColoumn + 3;
    }
    
    //room dimensions
    if (rooms->dimensions[0] != '\0')
    {
        token = strtok(rooms->dimensions, "X");
        rows = atoi (token);
        token = strtok(NULL, "X");
        coloumns = atoi (token);
    }
    
    for (i = *totalColoumn; i <= *totalColoumn + coloumns; i ++)
    {
        for (j = *totalRow; j <= *totalRow + rows; j ++)
        {
            mvaddch (j, i, '.');
        }
    }
    
    for (i = *totalRow; i <= *totalRow + rows; i ++)
    {
        mvaddch (i, *totalColoumn, '|');
        mvaddch (i, *totalColoumn + coloumns, '|');
    }
    for (j = *totalColoumn; j <= *totalColoumn + coloumns; j ++)
    {
        mvaddch (*totalRow, j, '-');
        mvaddch (*totalRow + rows, j, '-');
    }
    
    //door locations
    if (rooms->doorE[0] != '\0')
    {
        door = atoi (rooms->doorE);
        
        if (door >= rows)
        {
            door = rows - 2;
        }
        mvaddch (*totalRow + 1 + door, *totalColoumn + coloumns, '+');
    }
    if (rooms->doorW[0] != '\0')
    {
        door = atoi (rooms->doorW);
        
        if (door >= rows)
        {
            door = rows - 2;
        }
        mvaddch (*totalRow + 1 + door, *totalColoumn, '+');
    }
    if (rooms->doorN[0] != '\0')
    {
        door = atoi (rooms->doorN);
        
        if (door >= coloumns)
        {
            door = coloumns - 2;
        }
        mvaddch (*totalRow, *totalColoumn + 1 + door, '+');
    }
    if (rooms->doorS[0] != '\0')
    {
        door = atoi (rooms->doorS);
        
        if (door >= coloumns)
        {
            door = coloumns - 2;
        }
        mvaddch (*totalRow + rows, *totalColoumn + 1 + door, '+');
    }
    
    //Stairs
    if (rooms->stairs[0] != '\0')
    {
        token = strtok(rooms->stairs, ",");
        x = atoi (token);
        token = strtok(NULL, ",");
        y = atoi (token);
        
        mvaddch (y + *totalRow + 1, x + *totalColoumn + 1, '%');
    }
    
    //Monsters
    if (rooms->monster[0][0] != '\0')
    {
        for (i = 0; i < quantity->monsters; i ++)
        {
            token = strtok(rooms->monster[i], ",");
            x = atoi (token);
            token = strtok(NULL, ",");
            y = atoi (token);
            
            mvaddch (y + *totalRow + 1, x + *totalColoumn + 1, 'M');
        }
    }
    
    //Magic
    if (rooms->magic[0][0] != '\0')
    {
        for (i = 0; i < quantity->magic; i ++)
        {
            token = strtok(rooms->magic[i], ",");
            x = atoi (token);
            token = strtok(NULL, ",");
            y = atoi (token);
            
            mvaddch (y + *totalRow + 1, x + *totalColoumn + 1, '$');
        }
    }
    
    //Potions
    if (rooms->potion[0][0] != '\0')
    {
        for (i = 0; i < quantity->potions; i ++)
        {
            token = strtok(rooms->potion[i], ",");
            x = atoi (token);
            token = strtok(NULL, ",");
            y = atoi (token);
            
            mvaddch (y + *totalRow + 1, x + *totalColoumn + 1, '!');
        }
    }
    
    //Weapons
    if (rooms->weapon[0][0] != '\0')
    {
        for (i = 0; i < quantity->weapons; i ++)
        {
            token = strtok(rooms->weapon[i], ",");
            x = atoi (token);
            token = strtok(NULL, ",");
            y = atoi (token);
            
            mvaddch (y + *totalRow + 1, x + *totalColoumn + 1, ')');
        }
    }
    
    //Gold
    if (rooms->gold[0][0] != '\0')
    {
        for (i = 0; i < quantity->gold; i ++)
        {
            token = strtok(rooms->gold[i], ",");
            x = atoi (token);
            token = strtok(NULL, ",");
            y = atoi (token);
            
            mvaddch (y + *totalRow + 1, x + *totalColoumn + 1, '*');
        }
    }
    
    //Drawing the rooms 3 across and 2 down
    if (*num < 3)
    {
        *totalRow = 3;
        *totalColoumn = *totalColoumn + coloumns + 1;
    }
    else if (*num >= 3)
    {
        *totalRow = 25;
        *totalColoumn = *totalColoumn + coloumns + 1;
    }
    
    refresh ();
}
