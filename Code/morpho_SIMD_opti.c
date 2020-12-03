#include <stddef.h>
#include "../include/main.h"


#define threshold 10

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
        j=ncl;
    // rotation de registre code scalarisé
        a0 = vec_load2(X, i-1, j-1);
        a1 = vec_load2(X, i-0, j-1);
        a2 = vec_load2(X, i+1, j-1);

        b0 = vec_load2(X, i-1, j+0);
        b1 = vec_load2(X, i-0, j+0);
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

void erosion3_rot_LU_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
// --------------------------------------------------------
{
    int i, j, r;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    vuint8 aa0, cc0;
    vuint8 aa1, cc1;
    vuint8 aa2, cc2;

    vuint8 ra, rb, rc;
    vuint8 y;
    
    r = (nch)%3;
    //printf(" r = %d, nrl = %d, nrh = %d, ncl = %d, nch = %d\n", r, nrl, nrh, ncl, nch);
    // CODE A COMPLETER
    for(i = nrl; i <= nrh; i++)
    {
        j=ncl;
    // rotation de registre code scalarisé
        a0 = vec_load2(X, i-1, j-1);
        b0 = vec_load2(X, i-1, j+0);

        a1 = vec_load2(X, i-0, j-1);
        b1 = vec_load2(X, i-0, j+0);

        a2 = vec_load2(X, i+1, j-1);
        b2 = vec_load2(X, i+1, j+0);
        //printf("i = %d\n",i);
        for(j = ncl; j < (nch-r); j+=3)
        {
            //printf("j = %d\n",j);
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

            //LU3
            a0 = vec_load2(X, i-1, j+2);
            a1 = vec_load2(X, i-0, j+2);
            a2 = vec_load2(X, i+1, j+2);
            //printf("OK2\n");
            aa0 = vec_left1(b0, c0);
            cc0 = vec_right1(c0, a0); 
            aa1 = vec_left1(b1, c1); 
            cc1 = vec_right1(c1, a1); 
            aa2 = vec_left1(b2, c2); 
            cc2 = vec_right1(c2, a2);

            ra = vec_and3(aa0, c0, cc0);  // operateur Colonne
            rb = vec_and3(aa1, c1, cc1);
            rc = vec_and3(aa2, c2, cc2);

            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j+1, y);
            //LU3
            //printf("i = %d et j = %d\n", i, j);
            b0 = vec_load2(X, i-1, j+3);
            b1 = vec_load2(X, i-0, j+3);
            b2 = vec_load2(X, i+1, j+3);

            aa0 = vec_left1(c0, a0);
            cc0 = vec_right1(a0, b0); 
            aa1 = vec_left1(c1, a1); 
            cc1 = vec_right1(a1, b1); 
            aa2 = vec_left1(c2, a2); 
            cc2 = vec_right1(a2, b2);

            ra = vec_and3(aa0, a0, cc0);  // operateur Colonne
            rb = vec_and3(aa1, a1, cc1);
            rc = vec_and3(aa2, a2, cc2);

            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j+2, y); 

            //printf("18 ok");
        }
        //printf("j = %d\n", j);
        switch(r){
            case 2:
                a0 = vec_load2(X, i-1, j+1);
                b0 = vec_load2(X, i-1, j+2);

                a1 = vec_load2(X, i-0, j+1);
                b1 = vec_load2(X, i-0, j+2);

                a2 = vec_load2(X, i+1, j+1);
                b2 = vec_load2(X, i+1, j+2);
                c0 = vec_load2(X, i-1, j+3);
                c1 = vec_load2(X, i-0, j+3);
                c2 = vec_load2(X, i+1, j+3);

                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_and3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b1, cc1);
                rc = vec_and3(aa2, b2, cc2);

                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i, j+2, y);       
            case 1:
                a0 = vec_load2(X, i-1, j-0);
                b0 = vec_load2(X, i-1, j+1);

                a1 = vec_load2(X, i-0, j-0);
                b1 = vec_load2(X, i-0, j+1);

                a2 = vec_load2(X, i+1, j-0);
                b2 = vec_load2(X, i+1, j+1);
                c0 = vec_load2(X, i-1, j+2);
                c1 = vec_load2(X, i-0, j+2);
                c2 = vec_load2(X, i+1, j+2);
                //printf("OK2\n");
                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_and3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b1, cc1);
                rc = vec_and3(aa2, b2, cc2);

                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i, j+1, y);
            
            case 0:
                a0 = vec_load2(X, i-1, j-1);
                b0 = vec_load2(X, i-1, j+0);

                a1 = vec_load2(X, i-0, j-1);
                b1 = vec_load2(X, i-0, j+0);

                a2 = vec_load2(X, i+1, j-1);
                b2 = vec_load2(X, i+1, j+0);
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
                break;
        }
    }

    //printf("OK\n");
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
void dilatation3_rot_LU_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
// --------------------------------------------------------
{
    int i, j, r;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    vuint8 aa0, cc0;
    vuint8 aa1, cc1;
    vuint8 aa2, cc2;

    vuint8 ra, rb, rc;
    vuint8 y;
    
    r = (nch)%3;
    //printf(" r = %d, nrl = %d, nrh = %d, ncl = %d, nch = %d\n", r, nrl, nrh, ncl, nch);
    // CODE A COMPLETER
    for(i = nrl; i <= nrh; i++)
    {
        j=ncl;
    // rotation de registre code scalarisé
        a0 = vec_load2(X, i-1, j-1);
        b0 = vec_load2(X, i-1, j+0);

        a1 = vec_load2(X, i-0, j-1);
        b1 = vec_load2(X, i-0, j+0);

        a2 = vec_load2(X, i+1, j-1);
        b2 = vec_load2(X, i+1, j+0);
        //printf("i = %d\n",i);
        for(j = ncl; j < (nch-r); j+=3)
        {
            //printf("j = %d\n",j);
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

            ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, b1, cc1);
            rc = vec_or3(aa2, b2, cc2);

            // Moyennage
            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j, y);

            //LU3
            a0 = vec_load2(X, i-1, j+2);
            a1 = vec_load2(X, i-0, j+2);
            a2 = vec_load2(X, i+1, j+2);
            //printf("OK2\n");
            aa0 = vec_left1(b0, c0);
            cc0 = vec_right1(c0, a0); 
            aa1 = vec_left1(b1, c1); 
            cc1 = vec_right1(c1, a1); 
            aa2 = vec_left1(b2, c2); 
            cc2 = vec_right1(c2, a2);

            ra = vec_or3(aa0, c0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, c1, cc1);
            rc = vec_or3(aa2, c2, cc2);

            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j+1, y);
            //LU3
            //printf("i = %d et j = %d\n", i, j);
            b0 = vec_load2(X, i-1, j+3);
            b1 = vec_load2(X, i-0, j+3);
            b2 = vec_load2(X, i+1, j+3);

            aa0 = vec_left1(c0, a0);
            cc0 = vec_right1(a0, b0); 
            aa1 = vec_left1(c1, a1); 
            cc1 = vec_right1(a1, b1); 
            aa2 = vec_left1(c2, a2); 
            cc2 = vec_right1(a2, b2);

            ra = vec_or3(aa0, a0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, a1, cc1);
            rc = vec_or3(aa2, a2, cc2);

            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j+2, y); 

            //printf("18 ok");
        }
        //printf("j = %d\n", j);
        switch(r){
            case 2:
                a0 = vec_load2(X, i-1, j+1);
                b0 = vec_load2(X, i-1, j+2);

                a1 = vec_load2(X, i-0, j+1);
                b1 = vec_load2(X, i-0, j+2);

                a2 = vec_load2(X, i+1, j+1);
                b2 = vec_load2(X, i+1, j+2);
                c0 = vec_load2(X, i-1, j+3);
                c1 = vec_load2(X, i-0, j+3);
                c2 = vec_load2(X, i+1, j+3);

                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i, j+2, y);       
            case 1:
                a0 = vec_load2(X, i-1, j-0);
                b0 = vec_load2(X, i-1, j+1);

                a1 = vec_load2(X, i-0, j-0);
                b1 = vec_load2(X, i-0, j+1);

                a2 = vec_load2(X, i+1, j-0);
                b2 = vec_load2(X, i+1, j+1);
                c0 = vec_load2(X, i-1, j+2);
                c1 = vec_load2(X, i-0, j+2);
                c2 = vec_load2(X, i+1, j+2);
                //printf("OK2\n");
                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i, j+1, y);
            
            case 0:
                a0 = vec_load2(X, i-1, j-1);
                b0 = vec_load2(X, i-1, j+0);

                a1 = vec_load2(X, i-0, j-1);
                b1 = vec_load2(X, i-0, j+0);

                a2 = vec_load2(X, i+1, j-1);
                b2 = vec_load2(X, i+1, j+0);
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

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

            // Moyennage
                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i, j, y);
                break;
        }
    }

    //printf("OK\n");
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
        j=ncl;
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
            y = vec_and3(vec_and3(aa0, b0, cc0), vec_and3(aa1, b1, cc1), vec_and3(aa2, b2, cc2));
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

void erosion_dilatation3_pipeline_LU_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
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
    int r = (nch)%3; 
    // Prologue
    for(i = nrl; i <= nrl+2; i++)
    {
        j=ncl;
    // rotation de registre code scalarisé
        a0 = vec_load2(X, i-1, j-1);
        b0 = vec_load2(X, i-1, j+0);

        a1 = vec_load2(X, i-0, j-1);
        b1 = vec_load2(X, i-0, j+0);

        a2 = vec_load2(X, i+1, j-1);
        b2 = vec_load2(X, i+1, j+0);

        for(j = ncl; j < (nch-r); j+=3)
        {
            //printf("j = %d\n",j);
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

            //LU3
            a0 = vec_load2(X, i-1, j+2);
            a1 = vec_load2(X, i-0, j+2);
            a2 = vec_load2(X, i+1, j+2);
            //printf("OK2\n");
            aa0 = vec_left1(b0, c0);
            cc0 = vec_right1(c0, a0); 
            aa1 = vec_left1(b1, c1); 
            cc1 = vec_right1(c1, a1); 
            aa2 = vec_left1(b2, c2); 
            cc2 = vec_right1(c2, a2);

            ra = vec_and3(aa0, c0, cc0);  // operateur Colonne
            rb = vec_and3(aa1, c1, cc1);
            rc = vec_and3(aa2, c2, cc2);

            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j+1, y);
            //LU3
            //printf("i = %d et j = %d\n", i, j);
            b0 = vec_load2(X, i-1, j+3);
            b1 = vec_load2(X, i-0, j+3);
            b2 = vec_load2(X, i+1, j+3);

            aa0 = vec_left1(c0, a0);
            cc0 = vec_right1(a0, b0); 
            aa1 = vec_left1(c1, a1); 
            cc1 = vec_right1(a1, b1); 
            aa2 = vec_left1(c2, a2); 
            cc2 = vec_right1(a2, b2);

            ra = vec_and3(aa0, a0, cc0);  // operateur Colonne
            rb = vec_and3(aa1, a1, cc1);
            rc = vec_and3(aa2, a2, cc2);

            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j+2, y); 

            //printf("18 ok");
        }
        //printf("j = %d\n", j);
        switch(r){
            case 2:
                a0 = vec_load2(X, i-1, j+1);
                b0 = vec_load2(X, i-1, j+2);

                a1 = vec_load2(X, i-0, j+1);
                b1 = vec_load2(X, i-0, j+2);

                a2 = vec_load2(X, i+1, j+1);
                b2 = vec_load2(X, i+1, j+2);
                c0 = vec_load2(X, i-1, j+3);
                c1 = vec_load2(X, i-0, j+3);
                c2 = vec_load2(X, i+1, j+3);

                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_and3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b1, cc1);
                rc = vec_and3(aa2, b2, cc2);

                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(padding2, i, j+2, y);       
            case 1:
                a0 = vec_load2(X, i-1, j-0);
                b0 = vec_load2(X, i-1, j+1);

                a1 = vec_load2(X, i-0, j-0);
                b1 = vec_load2(X, i-0, j+1);

                a2 = vec_load2(X, i+1, j-0);
                b2 = vec_load2(X, i+1, j+1);
                c0 = vec_load2(X, i-1, j+2);
                c1 = vec_load2(X, i-0, j+2);
                c2 = vec_load2(X, i+1, j+2);
                //printf("OK2\n");
                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_and3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b1, cc1);
                rc = vec_and3(aa2, b2, cc2);

                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(padding2, i, j+1, y);
            
            case 0:
                a0 = vec_load2(X, i-1, j-1);
                b0 = vec_load2(X, i-1, j+0);

                a1 = vec_load2(X, i-0, j-1);
                b1 = vec_load2(X, i-0, j+0);

                a2 = vec_load2(X, i+1, j-1);
                b2 = vec_load2(X, i+1, j+0);
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
                break;
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

        for(j = ncl; j < (nch-r); j+=3)
        {
            //printf("j = %d\n",j);
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
////////
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
///////
            //LU3
            a0 = vec_load2(X, i-1, j+2);
            a1 = vec_load2(X, i-0, j+2);
            a2 = vec_load2(X, i+1, j+2);
            //printf("OK2\n");
            aa0 = vec_left1(b0, c0);
            cc0 = vec_right1(c0, a0); 
            aa1 = vec_left1(b1, c1); 
            cc1 = vec_right1(c1, a1); 
            aa2 = vec_left1(b2, c2); 
            cc2 = vec_right1(c2, a2);

            ra = vec_and3(aa0, c0, cc0);  // operateur Colonne
            rb = vec_and3(aa1, c1, cc1);
            rc = vec_and3(aa2, c2, cc2);

            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j+1, y);
//////////
            a02 = vec_load2(padding2, i-3, j+2);
            a12 = vec_load2(padding2, i-2, j+2);
            a22 = vec_load2(padding2, i-1, j+2);

            aa0 = vec_left1(b02, c02);
            cc0 = vec_right1(c02, a02); 
            aa1 = vec_left1(b12, c12); 
            cc1 = vec_right1(c12, a12); 
            aa2 = vec_left1(b22, c22); 
            cc2 = vec_right1(c22, a22); 

            ra = vec_or3(aa0, c02, cc0);  // operateur Colonne
            rb = vec_or3(aa1, c12, cc1);
            rc = vec_or3(aa2, c22, cc2);

            // Moyennage
            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i-2, j+1, y);
/////
            //LU3
            //printf("i = %d et j = %d\n", i, j);
            b0 = vec_load2(X, i-1, j+3);
            b1 = vec_load2(X, i-0, j+3);
            b2 = vec_load2(X, i+1, j+3);

            aa0 = vec_left1(c0, a0);
            cc0 = vec_right1(a0, b0); 
            aa1 = vec_left1(c1, a1); 
            cc1 = vec_right1(a1, b1); 
            aa2 = vec_left1(c2, a2); 
            cc2 = vec_right1(a2, b2);

            ra = vec_and3(aa0, a0, cc0);  // operateur Colonne
            rb = vec_and3(aa1, a1, cc1);
            rc = vec_and3(aa2, a2, cc2);

            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j+2, y); 
//////////
            b02 = vec_load2(padding2, i-3, j+3);
            b12 = vec_load2(padding2, i-2, j+3);
            b22 = vec_load2(padding2, i-1, j+3);

            aa0 = vec_left1(c02, a02);
            cc0 = vec_right1(a02, b02); 
            aa1 = vec_left1(c12, a12); 
            cc1 = vec_right1(a12, b12); 
            aa2 = vec_left1(c22, a22); 
            cc2 = vec_right1(a22, b22); 

            ra = vec_or3(aa0, a02, cc0);  // operateur Colonne
            rb = vec_or3(aa1, a12, cc1);
            rc = vec_or3(aa2, a22, cc2);

            // Moyennage
            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i-2, j+2, y);
/////
        }
        switch(r){
            case 2:
                a0 = vec_load2(X, i-1, j+1);
                b0 = vec_load2(X, i-1, j+2);

                a1 = vec_load2(X, i-0, j+1);
                b1 = vec_load2(X, i-0, j+2);

                a2 = vec_load2(X, i+1, j+1);
                b2 = vec_load2(X, i+1, j+2);
                c0 = vec_load2(X, i-1, j+3);
                c1 = vec_load2(X, i-0, j+3);
                c2 = vec_load2(X, i+1, j+3);

                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_and3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b1, cc1);
                rc = vec_and3(aa2, b2, cc2);

                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(padding2, i, j+2, y);    
        ///////
                b02 = vec_load2(padding2, i-3, j+2);
                b12 = vec_load2(padding2, i-2, j+2);
                b22 = vec_load2(padding2, i-1, j+2);

                a02 = vec_load2(padding2, i-3, j+1);
                a12 = vec_load2(padding2, i-2, j+1);
                a22 = vec_load2(padding2, i-1, j+1);    
                c02 = vec_load2(padding2, i-3, j+3);
                c12 = vec_load2(padding2, i-2, j+3);
                c22 = vec_load2(padding2, i-1, j+3);

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
                vec_store2(Y, i-0, j+2, y);   
            case 1:
                a0 = vec_load2(X, i-1, j-0);
                b0 = vec_load2(X, i-1, j+1);

                a1 = vec_load2(X, i-0, j-0);
                b1 = vec_load2(X, i-0, j+1);

                a2 = vec_load2(X, i+1, j-0);
                b2 = vec_load2(X, i+1, j+1);
                c0 = vec_load2(X, i-1, j+2);
                c1 = vec_load2(X, i-0, j+2);
                c2 = vec_load2(X, i+1, j+2);
                //printf("OK2\n");
                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_and3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b1, cc1);
                rc = vec_and3(aa2, b2, cc2);

                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(padding2, i, j+1, y);
        //////
                b02 = vec_load2(padding2, i-3, j+1);
                b12 = vec_load2(padding2, i-2, j+1);
                b22 = vec_load2(padding2, i-1, j+1);

                a02 = vec_load2(padding2, i-3, j-0);
                a12 = vec_load2(padding2, i-2, j-0);
                a22 = vec_load2(padding2, i-1, j-0);    
                c02 = vec_load2(padding2, i-3, j+2);
                c12 = vec_load2(padding2, i-2, j+2);
                c22 = vec_load2(padding2, i-1, j+2);

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
                vec_store2(Y, i-1, j+1, y);
            
            case 0:
                a0 = vec_load2(X, i-1, j-1);
                b0 = vec_load2(X, i-1, j+0);

                a1 = vec_load2(X, i-0, j-1);
                b1 = vec_load2(X, i-0, j+0);

                a2 = vec_load2(X, i+1, j-1);
                b2 = vec_load2(X, i+1, j+0);
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
            ////////
                b02 = vec_load2(padding2, i-3, j+0);
                b12 = vec_load2(padding2, i-2, j+0);
                b22 = vec_load2(padding2, i-1, j+0);

                a02 = vec_load2(padding2, i-3, j-1);
                a12 = vec_load2(padding2, i-2, j-1);
                a22 = vec_load2(padding2, i-1, j-1);    
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
                break;
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

        for(j = ncl; j < (nch-r); j+=3)
        {
            //printf("j = %d\n",j);
            // Initialisation 
            c0 = vec_load2(padding2, i-1, j+1);
            c1 = vec_load2(padding2, i-0, j+1);
            c2 = vec_load2(padding2, i+1, j+1);

            // Décalage a droite et à gauche
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

            //LU3
            a0 = vec_load2(padding2, i-1, j+2);
            a1 = vec_load2(padding2, i-0, j+2);
            a2 = vec_load2(padding2, i+1, j+2);
            //printf("OK2\n");
            aa0 = vec_left1(b0, c0);
            cc0 = vec_right1(c0, a0); 
            aa1 = vec_left1(b1, c1); 
            cc1 = vec_right1(c1, a1); 
            aa2 = vec_left1(b2, c2); 
            cc2 = vec_right1(c2, a2);

            ra = vec_or3(aa0, c0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, c1, cc1);
            rc = vec_or3(aa2, c2, cc2);

            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j+1, y);
            //LU3
            //printf("i = %d et j = %d\n", i, j);
            b0 = vec_load2(padding2, i-1, j+3);
            b1 = vec_load2(padding2, i-0, j+3);
            b2 = vec_load2(padding2, i+1, j+3);

            aa0 = vec_left1(c0, a0);
            cc0 = vec_right1(a0, b0); 
            aa1 = vec_left1(c1, a1); 
            cc1 = vec_right1(a1, b1); 
            aa2 = vec_left1(c2, a2); 
            cc2 = vec_right1(a2, b2);

            ra = vec_or3(aa0, a0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, a1, cc1);
            rc = vec_or3(aa2, a2, cc2);

            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j+2, y); 

            //printf("18 ok");
        }
        //printf("j = %d\n", j);
        switch(r){
            case 2:
                a0 = vec_load2(padding2, i-1, j+1);
                b0 = vec_load2(padding2, i-1, j+2);

                a1 = vec_load2(padding2, i-0, j+1);
                b1 = vec_load2(padding2, i-0, j+2);

                a2 = vec_load2(padding2, i+1, j+1);
                b2 = vec_load2(padding2, i+1, j+2);
                c0 = vec_load2(padding2, i-1, j+3);
                c1 = vec_load2(padding2, i-0, j+3);
                c2 = vec_load2(padding2, i+1, j+3);

                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i, j+2, y);       
            case 1:
                a0 = vec_load2(padding2, i-1, j-0);
                b0 = vec_load2(padding2, i-1, j+1);

                a1 = vec_load2(padding2, i-0, j-0);
                b1 = vec_load2(padding2, i-0, j+1);

                a2 = vec_load2(padding2, i+1, j-0);
                b2 = vec_load2(padding2, i+1, j+1);
                c0 = vec_load2(padding2, i-1, j+2);
                c1 = vec_load2(padding2, i-0, j+2);
                c2 = vec_load2(padding2, i+1, j+2);
                //printf("OK2\n");
                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i, j+1, y);
            
            case 0:
                a0 = vec_load2(padding2, i-1, j-1);
                b0 = vec_load2(padding2, i-1, j+0);

                a1 = vec_load2(padding2, i-0, j-1);
                b1 = vec_load2(padding2, i-0, j+0);

                a2 = vec_load2(padding2, i+1, j-1);
                b2 = vec_load2(padding2, i+1, j+0);
                c0 = vec_load2(padding2, i-1, j+1);
                c1 = vec_load2(padding2, i-0, j+1);
                c2 = vec_load2(padding2, i+1, j+1);

            // Décalage a droite et à gauche
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
                break;
        }
    }
    free_vui8matrix(padding2, nrl-2, nrh+2, ncl-1, nch+1);
}

void dilatation_erosion3_pipeline_LU_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
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
    int r = (nch)%3; 
    // Prologue
    for(i = nrl; i <= nrl+2; i++)
    {
        j=ncl;
    // rotation de registre code scalarisé
        a0 = vec_load2(X, i-1, j-1);
        b0 = vec_load2(X, i-1, j+0);

        a1 = vec_load2(X, i-0, j-1);
        b1 = vec_load2(X, i-0, j+0);

        a2 = vec_load2(X, i+1, j-1);
        b2 = vec_load2(X, i+1, j+0);

        for(j = ncl; j < (nch-r); j+=3)
        {
            //printf("j = %d\n",j);
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

            ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, b1, cc1);
            rc = vec_or3(aa2, b2, cc2);

            // Moyennage
            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j, y);

            //LU3
            a0 = vec_load2(X, i-1, j+2);
            a1 = vec_load2(X, i-0, j+2);
            a2 = vec_load2(X, i+1, j+2);
            //printf("OK2\n");
            aa0 = vec_left1(b0, c0);
            cc0 = vec_right1(c0, a0); 
            aa1 = vec_left1(b1, c1); 
            cc1 = vec_right1(c1, a1); 
            aa2 = vec_left1(b2, c2); 
            cc2 = vec_right1(c2, a2);

            ra = vec_or3(aa0, c0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, c1, cc1);
            rc = vec_or3(aa2, c2, cc2);

            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j+1, y);
            //LU3
            //printf("i = %d et j = %d\n", i, j);
            b0 = vec_load2(X, i-1, j+3);
            b1 = vec_load2(X, i-0, j+3);
            b2 = vec_load2(X, i+1, j+3);

            aa0 = vec_left1(c0, a0);
            cc0 = vec_right1(a0, b0); 
            aa1 = vec_left1(c1, a1); 
            cc1 = vec_right1(a1, b1); 
            aa2 = vec_left1(c2, a2); 
            cc2 = vec_right1(a2, b2);

            ra = vec_or3(aa0, a0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, a1, cc1);
            rc = vec_or3(aa2, a2, cc2);

            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j+2, y); 

            //printf("18 ok");
        }
        //printf("j = %d\n", j);
        switch(r){
            case 2:
                a0 = vec_load2(X, i-1, j+1);
                b0 = vec_load2(X, i-1, j+2);

                a1 = vec_load2(X, i-0, j+1);
                b1 = vec_load2(X, i-0, j+2);

                a2 = vec_load2(X, i+1, j+1);
                b2 = vec_load2(X, i+1, j+2);
                c0 = vec_load2(X, i-1, j+3);
                c1 = vec_load2(X, i-0, j+3);
                c2 = vec_load2(X, i+1, j+3);

                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(padding2, i, j+2, y);       
            case 1:
                a0 = vec_load2(X, i-1, j-0);
                b0 = vec_load2(X, i-1, j+1);

                a1 = vec_load2(X, i-0, j-0);
                b1 = vec_load2(X, i-0, j+1);

                a2 = vec_load2(X, i+1, j-0);
                b2 = vec_load2(X, i+1, j+1);
                c0 = vec_load2(X, i-1, j+2);
                c1 = vec_load2(X, i-0, j+2);
                c2 = vec_load2(X, i+1, j+2);
                //printf("OK2\n");
                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(padding2, i, j+1, y);
            
            case 0:
                a0 = vec_load2(X, i-1, j-1);
                b0 = vec_load2(X, i-1, j+0);

                a1 = vec_load2(X, i-0, j-1);
                b1 = vec_load2(X, i-0, j+0);

                a2 = vec_load2(X, i+1, j-1);
                b2 = vec_load2(X, i+1, j+0);
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

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

            // Moyennage
                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(padding2, i, j, y);
                break;
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

        for(j = ncl; j < (nch-r); j+=3)
        {
            //printf("j = %d\n",j);
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

            ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, b1, cc1);
            rc = vec_or3(aa2, b2, cc2);

            // Moyennage
            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j, y);
////////
            c02 = vec_load2(padding2, i-3, j+1);
            c12 = vec_load2(padding2, i-2, j+1);
            c22 = vec_load2(padding2, i-1, j+1);

            aa0 = vec_left1(a02, b02);
            cc0 = vec_right1(b02, c02); 
            aa1 = vec_left1(a12, b12); 
            cc1 = vec_right1(b12, c12); 
            aa2 = vec_left1(a22, b22); 
            cc2 = vec_right1(b22, c22); 

            ra = vec_and3(aa0, b02, cc0);  // operateur Colonne
            rb = vec_and3(aa1, b12, cc1);
            rc = vec_and3(aa2, b22, cc2);

            // Moyennage
            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i-2, j, y);
///////
            //LU3
            a0 = vec_load2(X, i-1, j+2);
            a1 = vec_load2(X, i-0, j+2);
            a2 = vec_load2(X, i+1, j+2);
            //printf("OK2\n");
            aa0 = vec_left1(b0, c0);
            cc0 = vec_right1(c0, a0); 
            aa1 = vec_left1(b1, c1); 
            cc1 = vec_right1(c1, a1); 
            aa2 = vec_left1(b2, c2); 
            cc2 = vec_right1(c2, a2);

            ra = vec_or3(aa0, c0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, c1, cc1);
            rc = vec_or3(aa2, c2, cc2);

            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j+1, y);
//////////
            a02 = vec_load2(padding2, i-3, j+2);
            a12 = vec_load2(padding2, i-2, j+2);
            a22 = vec_load2(padding2, i-1, j+2);

            aa0 = vec_left1(b02, c02);
            cc0 = vec_right1(c02, a02); 
            aa1 = vec_left1(b12, c12); 
            cc1 = vec_right1(c12, a12); 
            aa2 = vec_left1(b22, c22); 
            cc2 = vec_right1(c22, a22); 

            ra = vec_and3(aa0, c02, cc0);  // operateur Colonne
            rb = vec_and3(aa1, c12, cc1);
            rc = vec_and3(aa2, c22, cc2);

            // Moyennage
            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i-2, j+1, y);
/////
            //LU3
            //printf("i = %d et j = %d\n", i, j);
            b0 = vec_load2(X, i-1, j+3);
            b1 = vec_load2(X, i-0, j+3);
            b2 = vec_load2(X, i+1, j+3);

            aa0 = vec_left1(c0, a0);
            cc0 = vec_right1(a0, b0); 
            aa1 = vec_left1(c1, a1); 
            cc1 = vec_right1(a1, b1); 
            aa2 = vec_left1(c2, a2); 
            cc2 = vec_right1(a2, b2);

            ra = vec_or3(aa0, a0, cc0);  // operateur Colonne
            rb = vec_or3(aa1, a1, cc1);
            rc = vec_or3(aa2, a2, cc2);

            y = vec_or3(ra, rb, rc);  // operateur Ligne
            vec_store2(padding2, i, j+2, y); 
//////////
            b02 = vec_load2(padding2, i-3, j+3);
            b12 = vec_load2(padding2, i-2, j+3);
            b22 = vec_load2(padding2, i-1, j+3);

            aa0 = vec_left1(c02, a02);
            cc0 = vec_right1(a02, b02); 
            aa1 = vec_left1(c12, a12); 
            cc1 = vec_right1(a12, b12); 
            aa2 = vec_left1(c22, a22); 
            cc2 = vec_right1(a22, b22); 

            ra = vec_and3(aa0, a02, cc0);  // operateur Colonne
            rb = vec_and3(aa1, a12, cc1);
            rc = vec_and3(aa2, a22, cc2);

            // Moyennage
            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i-2, j+2, y);
/////
        }
        switch(r){
            case 2:
                a0 = vec_load2(X, i-1, j+1);
                b0 = vec_load2(X, i-1, j+2);

                a1 = vec_load2(X, i-0, j+1);
                b1 = vec_load2(X, i-0, j+2);

                a2 = vec_load2(X, i+1, j+1);
                b2 = vec_load2(X, i+1, j+2);
                c0 = vec_load2(X, i-1, j+3);
                c1 = vec_load2(X, i-0, j+3);
                c2 = vec_load2(X, i+1, j+3);

                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(padding2, i, j+2, y);    
        ///////
                b02 = vec_load2(padding2, i-3, j+2);
                b12 = vec_load2(padding2, i-2, j+2);
                b22 = vec_load2(padding2, i-1, j+2);

                a02 = vec_load2(padding2, i-3, j+1);
                a12 = vec_load2(padding2, i-2, j+1);
                a22 = vec_load2(padding2, i-1, j+1);    
                c02 = vec_load2(padding2, i-3, j+3);
                c12 = vec_load2(padding2, i-2, j+3);
                c22 = vec_load2(padding2, i-1, j+3);

                aa0 = vec_left1(a02, b02);
                cc0 = vec_right1(b02, c02); 
                aa1 = vec_left1(a12, b12); 
                cc1 = vec_right1(b12, c12); 
                aa2 = vec_left1(a22, b22); 
                cc2 = vec_right1(b22, c22); 

                ra = vec_and3(aa0, b02, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b12, cc1);
                rc = vec_and3(aa2, b22, cc2);

            // Moyennage
                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i-0, j+2, y);   
            case 1:
                a0 = vec_load2(X, i-1, j-0);
                b0 = vec_load2(X, i-1, j+1);

                a1 = vec_load2(X, i-0, j-0);
                b1 = vec_load2(X, i-0, j+1);

                a2 = vec_load2(X, i+1, j-0);
                b2 = vec_load2(X, i+1, j+1);
                c0 = vec_load2(X, i-1, j+2);
                c1 = vec_load2(X, i-0, j+2);
                c2 = vec_load2(X, i+1, j+2);
                //printf("OK2\n");
                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(padding2, i, j+1, y);
        //////
                b02 = vec_load2(padding2, i-3, j+1);
                b12 = vec_load2(padding2, i-2, j+1);
                b22 = vec_load2(padding2, i-1, j+1);

                a02 = vec_load2(padding2, i-3, j-0);
                a12 = vec_load2(padding2, i-2, j-0);
                a22 = vec_load2(padding2, i-1, j-0);    
                c02 = vec_load2(padding2, i-3, j+2);
                c12 = vec_load2(padding2, i-2, j+2);
                c22 = vec_load2(padding2, i-1, j+2);

                aa0 = vec_left1(a02, b02);
                cc0 = vec_right1(b02, c02); 
                aa1 = vec_left1(a12, b12); 
                cc1 = vec_right1(b12, c12); 
                aa2 = vec_left1(a22, b22); 
                cc2 = vec_right1(b22, c22); 

                ra = vec_and3(aa0, b02, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b12, cc1);
                rc = vec_and3(aa2, b22, cc2);

            // Moyennage
                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i-1, j+1, y);
            
            case 0:
                a0 = vec_load2(X, i-1, j-1);
                b0 = vec_load2(X, i-1, j+0);

                a1 = vec_load2(X, i-0, j-1);
                b1 = vec_load2(X, i-0, j+0);

                a2 = vec_load2(X, i+1, j-1);
                b2 = vec_load2(X, i+1, j+0);
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

                ra = vec_or3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_or3(aa1, b1, cc1);
                rc = vec_or3(aa2, b2, cc2);

            // Moyennage
                y = vec_or3(ra, rb, rc);  // operateur Ligne
                vec_store2(padding2, i, j, y);
            ////////
                b02 = vec_load2(padding2, i-3, j+0);
                b12 = vec_load2(padding2, i-2, j+0);
                b22 = vec_load2(padding2, i-1, j+0);

                a02 = vec_load2(padding2, i-3, j-1);
                a12 = vec_load2(padding2, i-2, j-1);
                a22 = vec_load2(padding2, i-1, j-1);    
                c02 = vec_load2(padding2, i-3, j+1);
                c12 = vec_load2(padding2, i-2, j+1);
                c22 = vec_load2(padding2, i-1, j+1);

                aa0 = vec_left1(a02, b02);
                cc0 = vec_right1(b02, c02); 
                aa1 = vec_left1(a12, b12); 
                cc1 = vec_right1(b12, c12); 
                aa2 = vec_left1(a22, b22); 
                cc2 = vec_right1(b22, c22); 

                ra = vec_and3(aa0, b02, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b12, cc1);
                rc = vec_and3(aa2, b22, cc2);

            // Moyennage
                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i-2, j, y);
                break;
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

        for(j = ncl; j < (nch-r); j+=3)
        {
            //printf("j = %d\n",j);
            // Initialisation 
            c0 = vec_load2(padding2, i-1, j+1);
            c1 = vec_load2(padding2, i-0, j+1);
            c2 = vec_load2(padding2, i+1, j+1);

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

            //LU3
            a0 = vec_load2(padding2, i-1, j+2);
            a1 = vec_load2(padding2, i-0, j+2);
            a2 = vec_load2(padding2, i+1, j+2);
            //printf("OK2\n");
            aa0 = vec_left1(b0, c0);
            cc0 = vec_right1(c0, a0); 
            aa1 = vec_left1(b1, c1); 
            cc1 = vec_right1(c1, a1); 
            aa2 = vec_left1(b2, c2); 
            cc2 = vec_right1(c2, a2);

            ra = vec_and3(aa0, c0, cc0);  // operateur Colonne
            rb = vec_and3(aa1, c1, cc1);
            rc = vec_and3(aa2, c2, cc2);

            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j+1, y);
            //LU3
            //printf("i = %d et j = %d\n", i, j);
            b0 = vec_load2(padding2, i-1, j+3);
            b1 = vec_load2(padding2, i-0, j+3);
            b2 = vec_load2(padding2, i+1, j+3);

            aa0 = vec_left1(c0, a0);
            cc0 = vec_right1(a0, b0); 
            aa1 = vec_left1(c1, a1); 
            cc1 = vec_right1(a1, b1); 
            aa2 = vec_left1(c2, a2); 
            cc2 = vec_right1(a2, b2);

            ra = vec_and3(aa0, a0, cc0);  // operateur Colonne
            rb = vec_and3(aa1, a1, cc1);
            rc = vec_and3(aa2, a2, cc2);

            y = vec_and3(ra, rb, rc);  // operateur Ligne
            vec_store2(Y, i, j+2, y); 

            //printf("18 ok");
        }
        //printf("j = %d\n", j);
        switch(r){
            case 2:
                a0 = vec_load2(padding2, i-1, j+1);
                b0 = vec_load2(padding2, i-1, j+2);

                a1 = vec_load2(padding2, i-0, j+1);
                b1 = vec_load2(padding2, i-0, j+2);

                a2 = vec_load2(padding2, i+1, j+1);
                b2 = vec_load2(padding2, i+1, j+2);
                c0 = vec_load2(padding2, i-1, j+3);
                c1 = vec_load2(padding2, i-0, j+3);
                c2 = vec_load2(padding2, i+1, j+3);

                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_and3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b1, cc1);
                rc = vec_and3(aa2, b2, cc2);

                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i, j+2, y);       
            case 1:
                a0 = vec_load2(padding2, i-1, j-0);
                b0 = vec_load2(padding2, i-1, j+1);

                a1 = vec_load2(padding2, i-0, j-0);
                b1 = vec_load2(padding2, i-0, j+1);

                a2 = vec_load2(padding2, i+1, j-0);
                b2 = vec_load2(padding2, i+1, j+1);
                c0 = vec_load2(padding2, i-1, j+2);
                c1 = vec_load2(padding2, i-0, j+2);
                c2 = vec_load2(padding2, i+1, j+2);
                //printf("OK2\n");
                aa0 = vec_left1(a0, b0);
                cc0 = vec_right1(b0, c0); 
                aa1 = vec_left1(a1, b1); 
                cc1 = vec_right1(b1, c1); 
                aa2 = vec_left1(a2, b2); 
                cc2 = vec_right1(b2, c2);

                ra = vec_and3(aa0, b0, cc0);  // operateur Colonne
                rb = vec_and3(aa1, b1, cc1);
                rc = vec_and3(aa2, b2, cc2);

                y = vec_and3(ra, rb, rc);  // operateur Ligne
                vec_store2(Y, i, j+1, y);
            
            case 0:
                a0 = vec_load2(padding2, i-1, j-1);
                b0 = vec_load2(padding2, i-1, j+0);

                a1 = vec_load2(padding2, i-0, j-1);
                b1 = vec_load2(padding2, i-0, j+0);

                a2 = vec_load2(padding2, i+1, j-1);
                b2 = vec_load2(padding2, i+1, j+0);
                c0 = vec_load2(padding2, i-1, j+1);
                c1 = vec_load2(padding2, i-0, j+1);
                c2 = vec_load2(padding2, i+1, j+1);

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
                break;
        }
    }
    free_vui8matrix(padding2, nrl-2, nrh+2, ncl-1, nch+1);
}

void traitement3_SIMD_opti(char* path_load, char* path_save){
 	printf("Lancement de l'algorithme de dilatation SIMD opti\n");
    
    char nom[150];
 	int nrl, nrh, ncl, nch;
 	int nrlY, nrhY, nclY, nchY;
 	int nrlb, nrhb, nclb, nchb; //with border
	int img_nbr = 1;
	//char nom_img[100];
	//char nom_res[100];
    char *format = "%d ";
    int card = card = card_vuint8();
    int b = 2;
    //uint8** image_courante = ui8matrix(nrl, nrh, ncl, nch);
    //init_uint8matrix(1, nrl, nrh, ncl, nch, image_courante);
	uint8 pixel_courant;
    //printf("%d\n",1 | 1);
    

    //--------------------------- upload image en format uint8**------------------------------------
	get_path(1, nom, path_load, "_binaire_SIMD_opti_openMP_2");
	uint8** image_courante = LoadPGM_ui8matrix(nom, &nrl, &nrh, &ncl, &nch);

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
    vuint8** padding2 = vui8matrix(nrlb, nrhb, nclb, nchb);

    // ---------------------------erosion SIMD----------------------------------
    //dilatation_erosion3_pipeline_rot_simd(padding, nrlY, nrhY, nclY, nchY, traitement);
    //printf("Debuuuut\n"); sleep(5);
    erosion3_rot_simd(padding, nrlY, nrhY, nclY, nchY, traitement);
    //erosion3_rot_LU_simd(padding, nrlY, nrhY, nclY, nchY, traitement);
    //erosion_dilatation3_pipeline_LU_simd(padding, nrlY, nrhY, nclY, nchY, padding2);
    //dilatation_erosion3_pipeline_LU_simd(padding2, nrlY, nrhY, nclY, nchY, traitement);
    //printf("OOOOOOOOOOOOOOOOOOK\n");
    //DEBUG(display_vui8matrix(traitement, nrlY, nrhY, nclY, nchY, "%d", "erosion LU")); DEBUG(puts(""));
    //printf("OOOOOOOOOOOOOOOOOOK2\n");

    //--------------- copie de traitement vers image courante ---------------------------------
    copy_vui8matrix_ui8matrix_padding_binaire(traitement, nrlY, nrhY, nclY, nchY, image_courante);
    // -------- Store de l'image ------------
    get_path(img_nbr, nom, path_save, "_traitement_SIMD_opti");
    SavePGM_ui8matrix(image_courante, nrl, nrh, ncl, nch, nom);
    
    for (img_nbr; img_nbr < 200; img_nbr++){

		//Chargement d'une image après traitement par SD
	    get_path(img_nbr, nom, path_load, "_binaire_SIMD_opti_openMP_2");
	    image_courante = LoadPGM_ui8matrix(nom, &nrl, &nrh, &ncl, &nch);

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
        //DEBUG(display_vui8matrix(traitement, nrlY, nrhY, nclY, nchY, "%d", "erosion LU")); DEBUG(puts(""));
        // ---------------------------erosion SIMD----------------------------------
        erosion3_rot_simd(padding, nrlY, nrhY, nclY, nchY, traitement);
        //dilatation_erosion3_pipeline_rot_simd(padding, nrlY, nrhY, nclY, nchY, traitement);
        //erosion3_rot_LU_simd(padding, nrlY, nrhY, nclY, nchY, traitement);
        //erosion_dilatation3_pipeline_LU_simd(padding, nrlY, nrhY, nclY, nchY, padding2);
        //dilatation_erosion3_pipeline_LU_simd(padding2, nrlY, nrhY, nclY, nchY, traitement);
        //--------------- copie de traitement vers image courante ---------------------------------
        copy_vui8matrix_ui8matrix_padding_binaire(traitement, nrlY, nrhY, nclY, nchY, image_courante);
        // -------- Store de l'image ------------
        get_path(img_nbr, nom, path_save, "_traitement_SIMD_opti");
        SavePGM_ui8matrix(image_courante, nrl, nrh, ncl, nch, nom);
		
	}
    free_vui8matrix(padding, nrlb, nrhb, nclb, nchb);
    free_vui8matrix(padding2, nrlb, nrhb, nclb, nchb);
    free_vui8matrix(traitement, nrlY, nrhY, nclY, nchY);
    free_ui8matrix(image_courante, nrl, nrh, ncl, nch);
    printf("Fin algo dilatation SIMD opti\n");
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





