#include "timer.h"
#include <sys/time.h> // works with GCC, not sure about intel
#include <stdlib.h>
#include <stdio.h>

void initialize_timer( )
{

   int i;
   for ( i=0; i < 4; i++) timer[i] = 0.0;

}

void timeit( int array_element, int mode )
{

   static struct timeval tv[4][2];

   gettimeofday(&tv[array_element][mode],NULL); // from sys/time.h
   
   if ( mode == 1 )
      timer[array_element] +=
         (double) ( tv[array_element][1].tv_usec - 
                    tv[array_element][0].tv_usec  ) / 1000000 +
         (double) ( tv[array_element][1].tv_sec - 
                    tv[array_element][0].tv_sec);

}

void print_timer()
{
   printf("Total simulation time:         %10.3f secs\n",timer[0]);
   printf("Force/energy time:             %10.3f secs (%5.2f%s)\n",
          timer[1],100.0 * timer[1] / timer[0], "%" );
   printf("Position/velocity update time: %10.3f secs (%5.2f%s)\n",
          timer[2],100.0 * timer[2] / timer[0], "%" );
   printf("Thermo/trajectory output time: %10.3f secs (%5.2f%s)\n",
          timer[3],100.0 * timer[3] / timer[0], "%" );
}