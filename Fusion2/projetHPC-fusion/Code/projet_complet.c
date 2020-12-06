#include "../include/main.h"

void projet_complet(char* path_commun){
	char traitement3_source[100];
	sprintf(traitement3_source, "%s/binaire_car_3", path_commun);
	printf("%s\n", traitement3_source);
	char traitement3_sauvegarde[100];
	sprintf(traitement3_sauvegarde, "%s/resultat_car_3", path_commun);

	int nrl = 0;
	int nrh = 239;
	int ncl = 0;
	int nch = 319;
	int nombre_image = 200;
	int N = 4;

	SD_SIMD_opti_openMP_2(nrl, nrh, ncl, nch, nombre_image, N, path_commun);
	traitement3_SIMD_opti_openMP(traitement3_source, traitement3_sauvegarde);
}