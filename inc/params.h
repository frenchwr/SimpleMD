
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
   float dt2;
   float dt2h;
   float pi;
   float kb; // Bolztmann's Constant (aJ/molecule/K)
   float MW; // molecular weight (grams/mole)
   float float_N;
   float Vol;
   float side;
   float sideh;
   float density;
} misc_params;

void set_params(lj_params *, misc_params *, int, float);