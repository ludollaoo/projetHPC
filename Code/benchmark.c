#include "../include/main.h"

void chrono(int nrl, int nrh, int ncl, int nch){

	double temps_exec;

	clock_t begin = clock();
	SD_SIMD_opti_openMP_2(nrl, nrh, ncl, nch, 200, 4, "/home/jebali/Bureau/EISE5/HPC/projetHPC/car3/resized_car_3");
    //traitement_sequentielle(1, "/home/jebali/Bureau/EISE5/HPC/projetHPC/car3/resized_car_3", "/home/jebali/Bureau/EISE5/HPC/projetHPC/Resultat_Sequentielle/resized_car_3");
    //traitement3_SIMD_opti("/home/jebali/Bureau/EISE5/HPC/projetHPC/car3/resized_car_3", "/home/jebali/Bureau/EISE5/HPC/projetHPC/Resultat_SIMD_opti/resized_car_3");
    //traitement3_SIMD("/home/jebali/Bureau/EISE5/HPC/projetHPC/car3/resized_car_3", "/home/jebali/Bureau/EISE5/HPC/projetHPC/Resultat_SIMD/resized_car_3");
	clock_t end = clock();

	temps_exec = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", temps_exec);
}

void benchmark(void){
	int nrl = 0;
	int nrh = 240;
	int ncl = 0;
	int nch = 320;
	for(int i = 0; i < 6; i++){
		printf("images de tailles: %d %d\n", nrh, nch);
		resize(nrl, nrh-1, ncl, nch-1);
		chrono(nrl, nrh-1, ncl, nch-1);
		nrh = nrh*2;;
		nch = nch*2;
	}
}
