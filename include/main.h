#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "omp.h"
#include "test_sequentielle.h"
#include "test_SIMD.h"


#include "SD.h"
#include "SD_sequentielle.h"
#include "SD_SIMD.h"
#include "SD_SIMD_opti.h"
#include "SD_SIMD_opti_openMP.h"
#include "utils.h"
#include "benchmark.h"

// Pour morpho
//#include "mutils.h"
#include "mymacro.h"
#include "simd_macro.h"
#include "projet_util.h"
#include "morpho.h"
#include "morpho_SIMD.h"
#include "morpho_SIMD_opti.h"
#include "morpho_SIMD_opti_openMP.h"



#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)
#define Vmin 1
#define Vmax 254
#define NOIR 0
#define BLANC 255
