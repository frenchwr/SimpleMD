# Simple MD Program

* This is a very basic NVE moleculer dynamics program that will
be used for the course I teach in the spring.

* This program borrows heavily from David Keffer's "The Working Person's 
Guide to Molecular Dynamics Simulations", although I'm writing in a different
language and plan to expand/replace certain parts of the program.

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

## Usage

## Output