#include "../headers/functions.h"

int main(int argc,char **argv){
	get_map_route(argc,argv);//gets and validates the map route
	welcome();//print a welcome message
	char option='1';//user's option from the main menu
	while(option!='8'){
		if (option!='0')
			main_menu();//print the main menu
		option=get_option();//user's option
		switch(option) {
			case '1':
				load_and_print_map();
				break;
			case '2':
				//generate map();
				break;
			case '3':
				//enter and validate route
				break;
			case '4':
				//find all possible routes (lists)
				break;
			case '5':
				//find all possible routes (trees)
				break;
			case '6':
				//print storaged routes
				break;
			case '7':
				//find the best routes
				break;
			case '8':
				//exit program
				printf("¡Hasta pronto!\n\n");
				break;
			default:
				//invalid option
				printf("\n¡Opción inválida! Por favor inténtelo nuevamente.\n");
				break;
		}
	}
	return 0;
}
