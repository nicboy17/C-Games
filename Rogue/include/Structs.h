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

#ifndef _NMAJOR_STRUCTSH
#define _NMAJOR_STRUCTSH

//Stores all of the parsed data for each room
typedef struct room
{
    char * dimensions;
    char * doorE;
    char * doorW;
    char * doorS;
    char * doorN;
    char * stairs;
    char * hero;
    char ** gold;
    char ** monster;
    char ** magic;
    char ** potion;
    char ** weapon;
}room;

//Stores the how many doubles there are
typedef struct amount
{
    int monsters;
    int magic;
    int potions;
    int weapons;
    int gold;
}amount;

//Stores the sum of the rows for each room
typedef struct teleport
{
    int room1;
    int room2;
    int room3;
    int room4;
    int room5;
    int room6;
}teleport;

#endif
