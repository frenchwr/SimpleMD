#include "atoms.h"
#include "cl_parse.h"
#include "params.h"
#include "initialization.h"
#include "print_traj.h"
#include "energy_force.h"
#include <math.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

// driver
void driver(int argc, char ** argv)
{

   // parse command line
   //      Arguments:
   //                (1) Number of particles
   //                (2) Number of timesteps
   //                (3) xyz output frequency
   //                (4) thermo output frequency
   args cl = parse_command_line( argc, argv);

   // Allocate space to store atomic positions and velocities
   Atoms atoms; 
   allocate_atoms( &atoms, cl.N);

   // initialization of parameters
   // Units are as follows:
   // length: Angstroms (1.0e-10 m)
   // time: fs (1.0e-15 s)
   // xmass = 1.0e-28 kg
   // energy = aJ (1.0e-18 J)
   // Temp = K
   //
   // Specify Thermodynamic state
   float T = 150.0; // temperature (K)
   float Vn = 113.23; // specific volume (Ang^3/molecule)

   lj_params lj;
   misc_params mp;
   set_params( &lj, &mp, cl.N, Vn);

   float ulong, vlong;
   compute_long_range_correction( &lj, &mp, &ulong, &vlong);

   // initialization of atomic positions
   initialize_positions( &atoms, mp.side);

   // initialization of atomic velocities
   initialize_velocities( &atoms, &mp, T);   

   // main loop:
   //           (1) solve for energy/force
   //           (2) update particle positions/velocities

   FILE *fp_out;
   if ( cl.xyz_freq != 0 ) fp_out = fopen("traj.xyz","w");
   
   int i;
   for (i=0; i < cl.n_timesteps; i++)
   {
      if ( i % cl.xyz_freq == 0 )
         print_xyz( fp_out, &atoms );

      if ( i % cl.thermo_freq == 0 ) {
         // calculate properties
         // output properties
      }

      compute_energy_and_force( &atoms, &lj, &mp, ulong, vlong, T );

   }


   if ( cl.xyz_freq != 0 ) fclose(fp_out);
   free_atoms(&atoms);
}

// main function
int main(int argc, char ** argv)
{

   driver( argc, argv);

   return 0;

}

