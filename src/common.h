
// Benchmark parameters
#define NUM_PARTICLES (1 << 27)
#define NB_POPULATE (1 << 22)


// Common includes
#include <stdlib.h>
#include <time.h>
#include <string.h>



// For an allocation to be aligned, use the macro ALIGNED after a type.

#define ALIGNEDAT 32
#define ALIGNED __attribute__((aligned(ALIGNEDAT)))


/*
// If the architecture supports vector size 512 (AVX-512 instructions)
#if defined(__AVX512F__)
const int VEC_ALIGN = 64;
// else if it supports vector size 256 (AVX instructions)
#elif defined(__AVX__)
const int VEC_ALIGN = 32;
// else probably it supports vector size 128 (SSE instructions).
#else
const int VEC_ALIGN = 16;
#endif

#if defined(__ICC) || defined(__INTEL_COMPILER) // Intel ICC/ICPC
#    if (__INTEL_COMPILER_BUILD_DATE >= 20150805)
#        define USING_C11
#    endif
#elif defined(__GNUC__)                         // GCC
#    if ((__GNUC__ > 4) || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 9)))
#        define USING_C11
#    endif
#else
#    define USING_C11
#endif

#if defined(USING_C11)
#    define ALIGNED _Alignas(alignment)
#else
#    define ALIGNED __attribute__((aligned(alignment)))
#endif
*/

