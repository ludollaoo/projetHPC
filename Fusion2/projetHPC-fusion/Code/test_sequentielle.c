#include <stddef.h>
#include "../include/main.h"

void test2D_sequentiel(void){
    // Matrice uint8 test
    int l = 2;
    int nrl, nrh, ncl, nch;
    nrl = 0*l;
    nrh = 2*l;
    ncl = 0*l;
    nch = 2*l;

    int expected_res_ero = 0;
    int expected_res_dila = 1;

    uint8 pixel_courant = 1;
	uint8** padding = ui8matrix(nrl, nrh, ncl, nch);

    init_uint8matrix(1, nrl, nrh, ncl, nch, padding);
    // Test erosion
    printf("Test Erosion\n");
    for(int k = 1; k <= 2; k++){
        nrl = 0*k;
        nrh = 2*k;
        ncl = 0*k;
        nch = 2*k;
        padding = ui8matrix(nrl, nrh, ncl, nch);
        init_uint8matrix(1, nrl, nrh, ncl, nch, padding);

        for(int i = nrl; i <= nrh; i++){
            for(int j = ncl; j <= nch; j++){
                padding[i][j] = 0;
                display_ui8matrix(padding, nrl, nrh, ncl,  nch, "%d", "padding_ero");
                pixel_courant = erosion_dilatation(k, 0, padding, k, k);
                if(pixel_courant == expected_res_ero) printf("OK\n"); 
                else {
                    printf("KO\n");
                    exit( EXIT_FAILURE );
                }   
                padding[i][j] = 1; 
            }
        }
    // Test dilatation
        printf("\n");
        printf("Test Dilatation\n");
        pixel_courant = 0;
        init_uint8matrix(0, nrl, nrh, ncl, nch, padding);
        for(int i = nrl; i <= nrh; i++){
            for(int j = ncl; j <= nch; j++){
                padding[i][j] = 1;
                display_ui8matrix(padding, nrl, nrh, ncl,  nch, "%d", "padding_dila");
                pixel_courant = erosion_dilatation(k, 1, padding, k, k);
                if(pixel_courant == expected_res_dila)  printf("OK\n"); 
                else{
                    printf("KO\n");
                    exit( EXIT_FAILURE );
                }
                padding[i][j] = 0; 
            }
        }   
    }   
}
