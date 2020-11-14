

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

#define vec_left1(v1, v2) (vuint8)_mm_shuffle_pd(_mm_srli_si128((vuint8)_mm_shuffle_pd(_mm_shufflehi_epi16(v1, _MM_SHUFFLE(3, 3, 3, 3)), v2, 0b01),7),_mm_slli_si128(v2, 1), 0b10)

#define vec_left2(v1, v2) (vuint8)_mm_shuffle_pd(_mm_srli_si128((vuint8)_mm_shuffle_pd(_mm_shufflehi_epi16(v1, _MM_SHUFFLE(3, 3, 3, 3)), v2, 0b01),6),_mm_slli_si128(v2, 2), 0b10)

#define vec_right1(v1, v2) (vuint8)_mm_shuffle_pd(_mm_srli_si128(v1, 1), _mm_slli_si128((vuint8)_mm_shuffle_pd(v1, _mm_shufflelo_epi16(v2, _MM_SHUFFLE(0, 0, 0, 0)), 0b01),7), 0b10)

#define vec_right2(v1, v2) (vuint8)_mm_shuffle_pd(_mm_srli_si128(v1, 2), _mm_slli_si128((vuint8)_mm_shuffle_pd(v1, _mm_shufflelo_epi16(v2, _MM_SHUFFLE(0, 0, 0, 0)), 0b01),6), 0b10)

#endif // __SIMD_MACRO_H__
