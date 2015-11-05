#include "atoms.h"
#include <stdio.h>
#include <stdlib.h>

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
