#include "atoms.h"
#include "cl_parse.h"
#include "params.h"
#include "initialization.h"
#include <math.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

// forward declarations
//
// TODO:
//       - Put print_xyz into external file
//
void driver(int,char **);
void print_xyz(FILE *,Atoms *, int);
void calc_energy();

// main function
int main(int argc, char ** argv)
{

   driver( argc, argv);

   return 0;

}

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

   // parameters for long range energy correction
   // TODO: move this to the function(s) that calculates energy and force
   float ulongpre = mp.float_N * 8.0 * lj.eps * mp.pi * mp.density;
   float ulong = ulongpre * ( lj.sig12 / ( 9.0 * lj.rcut9 ) - lj.sig6 / ( 6.0 * lj.rcut3 ) );
   float vlongpre = 96.0 * lj.eps * mp.pi * mp.density;
   float vlong = -1.0 * vlongpre * ( lj.sig12 / ( 9.0 * lj.rcut9 ) - lj.sig6 / ( 6.0 * lj.rcut3 ) ); 

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
         print_xyz( fp_out, &atoms, cl.N);

      if ( i % cl.thermo_freq == 0 ) {
         // calculate properties
         // output properties
      }

   }


   if ( cl.xyz_freq != 0 ) fclose(fp_out);
   free_atoms(&atoms);
}

void print_xyz(FILE * handle,Atoms * myatoms, int n_atoms)
{

   fprintf(handle,"%d\n",n_atoms);
   fprintf(handle,"atoms\n");
   int i;
   for (i=0; i<n_atoms; i++) {
      fprintf(handle,"C     %10.5f %10.5f %10.5f\n",
              myatoms->xx[i],
              myatoms->yy[i],
              myatoms->zz[i] );
   }

}

void calc_energy()
{

}
