#include "main.h"

void get_path(int numero_image, char* nom, char* path, char* complement){
	if(complement == NULL){
		sprintf(nom, "%s%03d.pgm", path, numero_image);
	}else{
		sprintf(nom, "%s%03d%s.pgm", path, numero_image, complement);
	}
	//printf("%s\n", nom);
}