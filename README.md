# Purpose of the aosoa demo

This demo is intented to highlight the impact of data layout representation
on performance. It compares:

   - the "array of structure" representation (AoS)
   - the "structure of array" representation (SoA)
   - the "array of structure of fixed-size arrays" representation (AoSoA).

The demo shows that, depending on the use case, AoS or SoA is superior,
and that AoSoA may be a good compromise.


# Benchmark program

The program used for the benchmark is a simplified version of a real piece
of code that was used for numeric simulation of plasma physics.

The demo program involves a representation of particles. In the AoS presentation,
a particle consists of a record with numerous float fields.

```
   typedef struct { float x, y, z, vx, vy, vz, c, m, v; } particle;
```

The demo program features two scenarios. 

The first scenario performs an update of the position of every particle.
For each particle `p`, the code updates its position (fields `x` and `y`), based on 
the current position and the speed and charge (fields `vx`, `vy`, and `c`) of the particle.

```
   p.x += p.vx;
   p.y += p.vy + 1.33 * p.c;
```

The second scenario involves assignments at random indices in
an array of particles. In the code snippet below, `i` denotes the random
index and `data` denotes an array storing `NUM_PARTICLES` particles.
All the fields of the particle are updated:the position fields are set 
to random values, the other fields are set to constant values.

```
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
```

For each scenario, we measure the execution time, excluding the time required
for allocating and initializing the data.


# Source code

Check out the representation of the particles in each of the three
files located in `src/*.c`.

A few common constants are shared in `src/common.h`.


# Running the demo

To play the demo, execute the `run.py` script which:

   - compiles the program using GCC (a recent version is better),
   - executes the two scenarios with AoS, SoA, and AoSoA,
   - report the sum of the execution time over the two scenarios.

```
   python run.py  

   # possibly: python3 run.py

   # if you don't have Python installed, use the simplified script:
   ./run.sh
```

The demo runs for approximately 20 to 30 seconds in total.


# Example results

Example results on a standard laptop hardware.

```
updates using aos: 0.93
updates using soa: 0.36
updates using aosoa: 0.39

populate using aos: 0.55
populate using soa: 2.83
populate using aosoa: 0.85

total using aos: 1.47
total using soa: 3.19
total using aosoa: 1.24
```

Note that the binary actually run for longer than the reported execution time
due to the time required for initializing the data.


# Interpretation

The first scenario, namely `updates`, is favorable to the "structure of arrays"
(SoA) representation. Indeed, with this representation, SIMD optimizations are
possible, processing batches of up to 16 particles at once on a hardware with
512-bit registers. Even processing batches 4 particles lead to significant speedups.

The second scenario, namely `populate`, is favorable to the "array of structures"
(AoS) representation. Indeed, with this representation, all the fields that are
written are adjacent in memory.

The AoSoA representation combines the benefits of both representation.
It delivers in-between performance. Depending on the exact ratio of operations
For a scenario like `updates`, it is essentially as fast as SoA, because
data can be processed by batches. For a scenario like `populate`, it performs
not quite as good as AoS, but much better than SoA, because the memory cells
to be updated are not too far appart in the main memory.


# Take-away message

Depending on the kind of operation performed by an algorithm, either SoA or AoS
can be significantly faster than the other. In extreme cases, it may be worth
switching between the two representations in the middle of a program, even though
moving all the data can be fairly expensive. In many other cases, the
AoSoA representation provides a great compromise.

The main challenge with writing a program in AoSoA style is that it somewhat
complicates the code, even more than SoA. Writing AoSoA code by hand is
certainly not a pleasant job. However, generating AoSoA code might be a 
pleasant hobby.


