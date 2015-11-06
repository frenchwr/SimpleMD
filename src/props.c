#include "atoms.h"
#include "params.h"
#include "props.h"

void calc_props( Atoms * myatoms, misc_params * m_pars, 
                 float U_long_range_corr, float temp, float * myprops )
{

   int atomi;
   float sumvsq = 0.0;
   for (atomi=0; atomi < myatoms->N; atomi++)
   {
      sumvsq += myatoms->vx[atomi] * myatoms->vx[atomi];
      sumvsq += myatoms->vy[atomi] * myatoms->vy[atomi];
      sumvsq += myatoms->vz[atomi] * myatoms->vz[atomi];
   }

   //myprops[0] = 0.5 * m_pars->xmass;

}