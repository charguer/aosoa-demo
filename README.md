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

The first scenario involves assignments at random indices in
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

The second scenario performs an update of the position of every particle.
For each particle `p`, the code updates its position (fields `x` and `y`), based on 
the current position and the speed and charge (fields `vx`, `vy`, and `c`) of the particle.

```
   p.x += p.vx;
   p.y += p.vy + 1.33 * p.c;
```


# Running the demo

To play the demo, execute the command:

```
   python run.py
```

The execution of this script requires Python and GCC.

If necessary, it is not hard to compile and execute the files by hand,
simply passing the argument "updates" or "populate" to the binary files
associated with each of the source files from the `src` folder.


# Example results

Example results on a standard laptop hardware.

```
updates using aos: 1.91
updates using soa: 0.87
updates using aosoa: 1.68

populate using aos: 1.77
populate using soa: 3.16
populate using aosoa: 2.17

total using aos: 3.68
total using soa: 4.03
total using aosoa: 3.85
```


# Interpretation

The first scenario, namely `populate`, is favorable to the "array of structures"
(AoS) representation. Indeed, with this representation, all updates are performed
at consecutive memory locations.

The second scenario, namely `updates`, is favorable to the "structure of arrays"
(SoA) representation. Indeed, with this representation, SIMD optimizations are
possible, processing batches of up to 16 particles at once on a hardware with
512-bit registers. Even processing batches 4 particles lead to significant speedups.

The AoSoA representation combines the benefits of both representation.
It delivers in-between performance. Depending on the exact ratio of operations
like in the first scenario versus those like in the second scenario, the
AoSoA representation might win overall.


