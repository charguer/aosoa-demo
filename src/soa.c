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

int main(int argc, char **argv) {
  char* mode = argv[1];

  data.x  = (float *) calloc(NUM_PARTICLES, sizeof(float));
  data.y  = (float *) calloc(NUM_PARTICLES, sizeof(float));
  data.z  = (float *) calloc(NUM_PARTICLES, sizeof(float));
  data.vx = (float *) calloc(NUM_PARTICLES, sizeof(float));
  data.vy = (float *) calloc(NUM_PARTICLES, sizeof(float));
  data.vz = (float *) calloc(NUM_PARTICLES, sizeof(float));
  data.c  = (float *) calloc(NUM_PARTICLES, sizeof(float));
  data.m  = (float *) calloc(NUM_PARTICLES, sizeof(float));
  data.v  = (float *) calloc(NUM_PARTICLES, sizeof(float));

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
