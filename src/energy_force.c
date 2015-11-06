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
                               misc_params * m_pars, float energy_long, 
                               float force_long, float temp )
{

   float force = 0.0;
   float pot_energy = 0.0;
   
   int atomi, atomj;
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
         
         }

      } 

   }

}

float minimum_image( float dist, float box_length, float half_box_length )
{
   float min_dist = dist;
   if (dist > half_box_length ) min_dist = dist - box_length; 
   if (dist < -half_box_length ) min_dist = dist + box_length;
   return min_dist; 
}