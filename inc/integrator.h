
#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "params.h"
#include "atoms.h"

void update_positions( Atoms *, misc_params * );
void update_velocities( Atoms *, misc_params * );
void pbc( Atoms *, float, float );

#endif