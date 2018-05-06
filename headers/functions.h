#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Global definitions
// Simbols (ASCII values):
#define START_POINT        65 // A
#define END_POINT          66 // B
#define STAIRS             69 // E 
#define OBSTACLE           79 // O
#define PENDIENT           83 // S
#define NORMAL_FLOOR       43 // +

// Costs:
#define START_POINT_COST   0
#define END_POINT_COST     0
#define STAIRS_COST        3
#define OBSTACLE_COST      -1
#define PENDIENT_COST      2
#define NORMAL_FLOOR_COST  1

// Utilities:
#define MAX_MAP_SIZE       20

// Structures:
typedef struct{
	int rows;
	int columns;
	char *path;
	char content[MAX_MAP_SIZE][MAX_MAP_SIZE];
} Map;

// Global variables:
static char valid_characters[6]={'A','B','E','O','S','+'};

#endif

// Function declarations:

// Gets the location of the map privided via command line
char *get_map_path(int,char**);

// Gets the user's option from the command line
char get_option(void);

// Gets dimensions to generate a random map
void get_dimensions(int*,int*);

// Loads the map in map->content
void load_map(Map**);

// Verifies the given map
int verify_map(Map);

// Verifies if the line contains valid simbols
int verify_line(char*);

// Verifies if the route given is valid
int verify_route(char*,Map);

// Generates a random map. Returns 1 if the operation was successful
int generate_map(Map**,int,int);

// Updates the .txt file whit the new map
void update_txt(Map);

// Calculates the total cost of the given route and checks if 
int route_cost(char*,Map,int*);

// Prints a welcome message
void welcome(void);

// Prints the main menu of the program
void main_menu(void);

// Prints the given map
void print_map(Map);
