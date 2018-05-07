#include "../headers/functions.h"

// Gets the location of the map provided by the user via command line
/* READY */
char *get_map_path(int argc,char **argv){
	if(argc==1){
		printf("ERROR: Debe ingresar ubicación de archivo \"mapa.txt\".\n");
		exit(1);
	}
	else if(argc>2){
		printf("ERROR: Demasiados argumentos ingresados.\n");
		exit(1);
	}
	return argv[1];
}

// Gets the user's option from the command line
/* READY */
char get_option(void){
	printf("Ingrese su opción: ");
	char option[20];
	scanf("%s",option);
	printf("\n");
	if((strlen(option)==1)&&('1'<=option[0])&&(option[0]<='8')){
		return option[0];
	}
	else
		return '0';
}

// Loads the map in map->content
/* READY */
void load_map(Map **map){
	char *temp_path=(*map)->path;
	free(*map);
	*map=(Map*)calloc((size_t)1,sizeof(Map));
	(*map)->path=temp_path;
	FILE *map_file=fopen((*map)->path,"r");
	int height=0,width=0;
	char line_buffer[MAX_MAP_SIZE];
	int i;
	while(fscanf(map_file,"%s",line_buffer)!=EOF){
		if(width==0)
			width=strlen(line_buffer);
		for(i=0;i<width;i++)
			((*map)->content)[height][i]=line_buffer[i];
		height++;
	}
	(*map)->rows=height;
	(*map)->columns=width;
	fclose(map_file);
	return;
}

// Verifies if the given map have a correct format
/* READY */
int verify_map(Map map){
	FILE *map_file=fopen(map.path,"r");
	int width=-1;
	int start_point_num=0;
	int end_point_num=0;
	char line_buffer[MAX_MAP_SIZE];
	while(fscanf(map_file,"%s",line_buffer)!=EOF){
		if(width==-1)
			width=strlen(line_buffer);
		if((strlen(line_buffer)!=width)||(strlen(line_buffer)<1)||(!verify_line(line_buffer,&start_point_num,&end_point_num))){
			fclose(map_file);
			return 0;
		}
	}
	fclose(map_file);
	if((start_point_num!=1)||(end_point_num!=1))
		return 0;
	return 1;
}

// Verifies if the line contains valid simbols and counts how many start points and end points have
/* READY */
int verify_line(char *line,int *start_point_num,int *end_point_num){
	int i,j;
	int flag;
	for(i=0;i<strlen(line);i++){
		flag=0;
		for(j=0;j<sizeof(valid_characters)/sizeof(char);j++)
			if(*(line+i)==valid_characters[j])
				flag=1;
		if(flag==0)
			return 0;
		*start_point_num+=(*(line+i)==(char)START_POINT) ? 1:0;
		*end_point_num+=(*(line+i)==(char)END_POINT) ? 1:0;
	}
	return 1;
}

// Verifies if the given route is valid
/* READY */
int verify_route(char *route,Map map){
	int iA,jA;
	find_point((char)START_POINT,map,&iA,&jA);
	int i;
	for(i=0;route[i]!='\0';i++){
		switch(route[i]){
			case '^':
				iA--;
				break;
			case 'v':
				iA++;
				break;
			case '<':
				jA--;
				break;
			case '>':
				jA++;
				break;
			default:
				return 0;
				break;
		}
		if((iA<0)||(jA<0)||(iA>=map.rows)||(jA>=map.columns))
			return 0;
		if(map.content[iA][jA]==(char)OBSTACLE)
			return 0;
	}
	return 1;
}

// Generates a random map. Returns 1 if the operation was successful
/* READY */
int generate_map(Map **map,int nfil,int ncol){
	if((nfil>1)&&(nfil<=MAX_MAP_SIZE)&&(ncol>1)&&(ncol<=MAX_MAP_SIZE)&&(map!=NULL)){
		char *temp_path=(*map)->path;
		free(*map);
		*map=(Map*)calloc((size_t)1,sizeof(Map));
		(*map)->path=temp_path;
		(*map)->rows=nfil;
		(*map)->columns=ncol;
		srand(time(NULL));
		int i=random()%nfil;
		int j=random()%ncol;
		int i_aux,j_aux;
		char char_buffer;
		do{
			i_aux=random()%nfil;
			j_aux=random()%ncol;
		} while((i_aux==i)||(j_aux==j));
		(*map)->content[i][j]=(char)START_POINT;
		(*map)->content[i_aux][j_aux]=(char)END_POINT;
		for(i=0;i<nfil;i++){
			for(j=0;j<ncol;j++){
				if(((*map)->content[i][j]!=(char)START_POINT)&&((*map)->content[i][j]!=(char)END_POINT)){
					do{
						i_aux=random()%(sizeof(valid_characters)/sizeof(char));
						char_buffer=valid_characters[i_aux];
					} while((char_buffer==(char)START_POINT)||(char_buffer==(char)END_POINT));
					(*map)->content[i][j]=char_buffer;
				}
			}
		}
		return 1;
	}
	else
		return 0;
}

// Updates the .txt file with the new map
/* READY */
void update_txt(Map map){
	FILE *map_file=fopen(map.path,"w");
	int i,j;
	for(i=0;i<map.rows;i++){
		for(j=0;j<map.columns;j++)
			fprintf(map_file,"%c",map.content[i][j]);
		fprintf(map_file,"%c",'\n');
	}
	fclose(map_file);
}

// Calculates the total cost of the given route and checks if it reaches the end point
/* READY */
int route_cost(char *route,Map map,int *goal){
	int iA,jA,iB,jB;
	find_point((char)START_POINT,map,&iA,&jA);
	find_point((char)END_POINT,map,&iB,&jB);
	int i,cost=0;
	for(i=0;route[i]!=EOF;i++){
		if(route[i]=='^')
			iA--;
		if(route[i]=='v')
			iA++;
		if(route[i]=='>')
			jA++;
		if(route[i]=='<')
			jA--;
		switch(map.content[iA][jA]){
			case (char)STAIRS:
				cost+=STAIRS_COST;
				break;
			case (char)PENDIENT:
				cost+=PENDIENT_COST;
				break;
			case (char)NORMAL_FLOOR:
				cost+=NORMAL_FLOOR_COST;
				break;
			default:
				break;
		}
	}
	*goal=map.content[iA][jA]==(char)END_POINT ? 1 : 0;
	return cost;
}

// Gets dimensions to generate a random map
/* READY */
void get_dimensions(int *nfil,int *ncol){
	printf("Ingrese número de filas (máximo %d): ",MAX_MAP_SIZE);
	scanf("%d",nfil);
	printf("\n");
	printf("Ingrese número de columnas (máximo %d): ",MAX_MAP_SIZE);
	scanf("%d",ncol);
	printf("\n");
	return;
}

// Finds the given point in the map. Useful only with (char)START_POINT and (char)END_POINT
/* READY */	
void find_point(char point,Map map,int *i,int *j){
	int i_aux;
	int j_aux;
	for(i_aux=0;i_aux<map.rows;i_aux++){
		for(j_aux=0;j_aux<map.columns;j_aux++){
			if(map.content[i_aux][j_aux]==point){
				*i=i_aux;
				*j=j_aux;
				return;
			}
		}
	}
	*i=-1;
	*j=-1;
	return;
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

// Prints the given map
/* READY */
void print_map(Map map){
	int rows=map.rows;
	int columns=map.columns;
	int i,j;
	printf("\n");
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++)
			printf("%c",map.content[i][j]);
		printf("\n");
	}
	printf("\nNúmero de filas: %d\nNúmero de columnas: %d\n\n",rows,columns);
	return;
}

// Prints all the routes storaged in lists
/* INCOMPLETE */
void print_routes_list(List *routes_list){
	/*List *head=NULL;
	List *cusror=NULL;
	int cost,i=0;
	for(*head=*routes_list;head!=NULL;head=*(routes_list+i)){
		
		i++;
	}*/
}

// Updates the list of all possible routes
/* INCOMPLETE */
void update_routes_lists(List **routes_list,Map map){
	/*srand(time(NULL));
	free(*routes_list);
	*routes_list=(List*)calloc((size_t)MAX_ROUTES_POSSIBLE,sizeof(List));
	int iA,jA,iB,jB;
	find_point((char)END_POINT,map,&iB,&jB);
	int route_num,iteration;
	char route[3*MAX_MAP_SIZE];
	int rand_num;
	int i,j;
	for(route_num=0;route_num<MAX_ROUTES_POSSIBLE;route_num++){
		find_point((char)START_POINT,map,&iA,&jA);
		i=iA;
		j=jA;
		for(iteration=0;iteration<3*MAX_MAP_SIZE;iteration++){
			do{
				rand_num=random()%4;
			}
			
		}
	}
	return;*/
}
