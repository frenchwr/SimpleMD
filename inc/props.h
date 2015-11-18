
#ifndef PROPS_H
#define PROPS_H

#include "atoms.h"
#include "params.h"

void calc_props( const Atoms *, const misc_params *, const float, 
                 const float, const float, float * );
void print_header();
void print_props( const float *, const int );

#endif