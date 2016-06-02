
#include "Particle.h"
#include "Global.h"

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

		result[i] =INFINIT_DISTANCE; // first -1
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


void Particle::update_weight(int** robot_sensor,bool** map){


	int* sens_distance = sensors_distance(map);
	double d = get_manhatan_distance(sens_distance,robot_sensor);
	
	if(weight>0)
	{
		weight = exp(-pow(d,2)/(2*pow(SIGMA_W,2)));
	}


}

double Particle::get_manhatan_distance(int* sens_distance,int** robot_sensor){
	
	const int DISTANCE = 0;
	const int PROBABILITY = 1;
	
	double sum=0;
	for(int i=0;i<sizeof(sens_distance);i++){
		int dif = (robot_sensor[DISTANCE][i]-sens_distance[i]);
		sum +=  (double)(robot_sensor[PROBABILITY][i]*pow(dif,2)*0.01);
	}

	return sqrt(sum);
}
