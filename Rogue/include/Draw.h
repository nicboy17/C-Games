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

#ifndef _NMAJOR_DRAWH
#define _NMAJOR_DRAWH

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include <curses.h>

//Draws the room
void drawRoom(room * rooms, int * totalRow, int * totalColoumn, int * num, amount * quantity);

#endif 
