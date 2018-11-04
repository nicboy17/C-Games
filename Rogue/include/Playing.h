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

#ifndef _NMAJOR_PLAYINGH
#define _NMAJOR_PLAYINGH

#include <ncurses.h>
#include <curses.h>

//Defines the keys for player movement
#define UP	    'w'
#define LEFT	'a'
#define DOWN	's'
#define RIGHT	'd'

//Handles player movement through array and collection of items
void playing(amount * draw, int x, int y, teleport * player);

//sets up Ncurses
void ncursesSetup();

#endif
