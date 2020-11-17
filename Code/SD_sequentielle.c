#include "main.h"

void SD_sequentielle_2(int nrl, int nrh, int ncl, int nch, int nb_img_max, int N, char* path){

	char nom[100];

	uint8 pixel_courant, pixel_moyenne, pixel_difference, pixel_ecart_type, pixel_binaire;

	uint8** image_courante 		= ui8matrix(nrl, nrh, ncl, nch);
	uint8** image_moyenne 		= ui8matrix(nrl, nrh, ncl, nch);
	uint8** image_difference 	= ui8matrix(nrl, nrh, ncl, nch);
	uint8** image_ecart_type 	= ui8matrix(nrl, nrh, ncl, nch);
	uint8** image_binaire 		= ui8matrix(nrl, nrh, ncl, nch);

	
	//initialisation de l'image moyenne
	get_path(0, nom, path, NULL);
	MLoadPGM_ui8matrix(nom, nrl, nrh, ncl, nch, image_moyenne);

	//initialisation de l'image ecart_type
	for(int i = nrl; i <= nrh; i++){
		for(int j = ncl; j <= nch; j++){
			image_ecart_type[i][j] = Vmin;
		}
	}

	//parcours des images
	for(int n_img = 1; n_img < nb_img_max; n_img++){

		//chargement de l'image courante
		get_path(n_img, nom, path, NULL);
		MLoadPGM_ui8matrix(nom, nrl, nrh, ncl, nch, image_courante);

		//image moyenne
		for(int i = nrl; i <= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				pixel_moyenne = image_moyenne[i][j];
				pixel_courant = image_courante[i][j];
				if(pixel_moyenne > pixel_courant){
					pixel_moyenne -= 1;
				}else if(pixel_moyenne < pixel_courant){
					pixel_moyenne += 1;
				}
				image_moyenne[i][j] = pixel_moyenne;
			}
		}

		//difference 
		for(int i = nrl; i <= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				pixel_moyenne = image_moyenne[i][j];
				pixel_courant = image_courante[i][j];
				pixel_difference = abs(pixel_courant - pixel_moyenne);
				image_difference[i][j] = pixel_difference;
			}
		}

		//ecart_type
		for(int i = nrl; i <= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				pixel_difference = image_difference[i][j];
				pixel_ecart_type = image_ecart_type[i][j];
				if(pixel_ecart_type < (N * pixel_difference)){
					pixel_ecart_type += 1;
				}else if(pixel_ecart_type > (N * pixel_difference)){
					pixel_ecart_type -= 1;
				}
				pixel_ecart_type = max(min(pixel_ecart_type, Vmax), Vmin);
				image_ecart_type[i][j] = pixel_ecart_type;
			}
		}

		//binaire
		for(int i = nrl; i <= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				pixel_ecart_type = image_ecart_type[i][j];
				pixel_difference = image_difference[i][j];
				if(pixel_difference < pixel_ecart_type){
					pixel_binaire = NOIR;
				}else{
					pixel_binaire = BLANC;
				}
				image_binaire[i][j] = pixel_binaire;
			}
		}

		//sauvegarde
		get_path(n_img, nom, path, "_binaire_2");
		SavePGM_ui8matrix(image_binaire, nrl, nrh, ncl, nch, nom);
	}

	free_ui8matrix(image_moyenne, nrl, nrh, ncl, nch);
	free_ui8matrix(image_courante, nrl, nrh, ncl, nch);
	free_ui8matrix(image_difference, nrl, nrh, ncl, nch);
	free_ui8matrix(image_ecart_type, nrl, nrh, ncl, nch);
	free_ui8matrix(image_binaire, nrl, nrh, ncl, nch);
}