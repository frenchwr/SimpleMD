#include "timer.h"
#include <sys/time.h> // works with GCC, not sure about intel
#include <stdlib.h>

void initialize_timer( double * time_array )
{

   int i;
   for ( i=0; i < 4; i++) time_array[i] = 0.0;

}

void timeit( int array_element, int mode, double * time_array )
{

   static struct timeval tv[4][2];

   gettimeofday(&tv[array_element][mode],NULL);
   
   if ( mode == 1 )
      time_array[array_element] +=
         (double) ( tv[array_element][1].tv_usec - 
                    tv[array_element][0].tv_usec  ) / 1000000 +
         (double) ( tv[array_element][1].tv_sec - 
                    tv[array_element][0].tv_sec);

}