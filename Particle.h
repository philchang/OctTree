#include "dVector.h"
#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
  int id;
  dVector pos;
public: 
  Particle( int i, double x, double y, double z) {
    id = i;
    pos[0] = x; pos[1] = y; pos[2] = z;
  }

  int getId(){ return id;}

  dVector getPosition() {
    return pos;
  }
};

#endif