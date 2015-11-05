
#ifndef ENERGY_FORCE_H
#define ENERGY_FORCE_H

#include "params.h"
#include "atoms.h"

void compute_long_range_correction(lj_params *, misc_params *,
                                   float *, float * );

void compute_energy_and_force();

#endif