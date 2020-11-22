#include "../include/main.h"

void SD_SIMD_2(int nrl, int nrh, int ncl, int nch, int nb_img_max, int N, char* path){

	char nom[100];

	int step;

	vuint8 vecteur_Vmax, vecteur_Vmin;
	vsint8 moins128, vecteur_gt, vecteur_lt, vecteur_eq;

	vuint8 vecteur_courant, vecteur_moyenne, vecteur_difference, vecteur_difference_2, vecteur_difference_1, vecteur_Ndifference, vecteur_ecart_type, vecteur_binaire;
	vsint8 vecteur_courant_s, vecteur_moyenne_s, vecteur_difference_s, vecteur_Ndifference_s, vecteur_ecart_type_s;

	uint8** image_courante 		= ui8matrix(nrl, nrh, ncl, nch);
	uint8** image_moyenne 		= ui8matrix(nrl, nrh, ncl, nch);
	uint8** image_difference 	= ui8matrix(nrl, nrh, ncl, nch);
	uint8** image_ecart_type 	= ui8matrix(nrl, nrh, ncl, nch);
	uint8** image_binaire 		= ui8matrix(nrl, nrh, ncl, nch);

	step = card_vuint8();
	moins128 = _mm_set1_epi8(-128);
	vecteur_Vmax = _mm_set1_epi8(Vmax);
	vecteur_Vmin = _mm_set1_epi8(Vmin);
	

	//chargement de l'image moyenne
	get_path(0, nom, path, NULL);
	MLoadPGM_ui8matrix(nom, nrl, nrh, ncl, nch, image_moyenne);

	//chargement  de l'image ecart_type
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
			for(int j = ncl; j <= nch; j = j + step){
				//chargement
				vecteur_moyenne = _mm_loadu_si128((uint8*) &image_moyenne[i][j]);
				vecteur_courant = _mm_loadu_si128((uint8*) &image_courante[i][j]);
				//conversion
				vecteur_moyenne_s = _mm_add_epi8(vecteur_moyenne, moins128);
				vecteur_courant_s = _mm_add_epi8(vecteur_courant, moins128);
				//comparaison
				vecteur_gt = _mm_cmpgt_epi8(vecteur_moyenne_s, vecteur_courant_s);
				vecteur_lt = _mm_cmplt_epi8(vecteur_moyenne_s, vecteur_courant_s);
				//maj
				vecteur_moyenne_s = _mm_add_epi8(vecteur_moyenne_s, vecteur_gt);
				vecteur_moyenne_s = _mm_sub_epi8(vecteur_moyenne_s, vecteur_lt);
				//deconversion
				vecteur_moyenne = _mm_sub_epi8(vecteur_moyenne_s, moins128);
				//rangement
				_mm_storeu_si128((uint8*) &image_moyenne[i][j], vecteur_moyenne);
			}
		}

		//image difference
		for(int i = nrl; i <= nrh; i++){
			for(int j = ncl; j <= nch; j = j + step){
				//chargement
				vecteur_moyenne = _mm_loadu_si128((uint8*) &image_moyenne[i][j]);
				vecteur_courant = _mm_loadu_si128((uint8*) &image_courante[i][j]);
				//difference
				vecteur_difference_2 = _mm_subs_epu8(vecteur_moyenne, vecteur_courant);
				vecteur_difference_1 = _mm_subs_epu8(vecteur_courant, vecteur_moyenne);
				//valeur absolue
				vecteur_difference = _mm_or_si128(vecteur_difference_1, vecteur_difference_2);
				//rangement
				_mm_storeu_si128((uint8*) &image_difference[i][j], vecteur_difference);
			}
		}

		//image ecart_type
		for(int i = nrl; i <= nrh; i++){
			for(int j = ncl; j <= nch; j = j + step){
				//chargement
				vecteur_difference = _mm_loadu_si128((uint8*) &image_difference[i][j]);
				vecteur_ecart_type = _mm_loadu_si128((uint8*) &image_ecart_type[i][j]);
				//calcul N*difference
				vecteur_Ndifference = _mm_set1_epi8(0);
				switch(N){
					case 4:
					vecteur_Ndifference = _mm_adds_epu8(vecteur_Ndifference, vecteur_difference);
					case 3:
					vecteur_Ndifference = _mm_adds_epu8(vecteur_Ndifference, vecteur_difference);
					case 2:
					vecteur_Ndifference = _mm_adds_epu8(vecteur_Ndifference, vecteur_difference);
					case 1:
					vecteur_Ndifference = _mm_adds_epu8(vecteur_Ndifference, vecteur_difference);
					break;
				}
				//conversion
				vecteur_Ndifference_s = _mm_add_epi8(vecteur_Ndifference, moins128);
				vecteur_ecart_type_s = _mm_add_epi8(vecteur_ecart_type, moins128);
				//comparaison
				vecteur_gt = _mm_cmpgt_epi8(vecteur_ecart_type_s, vecteur_Ndifference_s);
				vecteur_lt = _mm_cmplt_epi8(vecteur_ecart_type_s, vecteur_Ndifference_s);
				//maj
				vecteur_ecart_type = _mm_adds_epi8(vecteur_ecart_type, vecteur_gt);
				vecteur_ecart_type = _mm_subs_epi8(vecteur_ecart_type, vecteur_lt);
				//max, min
				vecteur_ecart_type = _mm_min_epu8(vecteur_ecart_type, vecteur_Vmax);
				vecteur_ecart_type = _mm_max_epu8(vecteur_ecart_type, vecteur_Vmin);
				//rangement
				_mm_storeu_si128((uint8*) &image_ecart_type[i][j], vecteur_ecart_type);
			}
		}

		//image binaire
		for(int i = nrl; i <= nrh; i++){
			for(int j = ncl; j <= nch; j = j + step){
				//chargement
				vecteur_difference = _mm_loadu_si128((uint8*) &image_difference[i][j]);
				vecteur_ecart_type = _mm_loadu_si128((uint8*) &image_ecart_type[i][j]);
				//conversion
				vecteur_ecart_type_s = _mm_add_epi8(vecteur_ecart_type, moins128);
				vecteur_difference_s = _mm_add_epi8(vecteur_difference, moins128);
				//comparaison
				vecteur_lt = _mm_cmplt_epi8(vecteur_ecart_type_s, vecteur_difference_s);
				vecteur_eq = _mm_cmpeq_epi8(vecteur_ecart_type_s, vecteur_difference_s);
				vecteur_binaire = _mm_add_epi8(vecteur_eq, vecteur_lt);
				//rangement
				_mm_storeu_si128((uint8*) &image_binaire[i][j], vecteur_binaire);
			}
		}
		
		get_path(n_img, nom, path, "_binaire_SIMD_2");
		SavePGM_ui8matrix(image_binaire, nrl, nrh, ncl, nch, nom);
	}

	free_ui8matrix(image_moyenne, nrl, nrh, ncl, nch);
	free_ui8matrix(image_courante, nrl, nrh, ncl, nch);
	free_ui8matrix(image_difference, nrl, nrh, ncl, nch);
	free_ui8matrix(image_ecart_type, nrl, nrh, ncl, nch);
	free_ui8matrix(image_binaire, nrl, nrh, ncl, nch);
}
