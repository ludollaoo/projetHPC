#include "main.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)
#define Vmin 1
#define Vmax 254
#define NOIR 0
#define BLANC 255

void SD_sequentielle(int nrl, int nrh, int ncl, int nch, int nb_img_max, int N, char* path, int sauvegarde){
	
	//chemin des images
	char nom[100];

	//creation et chargement de l'image moyenne
	uint8** image_moyenne = ui8matrix(nrl, nrh, ncl, nch);
	get_path(0, nom, path, NULL);
	MLoadPGM_ui8matrix(nom, nrl, nrh, ncl, nch, image_moyenne);
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
		//printf("%d/%d\n", n_img, nb_img_max - 1);

		//chargement de l'image courante
		get_path(n_img, nom, path, NULL);
		MLoadPGM_ui8matrix(nom, nrl, nrh, ncl, nch, image_courante);

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
			get_path(n_img, nom, path, "_moyenne");
			SavePGM_ui8matrix(image_moyenne, nrl, nrh, ncl, nch, nom);
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
			get_path(n_img, nom, path, "_difference");
			SavePGM_ui8matrix(image_difference, nrl, nrh, ncl, nch, nom);
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
			get_path(n_img, nom, path, "_ecart_type");
			SavePGM_ui8matrix(image_ecart_type, nrl, nrh, ncl, nch, nom);
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
			get_path(n_img, nom, path, "_binaire");
			SavePGM_ui8matrix(image_binaire, nrl, nrh, ncl, nch, nom);
		}
	}

	free_ui8matrix(image_moyenne, nrl, nrh, ncl, nch);
	free_ui8matrix(image_courante, nrl, nrh, ncl, nch);
	free_ui8matrix(image_difference, nrl, nrh, ncl, nch);
	free_ui8matrix(image_ecart_type, nrl, nrh, ncl, nch);
	free_ui8matrix(image_binaire, nrl, nrh, ncl, nch);
}

void test_SD_sequentielle(){
	int nrl = 0;
	int nrh = 1;
	int ncl = 0;
	int nch = 1;

	char nom[100];
	char* path = "/home/ludovic/HPC/Projet/Resultats/image";

	uint8** image0 = ui8matrix(nrl, nrh, ncl, nch);
	image0[0][0] = 128;
	image0[0][1] = 128;
	image0[1][0] = 128;
	image0[1][1] = 128;
	get_path(0, nom, path, NULL);
	SavePGM_ui8matrix(image0, nrl, nrh, ncl, nch, nom);


	uint8** image1 = ui8matrix(nrl, nrh, ncl, nch);
	image1[0][0] = 0;
	image1[0][1] = 0;
	image1[1][0] = 255;
	image1[1][1] = 255;
	get_path(1, nom, path, NULL);
	SavePGM_ui8matrix(image1, nrl, nrh, ncl, nch, nom);;

	uint8** image2 = ui8matrix(nrl, nrh, ncl, nch);
	image2[0][0] = 0;
	image2[0][1] = 255;
	image2[1][0] = 0;
	image2[1][1] = 255;
	get_path(2, nom, path, NULL);
	SavePGM_ui8matrix(image2, nrl, nrh, ncl, nch, nom);

	SD_sequentielle(nrl, nrh, ncl, nch, 3, 4, path, 1);

	MLoadPGM_ui8matrix("/home/ludovic/HPC/Projet/Resultats/image001_moyenne.pgm", nrl, nrh, ncl, nch, image0);
	assert(image0[0][0] == 127);
	assert(image0[0][1] == 127);
	assert(image0[1][0] == 129);
	assert(image0[1][1] == 129);

	MLoadPGM_ui8matrix("/home/ludovic/HPC/Projet/Resultats/image002_moyenne.pgm", nrl, nrh, ncl, nch, image0);
	assert(image0[0][0] == 126);
	assert(image0[0][1] == 128);
	assert(image0[1][0] == 128);
	assert(image0[1][1] == 130);

	MLoadPGM_ui8matrix("/home/ludovic/HPC/Projet/Resultats/image001_difference.pgm", nrl, nrh, ncl, nch, image0);
	assert(image0[0][0] == 127);
	assert(image0[0][1] == 127);
	assert(image0[1][0] == 126);
	assert(image0[1][1] == 126);

	MLoadPGM_ui8matrix("/home/ludovic/HPC/Projet/Resultats/image002_difference.pgm", nrl, nrh, ncl, nch, image0);
	assert(image0[0][0] == 126);
	assert(image0[0][1] == 127);
	assert(image0[1][0] == 128);
	assert(image0[1][1] == 125);

	MLoadPGM_ui8matrix("/home/ludovic/HPC/Projet/Resultats/image001_ecart_type.pgm", nrl, nrh, ncl, nch, image0);
	assert(image0[0][0] == 2);
	assert(image0[0][1] == 2);
	assert(image0[1][0] == 2);
	assert(image0[1][1] == 2);

	MLoadPGM_ui8matrix("/home/ludovic/HPC/Projet/Resultats/image002_ecart_type.pgm", nrl, nrh, ncl, nch, image0);
	assert(image0[0][0] == 3);
	assert(image0[0][1] == 3);
	assert(image0[1][0] == 3);
	assert(image0[1][1] == 3);

	MLoadPGM_ui8matrix("/home/ludovic/HPC/Projet/Resultats/image001_binaire.pgm", nrl, nrh, ncl, nch, image0);
	assert(image0[0][0] == 255);
	assert(image0[0][1] == 255);
	assert(image0[1][0] == 255);
	assert(image0[1][1] == 255);

	MLoadPGM_ui8matrix("/home/ludovic/HPC/Projet/Resultats/image002_binaire.pgm", nrl, nrh, ncl, nch, image0);
	assert(image0[0][0] == 255);
	assert(image0[0][1] == 255);
	assert(image0[1][0] == 255);
	assert(image0[1][1] == 255);

	free_ui8matrix(image0, nrl, nrh, ncl, nch);
	free_ui8matrix(image1, nrl, nrh, ncl, nch);
	free_ui8matrix(image2, nrl, nrh, ncl, nch);
}

void SD_SIMD(int nrl, int nrh, int ncl, int nch, int nb_img_max, int N, char* path, int sauvegarde){

}