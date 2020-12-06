#include "../include/main.h"

#define threshold 10

void copy_ui8matrix_ui8matrix_padding(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* -----------------------------------------------------------------------------
*/ 
{
    int i, j;

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            Y[i][j+2] = X[i][j];
        }
    }
}

uint8 erosion_dilatation(int taille_kernel, int traitement, uint8** padding, int i, int j){
    // 255 ou 1 si binaire
    uint8 pixel_courant = abs(1 - traitement);
    for(int k = -taille_kernel; k <= taille_kernel; k++)
    {
		for(int l = -taille_kernel; l <= taille_kernel; l++){
						// l'image "padding" de taille: abscisse(ncl -  nch+4) et ordonnée(nrl-2 à nrh+2)
					// traitement dilatation ou érosion
                    // padding[i+k][j+2+l] 
			if(padding[i+k][j+l] == traitement){	
				pixel_courant = traitement;
						//printf("Pixel blanc !!\n");
			}
		}
	}
    return pixel_courant;
}
//taille kernel: 1 pour kernel 3x3, 2 pour 5x5 et traitement: 255 pour dilatation et 0  pour erosion	
 void dilatation_erosion(int taille_kernel, int traitement, uint8** padding, int nrl, int nrh, int ncl, int nch, uint8** image_courante){
 	printf("Lancement de l'algorithme de dilatation\n");

	uint8 pixel_courant;
	char nom_res[100];
	copy_ui8matrix_ui8matrix_padding(image_courante, nrl, nrh, ncl, nch, padding);
	for(int i = nrl; i<= nrh; i++){
		for(int j = ncl; j <= nch; j++){
				// Variable de stockage de l'état du pixel après traitement. 
			pixel_courant = erosion_dilatation(taille_kernel, traitement, padding, i, j);
			// changement effectuer sur image courante directement
			image_courante[i][j] = pixel_courant;
		}
	}
	
 }

void morpho_sequentielle(int taille_kernel, uint8** padding, int nrl, int nrh, int ncl, int nch, uint8** image_courante){

    char nom[150];
    int traitement2 = 0;
	uint8 pixel_courant;

		// boule permetttant d'effectuer 4 etapes de traitement consécutives sur l'image courante:  erosion-dilatation-dilatation-erosion
	for(int etape = 1; etape <= 4; etape++){	
		if(etape == 4) traitement2 = 0;
		copy_ui8matrix_ui8matrix_padding(image_courante, nrl, nrh, ncl, nch, padding);
		for(int i = nrl; i<= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				pixel_courant = abs(255 - traitement2);
				for(int k = -taille_kernel; k <= taille_kernel; k++)
				{
					for(int l = -taille_kernel; l <= taille_kernel; l++){
						if(padding[i+k][j+2+l] == traitement2){	
							pixel_courant = traitement2;
								//printf("Pixel blanc !!\n");
						}
					}
				}
			    image_courante[i][j] = pixel_courant;
			}
		}
			// variable permettant d'effectuer l'autre traitement. 
		traitement2 = 255;
	}
    //printf("Fin traitement !!\n");


}
//taille kernel: 1 pour kernel 3x3, 2 pour 5x5 et traitement: 255 pour fermeture et 0  pour ouverture	
 void traitement_sequentielle(int taille_kernel, char* path_load, char* path_save){
 	printf("Lancement de l'algorithme de ouverture_fermeture\n");
	int traitement = 0;
    char nom[150];
 	int nrl, nrh, ncl, nch;
	int img_nbr = 1;
	//char nom_img[100];
	//char nom_res[100];

    get_path(1, nom, path_load, NULL);

	uint8 pixel_courant;
	uint8** image_courante = LoadPGM_ui8matrix(nom, &nrl, &nrh, &ncl, &nch);
	uint8** padding = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);

	for (img_nbr; img_nbr < 200; img_nbr++){
		get_path(img_nbr, nom, path_load, NULL);
		image_courante = LoadPGM_ui8matrix(nom, &nrl, &nrh, &ncl, &nch);
        
		morpho_sequentielle(taille_kernel, padding, nrl, nrh, ncl, nch, image_courante);
        //dilatation_erosion(taille_kernel, 0, padding, nrl, nrh, ncl, nch, image_courante);    

	    get_path(img_nbr, nom, path_save, "_traitement_sequentielle");
	    SavePGM_ui8matrix(image_courante, nrl, nrh, ncl, nch, nom);
	}
 }


