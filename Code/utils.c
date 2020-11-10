#include "main.h"

 void get_path(int numero_image, char * path, char* complement){
 	if(complement == NULL){
 		sprintf(path, "/home/ludovic/HPC/Projet/car3/car_3%03d.pgm", numero_image);
 	}else{
 		sprintf(path, "/home/ludovic/HPC/Projet/car3/car_3%03d%s.pgm", numero_image, complement);
 	}
 }