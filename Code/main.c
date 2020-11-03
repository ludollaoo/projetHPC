#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#define threshold 10
#define nb_img_max 200


 void frame_difference(){
 	printf("Lancement de l'algorithme de frame difference\n");

 	int nrl, nrh, ncl, nch;
	int img_nbr = 1;
	char nom_img[100];
	char nom_res[100];

	uint8 pixel_courant, pixel_precedent;
	int diff;
	uint8** image_precedente = LoadPGM_ui8matrix("/home/ludovic/HPC/Projet/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8** image_courante = LoadPGM_ui8matrix("/home/ludovic/HPC/Projet/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8** difference = ui8matrix(nrl, nrh, ncl, nch);

	for (img_nbr; img_nbr < 200; img_nbr++){
		sprintf(nom_img, "/home/ludovic/HPC/Projet/car3/car_3%03d.pgm", img_nbr);
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

		sprintf(nom_res, "/home/ludovic/HPC/Projet/Resultats/image_test3%03d", img_nbr);
		SavePGM_ui8matrix(difference, nrl, nrh, ncl, nch, nom_res);
		image_precedente = image_courante;
	}
 }

 void get_path(int numero_image, char * path){
 	sprintf(path, "/home/ludovic/HPC/Projet/car3/car_3%03d.pgm", numero_image);
 }



int main(void){
	//taille des images
	const int nrl = 0;
	const int nrh = 239;
	const int ncl = 0;
	const int nch = 319;

	//chemin des images
	char path[100];

	//////////////////////////////
	//calcul de la """moyenne"""//
	//////////////////////////////

	//creation et chargement de l'image moyenne
	uint8** moyenne = ui8matrix(nrl, nrh, ncl, nch);
	get_path(0, path);
	MLoadPGM_ui8matrix(path, nrl, nrh, ncl, nch, moyenne);
	uint8 pixel_moyenne;

	//creation de l'image courante
	uint8** image_courante = ui8matrix(nrl, nrh, ncl, nch);
	uint8 pixel_courant;

	//parcours des 200 images
	for(int n_img = 1; n_img < nb_img_max; n_img++){

		//chargement de l'image courante
		get_path(n_img, path);
		MLoadPGM_ui8matrix(path, nrl, nrh, ncl, nch, image_courante);

		//parcours de l'image courante et incrementation/decrementation de l'image moyenne
		for(int i = nrl; i <= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				pixel_moyenne = moyenne[i][j];
				pixel_courant = image_courante[i][j];
				if(pixel_moyenne > pixel_courant){
					moyenne[i][j] -= 1;
				}else if(pixel_moyenne < pixel_courant){
					moyenne[i][j] += 1;
				}
			}
		}
	}

	//visualisation de la moyenne
	//SavePGM_ui8matrix(moyenne, nrl, nrh, ncl, nch,"/home/ludovic/HPC/Projet/Code/image_test");

	free_ui8matrix(moyenne, nrl, nrh, ncl, nch);
	free_ui8matrix(image_courante, nrl, nrh, ncl, nch);
}

	// exemple de fonction pour ouverture et fermeture, attention au chemin
	//uint8** image = LoadPGM_ui8matrix("/home/ludovic/HPC/Projet/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	//SavePGM_ui8matrix(image, nrl, nrh, ncl, nch,"/home/ludovic/HPC/Projet/Code/image_test");
