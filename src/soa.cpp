#include "common_cpp.h"

float* float_array_calloc_aligned(size_t size) {
  return (float*) calloc_aligned(ALIGNMENT, size * sizeof(float));
}

typedef struct {
  // Position
  ALIGNED float* x;
  ALIGNED float* y;
  ALIGNED float* z;
  // Velocity
  ALIGNED float* vx;
  ALIGNED float* vy;
  ALIGNED float* vz;
  // Charge
  ALIGNED float* c;
  // Mass, volume
  ALIGNED float* m;
  ALIGNED float* v;

  void alloc() {
    x  = float_array_calloc_aligned(NUM_PARTICLES);
    y  = float_array_calloc_aligned(NUM_PARTICLES);
    z  = float_array_calloc_aligned(NUM_PARTICLES);
    vx = float_array_calloc_aligned(NUM_PARTICLES);
    vy = float_array_calloc_aligned(NUM_PARTICLES);
    vz = float_array_calloc_aligned(NUM_PARTICLES);
    c  = float_array_calloc_aligned(NUM_PARTICLES);
    m  = float_array_calloc_aligned(NUM_PARTICLES);
    v  = float_array_calloc_aligned(NUM_PARTICLES);
  }

  void free() {
    free(x);
    free(y);
    free(z);
    free(vx);
    free(vy);
    free(vz);
    free(c);
    free(m);
    free(v);
  }

} particles;


particles data;

int main(int argc, char **argv) {
  if (argc < 2) { return 1; }
  char* mode = argv[1];

  data.alloc();

  start_clock();
  if (strcmp(mode, "updates") == 0) {
    // Apply an in-place modification to every particle.
    /* Alignement does not seem to be automatically detected
    for (long i = 0; i < NUM_PARTICLES; i++) {
      data.x[i] += data.vx[i];
    }
    for (long i = 0; i < NUM_PARTICLES; i++) {
      data.y[i] += data.vy[i] + 1.33 * data.c[i];
    }
    */
    float* data_x = (float*)__builtin_assume_aligned(data.x, ALIGNMENT);
    float* data_vx = (float*)__builtin_assume_aligned(data.vx, ALIGNMENT);
    float* data_y = (float*)__builtin_assume_aligned(data.y, ALIGNMENT);
    float* data_vy = (float*)__builtin_assume_aligned(data.vy, ALIGNMENT);
    float* data_c = (float*)__builtin_assume_aligned(data.c, ALIGNMENT);
    for (long i = 0; i < NUM_PARTICLES; i++) {
      data_x[i] += data_vx[i];
    }
    for (long i = 0; i < NUM_PARTICLES; i++) {
      data_y[i] += data_vy[i] + 1.33 * data_c[i];
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
  stop_clock_and_report();
  particles_free(&data);

  return 0;
}
