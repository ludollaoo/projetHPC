#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "../include/nrdef.h"
#include "../include/nrutil.h"

#include "../include/vnrdef.h"
#include "../include/vnrutil.h"

#include "../include/mutil.h"

#include "../include/mymacro.h"
#include "../include/simd_macro.h"

// Decalage a gauche
/*
vuint8 _mm_left1(vuint8 vecteur0, vuint8 vecteur1)
{
    vuint8 x0 = vecteur0;
    vuint8 x1 = vecteur1;

    uint8 *px0 = &x0;
    uint8 * px1 = &x1;   
    x1 = _mm_slli_si128(x1, 1);
    
    px0 += 15;
    *px1 = *px0;
    
    return x1;
}

// Deacalage à droite
vuint8 _mm_right1(vuint8 vecteur1, vuint8 vecteur2)
{
    vuint8 x1 = vecteur1;
    vuint8 x2 = vecteur2;

    uint8 *px1 = &x1;
    uint8 *px2 = &x2;   
    x1 = _mm_srli_si128(x1, 1);
    
    px1 += 15;
    *px1 = *px2;
    
    return x1;
}
*/

void copy_ui8matrix_vui8matrix_padding_binaire(uint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
/* -----------------------------------------------------------------------------*/ 
{

    int i, j;
    vuint8 T[1];
    int taille_uint8;
    uint8 *temp = (uint8*) T;
    for(i = i0; i <= i1 ; i++){
        for(j = j0; j <= j1; j++){
            _mm_store_si128(T, Y[i][j]);
            taille_uint8 = 0;
            for(int k = j*16; k < (j*16)+16; k++){
                temp[taille_uint8] = X[i][k]>>7;
                taille_uint8++;
            }
            _mm_store_si128(&Y[i][j], T[0]);
        }
    }
}

void copy_vui8matrix_ui8matrix_padding_binaire(vuint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* -----------------------------------------------------------------------------
*/
{

    int i, j;
    vuint8 T[1];
    uint8* temp = (uint8*) T;
    for(i = i0; i <= i1 ; i++){
        for(j = j0; j <= j1; j++){
            _mm_store_si128(T, X[i][j]);
            temp = (uint8*) T;
            for(int k = j*16; k < (j*16)+16; k++){
                Y[i][k] = (*temp)*255;
                temp++;
            }
        }
    }
}

void init_uint8matrix(int chiffre, int i0, int i1, int j0, int j1, uint8 **Y)
/* ----------------------------------------------------------------------------- */
{
    int i, j;

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            Y[i][j] = 1;
        }
    }
}
