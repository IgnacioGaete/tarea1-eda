#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Global definitions
// Simbols (ASCII values):
#define START_POINT         65 // A
#define END_POINT           66 // B
#define STAIRS              69 // E 
#define OBSTACLE            79 // O
#define PENDIENT            83 // S
#define NORMAL_FLOOR        43 // +

// Costs:
#define START_POINT_COST    0
#define END_POINT_COST      0
#define STAIRS_COST         3
#define OBSTACLE_COST       -1
#define PENDIENT_COST       2
#define NORMAL_FLOOR_COST   1

// Utilities:
#define MAX_MAP_SIZE        20
#define MAX_ROUTES_POSSIBLE 100

// Structures:
typedef struct{
	int rows;
	int columns;
	char *path;
	char content[MAX_MAP_SIZE][MAX_MAP_SIZE];
} Map;

typedef struct list_model{
	int i;
	int j;
	int cost;
	struct list_model *next;
	struct list_model *prev;
} List;

// Global variables:
static char valid_characters[6]={'A','B','E','O','S','+'};

#endif

// Function declarations:

// Gets the location of the map provided by the user via command line
char *get_map_path(int,char**);

// Gets the user's option from the command line
char get_option(void);

// Gets dimensions to generate a random map
void get_dimensions(int*,int*);

// Loads the map in map->content
void load_map(Map**);

// Verifies if the given map have a correct format
int verify_map(Map);

// Verifies if the line contains valid simbols and counts how many start points and end points have
int verify_line(char*,int*,int*);

// Verifies if the given route is valid
int verify_route(char*,Map);

// Generates a random map. Returns 1 if the operation was successful
int generate_map(Map**,int,int);

// Updates the .txt file with the new map
void update_txt(Map);

// Calculates the total cost of the given route and checks if it reaches the end point
int route_cost(char*,Map,int*);

// Updates the list of all possible routes
void update_routes_lists(List**,Map);

// Finds the given point in the map. Useful only with (char)START_POINT and (char)END_POINT
void find_point(char,Map,int*,int*);

// Prints a welcome message
void welcome(void);

// Prints the main menu of the program
void main_menu(void);

// Prints the given map
void print_map(Map);

// Prints all the routes storaged in lists
void print_routes_list(List*);
