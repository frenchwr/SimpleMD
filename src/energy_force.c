#include "energy_force.h"
#include "params.h"
#include "atoms.h"

void compute_long_range_correction(lj_params * len_jo, misc_params * m_pars,
                                   float * energy_long, float * force_long )
{

   float ulongpre = m_pars->float_N * 8.0 * len_jo->eps * 
                    m_pars->pi * m_pars->density;
   *energy_long = ulongpre * ( len_jo->sig12 / ( 9.0 * len_jo->rcut9 ) - 
                               len_jo->sig6 / ( 6.0 * len_jo->rcut3 ) );

   float vlongpre = 96.0 * len_jo->eps * m_pars->pi * m_pars->density;
   *force_long = -1.0 * vlongpre * ( len_jo->sig12 / ( 9.0 * len_jo->rcut9 ) - 
                                     len_jo->sig6 / ( 6.0 * len_jo->rcut3 ) ); 

}

void compute_energy_and_force( Atoms * myatoms, lj_params * len_jo, 
                               misc_params * m_pars )
{

   int atomi, atomj;
   for (atomi=0; atomi < myatoms->N; atomi++)
   {
      myatoms->fx[atomi] = 0.0;
      myatoms->fy[atomi] = 0.0;
      myatoms->fz[atomi] = 0.0;
   }
   myatoms->pot_energy = 0.0;
   
   for (atomi=0; atomi < myatoms->N; atomi++)
   {

      for (atomj=atomi+1 ; atomj < myatoms->N; atomj++)
      {

         float xxi = myatoms->xx[atomi] - myatoms->xx[atomj];
         xxi = minimum_image( xxi, m_pars->side, m_pars->sideh );
         float yyi = myatoms->yy[atomi] - myatoms->yy[atomj];
         yyi = minimum_image( yyi, m_pars->side, m_pars->sideh );
         float zzi = myatoms->zz[atomi] - myatoms->zz[atomj];
         zzi = minimum_image( zzi, m_pars->side, m_pars->sideh );

         float dis2 = xxi*xxi + yyi*yyi + zzi*zzi;
         if ( dis2 <= len_jo->rcut2 )
         {
            float dis2i = 1.0 / dis2;
            float dis6i = dis2i * dis2i * dis2i;
            float dis12i = dis6i * dis6i;
            myatoms->pot_energy += len_jo->sig12 * dis12i - 
                                   len_jo->sig6 * dis6i;
            float fterm = dis2i * ( 2.0 * len_jo->sig12 * dis12i -
                                          len_jo->sig6 * dis6i );
            
            myatoms->fx[atomi] += fterm * xxi;
            myatoms->fy[atomi] += fterm * yyi;
            myatoms->fz[atomi] += fterm * zzi;
            myatoms->fx[atomj] -= fterm * xxi;
            myatoms->fy[atomj] -= fterm * yyi;
            myatoms->fz[atomj] -= fterm * zzi;
         
         }

      } 

   }
   for (atomi=0; atomi < myatoms->N; atomi++)
   {
      myatoms->fx[atomi] *= 24.0 * len_jo->eps;
      myatoms->fy[atomi] *= 24.0 * len_jo->eps;
      myatoms->fz[atomi] *= 24.0 * len_jo->eps;
   }
   myatoms->pot_energy *= 4.0 * len_jo->eps;

}

float minimum_image( float dist, float box_length, float half_box_length )
{
   float min_dist = dist;
   if (dist > half_box_length ) min_dist = dist - box_length; 
   if (dist < -half_box_length ) min_dist = dist + box_length;
   return min_dist; 
}