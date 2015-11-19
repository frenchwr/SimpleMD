#include "params.h"
#include "atoms.h"
#include "integrator.h"
#include "timer.h"

//**********************************************************************
// update_positions() function
//   - Update particle positions by numerical integration.
//   - Arguments:
//       - myatoms: struct containing all atomic information.
//       - m_pars: struct containing misc. parameters.
//**********************************************************************
void update_positions( Atoms * myatoms, const misc_params * m_pars )
{

   // Update particle positions with velocity Verlet algorithm
   timeit(2,0);
   int atomi;
   float const_fac = 0.5 * m_pars->xmassi * m_pars->dt;
   for ( atomi = 0; atomi < myatoms->N; atomi++ )
   {
      // compute factor for subsequent updates
      float vx_halfts_fac = const_fac * myatoms->fx[atomi];
      float vy_halfts_fac = const_fac * myatoms->fy[atomi];
      float vz_halfts_fac = const_fac * myatoms->fz[atomi];

      // update particle positions
      myatoms->xx[atomi] += myatoms->vx[atomi] * m_pars->dt + vx_halfts_fac * m_pars->dt;
      myatoms->yy[atomi] += myatoms->vy[atomi] * m_pars->dt + vy_halfts_fac * m_pars->dt;
      myatoms->zz[atomi] += myatoms->vz[atomi] * m_pars->dt + vz_halfts_fac * m_pars->dt;

      // compute velocity at half timestep, and store it as the 
      // particle velocity
      myatoms->vx[atomi] += vx_halfts_fac;
      myatoms->vy[atomi] += vy_halfts_fac;
      myatoms->vz[atomi] += vz_halfts_fac;
   }

}

//**********************************************************************
// update_velocities() function
//   - Update velocities of atoms by numerical integration.
//   - Arguments:
//       - myatoms: struct containing all atomic information.
//       - misc_params: struct containing misc. parameters.
//**********************************************************************
void update_velocities( Atoms * myatoms, const misc_params * m_pars )
{

   // Update particle velocities with velocity Verlet algorithm
   timeit(2,0);
   int atomi;
   float const_fac = 0.5 * m_pars->xmassi * m_pars->dt;
   for ( atomi = 0; atomi < myatoms->N; atomi++ )
   {
      myatoms->vx[atomi] += const_fac * myatoms->fx[atomi];     
      myatoms->vy[atomi] += const_fac * myatoms->fy[atomi];     
      myatoms->vz[atomi] += const_fac * myatoms->fz[atomi];     
   }
   timeit(2,1);

}

//**********************************************************************
// pbc() function
//   - Impose periodic boundary conditions.
//   - Arguments:
//       - myatoms: struct containing all atomic information.
//       - box_length: length of simulation cell.
//       - half_box_length: half of length of simulation cell.
//**********************************************************************
void pbc( Atoms * myatoms, const float box_length, const float half_box_length )
{

   int atomi;
   for ( atomi = 0; atomi < myatoms->N; atomi++ )
   {
      if (myatoms->xx[atomi] > half_box_length ) myatoms->xx[atomi] -= box_length; 
      if (myatoms->xx[atomi] < -half_box_length ) myatoms->xx[atomi] += box_length; 
      if (myatoms->yy[atomi] > half_box_length ) myatoms->yy[atomi] -= box_length; 
      if (myatoms->yy[atomi] < -half_box_length ) myatoms->yy[atomi] += box_length; 
      if (myatoms->zz[atomi] > half_box_length ) myatoms->zz[atomi] -= box_length; 
      if (myatoms->zz[atomi] < -half_box_length ) myatoms->zz[atomi] += box_length; 
   }
   timeit(2,1);

}