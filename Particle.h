#ifndef PARTICLES_GAURD
#define PARTICLES_GAURD

#include<iostream>
#include<math.h>


#define SENSORS_NUMBER 8
#define DISTANCES 7
#define SCALE 2
#define WALL 1

class Particle
{
   public:
      int x;   
	  int y;
	  double orientation;
      double weight;
	  static const double SENSORS_ORIENTATION[];

	  Particle(int x_,int y_,double weight_,double orint_);
	  int* sensors_distance(bool** map);

};

#endif