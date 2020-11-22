#include "../include/main.h"

void get_path(int numero_image, char* nom, char* path, char* complement){
	if(complement == NULL){
		sprintf(nom, "%s%03d.pgm", path, numero_image);
	}else{
		sprintf(nom, "%s%03d%s.pgm", path, numero_image, complement);
	}
	//printf("%s\n", nom);
}

void resize(int nrl, int nrh, int ncl, int nch){
	
	char nom[100];
	
	uint8** image_courante = ui8matrix(0, 239, 0, 319);
	uint8** image_resized = ui8matrix(nrl, nrh, ncl, nch);

	for(int n_img = 0; n_img < 200; n_img++){
		
		get_path(n_img, nom, "/home/jebali/Bureau/EISE5/HPC/projetHPC/car3/car_3", NULL);
		MLoadPGM_ui8matrix(nom, nrl, nrh, ncl, nch, image_courante);
		
		for(int i = nrl; i <= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				image_resized[i][j] = image_courante[i%240][j%320];
			}
		}

		sprintf(nom, "/home/jebali/Bureau/EISE5/HPC/projetHPC/car3/resized_car_3%03d.pgm", n_img);
		SavePGM_ui8matrix(image_resized, nrl, nrh, ncl, nch, nom);
	}
}
