#include <stdio.h>

#include "pixmap_io.h"

int width = 320;
int height = 240;

int main(){
	char* image = load_pixmap("/home/ludovic/HPC/Projet/car3/car_3000.pgm", &width, &height);
	store_pixmap("/home/ludovic/HPC/Projet/Code/image_test", image, width, height);
}