#ifndef PARTICLES_GAURD
#define PARTICLES_GAURD

#include<iostream>

class Particle
{
   public:
      int x;   
	  int y;
	  double orientation;
      double weight;
	  Particle(int x_,int y_,double weight_,double orint_);

};

#endif