
#include "Particle.h"

const double Particle::SENSORS_ORIENTATION []= {-0.3,-0.8,-1.57,-2.64,2.64,1.57,0.8,0.3};

Particle :: Particle(int x_,int y_,double weight_,double orint_){
		  x = x_;
		  y=y_;
		  orientation = orint_;
		  weight = weight_;
}

int* Particle::sensors_distance(bool** map){
	
	int result[SENSORS_NUMBER];

	for(int i=0;i<SENSORS_NUMBER;i++){

		result[i] =-1; // first -1
		for(int j=0;j<DISTANCES;j++){
			
			double teta = orientation+SENSORS_ORIENTATION[i];
			int new_x = x+ floor(SCALE*(j+1)*sin(teta));
			int new_y = y+ floor(SCALE*(j+1)*cos(teta));

			if(map[new_y][new_x]==WALL){
				result[i] = j+1;
				break;
			}

		}
	}
	return result;
}
