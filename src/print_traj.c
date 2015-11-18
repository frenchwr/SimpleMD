#include "atoms.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

void print_xyz(FILE * handle, const Atoms * myatoms)
{
   timeit(3,0);
   fprintf(handle,"%d\n",myatoms->N);
   fprintf(handle,"atoms\n");
   int i;
   for (i=0; i < myatoms->N; i++) {
      fprintf(handle,"C     %10.5f %10.5f %10.5f\n",
              myatoms->xx[i],
              myatoms->yy[i],
              myatoms->zz[i] );
   }
   timeit(3,1);

}
