
#ifndef ENERGY_FORCE_H
#define ENERGY_FORCE_H

#include "params.h"
#include "atoms.h"

void compute_long_range_correction(const lj_params *, const misc_params *,
                                   float *, float * );

void compute_energy_and_force( Atoms *, const lj_params *, const misc_params * );

float minimum_image( const float, const float, const float );

#endif