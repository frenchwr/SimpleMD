#include "params.h"
#include <math.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

void set_params(lj_params * len_jo, misc_params * m_pars, 
                const int n_atoms, const float vol_norm)
{

   // LJ Potential Parameters
   len_jo->sig = 3.884; // collision diameter
   len_jo->sig6 = powf(len_jo->sig,6.0);
   len_jo->sig12 = powf(len_jo->sig,12.0);
   len_jo->eps = 137.0; // well depth (K)
   len_jo->rcut = 15.0; // interaction cutoff
   len_jo->rcut2 = len_jo->rcut * len_jo->rcut;
   len_jo->rcut3 = powf(len_jo->rcut,3.0);
   len_jo->rcut9 = powf(len_jo->rcut,9.0);

   // Other parameters
   m_pars->dt = 2.0; // timestep
   m_pars->float_N = (float)n_atoms;
   float Vol = m_pars->float_N * vol_norm; // box volume
   m_pars->side = powf(Vol,1.0/3.0);
   m_pars->sideh = 0.5 * m_pars->side;
   m_pars->density = 1.0 / vol_norm;
   m_pars->pi = 2.0 * asin(1.0);
   float MW = 16.042; // molecular weight (grams/mole)
   m_pars->kb = 0.00001380660; // Bolztmann's Constant (aJ/molecule/K)
   m_pars->xmass = MW * 100.0 / 6.0220;
   m_pars->xmassi = 1.0 / m_pars->xmass;
   len_jo->eps *= m_pars->kb;

}
