
// Benchmark parameters
#define NUM_PARTICLES (1 << 27)
#define NB_POPULATE (1 << 22)


// Common includes
#include <stdlib.h>
#include <time.h>
#include <string.h>

// calloc_aligned combines calloc and alloc_aligned
inline void* calloc_aligned(size_t alignment, size_t size) {
  void* p = aligned_alloc(alignment, size);
  memset(p, 0, size);
  return p;

}

// If the architecture supports vector size 512 (AVX-512 instructions)
#if defined(__AVX512F__)
#define ALIGNMENT 64
// else if it supports vector size 256 (AVX instructions)
#elif defined(__AVX__)
#define ALIGNMENT 32
// else probably it supports vector size 128 (SSE instructions).
#else
#define ALIGNMENT 16
#endif

// For an allocation to be aligned, use the macro ALIGNED before a type.
#define ALIGNED _Alignas(ALIGNMENT)
// Note: before C11, syntax was "type __attribute__((aligned(ALIGNMENT)))"