# Source directory

- **mddriver.c**: contains the main simulation loop and calls functions from various files. Start here.

- **integrator.c**: this is where the atom positions and velocities are updated.

- **energy_force.c**: functions for computing energy and force acting on each particle. The most computationally expensive part of the program.

- **props.c**: thermodynamic properties computed here.

- **initialization.c**: functions for generating initial partical positions and velocities.

- **cl_parse.c**: parse command line to make adjusting simulation parameters a breeze.