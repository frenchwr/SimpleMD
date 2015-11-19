#include "atoms.h"
#include "cl_parse.h"
#include "params.h"
#include "initialization.h"
#include "print_traj.h"
#include "energy_force.h"
#include "props.h"
#include "integrator.h"
#include "timer.h"
#include <math.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

// timer[0]: total simulation time
// timer[1]: energy/force computation time
// timer[2]: particle position/velocity update time
// timer[3]: thermo and trajectory print time
double timer[4]; // global to improve readability of code

// TODO: 
//      (1) add better documentation in code

//***************************************************************************
// driver() function
//   - Main body of program.
//   - Creates Atoms structure, allocates memory, initializes parameters,
//     and runs simulation.
//   - Arguments:
//       - arg_count: number of arguments passed from command line.
//       - arg_list: array of strings containing arguments from command line.
//***************************************************************************
void driver(const int arg_count, char ** arg_list)
{

   // parse command line
   //      Arguments:
   //                (1) Number of particles
   //                (2) Number of timesteps
   //                (3) xyz output frequency
   //                (4) thermo output frequency
   args cl = parse_command_line( arg_count, arg_list);

   // Allocate space to store atomic positions and velocities
   Atoms atoms; // see atoms.h for definition of Atoms data structure
   allocate_atoms( &atoms, cl.N); // allocate space on heap for storing atomic data

   // Specify Thermodynamic state
   float Temperature = 150.0; // temperature (K)
   float Vn = 1.0 / 0.008832; // specific volume (Ang^3/molecule)

   // Units are as follows:
   // length: Angstroms (1.0e-10 m)
   // time: fs (1.0e-15 s)
   // xmass = 1.0e-28 kg
   // energy = aJ (1.0e-18 J)
   // Temp = K
   
   // Parameter initialization
   lj_params lj; // parameters for computing interaction potential
   misc_params mp; // other miscellaneous parameters needed throughout simulation
   set_params( &lj, &mp, cl.N, Vn); // load parameters

   // Print a few of the computed parameters
   printf("box length: %.3e Angstrom\n",mp.side);
   printf("density: %.3e molecules/Ang^3\n",mp.density);

   // Compute the long range correction in energy and force
   // These values are constant throughout the simulation and compensate for the
   // total force/energy lost due to using a finite interaction cutoff
   float ulong, vlong;
   compute_long_range_correction( &lj, &mp, &ulong, &vlong);

   // initialization of atomic positions
   initialize_positions( &atoms, mp.side, mp.sideh);

   // initialization of atomic velocities
   initialize_velocities( &atoms, &mp, Temperature);   

   // open file for writing trajectory
   FILE * fp_out = NULL;
   if ( cl.xyz_freq != 0 ) fp_out = fopen("traj.xyz","w");
    
   // props[0]: kinetic energy
   // props[1]: potential energy
   // props[2]: total energy
   // props[3]: temperature
   // props[4]: pressure
   float props[5];

   compute_energy_and_force( &atoms, &lj, &mp ); // compute initial energy/force

   printf("Beginning simulation....\n");
   print_header();
   int istep;

   initialize_timer();
   timeit(0,0); // start timer
   for (istep=0; istep <= cl.n_timesteps; istep++)
   {
  
      if ( istep % cl.xyz_freq == 0 )
         print_xyz( fp_out, &atoms ); // prints to traj.xyz in current directory

      if ( istep % cl.thermo_freq == 0 || istep == cl.n_timesteps ) {
         calc_props( &atoms, &mp, ulong, vlong, props );
         print_props( props, istep ); // prints thermo output to screen
      }

      update_positions( &atoms, &mp ); // update particle positions for next timestep
      pbc( &atoms, mp.side, mp.sideh ); // impose periodic boundary conditions
      compute_energy_and_force( &atoms, &lj, &mp ); // compute energy/force for next timestep
      update_velocities( &atoms, &mp ); // update particle velocities for next timestep

   }
   timeit(0,1); // end timer

   printf("Simulation Complete!\n");
   print_timer();

   if ( cl.xyz_freq != 0 ) fclose(fp_out);
   free_atoms(&atoms);

}

//***********************************************************************
// main() function
//   - Required in all C programs.
//   - Execution of entire program begins here.
//   - Arguments:
//       - argc: number of arguments passed from command line.
//       - argv: array of strings containing arguments from command line.
//***********************************************************************
int main(int argc, char ** argv)
{

   driver( argc, argv);

   return 0;

}

