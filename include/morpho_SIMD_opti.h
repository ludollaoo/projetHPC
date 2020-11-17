/* ---------------- */
/* --- simd2D.h --- */
/* ---------------- */

#ifndef __SIMD_2D_H__
#define __SIMD_2D_H__

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif

void erosion3_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y);
void erosion5_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
void dilatation3_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
void dilatation5_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y)
void traitement3_SIMD()
#ifdef __cplusplus
}
#endif

#endif // __SIMD_2D_H__
