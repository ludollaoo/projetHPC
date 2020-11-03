#include <stdio.h>

#include "nrdef.h"
#include "nrutil.h"


//debut de l'algorithme de frame difference
int main(void){

	int nrl, nrh, ncl, nch;
	int img_nbr = 0;
	char nom_img[100];

	for (img_nbr; img_nbr < 200; img_nbr++){
		sprintf(nom_img, "/home/ludovic/HPC/Projet/car3/car_3%d.pgm", img_nbr);
		printf("%s\n", nom_img);

	}


	// exemple de fonction pour ouverture et fermeture, attention au chemin
	//uint8** image = LoadPGM_ui8matrix("/home/ludovic/HPC/Projet/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	//SavePGM_ui8matrix(image, nrl, nrh, ncl, nch,"/home/ludovic/HPC/Projet/Code/image_test");
}