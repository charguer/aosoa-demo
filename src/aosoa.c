#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BLOCK_SIZE (1 << 10)
#define NB_BLOCKS (1 << 17)
#define NUM_PARTICLES (1 << 27) // (= BLOCK_SIZE * NB_BLOCKS)
#define NB_POPULATE (1 << 22)

typedef struct {
  // Position
  float x[BLOCK_SIZE];
  float y[BLOCK_SIZE];
  float z[BLOCK_SIZE];
  // Velocity
  float vx[BLOCK_SIZE];
  float vy[BLOCK_SIZE];
  float vz[BLOCK_SIZE];
  // Charge
  float c[BLOCK_SIZE];
  // Mass, volume
  float m[BLOCK_SIZE];
  float v[BLOCK_SIZE];
} particle_block;

particle_block* data;

int main(int argc, char **argv) {
  char *mode = argv[1];

  data = (particle_block*) calloc(NB_BLOCKS, sizeof(particle_block));

  if (strcmp(mode, "updates") == 0) {
    // Apply an in-place modification to every particle.
    for (int i = 0; i < NB_BLOCKS; i++) {
      particle_block* b = &data[i];
      for (int j = 0; j < BLOCK_SIZE; j++) {
        b->x[j] += b->vx[j];
      }
      for (int j = 0; j < BLOCK_SIZE; j++) {
        b->y[j] += b->vy[j] + 1.33 * b->c[j];
      }
    }

  } else if (strcmp(mode, "populate") == 0) {
    // Populate the scene with particles in random positions.
    srand(time(NULL));
    for (int k = 0; k < NB_POPULATE; k++) {
      int index = rand() % NUM_PARTICLES;
      int i = index / BLOCK_SIZE;
      int j = index % BLOCK_SIZE;
      data[i].x[j]  = (float) rand();
      data[i].y[j]  = (float) rand();
      data[i].z[j]  = (float) rand();
      data[i].vx[j] = 0.;
      data[i].vy[j] = 0.;
      data[i].vz[j] = 0.;
      data[i].c[j]  = 1.;
      data[i].m[j]  = 1.;
      data[i].v[j]  = 1.;
    }
  }

  free(data);

  return 0;
}
