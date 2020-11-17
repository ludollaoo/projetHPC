#include <stdio.h>
#include <stdlib.h>

#include "../include/nrdef.h"
#include "../include/nrutil.h"
#include "../include/morpho.h"
#include "../include/morpho_SIMD.h"
#include "../include/mymacro.h"
#include "../include/mutil.h"
#define threshold 10


 void frame_difference(){
 	printf("Lancement de l'algorithme de frame difference\n");

 	int nrl, nrh, ncl, nch;
	int img_nbr = 1;
	char nom_img[100];
	char nom_res[100];

	uint8 pixel_courant, pixel_precedent;
	int diff;
	uint8** image_precedente = LoadPGM_ui8matrix("/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8** image_courante = LoadPGM_ui8matrix("/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8** difference = ui8matrix(nrl, nrh, ncl, nch);

	for (img_nbr; img_nbr < 200; img_nbr++){
		sprintf(nom_img, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/car3/car_3%03d.pgm", img_nbr);
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

		sprintf(nom_res, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat/image_test3%03d", img_nbr);
		SavePGM_ui8matrix(difference, nrl, nrh, ncl, nch, nom_res);
		image_precedente = image_courante;
	}
	printf("Fin frame difference\n");
 }
/*
void padding(){

 	printf("Lancement padding\n");

 	int nrl, nrh, ncl, nch;
	int img_nbr = 1;
	char nom_img[100];
	char nom_res[100];
	int taille_ordonnee;
	int taille_abscisse;
	uint8** image_courante = LoadPGM_ui8matrix("/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat/image_test3001", &nrl, &nrh, &ncl, &nch);
	uint8** difference = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
 	printf("ouverture image padding\n");
	printf("nrl = %d, nrh = %d, ncl = %d, nch = %d\n", nrl, nrh, ncl, nch);

	for (img_nbr; img_nbr < 200; img_nbr++){
		sprintf(nom_img, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat/image_test3%03d", img_nbr);
		image_courante = LoadPGM_ui8matrix( nom_img, &nrl, &nrh, &ncl, &nch);
		//redimension image avec padding
		difference = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
		taille_ordonnee = abs((nrh) - (nrl))+1;
		taille_abscisse = abs((nch) - (ncl))+1;
		/*for(int i = nrl; i<= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				difference[i][j] = image_courante[i][j];
			}
		}
		for(int i = -2 ; i < taille_ordonnee+2; i++){
			// Portion droite

			difference[nrl+i][taille_abscisse+2] = 100;
			difference[nrl+i][taille_abscisse+3] = 100;
			// Portion gauche

			difference[nrl+i][0] = 100;
			difference[nrl+i][1] = 100;				
		}
		for(int j = 2; j < taille_abscisse+2; j++){
			// Portion basse
			difference[nrl-1][ncl+j] = 100;
			difference[nrl-2][ncl+j] = 100;
			// Portion haute
			difference[taille_ordonnee+0][ncl+j] = 100;
			difference[taille_ordonnee+1][ncl+j] = 100;
		}
		for(int i = nrl; i<= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				difference[i][j+2] = image_courante[i][j];
			}
		}

		sprintf(nom_res, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat2/image_test3%03d", img_nbr);
		SavePGM_ui8matrix(difference, nrl-2, nrh+2, ncl-2, nch+2, nom_res);
		
	}
}
void copy_ui8matrix_ui8matrix_padding(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
----------------------------------------------------------------------------- 
{
    int i, j;

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            Y[i][j+2] = X[i][j];
        }
    }
}
//taille kernel: 1 pour kernel 3x3, 2 pour 5x5 et traitement: 255 pour dilatation et 0  pour erosion	
 void dilatation_erosion(int taille_kernel, int traitement){
 	printf("Lancement de l'algorithme de dilatation\n");

 	int nrl, nrh, ncl, nch;
	int img_nbr = 1;
	char nom_img[100];
	char nom_res[100];

	uint8 pixel_courant;
	uint8** image_courante = LoadPGM_ui8matrix("/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat/image_test3001", &nrl, &nrh, &ncl, &nch);
	//Initialisation d'une image avec des bords de 2*2 afin d'effectuer un traitement avec filtre 3*3 ou 5*5
	uint8** padding = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	
	for (img_nbr; img_nbr < 200; img_nbr++){
		//Chargement d'une image après traitement par SD
		sprintf(nom_img, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat/image_test3%03d", img_nbr);
		image_courante = LoadPGM_ui8matrix( nom_img, &nrl, &nrh, &ncl, &nch);
		//copie de l'image courante, dans l'image avec padding. Elle servira afin d'effectuer le traitement
		copy_ui8matrix_ui8matrix_padding(image_courante, nrl, nrh, ncl, nch, padding);
		//Parcours de l'image courante d'abscisse(ncl - nch) et ordonnée (nrl - nrh)
		for(int i = nrl; i<= nrh; i++){
			for(int j = ncl; j <= nch; j++){
				// Variable de stockage de l'état du pixel après traitement. 
				pixel_courant = abs(255 - traitement);
				// double Boucle afin de parcourir tous les pixels du filtres et ainsi effectuer le traitement.
				for(int k = -taille_kernel; k <= taille_kernel; k++)
				{
					for(int l = -taille_kernel; l <= taille_kernel; l++){
						// l'image "padding" de taille: abscisse(ncl -  nch+4) et ordonnée(nrl-2 à nrh+2)
						// traitement dilatation ou érosion
						if(padding[i+k][j+2+l] == traitement){	
							pixel_courant = traitement;
							//printf("Pixel blanc !!\n");
						}
					}
				}
				// changement effectuer sur image courante directement
				image_courante[i][j] = pixel_courant;
			}
		}

		//printf("Fin traitement !!\n");
		sprintf(nom_res, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat2/image_dilatation3%03d", img_nbr);
		SavePGM_ui8matrix(image_courante, nrl, nrh, ncl, nch, nom_res);
	}
 }

//taille kernel: 1 pour kernel 3x3, 2 pour 5x5 et traitement: 255 pour fermeture et 0  pour ouverture	
 void ouverture_fermeture(int taille_kernel, int traitement){
 	printf("Lancement de l'algorithme de ouverture_fermeture\n");
	
 	int nrl, nrh, ncl, nch;
	int img_nbr = 1;
	char nom_img[100];
	char nom_res[100];

	uint8 pixel_courant;
	uint8** image_courante = LoadPGM_ui8matrix("/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat/image_test3001", &nrl, &nrh, &ncl, &nch);
	uint8** padding = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);

	for (img_nbr; img_nbr < 200; img_nbr++){
		sprintf(nom_img, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat/image_test3%03d", img_nbr);
		image_courante = LoadPGM_ui8matrix( nom_img, &nrl, &nrh, &ncl, &nch);
		int traitement2 = traitement;
		// boule permetttant d'effectuer 2 etapes de traitement consécutives sur l'image courante: dilatation-erosion ou erosion-dilatation 
		for(int etape = 1; etape <= 2; etape++){	
			
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
			traitement2 = abs(255 - traitement);

		}

		//printf("Fin traitement !!\n");
		sprintf(nom_res, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat2/image_dilatation3%03d", img_nbr);
		SavePGM_ui8matrix(image_courante, nrl, nrh, ncl, nch, nom_res);
		
	}
 }
*/
int main(void){
	frame_difference();
    double t0, t1, dt, tmin, t;
    int iter, niter = 4;
    int run, nrun = 5;
    double cycles, cycles2;
    char *format = "%6.2f ";
	//padding();
	//taille kernel: 1 pour kernel 3x3, 2 pour 5x5 et traitement: 255 pour dilatation et 0  pour erosion
	CHRONO(traitement3_SIMD(),cycles2); printf("SIMD   \n"); 

    sleep(5);
    CHRONO(main_morpho(), cycles);  printf("C   \n");



    printf("t0 = %f ; t1 = %f\n", (cycles/(320*240)), (cycles2/(320*240)));
    //test();
	//taille kernel: 1 pour kernel 3x3, 2 pour 5x5 et traitement: 255 pour fermeture et 0  pour ouverture	
	//ouverture_fermeture(1, 0);
}

	// exemple de fonction pour ouverture et fermeture, attention au chemin
	//uint8** image = LoadPGM_ui8matrix("/home/ludovic/HPC/Projet/car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
	//SavePGM_ui8matrix(image, nrl, nrh, ncl, nch,"/home/ludovic/HPC/Projet/Code/image_test");
