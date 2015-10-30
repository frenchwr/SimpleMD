#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include "atoms.h"

typedef struct {
   int N; // number of atoms in simulation
   int n_timesteps; // number of simulation timesteps
   int xyz_freq; // output frequency (in timesteps) of atomic coordinates
   int thermo_freq; // output frequency of thermodynamic quantities
} args;

// blah blah blah just
// an arbitrary change to the file

// forward declarations
void driver(int,char **);
args parse_command_line(int,char **);
int check_arg_sane( char **, int, int );
void allocate_atoms(Atoms *,int);
float * safe_malloc_float(int);
void free_atoms(Atoms *);
void print_atoms(Atoms *);
void print_xyz(FILE *,Atoms *, int);
void initialize_positions(Atoms *, float);
void initialize_velocities(Atoms *);

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
   int N = cl_args.N;
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
   float sig = 3.884; // collision diameter
   float eps = 137.0; // well depth (K)
   float MW = 16.042; // molecular weight (grams/mole)
   float rcut = 15.0; // interaction cutoff

   // Other parameters
   float dt = 2.0; // timestep

   // Compute other parameters that get reused
   float dt2 = dt * dt;
   float dt2h = 0.5 * dt2;
   float float_N = (float)N;
   float Vol = float_N * Vn;
   float side = powf(Vol,1.0/3.0);
   printf("side: %10.4f\n",side);
   float sideh = 0.5 * side;
   float density = 1.0 / Vn;
   float sig6 = powf(sig,6.0);
   float sig12 = powf(sig,12.0);
   float rcut2 = rcut * rcut;
   

   // initialization of atomic positions
   initialize_positions(&atoms,side);

   // initialization of atomic velocities
   initialize_velocities(&atoms);   

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

args parse_command_line(int argc,char ** argv)
{

   // defaults
   args cl_args;
   cl_args.N = 100;
   cl_args.n_timesteps = 10000;
   cl_args.xyz_freq = 100;
   cl_args.thermo_freq = 100;

   int cnt = 1;
   while ( cnt < argc )
   {

      if ( !strcmp(argv[cnt],"-N") ) 
         cl_args.N = check_arg_sane( argv,++cnt,argc );
      else if ( !strcmp(argv[cnt],"-ts") ) 
         cl_args.n_timesteps = check_arg_sane( argv,++cnt,argc );
      else if ( !strcmp(argv[cnt],"-xyz") ) 
         cl_args.xyz_freq = check_arg_sane( argv,++cnt,argc );
      else if ( !strcmp(argv[cnt],"-o") ) 
         cl_args.thermo_freq = check_arg_sane( argv,++cnt,argc );
      else if ( !strcmp(argv[cnt],"--help") || !strcmp(argv[cnt],"-h") ) {
         printf("Usage: ./run_md [-N <n_particles>] [-ts <n_timesteps>] [-xyz <xyz_file_output_frequency>] [-o <thermo_output_frequency>]\n");
         printf("Defaults:\nn_particles: 100\nn_timesteps: 10000\nxyz_file_output_fequency: 100\nthermo_output_frequency: 100\n");
         exit(-1);
      }
      else {
         printf("\n***Error: Unrecognized CL option: %s\n\n",argv[cnt]);
         printf("Usage: ./run_md [-N <n_particles>] [-ts <n_timesteps>] [-xyz <xyz_file_output_frequency>] [-o <thermo_output_frequency>]\n");
         printf("Defaults:\nn_particles: 100\nn_timesteps: 10000\nxyz_file_output_fequency: 100\nthermo_output_frequency: 100\n");
         exit(-1);
      }
      cnt++;

   }

   printf("=======Command line arguments=======\n");
   printf("N_atoms: %d\n",cl_args.N);
   printf("n_timesteps: %d\n",cl_args.n_timesteps);
   printf("xyz_file_output_frequency: %d\n",cl_args.xyz_freq);
   printf("thermo_output_frequency: %d\n",cl_args.thermo_freq);
   printf("====================================\n");

   return cl_args;

}

int check_arg_sane( char ** arg_strs, int arg_i, int n_args )
{

   if ( n_args <= arg_i ) {
      printf("Expected integer after flag: %s\n",arg_strs[arg_i-1]);
      exit(-1);
   }

   char * arg_str = arg_strs[arg_i];
   int length = strlen(arg_str);
   int i;
   for (i=0; i<length; i++) {
      if ( !isdigit(arg_str[i]) ) {
         printf("arg: %s should be a non-negative integer\n",arg_str);
         exit(-1);           
      }
   }

   int result = atoi(arg_str);
   if ( result < 1 ) {
      printf("arg: %s should be greater than zero!\n",arg_str);
      exit(-1);
   }

   return result;

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

void initialize_velocities(Atoms * myatoms)
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
   
}













