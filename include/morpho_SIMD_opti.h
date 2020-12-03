/* ---------------- */
/* --- simd2D.h --- */
/* ---------------- */

#ifndef __SIMD_2D_H__
#define __SIMD_2D_H__

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif

void erosion3_rot_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y);
void erosion5_rot_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y);
void erosion3_rot_LU_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y);
void dilatation3_rot_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y);
void dilatation5_rot_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y);
void dilatation3_rot_LU_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y);

void dilatation_erosion3_pipeline_rot_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y);

void erosion_dilatation3_pipeline_LU_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y);
void dilatation_erosion3_pipeline_LU_simd(vuint8** X, int nrl, int nrh, int ncl, int nch, vuint8** Y);
void traitement3_SIMD_opti(char* path_load, char* path_save);

#ifdef __cplusplus
}
#endif

#endif // __SIMD_2D_H__
