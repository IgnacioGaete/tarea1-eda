#include "../headers/functions.h"

int main(int argc,char **argv){
	Map *map=(Map*)calloc((size_t)1,sizeof(Map));
	map->path=get_map_path(argc,argv);//get and validate the map route
	List *routes_list=(List*)calloc((size_t)MAX_ROUTES_POSSIBLE,sizeof(List));
	char option='1';//user's option from the main menu
	char route[5*MAX_MAP_SIZE];//route given by the user in option 3
	int nfil,ncol;//number of rows and columns given by the user in option 2
	int cost,goal;//cost of route and whether it reaches the end point or not
	welcome();//prints a welcome message
	while(option!='8'){
		if (option!='0')
			main_menu();//print the main menu
		option=get_option();//user's option
		switch(option){
			case '1'://load map
				if(verify_map(*map)){//verifies if the map have a correct format
					load_map(&map);//stores the map from the .txt file into the map structure
					printf("¡Mapa cargado con éxito!. Su contenido se muestra a continuación:\n");
					print_map(*map);//prints the map and it dimensions
				}
				else
					printf("ERROR: ¡Mapa inválido!\n");
				break;
			case '2'://generate a random map
				get_dimensions(&nfil,&ncol);//gets dimensions and stores them in nfil and ncol
				if(generate_map(&map,nfil,ncol)){
					if(verify_map(*map)){
						update_txt(*map);
						printf("¡Mapa generado con éxito!. Su contenido se muestra a continuación:\n");
						print_map(*map);
					}
					else
						printf("ERROR: Mapa inválido.\n");
				}
				else
					printf("ERROR: Mapa no pudo generarse correctamente.\n");
				break;
			case '3'://enter and validate route
				printf("Mapa actual:\n");
				print_map(*map);
				printf("\nIngrese ruta (largo máximo de %d caracteres): ",(int)(sizeof(route)/sizeof(char)));
				scanf("%s",route);
				if(verify_route(route,*map)){
					cost=route_cost(route,*map,&goal);//calculates the cost of that route and set goal=1 if it reaches the end point
					printf("\nLa ruta especificada %s llega a destino. Coste total: %d.\n",goal ? "SÍ" : "NO",cost);
				}
				else
					printf("ERROR: ¡Ruta inválida! (imposible salir del mapa o pasar cierto obstáculo)\n");
				break;
			case '4'://find all possible routes (lists)
				if(verify_map(*map)){
					update_routes_lists(&routes_list,*map);
				}
				else
					printf("ERROR: Mapa inválido.\n");
				break;
			case '5'://find all possible routes (trees)
				printf("ERROR: Opción no implementada.\n");
				break;
			case '6'://print storaged routes
				printf("ERROR: Opción no implementada.\n");
				//print_routes_list(routes_list);
				break;
			case '7'://find the best routes
				printf("ERROR: Opción no implementada.\n");
				break;
			case '8'://exit program
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
