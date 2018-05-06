#include "../headers/functions.h"

int main(int argc,char **argv){
	Map *map=(Map*)calloc((size_t)1,sizeof(Map));
	map->path=get_map_path(argc,argv);//get and validate the map route
	Map *random_map=(Map*)calloc((size_t)1,sizeof(Map));
	random_map->path=map->path;
	char option='1';//user's option from the main menu
	char route[5*MAX_MAP_SIZE];
	int nfil,ncol;
	int cost,goal;
	welcome();//print a welcome message
	while(option!='8'){
		if (option!='0')
			main_menu();//print the main menu
		option=get_option();//user's option
		switch(option){
			case '1'://load map
				if(verify_map(*map)){
					load_map(&map);
					printf("¡Mapa cargado con éxito!. Su contenido se muestra a continuación:\n");
					print_map(*map);
				}
				else
					printf("ERROR: ¡Mapa inválido!\n");
				break;
			case '2'://generate a random map
				get_dimensions(&nfil,&ncol);//gets dimensions and stores them in nfil and ncol
				if(generate_map(&random_map,nfil,ncol)){
					if(verify_map(*random_map)){
						free(map);
						map=random_map;
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
				print_map(*map);
				printf("\nIngrese ruta (largo máximo de %d caracteres): ",(int)(sizeof(route)/sizeof(char)));
				scanf("%s",route);
				if(verify_route(route,*map)){
					cost=route_cost(route,*map,&goal);
					printf("\nLa ruta especificada %s llega a destino. Coste total: %d.\n",goal ? "SÍ" : "NO",cost);
				}
				else
					printf("ERROR: ¡Ruta inválida! (imposible salir del mapa o pasar cierto obstáculo)\n");
				break;
			case '4'://find all possible routes (lists)
				
				break;
			case '5'://find all possible routes (trees)
				
				break;
			case '6'://print storaged routes
				
				break;
			case '7'://find the best routes
				
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
