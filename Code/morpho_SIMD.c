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
#include "../include/projet_util.h"

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
            y = vec_and5(vec_and5(aa0, aa1, b0, aa3, aa4), vec_and5(bb0, bb1, b1, bb3, bb4), vec_and5(cc0, cc1, b2, cc3, cc4), vec_and5(dd0, dd1, b3, dd3, dd4), vec_and5(ee0, ee1, b4, ee3, ee4));
            vec_store2(Y, i, j, y);
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
            y = vec_or3(vec_or3(aa0, b0, cc0), vec_or3(aa1, b1, cc1), vec_or3(aa2, b2, cc2));
            vec_store2(Y, i, j, y);
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


    //--------------copie de image_courant vers padding : 1ere ligne------------------------
    copy_ui8matrix_vui8matrix_padding_binaire(image_courante, nrlY, nrhY, nclY, nchY, padding);

    //--------------------------creation matrice Y -----------------------------
    vuint8** traitement = vui8matrix(nrlY, nrhY, nclY, nchY);

    //--------------------------Creation padding2 de meme taille taille que padding --------------------------------
    vuint8** padding2 = vui8matrix(nrlb, nrhb, nclb, nchb);

    // ---------------------------erosion SIMD----------------------------------

    erosion3_simd(padding, nrlY, nrhY, nclY, nchY, padding2);
    dilatation3_simd(padding2, nrlY, nrhY, nclY, nchY, traitement);
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

        //--------------copie de image_courant vers padding : 1ere ligne------------------------
        copy_ui8matrix_vui8matrix_padding_binaire(image_courante, nrl, nrh, nclb, nchb, padding);

        //--------------------------creation matrice Y -----------------------------
        traitement = vui8matrix(nrlY, nrhY, nclY, nchY);
        
        // ---------------------------erosion SIMD----------------------------------
        erosion3_simd(padding, nrlY, nrhY, nclY, nchY, padding2);
        dilatation3_simd(padding2, nrlY, nrhY, nclY, nchY, traitement);
        //dilatation3_simd(padding, nrlY, nrhY, nclY, nchY, padding2);
        //erosion3_simd(padding2, nrlY, nrhY, nclY, nchY, traitement);
        //--------------- copie de traitement vers image courante ---------------------------------
        copy_vui8matrix_ui8matrix_padding_binaire(traitement, nrlY, nrhY, nclY, nchY, image_courante);
        // -------- Store de l'image ------------
        sprintf(nom_res, "/home/jebali/Bureau/EISE5/HPC/ProjetHPC/projetHPC/ResultatSIMD/image_dilatation3%03d", img_nbr);
	    SavePGM_ui8matrix(image_courante, nrl, nrh, ncl, nch, nom_res);
		
	}
    free_vui8matrix(padding, nrlb, nrhb, nclb, nchb);
    free_vui8matrix(padding2, nrlb, nrhb, nclb, nchb);
    free_vui8matrix(traitement, nrlY, nrhY, nclY, nchY);
    free_ui8matrix(image_courante, nrl, nrh, ncl, nch);
    printf("Fin algo dilatation SIMD\n");
 }
 

