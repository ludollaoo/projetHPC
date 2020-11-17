#include "main.h"

int main(void){

	//SD_sequentielle(0, 239, 0, 319, 200, 4, "/home/ludovic/HPC/Projet/car3/car_3", 1);
	//test_SD_sequentielle();
	//test_SIMD();
	//SD_SIMD(0, 239, 0, 319, 200, 4, "/home/ludovic/HPC/Projet/car3/car_3", 1);
	//SD_sequentielle_2(0, 239, 0, 319, 200, 4, "/home/ludovic/HPC/Projet/car3/car_3");
	//SD_SIMD_2(0, 239, 0, 319, 200, 4, "/home/ludovic/HPC/Projet/car3/car_3");
	//SD_SIMD_opti_2(0, 239, 0, 319, 200, 4, "/home/ludovic/HPC/Projet/car3/car_3");
	SD_SIMD_opti_openMP_2(0, 239, 0, 319, 200, 4, "/home/ludovic/HPC/Projet/car3/car_3");
}
