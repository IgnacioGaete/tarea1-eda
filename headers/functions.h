#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Global definitions:
// Simbols (ASCII values):
#define START_POINT        65
#define END_POINT          66
#define STAIRS             69
#define OBSTACLE           79
#define PENDIENT           83
#define NORMAL_FLOOR       43

// Costs:
#define START_POINT_COST   -1
#define END_POINT_COST     -1
#define STAIRS_COST        3
#define OBSTACLE_COST      -1
#define PENDIENT_COST      2
#define NORMAL_FLOOR_COST  1

// Others:

// Global variables:
static char *map_route=NULL;
static FILE *map_file=NULL;
static char valid_characters[6]={'A','B','E','O','S','+'};

#endif

// Function declarations:

// Gets the location of the map privided via command line
void get_map_route(int,char**);

// Gets the user's option from the command line
char get_option(void);

// Load the map to map_file and prints it, only if verify_map is true
void load_and_print_map(void);

// Verifies the map and gets the dimensions
int verify_map(int*);

// Verifies if the line contains valid simbols
int verify_line(char*);

// Prints a welcome message
void welcome(void);

// Prints the main menu of the program
void main_menu(void);
