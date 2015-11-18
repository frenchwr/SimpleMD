#include "atoms.h"
#include <stdio.h>
#include <stdlib.h>

void allocate_atoms( Atoms * myatoms, const int n_atoms )
{
   myatoms->xx = safe_malloc_float( n_atoms );
   myatoms->yy = safe_malloc_float( n_atoms );
   myatoms->zz = safe_malloc_float( n_atoms );
   myatoms->vx = safe_malloc_float( n_atoms );
   myatoms->vy = safe_malloc_float( n_atoms );
   myatoms->vz = safe_malloc_float( n_atoms );
   myatoms->fx = safe_malloc_float( n_atoms );
   myatoms->fy = safe_malloc_float( n_atoms );
   myatoms->fz = safe_malloc_float( n_atoms );
   myatoms->N = n_atoms;
}

float * safe_malloc_float(const int vec_size)
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
   free(myatoms->fx);
   free(myatoms->fy);
   free(myatoms->fz);
}
