#include "common.h"

#define BLOCK_SIZE (1 << 10)
#define NB_BLOCKS (NUM_PARTICLES / BLOCK_SIZE)

typedef struct {
  // Position
  float x, y, z;
  // Velocity
  float vx, vy, vz;
  // Charge
  float c;
  // Mass, volume
  float m, v;
} particle;

typedef particle particle_block[BLOCK_SIZE];
  // warning, the syntax is very strange, to mean: type particle_block = particle[BLOCK_SIZE].
  // alternative is:   typedef struct { particle[BLOCK_SIZE] block; } particle_block;
  // but then one needs to write an extra ".block" to access the data at the right type.
  // beware also that sizeof(particle_block) might not return what you expect.
particle_block* data; // data[NB_BLOCKS][BLOCK_SIZE]

int main(int argc, char **argv) {
  if (argc < 2) { return 1; }
  char* mode = argv[1];

  data = (particle_block*) calloc_aligned(ALIGNMENT, NUM_PARTICLES * sizeof(particle));
     // recall that NUM_PARTICLES = NB_BLOCKS * BLOCK_SIZE

  start_clock();
  if (strcmp(mode, "updates") == 0) {
    // Apply an in-place modification to every particle.

    // The 'for' and binding of 'i1' and 'i2' can then be replaced with:
    // for (int i1 = 0; i1 < NB_BLOCKS; i1++) {
    // for (int i2 = 0; i2 < BLOCK_SIZE; i2++) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
      int i1 = i / BLOCK_SIZE;
      int i2 = i % BLOCK_SIZE;
      data[i1][i2].x += data[i1][i2].vx;
      data[i1][i2].y += data[i1][i2].vy + 1.33 * data[i1][i2].c;
    }

  } else if (strcmp(mode, "populate") == 0) {
    // Populate the scene with random particles at random positions.
    srand(time(NULL));
    for (int k = 0; k < NB_POPULATE; k++) {
      int i = rand() % NUM_PARTICLES;
      int i1 = i / BLOCK_SIZE;
      int i2 = i % BLOCK_SIZE;
      data[i1][i2].x  = (float) rand();
      data[i1][i2].y  = (float) rand();
      data[i1][i2].z  = (float) rand();
      data[i1][i2].vx = 0.;
      data[i1][i2].vy = 0.;
      data[i1][i2].vz = 0.;
      data[i1][i2].c  = 1.;
      data[i1][i2].m  = 1.;
      data[i1][i2].v  = 1.;
    }
  }

  stop_clock_and_report();
  free(data);

  return 0;
}
