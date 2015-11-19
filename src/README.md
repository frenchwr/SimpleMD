# Source directory

Below is a brief description of each source file, listed in the order in which they are invoked from the program.

- **mddriver.c**: contains the main simulation loop and calls functions from various files. Start here.

- **cl_parse.c**: parse command line to make adjusting simulation parameters a breeze.

- **atoms.c**: handles memory management for Atoms struct.

- **params.c**: sets parameters for simulation.

- **energy_force.c**: functions for computing energy and force acting on each particle. The most computationally expensive part of the program.

- **initialization.c**: functions for generating initial partical positions and velocities.

- **props.c**: thermodynamic properties computed here.

- **timer.c**: enables timing of execution of different portions of program.

- **print_traj.c**: prints trajectory of simulation to file.

- **integrator.c**: this is where the atom positions and velocities are updated.