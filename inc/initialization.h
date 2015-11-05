
#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "atoms.h"
#include "params.h"

void initialize_positions(Atoms *, float);
void initialize_velocities(Atoms *, misc_params *, float);

#endif