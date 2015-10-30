
typedef struct {
   float * xx; // array of x positions of atoms
   float * yy; // array of y positions of atoms
   float * zz; // array of z positions of atoms
   float * vx; // array of x-component of velocity of atoms
   float * vy; // array of y-component of velocity of atoms
   float * vz; // array of z-component of velocity of atoms
   int N; // number of atoms
} Atoms;
