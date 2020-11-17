/* ---------------- */
/* --- simd2D.h --- */
/* ---------------- */

#ifndef __SIMD_2D_H__
#define __SIMD_2D_H__

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif

void copy_ui8matrix_vui8matrix_padding_binaire(uint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y);
void copy_vui8matrix_ui8matrix_padding_binaire(vuint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);
void init_uint8matrix(int chiffre, int i0, int i1, int j0, int j1, uint8 **Y);


#ifdef __cplusplus
}
#endif

#endif // __SIMD_2D_H__
