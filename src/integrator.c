#include "params.h"
#include "atoms.h"
#include "integrator.h"

void update_positions( Atoms * myatoms, misc_params * m_pars )
{

   // Update particle positions with velocity Verlet algorithm
   int atomi;
   for ( atomi = 0; atomi < myatoms->N; atomi++ )
   {
      float dx = myatoms->vx[atomi] * m_pars->dt + 0.5 * myatoms->fx[atomi] * m_pars->xmassi * m_pars->dt2;
      float dy = myatoms->vy[atomi] * m_pars->dt + 0.5 * myatoms->fy[atomi] * m_pars->xmassi * m_pars->dt2;
      float dz = myatoms->vz[atomi] * m_pars->dt + 0.5 * myatoms->fz[atomi] * m_pars->xmassi * m_pars->dt2;
      myatoms->xx[atomi] += dx;
      myatoms->yy[atomi] += dy;
      myatoms->zz[atomi] += dz;

      myatoms->vx[atomi] += 0.5 * myatoms->fx[atomi] * m_pars->xmassi * m_pars->dt;
      myatoms->vy[atomi] += 0.5 * myatoms->fy[atomi] * m_pars->xmassi * m_pars->dt;
      myatoms->vz[atomi] += 0.5 * myatoms->fz[atomi] * m_pars->xmassi * m_pars->dt;
   }

}

void update_velocities( Atoms * myatoms, misc_params * m_pars )
{

   // Update particle velocities with velocity Verlet algorithm
   int atomi;
   for ( atomi = 0; atomi < myatoms->N; atomi++ )
   {
      myatoms->vx[atomi] += 0.5 * myatoms->fx[atomi] * m_pars->xmassi * m_pars->dt;
      myatoms->vy[atomi] += 0.5 * myatoms->fy[atomi] * m_pars->xmassi * m_pars->dt;
      myatoms->vz[atomi] += 0.5 * myatoms->fz[atomi] * m_pars->xmassi * m_pars->dt;
   }

}

void pbc( Atoms * myatoms, float box_length, float half_box_length )
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

}