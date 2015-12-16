# Simple MD Program

* This is a very basic NVE moleculer dynamics program that will
be used for the course I teach in the spring.

* This program borrows heavily from David Keffer's "The Working Person's 
Guide to Molecular Dynamics Simulations", although I have written the program in a different
language and also expanded/replaced certain parts of the program.

* The idea for the class is that students will start with this basic
serial version of the code and then add parallel support with PThreads,
OpenMP, MPI, CUDA, or whatever.

## Project Layout

- **bin/**: binary built to this directory.
- **images/**: photo gallery of simulation snapshots.
- **inc/**: contains header files with function prototypes, struct definitions, etc.
- **obj/**: object files stored in this directory.
- **src/**: source files.
- **Makefile**: automated build script.
- **simulate.sh**: shell script with examples for running program.

## Building Program

To build simply type:

```
make
```

If this is your first time to build the program you should see:

```
$ make
gcc -Iinc -lm -Wall -c src/atoms.c -o obj/atoms.o
gcc -Iinc -lm -Wall -c src/cl_parse.c -o obj/cl_parse.o
gcc -Iinc -lm -Wall -c src/energy_force.c -o obj/energy_force.o
gcc -Iinc -lm -Wall -c src/initialization.c -o obj/initialization.o
gcc -Iinc -lm -Wall -c src/integrator.c -o obj/integrator.o
gcc -Iinc -lm -Wall -c src/mddriver.c -o obj/mddriver.o
gcc -Iinc -lm -Wall -c src/params.c -o obj/params.o
gcc -Iinc -lm -Wall -c src/print_traj.c -o obj/print_traj.o
gcc -Iinc -lm -Wall -c src/props.c -o obj/props.o
gcc -Iinc -lm -Wall -c src/timer.c -o obj/timer.o
gcc -lm  obj/atoms.o obj/cl_parse.o obj/energy_force.o obj/initialization.o obj/integrator.o obj/mddriver.o obj/params.o obj/print_traj.o obj/props.o obj/timer.o -o bin/run_md
```

If you have not edited any files since last running make, then you should see:

```
$ make
make: `bin/run_md' is up to date.
```

Make automates the build process, so if you only edit a single source file, only that source file will be recompiled. If you want to blow away all the object files and the program binary, you can run:

```
$ make cleanall
```

while

```
$ make clean
```

will remove just the binary in **bin/**.

## Usage

To run from the project root directory simply type:

```
bin/run_md
```

This will run the program with default parameters. To see a list of command-line options and a list of defaults, pass **--help** as a command-line argument:

```
$ bin/run_md --help
Usage: ./run_md [-N <n_particles>] [-ts <n_timesteps>] [-xyz <xyz_file_output_frequency>] [-o <thermo_output_frequency>]
Defaults:
n_particles: 100
n_timesteps: 10000
xyz_file_output_fequency: 100
thermo_output_frequency: 100
```

The project root directory also contains a Bash script for running a number of pre-determined simulations. To run with the default parameters simply type:

```
bash simulate.sh
```

## Output

Below is an example of the output from a simulation with the default parameters using GCC 4.4.7 with no optimization on a Intel Xeon E5620 @ 2.40GHz.

```
[frenchwr@vmps10 md]$ bash simulate.sh 
running: bin/run_md -N 125
=======Command line arguments=======
N_atoms: 125
n_timesteps: 10000
xyz_file_output_frequency: 100
thermo_output_frequency: 100
====================================
box length: 2.419e+01 Angstrom
density: 8.832e-03 molecules/Ang^3
Beginning simulation....
 Timestep     KE          PE        TotE        Temp   Pressure
      0   3.883e-01  -8.432e-01  -4.54901e-01  150.00  -7.240e-05
    100   2.790e-01  -7.329e-01  -4.53904e-01  107.78  -7.789e-06
    200   3.488e-01  -8.022e-01  -4.53412e-01  134.75  -1.379e-05
    300   3.913e-01  -8.446e-01  -4.53270e-01  151.15  -1.782e-05
    400   3.670e-01  -8.203e-01  -4.53274e-01  141.76  -3.988e-06
    500   3.754e-01  -8.286e-01  -4.53236e-01  145.01  -7.795e-06
    600   3.850e-01  -8.383e-01  -4.53259e-01  148.73  -8.743e-06
    700   3.775e-01  -8.308e-01  -4.53237e-01  145.83  -1.073e-06
    800   4.006e-01  -8.539e-01  -4.53247e-01  154.75  -5.536e-06
    900   3.634e-01  -8.167e-01  -4.53250e-01  140.38  8.770e-06
   1000   3.879e-01  -8.412e-01  -4.53294e-01  149.84  -2.372e-06
   1100   3.943e-01  -8.476e-01  -4.53267e-01  152.33  -6.303e-06
   1200   3.781e-01  -8.314e-01  -4.53226e-01  146.07  -2.062e-06
   1300   3.886e-01  -8.419e-01  -4.53277e-01  150.13  -3.920e-06
   1400   3.756e-01  -8.289e-01  -4.53264e-01  145.09  4.032e-06
   1500   3.950e-01  -8.483e-01  -4.53284e-01  152.57  -7.619e-06
   1600   3.804e-01  -8.336e-01  -4.53252e-01  146.93  -4.261e-06
   1700   3.877e-01  -8.410e-01  -4.53306e-01  149.78  -7.130e-06
   1800   3.795e-01  -8.329e-01  -4.53360e-01  146.61  6.970e-06
   1900   4.003e-01  -8.536e-01  -4.53320e-01  154.63  -1.702e-06
   2000   3.875e-01  -8.408e-01  -4.53274e-01  149.68  5.651e-06
   2100   4.062e-01  -8.595e-01  -4.53301e-01  156.91  -3.320e-06
   2200   3.882e-01  -8.415e-01  -4.53267e-01  149.97  4.631e-06
   2300   3.997e-01  -8.530e-01  -4.53264e-01  154.42  -2.549e-06
   2400   4.112e-01  -8.645e-01  -4.53298e-01  158.84  -7.109e-06
   2500   4.067e-01  -8.600e-01  -4.53296e-01  157.12  -1.185e-06
   2600   4.078e-01  -8.611e-01  -4.53295e-01  157.55  -2.100e-06
   2700   4.009e-01  -8.542e-01  -4.53266e-01  154.87  -6.252e-07
   2800   4.122e-01  -8.655e-01  -4.53313e-01  159.24  7.340e-07
   2900   3.936e-01  -8.469e-01  -4.53310e-01  152.03  1.425e-06
   3000   3.914e-01  -8.447e-01  -4.53338e-01  151.18  5.180e-06
   3100   4.077e-01  -8.610e-01  -4.53313e-01  157.48  6.553e-07
   3200   3.946e-01  -8.479e-01  -4.53281e-01  152.43  2.449e-06
   3300   3.893e-01  -8.425e-01  -4.53243e-01  150.37  -4.636e-06
   3400   4.093e-01  -8.625e-01  -4.53203e-01  158.12  -1.571e-05
   3500   3.628e-01  -8.160e-01  -4.53259e-01  140.14  4.630e-06
   3600   3.925e-01  -8.457e-01  -4.53248e-01  151.61  -7.838e-06
   3700   3.749e-01  -8.282e-01  -4.53250e-01  144.82  -5.539e-06
   3800   3.874e-01  -8.406e-01  -4.53239e-01  149.64  -2.888e-08
   3900   4.067e-01  -8.599e-01  -4.53220e-01  157.09  -5.110e-06
   4000   4.027e-01  -8.559e-01  -4.53243e-01  155.54  -4.423e-06
   4100   3.806e-01  -8.338e-01  -4.53242e-01  147.01  6.911e-06
   4200   3.929e-01  -8.461e-01  -4.53235e-01  151.77  -6.156e-06
   4300   3.868e-01  -8.401e-01  -4.53255e-01  149.43  -5.675e-06
   4400   3.915e-01  -8.447e-01  -4.53232e-01  151.23  -5.125e-06
   4500   3.948e-01  -8.480e-01  -4.53245e-01  152.51  -2.586e-07
   4600   3.795e-01  -8.327e-01  -4.53226e-01  146.60  2.143e-06
   4700   3.847e-01  -8.379e-01  -4.53249e-01  148.60  -5.358e-06
   4800   3.860e-01  -8.392e-01  -4.53235e-01  149.09  7.694e-07
   4900   3.899e-01  -8.431e-01  -4.53258e-01  150.59  -3.229e-06
   5000   3.829e-01  -8.362e-01  -4.53322e-01  147.92  8.065e-07
   5100   3.987e-01  -8.520e-01  -4.53291e-01  154.00  -2.326e-06
   5200   3.938e-01  -8.471e-01  -4.53247e-01  152.14  3.772e-06
   5300   3.791e-01  -8.323e-01  -4.53232e-01  146.45  6.586e-06
   5400   3.723e-01  -8.257e-01  -4.53305e-01  143.83  4.653e-06
   5500   4.049e-01  -8.582e-01  -4.53289e-01  156.41  -4.113e-06
   5600   3.983e-01  -8.515e-01  -4.53253e-01  153.84  -6.733e-06
   5700   3.691e-01  -8.223e-01  -4.53198e-01  142.58  -2.884e-06
   5800   3.875e-01  -8.407e-01  -4.53179e-01  149.68  -1.105e-05
   5900   3.932e-01  -8.464e-01  -4.53210e-01  151.87  -1.305e-05
   6000   3.713e-01  -8.246e-01  -4.53263e-01  143.43  -6.830e-07
   6100   3.772e-01  -8.305e-01  -4.53275e-01  145.71  -2.825e-06
   6200   3.830e-01  -8.362e-01  -4.53247e-01  147.94  -1.005e-05
   6300   3.893e-01  -8.425e-01  -4.53222e-01  150.39  -1.361e-05
   6400   3.716e-01  -8.249e-01  -4.53231e-01  143.56  -1.096e-05
   6500   3.685e-01  -8.217e-01  -4.53238e-01  142.34  -1.192e-05
   6600   3.746e-01  -8.278e-01  -4.53249e-01  144.69  -1.545e-05
   6700   3.664e-01  -8.196e-01  -4.53227e-01  141.53  -1.215e-05
   6800   3.573e-01  -8.105e-01  -4.53258e-01  138.00  -4.989e-06
   6900   3.700e-01  -8.233e-01  -4.53256e-01  142.94  -9.059e-06
   7000   3.713e-01  -8.246e-01  -4.53278e-01  143.43  -1.882e-06
   7100   3.985e-01  -8.518e-01  -4.53257e-01  153.95  -7.574e-06
   7200   3.984e-01  -8.517e-01  -4.53299e-01  153.91  -7.369e-06
   7300   3.848e-01  -8.381e-01  -4.53301e-01  148.65  2.548e-06
   7400   3.888e-01  -8.421e-01  -4.53328e-01  150.20  -3.761e-06
   7500   3.859e-01  -8.392e-01  -4.53286e-01  149.06  -5.358e-06
   7600   3.845e-01  -8.378e-01  -4.53288e-01  148.52  -5.018e-06
   7700   3.688e-01  -8.222e-01  -4.53382e-01  142.47  4.063e-06
   7800   3.971e-01  -8.504e-01  -4.53355e-01  153.38  -1.063e-05
   7900   3.769e-01  -8.302e-01  -4.53262e-01  145.61  -5.815e-06
   8000   3.921e-01  -8.454e-01  -4.53275e-01  151.48  -9.699e-06
   8100   4.077e-01  -8.609e-01  -4.53248e-01  157.48  -9.742e-06
   8200   3.975e-01  -8.508e-01  -4.53256e-01  153.56  -6.213e-06
   8300   3.933e-01  -8.466e-01  -4.53227e-01  151.94  -1.480e-05
   8400   3.794e-01  -8.327e-01  -4.53269e-01  146.57  -1.214e-05
   8500   3.884e-01  -8.416e-01  -4.53245e-01  150.03  -1.574e-05
   8600   3.645e-01  -8.177e-01  -4.53195e-01  140.80  6.260e-07
   8700   4.011e-01  -8.543e-01  -4.53228e-01  154.94  -1.170e-06
   8800   3.558e-01  -8.090e-01  -4.53201e-01  137.44  1.323e-05
   8900   4.105e-01  -8.637e-01  -4.53233e-01  158.56  -5.024e-06
   9000   3.994e-01  -8.527e-01  -4.53275e-01  154.28  -5.071e-06
   9100   3.709e-01  -8.242e-01  -4.53266e-01  143.29  4.368e-06
   9200   3.877e-01  -8.410e-01  -4.53269e-01  149.78  -4.374e-06
   9300   3.713e-01  -8.245e-01  -4.53239e-01  143.43  6.201e-06
   9400   3.858e-01  -8.390e-01  -4.53186e-01  149.04  -7.370e-06
   9500   3.856e-01  -8.389e-01  -4.53262e-01  148.95  -1.216e-05
   9600   3.871e-01  -8.404e-01  -4.53272e-01  149.55  -7.571e-06
   9700   3.911e-01  -8.443e-01  -4.53223e-01  151.06  -6.837e-06
   9800   3.860e-01  -8.392e-01  -4.53197e-01  149.13  -7.472e-07
   9900   4.124e-01  -8.656e-01  -4.53237e-01  159.31  -9.298e-06
  10000   3.943e-01  -8.476e-01  -4.53270e-01  152.33  2.394e-06
Simulation Complete!
Total simulation time:              8.014 secs
Force/energy time:                  7.910 secs (98.70%)
Position/velocity update time:      0.086 secs ( 1.07%)
Thermo/trajectory output time:      0.016 secs ( 0.20%)
```

## Viewing Simulation

Copy the traj.xyz file to your local machine and visualize the simulation with free 
software like Visual Molecular Dynamic (http://www.ks.uiuc.edu/Research/vmd/). Here are a few example
snapshots:

<center>
rc="https://github.com/frenchwr/SimpleMD/blob/master/images/125atoms.png" alt="1">
rc="https://github.com/frenchwr/SimpleMD/blob/master/images/5000atoms.png" alt="1">
</center>
