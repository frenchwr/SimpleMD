
#ifndef TIMER_H
#define TIMER_H

// By declaring this variable as extern it 
// is made visible to all external files in the
// source tree once it's declared as global from
// mddriver.c
extern double timer[4];

void initialize_timer( double * );
void timeit( int, int, double * );

#endif