
#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "atoms.h"
#include "params.h"

void initialize_positions(Atoms *, const float, const float);
void initialize_velocities(Atoms *, const misc_params *, const float);

#endif