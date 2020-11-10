#include "main.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)
#define nb_img_max 200
#define Vmin 1
#define Vmax 254
#define NOIR 0
#define BLANC 255

void SD_sequentielle(int nrl, int nrh, int ncl, int nch, int nb_image_max, int N, int sauvegarde){
	
	//chemin des images
	char path[100];

	//creation et chargement de l'image moyenne
	uint8** image_moyenne = ui8matrix(nrl, nrh, ncl, nch);
	get_path(0, path, NULL);
	MLoadPGM_ui8matrix(path, nrl, nrh, ncl, nch, image_moyenne);
	uint8 pixel_moyenne;

	//creation de l'image courante
	uint8** image_courante = ui8matrix(nrl, nrh, ncl, nch);
	uint8 pixel_courant;

	//creation de l'image difference
	uint8** image_difference = ui8matrix(nrl, nrh, ncl, nch);
	uint8 pixel_difference;

	//creation  de l'image ecrat_type
	uint8** image_ecart_type = ui8matrix(nrl, nrh, ncl, nch);
	for(int i = nrl; i <= nrh; i++){
		for(int j = ncl; j <= nch; j++){
			image_ecart_type[i][j] = Vmin;
		}
	}
	uint8 pixel_ecart_type;

	//creation de l'image binaire
	uint8** image_binaire = ui8matrix(nrl, nrh, ncl, nch);
	uint8 pixel_binaire;

	//parcours des 200 images
	for(int n_img = 1; n_img < nb_img_max; n_img++){

		//chargement de l'image courante
		get_path(n_img, path, NULL);
		MLoadPGM_ui8matrix(path, nrl, nrh, ncl, nch, image_courante);

		//parcours de l'image courante et incrementation/decrementation de l'image moyenne
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

		//visualisation de l'image moyenne
		if(sauvegarde){
			get_path(n_img, path, "_moyenne");
			SavePGM_ui8matrix(image_moyenne, nrl, nrh, ncl, nch, path);
		}

		//difference entre la moyenne et l'image courante
		for(int i = nrl; i <= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				pixel_moyenne = image_moyenne[i][j];
				pixel_courant = image_courante[i][j];
				pixel_difference = abs(pixel_courant - pixel_moyenne);
				image_difference[i][j] = pixel_difference;
			}
		}

		//visualisation de l'image difference
		if(sauvegarde){
			get_path(n_img, path, "_difference");
			SavePGM_ui8matrix(image_difference, nrl, nrh, ncl, nch, path);
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
				}else{
					pixel_ecart_type = max(min(pixel_ecart_type, Vmax), Vmin);
				}
				image_ecart_type[i][j] = pixel_ecart_type;
			}
		}

		//visualition de l'ecart type
		if(sauvegarde){
			get_path(n_img, path, "_ecart_type");
			SavePGM_ui8matrix(image_ecart_type, nrl, nrh, ncl, nch, path);
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
		//visualition de l'image binaire
		if(sauvegarde){
			get_path(n_img, path, "_binaire");
			SavePGM_ui8matrix(image_binaire, nrl, nrh, ncl, nch, path);
		}
	}

	free_ui8matrix(image_moyenne, nrl, nrh, ncl, nch);
	free_ui8matrix(image_courante, nrl, nrh, ncl, nch);
	free_ui8matrix(image_difference, nrl, nrh, ncl, nch);
	free_ui8matrix(image_ecart_type, nrl, nrh, ncl, nch);
	free_ui8matrix(image_binaire, nrl, nrh, ncl, nch);
}