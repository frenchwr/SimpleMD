#include "params.h"
#include <math.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

//************************************************************************
// set_params() function
//   - Set simulation parameters.
//   - Arguments:
//       - len_jo: struct containing lennard jones interaction parameters.
//       - m_pars: struct containing misc. parameters.
//       - n_atoms: number of atoms in simulation.
//       - vol_norm: normal volume of simulation.
//************************************************************************
void set_params(lj_params * len_jo, misc_params * m_pars, 
                const int n_atoms, const float vol_norm)
{

   // LJ Potential Parameters
   len_jo->sig = 3.884; // collision diameter
   len_jo->sig6 = powf(len_jo->sig,6.0); // sig^6
   len_jo->sig12 = powf(len_jo->sig,12.0); // sig^12
   len_jo->eps = 137.0; // well depth (K)
   len_jo->rcut = 15.0; // interaction cutoff
   len_jo->rcut2 = len_jo->rcut * len_jo->rcut; // rcut^2
   len_jo->rcut3 = powf(len_jo->rcut,3.0); // rcut^3
   len_jo->rcut9 = powf(len_jo->rcut,9.0); // rcut^9

   // Other parameters
   m_pars->dt = 2.0; // timestep
   m_pars->float_N = (float)n_atoms; // number atoms cast as float
   float Vol = m_pars->float_N * vol_norm; // box volume
   m_pars->side = powf(Vol,1.0/3.0); // length of simulation cell
   m_pars->sideh = 0.5 * m_pars->side; // half length of simulation cell
   m_pars->density = 1.0 / vol_norm; // density
   m_pars->pi = 2.0 * asin(1.0);
   float MW = 16.042; // molecular weight (grams/mole)
   m_pars->kb = 0.00001380660; // Bolztmann's Constant (aJ/molecule/K)
   m_pars->xmass = MW * 100.0 / 6.0220; // mass of single particle
   m_pars->xmassi = 1.0 / m_pars->xmass; // inverse of mass of single particle

   len_jo->eps *= m_pars->kb; // convert well depth to appropriate units

}
