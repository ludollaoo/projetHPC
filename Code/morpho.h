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
void dilatation_erosion(int taille_kernel, int traitement);
void ouverture_fermeture(int taille_kernel, int traitement);

#ifdef __cplusplus
}
#endif

#endif // __SIMD_2D_H__
