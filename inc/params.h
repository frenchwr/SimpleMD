
#ifndef PARAMS_H
#define PARAMS_H

typedef struct {
   float sig; // collision diameter
   float sig6; // sig^6
   float sig12; // sig^12
   float eps; // well depth (K)
   float rcut; // interaction cutoff
   float rcut2; // rcut^2
   float rcut3; // rcut^3
   float rcut9; // rcut^9
} lj_params;

typedef struct {
   float dt; // timestep
   float pi; // 3.14
   float kb; // Bolztmann's Constant (aJ/molecule/K)
   float float_N; // # atoms as float
   float side; // length of side of box
   float sideh; // half length of box
   float density; // density of particles in box
   float xmass; // particle mass
   float xmassi; // inverse of particle mass
} misc_params;

void set_params(lj_params *, misc_params *, const int, const float);

#endif