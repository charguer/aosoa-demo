#include "common.h"

typedef struct {
  // Position
  float* x;
  float* y;
  float* z;
  // Velocity
  float* vx;
  float* vy;
  float* vz;
  // Charge
  float* c;
  // Mass, volume
  float* m;
  float* v;
} particles;

particles data;

inline float* float_array_calloc_aligned(size_t size) {
  return (float*) calloc_aligned(ALIGNMENT, size * sizeof(float));
}

int main(int argc, char **argv) {
  char* mode = argv[1];

  data.x  = float_array_calloc_aligned(NUM_PARTICLES);
  data.y  = float_array_calloc_aligned(NUM_PARTICLES);
  data.z  = float_array_calloc_aligned(NUM_PARTICLES);
  data.vx = float_array_calloc_aligned(NUM_PARTICLES);
  data.vy = float_array_calloc_aligned(NUM_PARTICLES);
  data.vz = float_array_calloc_aligned(NUM_PARTICLES);
  data.c  = float_array_calloc_aligned(NUM_PARTICLES);
  data.m  = float_array_calloc_aligned(NUM_PARTICLES);
  data.v  = float_array_calloc_aligned(NUM_PARTICLES);

  if (strcmp(mode, "updates") == 0) {
    // Apply an in-place modification to every particle.
    for (long i = 0; i < NUM_PARTICLES; i++) {
      data.x[i] += data.vx[i];
    }
    for (long i = 0; i < NUM_PARTICLES; i++) {
      data.y[i] += data.vy[i] + 1.33 * data.c[i];
    }

  } else if (strcmp(mode, "populate") == 0) {
    // Populate the scene with particles in random positions.
    srand(time(NULL));
    for (int k = 0; k < NB_POPULATE; k++) {
      int i = rand() % NUM_PARTICLES;
      data.x[i]  = (float) rand();
      data.y[i]  = (float) rand();
      data.z[i]  = (float) rand();
      data.vx[i] = 0.;
      data.vy[i] = 0.;
      data.vz[i] = 0.;
      data.c[i]  = 1.;
      data.m[i]  = 1.;
      data.v[i]  = 1.;
    }
  }

  free(data.x);
  free(data.y);
  free(data.z);
  free(data.vx);
  free(data.vy);
  free(data.vz);
  free(data.c);
  free(data.m);
  free(data.v);

  return 0;
}
