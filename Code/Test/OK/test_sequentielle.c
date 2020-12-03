#include <stddef.h>
#include "../include/main.h"

void test2D_sequentiel(void){
    // Matrice uint8 test
    int k = 1;
    int nrl, nrh, ncl, nch;
    nrl = 0*k;
    nrh = 2*k;
    ncl = 0*k;
    nch = 2*k;

    int expected_res = 0;

    uint8** image_courante = ui8matrix(nrl, nrh, ncl, nch);
	uint8** padding = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);

    init_uint8matrix(1, nrl-2, nrh+2, ncl-2, nch+2, padding);
    DEBUG(display_ui8matrix(padding, nrl-2, nrh+2, ncl-2,  nch+2, "%d", "padding")); DEBUG(puts(""));
    
    /*for(int i = nrl; i <= nrh; i++){
        for(int j = ncl; j < nch; j++){
            init_uint8matrix(1, nrl, nrh, ncl, nch, padding);
        }
    }*/
    
}
