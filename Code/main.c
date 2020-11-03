#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#define threshold 10


 void frame_difference(){
 	printf("Lancement de l'algorithme de frame difference\n");

 	int nrl, nrh, ncl, nch;
	int img_nbr = 1;
	char nom_img[100];
	char nom_res[100];

	uint8 pixel_courant, pixel_precedent;
	int diff;
	uint8** image_precedente = LoadPGM_ui8matrix("/home/jebali/Bureau/EISE5/ProjetHPC/projetHPC/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8** image_courante = LoadPGM_ui8matrix("/home/jebali/Bureau/EISE5/ProjetHPC/projetHPC/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8** difference = ui8matrix(nrl, nrh, ncl, nch);

	for (img_nbr; img_nbr < 200; img_nbr++){
		sprintf(nom_img, "/home/jebali/Bureau/EISE5/ProjetHPC/projetHPC/car3/car_3%03d.pgm", img_nbr);
		image_courante = LoadPGM_ui8matrix( nom_img, &nrl, &nrh, &ncl, &nch);
		difference = ui8matrix(nrl, nrh, ncl, nch);
		
		for(int i = nrl; i<= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				pixel_courant = image_courante[i][j];
				pixel_precedent = image_precedente[i][j];
				//difference[i][j] = 255;
				diff = abs(pixel_precedent - pixel_courant);
				if(diff > threshold){
					difference[i][j] = 255;
				}else{
					difference[i][j] = 0;
				}
			}
		}

		sprintf(nom_res, "/home/jebali/Bureau/EISE5/ProjetHPC/projetHPC/Resultats/image_test3%03d", img_nbr);
		SavePGM_ui8matrix(difference, nrl, nrh, ncl, nch, nom_res);
		image_precedente = image_courante;
	}
 }



int main(void){
	frame_difference();
}

	// exemple de fonction pour ouverture et fermeture, attention au chemin
	//uint8** image = LoadPGM_ui8matrix("/home/ludovic/HPC/Projet/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	//SavePGM_ui8matrix(image, nrl, nrh, ncl, nch,"/home/ludovic/HPC/Projet/Code/image_test");
