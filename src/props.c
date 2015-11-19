#include "atoms.h"
#include "params.h"
#include "props.h"
#include "timer.h"
#include <stdio.h>

//**************************************************************************
// calc_props() function
//   - Compute thermodynamic properties of system.
//   - Arguments:
//       - myatoms: struct containing all atom information.
//       - m_pars: struc containing misc. parameters.
//       - U_long_range_corr: long-range correction to energy.
//       - V_long_range_corr: long-range correction to force.
//       - myprops: thermodynamic properties to print.
//**************************************************************************
void calc_props( const Atoms * myatoms, const misc_params * m_pars, 
                 const float U_long_range_corr, const float V_long_range_corr, 
                 float * myprops )
{

   timeit(3,0);
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

   myprops[0] = xKE; // kinetic energy
   myprops[1] = myatoms->pot_energy + U_long_range_corr; // potential energy
   myprops[2] = xKE + myatoms->pot_energy + U_long_range_corr; // total energy
   myprops[3] = temperature; // temperature
   myprops[4] = m_pars->density * ( m_pars->kb * temperature - 
                myatoms->virial / ( 3.0 * m_pars->float_N ) -
                V_long_range_corr / 3.0 ); // pressure

}

//**************************************************************************
// print_header() function
//   - Prints header (column labels) for thermodynamic output.
//   - No args.
//**************************************************************************
void print_header()
{

   printf(" Timestep     KE          PE        TotE        Temp   Pressure\n");

}

//**************************************************************************
// print_props() function
//   - Prints thermodynamic properties of system.
//   - Arguments:
//       - myprops: thermodynamic properties to print.
//       - timestep: current timestep of simulation.
//**************************************************************************
void print_props( const float * myprops, const int timestep )
{

   printf("%*d",7,timestep);   
   printf("   %.3e  %.3e  %.5e %7.2f  %.3e\n",
          myprops[0],myprops[1],myprops[2],myprops[3],myprops[4]);   
   timeit(3,1);

}