
#ifndef PROPS_H
#define PROPS_H

#include "atoms.h"
#include "params.h"

void calc_props( Atoms *, misc_params *, float, float, float, float * );
void print_header();
void print_props( float *, int );

#endif