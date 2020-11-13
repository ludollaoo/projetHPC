/* ---------------- */
/* --- simd2D.h --- */
/* ---------------- */

#ifndef __SIMD_2D_H__
#define __SIMD_2D_H__

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif

void avg3_reg_vf32matrix(vfloat32** X, int n, vfloat32 **Y);
void avg3_rot_vf32matrix(vfloat32** X, int n, vfloat32 **Y);
void avg3_red_vf32matrix(vfloat32** X, int n, vfloat32 **Y);
void avg5_reg_vf32matrix(vfloat32** X, int n, vfloat32 **Y);
void avg5_rot_vf32matrix(vfloat32** X, int n, vfloat32 **Y);
void avg5_red_vf32matrix(vfloat32** X, int n, vfloat32 **Y);

void main_2D(int argc, char * argv[]);
    
#ifdef __cplusplus
}
#endif

#endif // __SIMD_2D_H__
