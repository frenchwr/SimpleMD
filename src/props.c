#include "atoms.h"
#include "params.h"
#include "props.h"
#include <stdio.h>

void calc_props( Atoms * myatoms, misc_params * m_pars, 
                 float U_long_range_corr, float V_long_range_corr, 
                 float temp, float * myprops )
{

   int atomi;
   float sumvsq = 0.0;
   for (atomi=0; atomi < myatoms->N; atomi++)
   {
      sumvsq += myatoms->vx[atomi] * myatoms->vx[atomi];
      sumvsq += myatoms->vy[atomi] * myatoms->vy[atomi];
      sumvsq += myatoms->vz[atomi] * myatoms->vz[atomi];
   }

   float xKE = 0.5 * m_pars->xmass * sumvsq;
   float temperature = 2.0 * xKE / (3.0 * m_pars->float_N * m_pars->kb );

   myprops[0] = xKE;
   myprops[1] = myatoms->pot_energy + U_long_range_corr;
   myprops[2] = xKE + myatoms->pot_energy + U_long_range_corr;
   myprops[3] = temperature;
   myprops[4] = m_pars->density * ( m_pars->kb * temperature - 
                myatoms->virial / ( 3.0 * m_pars->float_N ) -
                V_long_range_corr / 3.0 );

}

void print_header()
{

   printf(" Timestep     KE           PE         TotE        Temp      Pressure\n");

}

void print_props( float * myprops, int timestep )
{

   printf("%*d",7,timestep);   
   printf("  %10.7f   %10.7f   %10.7f   %7.2f   %13.10f\n",
          myprops[0],myprops[1],myprops[2],myprops[3],myprops[4]);   

}