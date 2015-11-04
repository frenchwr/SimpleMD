#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "cl_parse.h"

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