#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "../include/nrdef.h"
#include "../include/nrutil.h"

#include "../include/vnrdef.h"
#include "../include/vnrutil.h"

#include "../include/mutil.h"

#include "../include/simd2D.h"
#include "../include/mymacro.h"
#include "../include/simd_macro.h"


#define threshold 10

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
void erosion3_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
// --------------------------------------------------------
{
    int i, j;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    vuint8 aa0, cc0;
    vuint8 aa1, cc1;
    vuint8 aa2, cc2;

    vuint8 y;
    
    // CODE A COMPLETER
    for(i = nrl; i <= nrh; i++)
    {
        for(j = ncl; j <= nch; j++)
        {
            // Initialisation 
            a0 = vec_load2(X, i-1, j-1);
            b0 = vec_load2(X, i-1, j+0);
            c0 = vec_load2(X, i-1, j+1);

            a1 = vec_load2(X, i-0, j-1);
            b1 = vec_load2(X, i-0, j+0);
            c1 = vec_load2(X, i-0, j+1);

            a2 = vec_load2(X, i+1, j-1);
            b2 = vec_load2(X, i+1, j+0);
            c2 = vec_load2(X, i+1, j+1);
        
            // Décalage a droite et à gauche
            aa0 = vec_left1(a0, b0); 
            cc0 = vec_right1(b0, c0); 
            aa1 = vec_left1(a1, b1); 
            cc1 = vec_right1(b1, c1); 
            aa2 = vec_left1(a2, b2); 
            cc2 = vec_right1(b2, c2); 

            // Moyennage
            y = vec_and3(vec_and3(aa0, b0, cc0), vec_and3(aa1, b1, cc1), vec_and3(aa2, b2, cc2));
            vec_store2(Y, i, j, y);
        }
    }
}

void erosion3_rot_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
// --------------------------------------------------------
{
    int i, j;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    vuint8 aa0, cc0;
    vuint8 aa1, cc1;
    vuint8 aa2, cc2;

    vuint8 ra, rb, rc;
    vuint8 y;
    
    // CODE A COMPLETER
    for(i = nrl; i <= nrh; i++)
    {
        j=0;
    // rotation de registre code scalarisé
        a0 = vec_load2(X, i-1, j-1);
        b0 = vec_load2(X, i-1, j+0);

        a1 = vec_load2(X, i-0, j-1);
        b1 = vec_load2(X, i-0, j+0);

        a2 = vec_load2(X, i+1, j-1);
        b2 = vec_load2(X, i+1, j+0);

        for(j = ncl; j <= nch; j++)
        {
            // Initialisation 
            c0 = vec_load2(X, i-1, j+1);
            c1 = vec_load2(X, i-0, j+1);
            c2 = vec_load2(X, i+1, j+1);
        
            // Décalage a droite et à gauche
            aa0 = vec_left1(a0, b0);
            cc0 = vec_right1(b0, c0); 
            aa1 = vec_left1(a1, b1); 
            cc1 = vec_right1(b1, c1); 
            aa2 = vec_left1(a2, b2); 
            cc2 = vec_right1(b2, c2); 

            ra = vec_and3(aa0, b0, cc0);  // operateur Colonne
            rb = vec_and3(aa1, b1, cc1);
            rc = vec_and3(aa2, b2, cc2);

            // Moyennage
            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j, y);

            // rotation de regisre
            a0 = b0;
            b0 = c0;

            a1 = b1;
            b1 = c1;

            a2 = b2;
            b2 = c2;
        }
    }
}

void dilatation3_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
// --------------------------------------------------------
{
    int i, j;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    vuint8 aa0, cc0;
    vuint8 aa1, cc1;
    vuint8 aa2, cc2;

    vuint8 y;
    
    // CODE A COMPLETER
    for(i = nrl; i <= nrh; i++)
    {
        j=0;
    // rotation de registre code scalarisé
        a0 = vec_load2(X, i-1, j-1);
        b0 = vec_load2(X, i-1, j+0);

        a1 = vec_load2(X, i-0, j-1);
        b1 = vec_load2(X, i-0, j+0);

        a2 = vec_load2(X, i+1, j-1);
        b2 = vec_load2(X, i+1, j+0);

        for(j = ncl; j <= nch; j++)
        {
            // Initialisation 
            c0 = vec_load2(X, i-1, j+1);
            c1 = vec_load2(X, i-0, j+1);
            c2 = vec_load2(X, i+1, j+1);
        
            // Décalage a droite et à gauche
            aa0 = vec_left1(a0, b0); 
            cc0 = vec_right1(b0, c0); 
            aa1 = vec_left1(a1, b1); 
            cc1 = vec_right1(b1, c1); 
            aa2 = vec_left1(a2, b2); 
            cc2 = vec_right1(b2, c2); 

            // Moyennage
            y = vec_or3(vec_or3(aa0, b0, cc0), vec_or3(aa1, b1, cc1), vec_or3(aa2, b2, cc2));
            vec_store2(Y, i, j, y);

            a0 = b0;
            b0 = c0;

            a1 = b1;
            b1 = c1;

            a2 = b2;
            b2 = c2;
        }
    }
}

void dilatation3_rot_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
// --------------------------------------------------------
{
    int i, j;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    vuint8 aa0, cc0;
    vuint8 aa1, cc1;
    vuint8 aa2, cc2;

    vuint8 y;
    
    // CODE A COMPLETER
    for(i = nrl; i <= nrh; i++)
    {
        j=0;
    // rotation de registre code scalarisé
        a0 = vec_load2(X, i-1, j-1);
        b0 = vec_load2(X, i-1, j+0);

        a1 = vec_load2(X, i-0, j-1);
        b1 = vec_load2(X, i-0, j+0);

        a2 = vec_load2(X, i+1, j-1);
        b2 = vec_load2(X, i+1, j+0);

        for(j = ncl; j <= nch; j++)
        {
            // Initialisation 
            c0 = vec_load2(X, i-1, j+1);
            c1 = vec_load2(X, i-0, j+1);
            c2 = vec_load2(X, i+1, j+1);
        
            // Décalage a droite et à gauche
            aa0 = vec_left1(a0, b0); 
            cc0 = vec_right1(b0, c0); 
            aa1 = vec_left1(a1, b1); 
            cc1 = vec_right1(b1, c1); 
            aa2 = vec_left1(a2, b2); 
            cc2 = vec_right1(b2, c2); 

            // Moyennage
            y = vec_or3(vec_or3(aa0, b0, cc0), vec_or3(aa1, b1, cc1), vec_or3(aa2, b2, cc2));
            vec_store2(Y, i, j, y);

            a0 = b0;
            b0 = c0;

            a1 = b1;
            b1 = c1;

            a2 = b2;
            b2 = c2;
        }
    }
}

void dilatation_erosion3_pipeline_rot_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
// --------------------------------------------------------
{
    int i, j;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    vuint8 a02, b02, c02;
    vuint8 a12, b12, c12;
    vuint8 a22, b22, c22;

    vuint8 aa0, cc0;
    vuint8 aa1, cc1;
    vuint8 aa2, cc2;

    vuint8** padding2 = vui8matrix(nrl-2, nrh+2, ncl-1, nch+1);

    vuint8 ra, rb, rc;
    vuint8 y;
    
    // Prologue
    for(i = nrl; i <= nrl+2; i++)
    {
        j=0;
    // rotation de registre code scalarisé
        a0 = vec_load2(X, i-1, j-1);
        b0 = vec_load2(X, i-1, j+0);

        a1 = vec_load2(X, i-0, j-1);
        b1 = vec_load2(X, i-0, j+0);

        a2 = vec_load2(X, i+1, j-1);
        b2 = vec_load2(X, i+1, j+0);

        for(j = ncl; j <= nch; j++)
        {
            // Initialisation 
            c0 = vec_load2(X, i-1, j+1);
            c1 = vec_load2(X, i-0, j+1);
            c2 = vec_load2(X, i+1, j+1);
        
            // Décalage a droite et à gauche
            aa0 = vec_left1(a0, b0); 
            cc0 = vec_right1(b0, c0); 
            aa1 = vec_left1(a1, b1); 
            cc1 = vec_right1(b1, c1); 
            aa2 = vec_left1(a2, b2); 
            cc2 = vec_right1(b2, c2); 

            // Moyennage
            y = vec_or3(vec_or3(aa0, b0, cc0), vec_or3(aa1, b1, cc1), vec_or3(aa2, b2, cc2));
            vec_store2(padding2, i, j, y);

            a0 = b0;
            b0 = c0;

            a1 = b1;
            b1 = c1;

            a2 = b2;
            b2 = c2;
        }
    }
    
    // Debut boucle
    for(i = nrl+2; i <= nrh; i++)
    {
        j=ncl;
        a0 = vec_load2(X, i-1, j-1);
        b0 = vec_load2(X, i-1, j+0);

        a1 = vec_load2(X, i-0, j-1);
        b1 = vec_load2(X, i-0, j+0);

        a2 = vec_load2(X, i+1, j-1);
        b2 = vec_load2(X, i+1, j+0);

        b02 = vec_load2(padding2, i-3, j);
        b12 = vec_load2(padding2, i-2, j);
        b22 = vec_load2(padding2, i-1, j);

        a02 = vec_load2(padding2, i-3, j-1);
        a12 = vec_load2(padding2, i-2, j-1);
        a22 = vec_load2(padding2, i-1, j-1);

        for(j = ncl; j <= nch; j++)
        {
            // Initialisation 
            
            c0 = vec_load2(X, i-1, j+1);
            c1 = vec_load2(X, i-0, j+1);
            c2 = vec_load2(X, i+1, j+1);
        
            // Décalage a droite et à gauche
            aa0 = vec_left1(a0, b0);
            cc0 = vec_right1(b0, c0); 
            aa1 = vec_left1(a1, b1); 
            cc1 = vec_right1(b1, c1); 
            aa2 = vec_left1(a2, b2); 
            cc2 = vec_right1(b2, c2); 

            ra = vec_and3(aa0, b0, cc0);  // operateur Colonne
            rb = vec_and3(aa1, b1, cc1);
            rc = vec_and3(aa2, b2, cc2);

            // Moyennage
            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j, y);
           
            c02 = vec_load2(padding2, i-3, j+1);
            c12 = vec_load2(padding2, i-2, j+1);
            c22 = vec_load2(padding2, i-1, j+1);

            aa0 = vec_left1(a02, b02);
            cc0 = vec_right1(b02, c02); 
            aa1 = vec_left1(a12, b12); 
            cc1 = vec_right1(b12, c12); 
            aa2 = vec_left1(a22, b22); 
            cc2 = vec_right1(b22, c22); 

            ra = vec_or3(aa0, b02, cc0);  // operateur Colonne
            rb = vec_or3(aa1, b12, cc1);
            rc = vec_or3(aa2, b22, cc2);

            // Moyennage
            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i-2, j, y);
            
            a0 = b0;
            b0 = c0;
            a1 = b1;
            b1 = c1;
            a2 = b2;
            b2 = c2;

            a02 = b02;
            b02 = c02;
            a12 = b12;
            b12 = c12;
            a22 = b22;
            b22 = c22;
   
        }
    }
      // epilogue
      for(i = nrh-2; i <= nrh; i++)
    {
        j=ncl;
        b0 = vec_load2(padding2, i-1, j);
        b1 = vec_load2(padding2, i-0, j);
        b2 = vec_load2(padding2, i+1, j);

        a0 = vec_load2(padding2, i-1, j-1);
        a1 = vec_load2(padding2, i-0, j-1);
        a2 = vec_load2(padding2, i+1, j-1);

        for(j = ncl; j <= nch; j++)
        {
            c0 = vec_load2(padding2, i-1, j+1);
            c1 = vec_load2(padding2, i-0, j+1);
            c2 = vec_load2(padding2, i+1, j+1);

            aa0 = vec_left1(a0, b0);
            cc0 = vec_right1(b0, c0); 
            aa1 = vec_left1(a1, b1); 
            cc1 = vec_right1(b1, c1); 
            aa2 = vec_left1(a2, b2); 
            cc2 = vec_right1(b2, c2); 

            ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, b1, cc1);
            rc = vec_or3(aa2, b2, cc2);

            // Moyennage
            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j, y);

            a0 = b0;
            b0 = c0;

            a1 = b1;
            b1 = c1;

            a2 = b2;
            b2 = c2;
        }
    }
    free_vui8matrix(padding2, nrl-2, nrh+2, ncl-1, nch+1);
}

//----------------Filtre 5x5-------------------------------
void erosion5_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
// --------------------------------------------------------
{
    int i, j;
    vuint8 a0, b0, c0, d0, e0; 
    vuint8 a1, b1, c1, d1, e1;
    vuint8 a2, b2, c2, d2, e2;
    vuint8 a3, b3, c3, d3, e3;
    vuint8 a4, b4, c4, d4, e4;

    vuint8 aa0, aa1, aa3, aa4; // registres non alignes ligne 1
    vuint8 bb0, bb1, bb3, bb4; // registres non alignes ligne 2
    vuint8 cc0, cc1, cc3, cc4; // registres non alignes ligne 3
    vuint8 dd0, dd1, dd3, dd4; // registres non alignes ligne 4
    vuint8 ee0, ee1, ee3, ee4; // registres non alignes ligne 5

    vuint8 y;
    
    // CODE A COMPLETER
    for(i = nrl; i <= nrh; i++)
    {
        j=ncl;
 
        a0 = vec_load2(X, i-2, j-1);
        b0 = vec_load2(X, i-2, j+0);

        a1 = vec_load2(X, i-1, j-1);
        b1 = vec_load2(X, i-1, j+0);

        a2 = vec_load2(X, i+0, j-1);
        b2 = vec_load2(X, i+0, j+0);

        a3 = vec_load2(X, i+1, j-1);
        b3 = vec_load2(X, i+1, j+0);

        a4 = vec_load2(X, i+2, j-1);
        b4 = vec_load2(X, i+2, j+0);


        for(j = ncl; j <= nch; j++)
        {
            // Initialisation

            c0 = vec_load2(X, i-2, j+1);
            c1 = vec_load2(X, i-1, j+1);
            c2 = vec_load2(X, i+0, j+1);
            c3 = vec_load2(X, i+1, j+1);
            c4 = vec_load2(X, i+2, j+1);
        
            // Décalage a droite et à gauche
            aa1 = vec_left1(a0, b0); 
            aa3 = vec_right1(b0, c0); 
            bb1 = vec_left1(a1, b1); 
            bb3 = vec_right1(b1, c1); 
            cc1 = vec_left1(a2, b2); 
            cc3 = vec_right1(b2, c2); 
            dd1 = vec_left1(a3, b3); 
            dd3 = vec_right1(b3, c3); 
            ee1 = vec_left1(a4, b4); 
            ee3 = vec_right1(b4, c4);

            aa0 = vec_left2(a0, b0);  
            aa4 = vec_right2(b0, c0); 
            bb0 = vec_left2(a1, b1); 
            bb4 = vec_right2(b1, c1); 
            cc0 = vec_left2(a2, b2); 
            cc4 = vec_right2(b2, c2); 
            dd0 = vec_left2(a3, b3); 
            dd4 = vec_right2(b3, c3); 
            ee0 = vec_left2(a4, b4); 
            ee4 = vec_right2(b4, c4);

            // Moyennage
            y = vec_and5(vec_and5(aa0, aa1, b0, aa3, aa4), vec_and5(bb0, bb1, b1, bb3, bb4), vec_and5(cc0, cc1, b2, cc3, cc4), vec_and5(dd0, dd1, b3, dd3, dd4), vec_and5(ee0, ee1, b4, ee3, ee4));
            vec_store2(Y, i, j, y);

            a0 = b0;
            b0 = c0;

            a1 = b1;
            b1 = c1;

            a2 = b2;
            b2 = c2;
            
            a3 = b3;
            b3 = c3;

            a4 = b4;
            b4 = c4;


        }
    }
}

void dilatation5_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
// --------------------------------------------------------
{
    int i, j;
    vuint8 a0, b0, c0, d0, e0; 
    vuint8 a1, b1, c1, d1, e1;
    vuint8 a2, b2, c2, d2, e2;
    vuint8 a3, b3, c3, d3, e3;
    vuint8 a4, b4, c4, d4, e4;

    vuint8 aa0, aa1, aa3, aa4; // registres non alignes ligne 1
    vuint8 bb0, bb1, bb3, bb4; // registres non alignes ligne 2
    vuint8 cc0, cc1, cc3, cc4; // registres non alignes ligne 3
    vuint8 dd0, dd1, dd3, dd4; // registres non alignes ligne 4
    vuint8 ee0, ee1, ee3, ee4; // registres non alignes ligne 5

    vuint8 y;
    
    // CODE A COMPLETER
    for(i = nrl; i <= nrh; i++)
    {
        for(j = ncl; j <= nch; j++)
        {
            // Initialisation 
            a0 = vec_load2(X, i-2, j-1);
            b0 = vec_load2(X, i-2, j+0);
            c0 = vec_load2(X, i-2, j+1);

            a1 = vec_load2(X, i-1, j-1);
            b1 = vec_load2(X, i-1, j+0);
            c1 = vec_load2(X, i-1, j+1);

            a2 = vec_load2(X, i+0, j-1);
            b2 = vec_load2(X, i+0, j+0);
            c2 = vec_load2(X, i+0, j+1);

            a3 = vec_load2(X, i+1, j-1);
            b3 = vec_load2(X, i+1, j+0);
            c3 = vec_load2(X, i+1, j+1);

            a4 = vec_load2(X, i+2, j-1);
            b4 = vec_load2(X, i+2, j+0);
            c4 = vec_load2(X, i+2, j+1);
        
            // Décalage a droite et à gauche
            aa1 = vec_left1(a0, b0); 
            aa3 = vec_right1(b0, c0); 
            bb1 = vec_left1(a1, b1); 
            bb3 = vec_right1(b1, c1); 
            cc1 = vec_left1(a2, b2); 
            cc3 = vec_right1(b2, c2); 
            dd1 = vec_left1(a3, b3); 
            dd3 = vec_right1(b3, c3); 
            ee1 = vec_left1(a4, b4); 
            ee3 = vec_right1(b4, c4);

            aa0 = vec_left2(a0, b0); 
            aa4 = vec_right2(b0, c0); 
            bb0 = vec_left2(a1, b1); 
            bb4 = vec_right2(b1, c1); 
            cc0 = vec_left2(a2, b2); 
            cc4 = vec_right2(b2, c2); 
            dd0 = vec_left2(a3, b3); 
            dd4 = vec_right2(b3, c3); 
            ee0 = vec_left2(a4, b4); 
            ee4 = vec_right2(b4, c4);

            // Moyennage
            y = vec_or5(vec_or5(aa0, aa1, b0, aa3, aa4), vec_or5(bb0, bb1, b1, bb3, bb4), vec_or5(cc0, cc1, b2, cc3, cc4), vec_or5(dd0, dd1, b3, dd3, dd4), vec_or5(ee0, ee1, b4, ee3, ee4));
            vec_store2(Y, i, j, y);
        }
    }
}

void copy_ui8matrix_vui8matrix_padding_binaire(uint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
/* -----------------------------------------------------------------------------*/ 
{

    int i, j;
    vuint8 T[1];
    uint8 *temp = (uint8*) T;
    for(i = i0; i <= i1 ; i++){
        for(j = j0; j <= j1; j++){
            _mm_store_si128(T, Y[i][j]);
            //DEBUG(display_vuint8(T[0], "%3d", "T[0]\n")); DEBUG(puts(""));
            //printf("ok i = %d, j = %d\n", i, j);
            int taille_uint8 = 0;
            for(int k = j*16; k < (j*16)+16; k++){
                temp[taille_uint8] = X[i][k]>>7;
                taille_uint8++;
            }
            //printf("taille_unint8 = %d\n",taille_uint8);
            //DEBUG(display_vuint8(T[0], "%3d", "T[0]\n")); DEBUG(puts(""));
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
    //printf("nrlY = %dY, nrhY = %d, nclY = %d, nchY = %d\n", i0, i1, j0, j1);
    for(i = i0; i <= i1 ; i++){
        for(j = j0; j <= j1; j++){
            _mm_store_si128(T, X[i][j]);
            temp = (uint8*) T;
            //DEBUG(display_vuint8(T[0], "%3d", "T[0]\n")); DEBUG(puts(""));
            //printf("ok i = %d, j = %d\n", i, j);
            //int taille_uint8 = 0;
            //printf("ok ligne = %3d, colonne = %3d\n", i, j);
            for(int k = j*16; k < (j*16)+16; k++){
                Y[i][k] = (*temp)*255;
                //printf("ok k = %4d  ", k);
                //taille_uint8++;
                temp++;
            }
            //printf("\n");
            //printf("taille_unint8 = %d\n",taille_uint8);
            //DEBUG(display_vuint8(T[0], "%3d", "T[0]\n")); DEBUG(puts(""));
            
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

//taille kernel: 1 pour kernel 3x3, 2 pour 5x5 et traitement: 255 pour dilatation et 0  pour erosion	
 void traitement3_SIMD(){
 	printf("Lancement de l'algorithme de dilatation SIMD\n");

 	int nrl, nrh, ncl, nch;
 	int nrlY, nrhY, nclY, nchY;
 	int nrlb, nrhb, nclb, nchb; //with border
	int img_nbr = 2;
	char nom_img[100];
	char nom_res[100];
    char *format = "%d ";
    int card = card = card_vuint8();
    int b = 2;
    //uint8** image_courante = ui8matrix(nrl, nrh, ncl, nch);
    //init_uint8matrix(1, nrl, nrh, ncl, nch, image_courante);
	uint8 pixel_courant;
    //printf("%d\n",1 | 1);

    //--------------------------- upload image en format uint8**------------------------------------
	uint8** image_courante = LoadPGM_ui8matrix("/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat/image_test3001", &nrl, &nrh, &ncl, &nch);

    //-------------------calcul parametre pour matrice de format vuint8** ---------------------------
    s2v(nrl-b, nrh+b, ncl-b, nch+b, card, &nrlb, &nrhb, &nclb, &nchb);
    s2v(nrl, nrh, ncl, nch, card, &nrlY, &nrhY, &nclY, &nchY);
    //----------------------Déclaration matrice SIMD -------------------------------
	vuint8** padding = vui8matrix(nrlb, nrhb, nclb, nchb);

    // ----------------------Initialisation à zero------------------------------------
	//zero_vui8matrix(padding,  nrlb, nrhb, nclb, nchb);
    //printf("nrl = %d, nrh = %d, ncl = %d, nch = %d\n", nrl, nrh, ncl, nch);
    //printf("nrlb = %d, nrhb = %d, nclb = %d, nchb = %d\n", nrlb, nrhb, nclb, nchb);

    //--------------copie de image_courant vers padding : 1ere ligne------------------------
    copy_ui8matrix_vui8matrix_padding_binaire(image_courante, nrlY, nrhY, nclY, nchY, padding);

    //DEBUG(display_vui8matrix(padding,  nrlb, nrhb, nclb, nchb, format, "padding"));
    //DEBUG(display_ui8matrix(image_courante, nrl, nrh, ncl, nch, "%d", "image_courante\n")); DEBUG(puts(""));
    //padding[0][0] = _mm_add_epi8(padding[0][0], image_courante[0][0]);

    //--------------------------creation matrice Y -----------------------------
    vuint8** traitement = vui8matrix(nrlY, nrhY, nclY, nchY);
    //printf("nrlY = %d, nrhY = %d, nclY = %d, nchY = %d\n", nrlY, nrhY, nclY, nchY);

    //--------------------------Creation padding2 de meme taille taille que padding --------------------------------
    //vuint8** padding2 = vui8matrix(nrlb, nrhb, nclb, nchb);

    // ---------------------------erosion SIMD----------------------------------
    dilatation_erosion3_pipeline_rot_simd(padding, nrlY, nrhY, nclY, nchY, traitement);
    //erosion3_simd(padding, nrlY, nrhY, nclY, nchY, padding2);
    //dilatation3_simd(padding2, nrlY, nrhY, nclY, nchY, traitement);
    //dilatation3_simd(padding, nrlY, nrhY, nclY, nchY, padding2);
    //erosion3_simd(padding2, nrlY, nrhY, nclY, nchY, traitement);
    //--------------- copie de traitement vers image courante ---------------------------------
    copy_vui8matrix_ui8matrix_padding_binaire(traitement, nrlY, nrhY, nclY, nchY, image_courante);
    // -------- Store de l'image ------------
    sprintf(nom_res, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/ResultatSIMD/image_dilatation3%03d", 1);
	SavePGM_ui8matrix(image_courante, nrl, nrh, ncl, nch, nom_res);
    
    for (img_nbr; img_nbr < 200; img_nbr++){

		//Chargement d'une image après traitement par SD
		sprintf(nom_img, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/Resultat/image_test3%03d", img_nbr);
		image_courante = LoadPGM_ui8matrix( nom_img, &nrl, &nrh, &ncl, &nch);

        //-------------------calcul parametre pour matrice de format vuint8** ---------------------------
        s2v(nrl-b, nrh+b, ncl-b, nch+b, card, &nrlb, &nrhb, &nclb, &nchb);
        s2v(nrl, nrh, ncl, nch, card, &nrlY, &nrhY, &nclY, &nchY);
        //----------------------Déclaration matrice SIMD -------------------------------
	    padding = vui8matrix(nrlb, nrhb, nclb, nchb);

        // ----------------------Initialisation à zero------------------------------------
	    //zero_vui8matrix(padding,  nrlb, nrhb, nclb, nchb);

        //--------------copie de image_courant vers padding : 1ere ligne------------------------
        copy_ui8matrix_vui8matrix_padding_binaire(image_courante, nrl, nrh, nclb, nchb, padding);

        //--------------------------creation matrice Y -----------------------------
        traitement = vui8matrix(nrlY, nrhY, nclY, nchY);
        
        // ---------------------------erosion SIMD----------------------------------
        dilatation_erosion3_pipeline_rot_simd(padding, nrlY, nrhY, nclY, nchY, traitement);
        //erosion3_simd(padding, nrlY, nrhY, nclY, nchY, padding2);
        //dilatation3_simd(padding2, nrlY, nrhY, nclY, nchY, traitement);
        //dilatation3_simd(padding, nrlY, nrhY, nclY, nchY, padding2);
        //erosion3_simd(padding2, nrlY, nrhY, nclY, nchY, traitement);
        //--------------- copie de traitement vers image courante ---------------------------------
        copy_vui8matrix_ui8matrix_padding_binaire(traitement, nrlY, nrhY, nclY, nchY, image_courante);
        // -------- Store de l'image ------------
        sprintf(nom_res, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/ResultatSIMD/image_dilatation3%03d", img_nbr);
	    SavePGM_ui8matrix(image_courante, nrl, nrh, ncl, nch, nom_res);
		
	}
    free_vui8matrix(padding, nrlb, nrhb, nclb, nchb);
    //free_vui8matrix(padding2, nrlb, nrhb, nclb, nchb);
    free_vui8matrix(traitement, nrlY, nrhY, nclY, nchY);
    free_ui8matrix(image_courante, nrl, nrh, ncl, nch);
    printf("Fin algo dilatation SIMD");
 }
    
void test()
{
    // Decalage a gauche de 2
    vuint8 v1 = _mm_setr_epi8(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vuint8 v2 = _mm_setr_epi8(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
    /*
    v1 = _mm_shufflehi_epi16(v1, _MM_SHUFFLE(3, 3, 3, 3));
    v1 = (vuint8)_mm_shuffle_pd(v1, v2, 0b01);
    v1 = _mm_srli_si128(v1, 6);
    v2 = _mm_slli_si128(v2, 2);
    v1 = (vuint8)_mm_shuffle_pd(v1, v2, 0b10);*/
    
    //v1 = (vuint8)_mm_shuffle_pd(_mm_srli_si128((vuint8)_mm_shuffle_pd(_mm_shufflehi_epi16(v1, _MM_SHUFFLE(3, 3, 3, 3)), v2, 0b01),6),_mm_slli_si128(v2, 2), 0b10);

    // Decalage a droite de 2
    /*
    v2 = _mm_shufflelo_epi16(v2, _MM_SHUFFLE(0, 0, 0, 0));
    v2 = (vuint8)_mm_shuffle_pd(v1, v2, 0b01);
    v2 = _mm_slli_si128(v2, 6);
    v1 = _mm_srli_si128(v1, 2);
    v2 = (vuint8)_mm_shuffle_pd(v1, v2, 0b10);*/
    //v1 = (vuint8)_mm_shuffle_pd(_mm_srli_si128(v1, 2), _mm_slli_si128((vuint8)_mm_shuffle_pd(v1, _mm_shufflelo_epi16(v2, _MM_SHUFFLE(0, 0, 0, 0)), 0b01),6), 0b10);

    
    // Decalage a gauche de 1
    /*
    v1 = _mm_shufflehi_epi16(v1, _MM_SHUFFLE(3, 3, 3, 3));
    v1 = (vuint8)_mm_shuffle_pd(v1, v2, 0b01);
    v1 = _mm_srli_si128(v1, 7);
    v2 = _mm_slli_si128(v2, 1);
    v1 = (vuint8)_mm_shuffle_pd(v1, v2, 0b10);
    v1 = (vuint8)_mm_shuffle_pd(_mm_srli_si128((vuint8)_mm_shuffle_pd(_mm_shufflehi_epi16(v1, _MM_SHUFFLE(3, 3, 3, 3)), v2, 0b01),7),_mm_slli_si128(v2, 1), 0b10);*/

    // Decalage a droite de 1
    /*v1 = (vuint8)_mm_shuffle_pd(_mm_srli_si128(v1, 1), _mm_slli_si128((vuint8)_mm_shuffle_pd(v1, _mm_shufflelo_epi16(v2, _MM_SHUFFLE(0, 0, 0, 0)), 0b01),7), 0b10);*/
    uint8 a = 0b11;
    //addition d'un bit
    a = a << 1;
    a+=0b1;
    printf("a = %d\n", a);
    DEBUG(display_vuint8(vec_right2(v1,v2), "%3d", "v1\n")); DEBUG(puts(""));
}

//taille kernel: 1 pour kernel 3x3, 2 pour 5x5 et traitement: 255 pour fermeture et 0  pour ouverture	
/* void ouverture_fermeture(int taille_kernel, int traitement){
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
 }*/



