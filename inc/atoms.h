
#ifndef ATOMS_H
#define ATOMS_H

typedef struct {
   float * xx; // array of x positions of atoms
   float * yy; // array of y positions of atoms
   float * zz; // array of z positions of atoms
   float * vx; // array of x-component of velocity of atoms
   float * vy; // array of y-component of velocity of atoms
   float * vz; // array of z-component of velocity of atoms
   float * fx; // array of x-component of force acting on atoms
   float * fy; // array of y-component of force acting on atoms
   float * fz; // array of z-component of force acting on atoms
   int N; // number of atoms
   float pot_energy; // potential energy of system
   float virial; // virial of system
} Atoms;

void allocate_atoms(Atoms *,int);
float * safe_malloc_float(int);
void free_atoms(Atoms *);

#endif
