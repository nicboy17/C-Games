/**************************************************************************
 Student Name: Nick Maior                Student Number: 0879292
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
#include "Parse.h"

//Parses array
void roomProperties(char * roomX, room  * rooms, amount * quantity)
{
    int i = 0;
    int j = 0;
    
    char * token;
    
    //Initializes and clears structs
    quantity->gold = 0;
    quantity->monsters = 0;
    quantity->magic = 0;
    quantity->potions = 0;
    quantity->weapons = 0;
    for (i = 0; i < 10; i ++)
    {
        rooms->hero[i] = '\0';
        rooms->stairs[i] = '\0';
        rooms->dimensions[i] = '\0';
    }
    for (i = 0; i < 6; i ++)
    {
        for (j = 0; j < 100; j ++)
        {
            rooms->weapon[i][j] = '\0';
            rooms->potion[i][j] = '\0';
            rooms->magic[i][j] = '\0';
            rooms->monster[i][j] = '\0';
            rooms->gold[i][j] = '\0';
        }
    }
    
    //sorts all of the data into the appropiate array
    token = strtok(roomX, " ");
    while (token != NULL)
    {
        if (isdigit(token[0]))
        {
            //Dimensions
            for (i = 0; i < strlen(token); i++)
            {
                rooms->dimensions[i] = token[i];
            }
        }
        //Doors
        else if (token[0] == 'd' && token[1] == 'e')
        {
            rooms->doorE[0] = token[2];
            rooms->doorE[1] = token[3];
        }
        else if (token[0] == 'd' && token[1] == 'w')
        {
            rooms->doorW[0] = token[2];
            rooms->doorW[1] = token[3];
        }
        else if (token[0] == 'd' && token[1] == 'n')
        {
            rooms->doorN[0] = token[2];
            rooms->doorN[1] = token[3];
        }
        else if (token[0] == 'd' && token[1] == 's')
        {
            rooms->doorS[0] = token[2];
            rooms->doorS[1] = token[3];
        }
        //Hero
        else if (token[0] == 'h')
        {
            for (i = 1; i < strlen(token); i ++)
            {
                rooms->hero[i-1] = token[i];
            }
        }
        //Stairs
        else if (token[0] == 's')
        {
            for (i = 1; i < strlen(token); i++)
            {
                rooms->stairs[i-1] = token[i];
            }
        }
        //Gold
        else if (token[0] == 'g')
        {
            for (i = 1; i < strlen(token); i ++)
            {
                rooms->gold[quantity->gold][i-1] = token[i];
            }
            quantity->gold ++;
        }
        //Monsters
        else if (token[0] == 'M')
        {
            for (i = 1; i < strlen(token); i ++)
            {
                rooms->monster[quantity->monsters][i-1] = token[i];
            }
            quantity->monsters ++;
        }
        //Magic
        else if (token[0] == 'm')
        {
            for (i = 1; i < strlen(token); i ++)
            {
                rooms->magic[quantity->magic][i-1] = token[i];
            }
            quantity->magic ++;
        }
        //Potions
        else if (token[0] == 'p')
        {
            for (i = 1; i < strlen(token); i ++)
            {
                rooms->potion[quantity->potions][i-1] = token[i];
            }
            quantity->potions ++;
        }
        //Weapons
        else if (token[0] == 'w')
        {
            for (i = 1; i < strlen(token); i ++)
            {
                rooms->weapon[quantity->weapons][i-1] = token[i];
            }
            quantity->weapons ++;
        }
        
        token = strtok(NULL, " ");
    }
}
