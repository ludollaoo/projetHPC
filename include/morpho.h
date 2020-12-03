/* ---------------- */
/* --- simd2D.h --- */
/* ---------------- */

#ifndef __SIMD_2D_H__
#define __SIMD_2D_H__

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif

void copy_ui8matrix_ui8matrix_padding(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);
uint8 erosion_dilatation(int taille_kernel, int traitement, uint8** padding, int i, int j);
void dilatation_erosion(int taille_kernel, int traitement,uint8** padding, int nrl, int nrh, int ncl, int nch, uint8** image_courante);
void morpho_sequentielle(int taille_kernel,uint8** padding, int nrl, int nrh, int ncl, int nch, uint8** image_courante);
void traitement_sequentielle(int taille_kernel, char* path_load, char* path_save);

#ifdef __cplusplus
}
#endif

#endif // __SIMD_2D_H__
