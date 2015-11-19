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

This will run the program with default parameters. To see a list of command-line options and a list of defaults, pass --help as a command-line argument:

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