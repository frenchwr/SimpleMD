#include "initialization.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

//**********************************************************************
// initialize_positions() function
//   - Initializes atomic positions on a simple lattice.
//   - Arguments:
//       - myatoms: struct containing all atomic information.
//       - box_length: length of simulation cell.
//       - half_box_length: half the length of the simulation cell.
//**********************************************************************
void initialize_positions(Atoms * myatoms, const float box_length, 
                          const float half_box_length)
{

   // determine number of atoms to place along each direction
   int n_atoms = myatoms->N;
   float float_N = (float)n_atoms;
   float atoms1d_float = cbrtf( float_N ); // N^(1/3), from <math.h>
   int atoms1d_round = (int)atoms1d_float; // number of atoms along single direction
   float atoms1d_round_float = (float)atoms1d_round;
   if ( atoms1d_float - atoms1d_round_float > 1.0E-14 ) {
      atoms1d_round++;
      atoms1d_round_float = (float)atoms1d_round;
   }

   // position atoms on simple 3d lattice
   int cur_atom_cnt = 0;
   float atom_offset = box_length / atoms1d_round_float;
   int ix,iy,iz;
   for ( ix=0; ix < atoms1d_round; ix++) {
      for ( iy=0; iy < atoms1d_round; iy++) {
         for ( iz=0; iz < atoms1d_round; iz++) {
            if ( cur_atom_cnt < n_atoms ) {
               myatoms->xx[cur_atom_cnt] = atom_offset * (float)ix - half_box_length;
               myatoms->yy[cur_atom_cnt] = atom_offset * (float)iy - half_box_length;
               myatoms->zz[cur_atom_cnt] = atom_offset * (float)iz - half_box_length;
            }
            cur_atom_cnt++;
         }
      }
   }

}

//**************************************************************************
// initialize_velocities() function
//   - Scale velocities randomly, and scale to target temperature of system.
//   - Arguments:
//       - myatoms: struct containing all atomic information.
//       - m_pars: struct containing misc. parameters.
//       - temp: temperature of system.
//**************************************************************************
void initialize_velocities(Atoms * myatoms, const misc_params * m_pars, 
                           const float temp)
{
   // temperature factor for velocity scaling
   float tempfac = 3.0 * m_pars->float_N * m_pars->kb * m_pars->xmassi * temp;  

   // generate random seed based on the current time
   // for initializing the random number generator
   srand((unsigned int)time(NULL));

   int natoms = myatoms->N;
   int i;
   // random velocities from -1 to 1
   for (i=0; i<natoms; i++) {
      myatoms->vx[i] = 2.0 * (float)rand() / (float)(RAND_MAX) - 1.0;
      myatoms->vy[i] = 2.0 * (float)rand() / (float)(RAND_MAX) - 1.0;
      myatoms->vz[i] = 2.0 * (float)rand() / (float)(RAND_MAX) - 1.0;
   }

   float sumx=0.0, sumy=0.0, sumz=0.0;
   // enforce zero net momentum
   for (i=0; i<natoms; i++) {
      sumx += myatoms->vx[i];
      sumy += myatoms->vy[i];
      sumz += myatoms->vz[i];
   }
   for (i=0; i<natoms; i++) {
      myatoms->vx[i] -= sumx / (float)natoms;
      myatoms->vy[i] -= sumy / (float)natoms;
      myatoms->vz[i] -= sumz / (float)natoms;
   }

   // scale velocities to set point temperature
   float sumvsq = 0.0;
   for (i=0; i<natoms; i++) {
      sumvsq += myatoms->vx[i] * myatoms->vx[i] +
                myatoms->vy[i] * myatoms->vy[i] +
                myatoms->vz[i] * myatoms->vz[i];
   }
   float scaling = sqrt(tempfac/sumvsq);
   for (i=0; i<natoms; i++) {
      myatoms->vx[i] *= scaling;
      myatoms->vy[i] *= scaling;
      myatoms->vz[i] *= scaling;
   }
   
}