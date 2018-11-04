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
#include "Main.h"

/*
 -Takes in file name
 -Calls all functions
*/
int main(int argc, char * argv[])
{
    int x = 0;
    int y = 0;
    int i = 0;
    int row = 0;
    int coloumn = 0;
    int num = 0;
    char * token;
    char buffer[150];
    
    //Creates dynamic memory
    struct room * rooms;
    rooms = malloc(sizeof(struct room));
    rooms->dimensions = malloc(sizeof(char)*10);
    rooms->doorE = malloc(sizeof(char)*10);
    rooms->doorW = malloc(sizeof(char)*10);
    rooms->doorN = malloc(sizeof(char)*10);
    rooms->doorS = malloc(sizeof(char)*10);
    rooms->hero = malloc(sizeof(char)*10);
    rooms->stairs = malloc(sizeof(char)*10);
    
    rooms->gold = malloc(sizeof(char*)*6);
    rooms->monster = malloc(sizeof(char*)*6);
    rooms->magic = malloc(sizeof(char*)*6);
    rooms->potion = malloc(sizeof(char*)*6);
    rooms->weapon = malloc(sizeof(char*)*6);
    
    for (i = 0; i < 6; i ++)
    {
        rooms->gold[i] = malloc(sizeof(char)*100);
        rooms->monster[i] = malloc(sizeof(char)*100);
        rooms->magic[i] = malloc(sizeof(char)*100);
        rooms->potion[i] = malloc(sizeof(char)*100);
        rooms->weapon[i] = malloc(sizeof(char)*100);
    }
    
    struct amount * quantity;
    quantity = malloc(sizeof(struct amount));
    //Initializes values
    quantity->gold = 0;
    quantity->monsters = 0;
    quantity->magic = 0;
    quantity->potions = 0;
    quantity->weapons = 0;
    
    struct teleport * player;
    player = malloc(sizeof(struct teleport));
    player->room1 = 0;
    player->room2 = 0;
    player->room3 = 0;
    player->room4 = 0;
    player->room5 = 0;
    player->room6 = 0;
    
    //Reads in file
    FILE * map;
    map = fopen(argv[1], "r");
    
    if (map == NULL)
    {
        printf ("error opening file\n");
        exit(0);
    }
    
    //Sets up Ncurses
    ncursesSetup();
    
    //Gets room instructions from file
    while (fgets(buffer, sizeof buffer, map) != NULL)
    {
        //Parses data into struct
        roomProperties(buffer, &*rooms, &*quantity);
        
        //Draws room from roomProperties
        drawRoom(rooms, &row, &coloumn, &num, quantity);
        
        //Collects lengths into struct from teleportation
        if (num == 0)
        {
            player->room1 = coloumn;
        }
        else if (num == 1)
        {
            player->room2 = coloumn;
        }
        else if (num == 2)
        {
            player->room3= coloumn;
        }
        else if (num == 3)
        {
            player->room4 = coloumn;
        }
        else if (num == 4)
        {
            player->room5 = coloumn;
        }
        else if (num == 5)
        {
            player->room6 = coloumn;
        }
        
        //Hero initial position
        if (rooms->hero[0] != '\0')
        {
            token = strtok(rooms->hero, ",");
            x = atoi (token);
            token = strtok(NULL, ",");
            y = atoi (token);
        }
        num ++;
    }
    fclose(map);
    
    //Moves hero to initial position
    mvaddch (4 + y, 4 + x, '@');
    move(4 + y, 4 + x);
    
    //Reuses struct for picking up items in playing function
    quantity->gold = 0;
    quantity->monsters = 0;
    quantity->magic = 0;
    quantity->potions = 0;
    quantity->weapons = 0;
    
    playing(&*quantity, x, y, player);
    
    //ends Ncurses
    refresh();
    endwin();
    
    //prints inventory at the end
    printf("%d weapons collected\n", quantity->weapons);
    printf("%d gold collected\n", quantity->gold);
    printf("%d potions collected\n", quantity->potions);
    printf("%d magic collected\n", quantity->magic);
    
    //Frees memory
    free(rooms->dimensions);
    free(rooms->doorE);
    free(rooms->doorW);
    free(rooms->doorN);
    free(rooms->doorS);
    free(rooms->hero);
    free(rooms->stairs);
    
    free(rooms->gold);
    free(rooms->monster);
    free(rooms->magic);
    free(rooms->potion);
    free(rooms->weapon);
    
    free(rooms);
    free(quantity);
    free (player);

    return 0;
}



