#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_PARTICLES (1 << 27)
#define NB_POPULATE (1 << 22)

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

particle* data;

int main(int argc, char **argv) {
  char* mode = argv[1];

  data = (particle*) calloc(NUM_PARTICLES, sizeof(particle));

  if (strcmp(mode, "updates") == 0) {
    // Apply an in-place modification to every particle.
    for (int i = 0; i < NUM_PARTICLES; i++) {
      data[i].x += data[i].vx;
      data[i].y += data[i].vy + 1.33 * data[i].c;
    }

  } else if (strcmp(mode, "populate") == 0) {
    // Populate the scene with random particles at random positions.
    srand(time(NULL));
    for (int k = 0; k < NB_POPULATE; k++) {
      int i = rand() % NUM_PARTICLES;
      data[i].x  = (float) rand();
      data[i].y  = (float) rand();
      data[i].z  = (float) rand();
      data[i].vx = 0.;
      data[i].vy = 0.;
      data[i].vz = 0.;
      data[i].c  = 1.;
      data[i].m  = 1.;
      data[i].v  = 1.;
    }
  }

  free(data);

  return 0;
}
