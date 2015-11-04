#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include "atoms.h"
#include "cl_parse.h"

typedef struct {
   float sig; // collision diameter
   float sig6; // sig^6
   float sig12; // sig^12
   float eps; // well depth (K)
   float rcut; // interaction cutoff
   float rcut2; // rcut^2
   float rcut3; // rcut^3
   float rcut9; // rcut^9
} lj_params;

typedef struct {
   float dt; // timestep
   float dt2;
   float dt2h;
   float pi;
   float kb; // Bolztmann's Constant (aJ/molecule/K)
   float MW; // molecular weight (grams/mole)
   float float_N;
   float Vol;
   float side;
   float sideh;
   float density;
} misc_params;

// forward declarations
void driver(int,char **);
void allocate_atoms(Atoms *,int);
float * safe_malloc_float(int);
void free_atoms(Atoms *);
void print_atoms(Atoms *);
void print_xyz(FILE *,Atoms *, int);
void initialize_positions(Atoms *, float);
void initialize_velocities(Atoms *, float);
void calc_energy();

// main function
int main(int argc, char ** argv)
{

   driver(argc,argv);

   return 0;

}

// driver
void driver(int argc, char ** argv)
{

   // parse command line
   //      Arguments:
   //                (1) Number of particles
   //                (2) Number of timesteps
   //                (3) xyz output frequency
   //                (4) thermo output frequency
   args cl_args = parse_command_line(argc,argv);
   int N = cl_args.N; // not sure why I'm doing this...just use cl_args
   Atoms atoms; 
   allocate_atoms(&atoms,N);

   // initialization of parameters
   // Units are as follows:
   // length: Angstroms (1.0e-10 m)
   // time: fs (1.0e-15 s)
   // xmass = 1.0e-28 kg
   // energy = aJ (1.0e-18 J)
   // Temp = K
   //
   // Specify Thermodynamic state
   float T = 150.0; // temperature (K)
   float Vn = 113.23; // specific volume (Ang^3/molecule)

   // LJ Potential Parameters
   lj_params lj;
   lj.sig = 3.884; // collision diameter
   lj.sig6 = powf(lj.sig,6.0);
   lj.sig12 = powf(lj.sig,12.0);
   lj.eps = 137.0; // well depth (K)
   lj.rcut = 15.0; // interaction cutoff
   lj.rcut2 = lj.rcut * lj.rcut;
   lj.rcut3 = powf(lj.rcut,3.0);
   lj.rcut9 = powf(lj.rcut,9.0);

   // Other parameters
   misc_params mp;
   mp.dt = 2.0; // timestep
   mp.dt2 = mp.dt * mp.dt;
   mp.dt2h = 0.5 * mp.dt2;
   mp.float_N = (float)N;
   mp.Vol = mp.float_N * Vn;
   mp.side = powf(mp.Vol,1.0/3.0);
   mp.sideh = 0.5 * mp.side;
   mp.density = 1.0 / Vn;
   mp.pi = 2.0 * asin(1.0);
   mp.MW = 16.042; // molecular weight (grams/mole)
   mp.kb = 0.00001380660; // Bolztmann's Constant (aJ/molecule/K)
   lj.eps *= mp.kb;

   // parameters for long range energy correction
   float ulongpre = mp.float_N * 8.0 * lj.eps * mp.pi * mp.density;
   float ulong = ulongpre * ( lj.sig12 / ( 9.0 * lj.rcut9 ) - lj.sig6 / ( 6.0 * lj.rcut3 ) );
   float vlongpre = 96.0 * lj.eps * mp.pi * mp.density;
   float vlong = -1.0 * vlongpre * ( lj.sig12 / ( 9.0 * lj.rcut9 ) - lj.sig6 / ( 6.0 * lj.rcut3 ) ); 

   // temperature factor for velocity scaling
   // TODO: If this not needed elsewhere then just leave
   //       it locally in the initialize velocities function
   float xmass = mp.MW * 100.0 / 6.0220;
   float xmassi = 1.0 / xmass;
   float tfac = 3.0 * mp.float_N * mp.kb * T * xmassi;

   // initialization of atomic positions
   initialize_positions(&atoms,mp.side);

   // initialization of atomic velocities
   initialize_velocities(&atoms,tfac);   

   // main loop:
   //           (1) solve for energy/force
   //           (2) update particle positions/velocities
   int n_timesteps = cl_args.n_timesteps;
   int xyz_freq = cl_args.xyz_freq;
   int thermo_freq = cl_args.thermo_freq;

   FILE *fp_out;
   if ( xyz_freq != 0 ) fp_out = fopen("traj.xyz","w");
   
   int i;
   for (i=0; i<n_timesteps; i++)
   {
      if ( i%xyz_freq == 0 )
         print_xyz(fp_out,&atoms,N);

      if ( i%thermo_freq == 0 ) {
         // calculate properties
         // output properties
      }

   }


   if ( xyz_freq != 0 ) fclose(fp_out);
   free_atoms(&atoms);
}

void allocate_atoms( Atoms * myatoms, int n_atoms )
{
   myatoms->xx = safe_malloc_float( n_atoms );
   myatoms->yy = safe_malloc_float( n_atoms );
   myatoms->zz = safe_malloc_float( n_atoms );
   myatoms->vx = safe_malloc_float( n_atoms );
   myatoms->vy = safe_malloc_float( n_atoms );
   myatoms->vz = safe_malloc_float( n_atoms );
   myatoms->N = n_atoms;
}

float * safe_malloc_float(int vec_size)
{
   float * vec;
   vec = (float *)malloc( vec_size * sizeof(float) );
   if ( vec == NULL ) {
      printf("Allocation failed, exiting.\n");
      exit(-1);
   }
   return vec;
}

void free_atoms( Atoms * myatoms )
{
   free(myatoms->xx);
   free(myatoms->yy);
   free(myatoms->zz);
   free(myatoms->vx);
   free(myatoms->vy);
   free(myatoms->vz);
}


void print_xyz(FILE * handle,Atoms * myatoms, int n_atoms)
{

   fprintf(handle,"%d\n",n_atoms);
   fprintf(handle,"atoms\n");
   int i;
   for (i=0; i<n_atoms; i++) {
      fprintf(handle,"C     %10.5f %10.5f %10.5f\n",
              myatoms->xx[i],
              myatoms->yy[i],
              myatoms->zz[i] );
   }

}

void initialize_positions(Atoms * myatoms, float box_length)
{
   int n_atoms = myatoms->N;
   float float_N = (float)n_atoms;
   float box_length_float = cbrtf( float_N ); // from <math.h>
   int box_length_round = (int)box_length_float;
   float box_length_round_float = (float)box_length_round;
   if ( box_length_float - box_length_round_float > 1.0E-14 ) {
      box_length_round++;
      box_length_round_float = (float)box_length_round;
   }

   int cur_atom_cnt = 0;
   float atom_offset = box_length / box_length_round_float;
   int ix,iy,iz;
   for ( ix=0; ix < box_length_round; ix++) {
      for ( iy=0; iy < box_length_round; iy++) {
         for ( iz=0; iz < box_length_round; iz++) {
            if ( cur_atom_cnt < n_atoms ) {
               myatoms->xx[cur_atom_cnt] = atom_offset*(float)ix;
               myatoms->yy[cur_atom_cnt] = atom_offset*(float)iy;
               myatoms->zz[cur_atom_cnt] = atom_offset*(float)iz;
            }
            cur_atom_cnt++;
         }
      }
   }
}

void initialize_velocities(Atoms * myatoms, float tempfac)
{

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

void calc_energy()
{

}
