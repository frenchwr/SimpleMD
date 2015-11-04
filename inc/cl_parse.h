
typedef struct {
   int N; // number of atoms in simulation
   int n_timesteps; // number of simulation timesteps
   int xyz_freq; // output frequency (in timesteps) of atomic coordinates
   int thermo_freq; // output frequency of thermodynamic quantities
} args;

args parse_command_line(int,char **);
int check_arg_sane( char **, int, int );