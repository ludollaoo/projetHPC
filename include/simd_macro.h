

/* -------------------- */
/* --- simd_macro.h --- */
/* -------------------- */


#ifndef __SIMD_MACRO_H__
#define __SIMD_MACRO_H__

// a remplir

#define vec_load2(T, i, j) _mm_load_si128((uint8*) &T[i][j])
#define vec_store2(T, i, j, x) _mm_store_si128((uint8*) &T[i][j], x)

#define vec_or3(x0, x1, x2) _mm_or_si128(x0, _mm_or_si128(x1, x2))
#define vec_or5(x0, x1, x2, x3, x4) _mm_or_si128(x0, _mm_or_si128(x1, _mm_or_si128(x2, _mm_or_si128(x3, x4))))

#define vec_and3(x0, x1, x2) _mm_and_si128(x0, _mm_and_si128(x1, x2))
#define vec_and5(x0, x1, x2, x3, x4) _mm_and_si128(x0, _mm_and_si128(x1, _mm_and_si128(x2, _mm_and_si128(x3, x4))))

#define vec_set(x) _mm_set1_ps(x)

#endif // __SIMD_MACRO_H__
