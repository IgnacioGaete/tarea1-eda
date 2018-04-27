#include "../headers/functions.h"

// Global variables:
//static char *map_route=NULL;
//static FILE *map_file=NULL;
//static char allowed_characters={};

// Gets the location of the map privided via command line
/* READY */
void get_map_route(int argc,char **argv){
	if(argc==1){
		printf("ERROR: Debe ingresar ubicación de archivo \"mapa.txt\".\n");
		exit(1);
	}
	else if(argc>2){
		printf("ERROR: Demasiados argumentos ingresados.\n");
		exit(1);
	}
	else{
		map_route=argv[1];
		return;
	}
}

// Gets the user's option from the command line
/* READY */
char get_option(void){
	printf("Ingrese su opción: ");
	char option[5];
	scanf("%s",option);
	printf("\n");
	if(('0'<option[0])&&(option[0]<'9')){
		return option[0];
	}
	else
		return '0';
}

// Load the map to map_file and prints it, only if verify_map is true
/* INCOMPLETE */
void load_and_print_map(void){
	int dim[2]={0,0};
	if(verify_map(dim)){
		char line_buffer[MAX_NUM_COL];
		map_file=fopen(map_route,"r");
		printf("¡Mapa cargado con éxito!. Su contenido se muestra a continuación:\n\n");
		while (fscanf(map_file,"%s",line_buffer)!=EOF)
			printf("%s\n",buffer);
		fclose(map_file);
		printf("\nNúmero de columnas: %d\nNúmero de filas: %d\n",dim[0],dim[1]);
		sleep(3);
		return;
	}
	else{
		printf("ERROR: Mapa inválido.\n");
		return;
	}
}

// Verifies the map and obtains the dimensions
int verify_map(int *dim){
	map_file=fopen(map_route,"r");
	int width=-1,height=0;
	int out=1;
	char line_buffer[MAX_NUM_COL];
	while(fscanf(map_file,"%s",line_buffer)!=EOF){
		if(width==-1)
			width=strlen(line_buffer);
		if((strlen(line_buffer)!=width)||verify_line(line_buffer)){
			printf("ERROR: Mapa incorrecto.\n");
			width=-1;
			height=-1;
			out=0;
			break;
		}
		height++;
	}
	*dim=width;
	*(dim+1)=height;
	fclose(map_file);
	return out;
}

// Verifies if the line contains valid simbols
/* INCOMPLETE */
int verify_line(char *line){
	/* CONTINUE HERE */
}

// Prints a welcome message
/* READY */
void welcome(void){
	printf("\n");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*                  ¡Bienvenid@!                  *\n");
	printf("*                ELO320 - Tarea 1                *\n");
	printf("*                                                *\n");
	printf("**************************************************\n");
	printf("\n");
	return;
}

// Prints the main menu of the program
/* READY */
void main_menu(void){
	printf("\n");
	printf("Menú principal:\n\n");
	printf("1) Cargar mapa.\n");
	printf("2) Generar un mapa.\n");
	printf("3) Ingresar y validar ruta.\n");
	printf("4) Encontrar todas las rutas posibles (listas).\n");
	printf("5) Encontrar todas las listas posibles (árboles).\n");
	printf("6) Desplegar rutas almacenadas.\n");
	printf("7) Encontrar la mejor ruta posible.\n");
	printf("8) Salir del programa.\n");
	printf("\n");
	return;
}
