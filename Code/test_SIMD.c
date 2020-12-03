#include <stddef.h>
#include "../include/main.h"

//void (*ero[6])(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y) = {erosion3_simd,erosion5_simd,erosion3_rot_simd,erosion5_rot_simd,erosion3_rot_LU_simd};

//void (*dila[6])(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y) = {dilatation3_simd,dilatation5_simd,dilatation3_rot_simd,dilatation5_rot_simd,dilatation3_rot_LU_simd};

int compare(vuint8 vecteur0)
{
    vuint8 x0 = vecteur0;
    uint8 *px0 = &x0;  
    for(int i = 1; i <= 16; i++){
        if(*px0 == 0) return 0; 
        px0 += sizeof(uint8);
    }
    return 1;
}

vuint8 init_vuint8_test(int j, int valeur)
/* ---------------------------------------- */
{
    int i;
    vuint8 T[1];
    uint8 *p = (uint8*) T;
    uint8 x0 = valeur;
    for(i=0; i<16; i++) {
        p[i] = x0;
    }
    p[j] = abs(1-valeur);
    return T[0];
}

void init_vuint8_traitement(vuint8 ** m, int j, int valeur)
/* ---------------------------------------- */
{
    int i;
    vuint8 T[1];
    uint8 *p = (uint8*) T;
    uint8 x0 = valeur;
    for(i=0; i<16; i++) {
        p[i] = x0;
    }
    p[j] = abs(1-valeur);
    if(j == 0) p[j+1] = abs(1-valeur);
    else if(j == 15) p[j-1] = abs(1-valeur);
    else{
        p[j-1] = abs(1-valeur);
        p[j+1] = abs(1-valeur);
    }
    _mm_store_si128(&m[0][0], T[0]);
}

void init_vui8matrix_test(vuint8 **m, int i0, int i1, int j0, int j1, int k, int l, int indice, int valeur)
/* ---------------------------------------------------------- */
{
    int i, j;
    vuint8 x, x0 = init_vuint8_param(valeur, 0);
    vuint8 xstep = init_vuint8_test(indice, valeur);
    
    for(i=i0; i<=i1; i++) {
        x = x0;
        for(j=j0; j<=j1; j++) {
            _mm_store_si128(&m[i][j], x);
        }
    }
    _mm_store_si128(&m[k][l], xstep);
}

void test2D_SIMD(void){
    // Matrice uint8 test
    int b = 1;
    int l = 1;
 	int nrlY, nrhY, nclY, nchY;
    int nrl, nrh, ncl, nch;
 	int nrlb, nrhb, nclb, nchb; //with border
    nrl = 0*l;
    nrh = 0*l;
    ncl = 0*l;
    nch = 15*l;
    int card = card = card_vuint8();
    
    int valeur_dila = 0;
    int valeur_ero = 1;
    uint8 pixel_courant = 1;


    s2v(nrl-b, nrh+b, ncl-b, nch+b, card, &nrlb, &nrhb, &nclb, &nchb);
    s2v(nrl, nrh, ncl, nch, card, &nrlY, &nrhY, &nclY, &nchY);
    vuint8** padding = vui8matrix(nrlb, nrhb, nclb, nchb);
    init_vui8matrix(padding, nrlb, nrhb, nclb, nchb);
    display_vui8matrix(padding, nrlb, nrhb, nclb, nchb, "%3d", "padding\n");
    
    vuint8** expected_res_ero = vui8matrix(nrlY, nrhY, nclY, nchY);
    vuint8** expected_res_dila = vui8matrix(nrlY, nrhY, nclY, nchY);

    vuint8** traitement = vui8matrix(nrlY, nrhY, nclY, nchY);
    display_vui8matrix(traitement, nrlY, nrhY, nclY, nchY, "%3d", "traitement\n");
    erosion3_simd(padding, nrlY, nrhY, nclY, nchY, traitement);   
    display_vui8matrix(traitement, nrlY, nrhY, nclY, nchY, "%3d", "traitement\n");
    for(int i = nrlb; i <= nrhb; i++){
        printf("TEST EROSION\n");
        for(int k = 0; k < 16; k++){

            init_vui8matrix_test(padding, nrlb, nrhb, nclb, nchb, i, 0, k, valeur_ero);
            display_vui8matrix(padding, nrlb, nrhb, nclb, nchb, "%3d", "padding\n");
            erosion3_simd(padding, nrlY, nrhY, nclY, nchY, traitement);
            init_vuint8_traitement(expected_res_ero, k, valeur_ero);
            display_vui8matrix(expected_res_ero, nrlY, nrhY, nclY, nchY, "%3d", "expected_ero\n");
            display_vui8matrix(traitement, nrlY, nrhY, nclY, nchY, "%3d", "traitement\n");
            if(compare(_mm_cmpeq_epi8(traitement[0][0], expected_res_ero[0][0])) == 1) printf("OK\n");
            else{
                printf("KO\n");
                exit( EXIT_FAILURE );
            }
        }
        printf("TEST DILATATION\n");
        for(int k = 0; k < 16; k++){
        //printf("TEST DILATATION\n");
    
            init_vui8matrix_test(padding, nrlb, nrhb, nclb, nchb, i, 0, k, valeur_dila);
            display_vui8matrix(padding, nrlb, nrhb, nclb, nchb, "%3d", "padding\n");
            dilatation3_simd(padding, nrlY, nrhY, nclY, nchY, traitement);
            init_vuint8_traitement(expected_res_ero, k, valeur_dila);
            display_vui8matrix(expected_res_ero, nrlY, nrhY, nclY, nchY, "%3d", "expected_ero\n");
            display_vui8matrix(traitement, nrlY, nrhY, nclY, nchY, "%3d", "traitement\n");
            if(compare(_mm_cmpeq_epi8(traitement[0][0], expected_res_ero[0][0])) == 1) printf("OK\n");
            else{
                printf("KO\n");
                exit( EXIT_FAILURE );
            }
        }
    } 
}     

