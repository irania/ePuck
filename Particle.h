#ifndef PARTICLES_GAURD
#define PARTICLES_GAURD

#include<iostream>
#include<math.h>
#include "Global.h"


#define DISTANCES 7
#define SCALE 2
#define WALL 1
#define SIGMA_W 0.69

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
	  void update_weight(int** robot_sensor,bool** map);
	  double get_manhatan_distance(int* sens_distance,int** robot_sensor);

};

#endif