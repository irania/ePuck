#include "Sensors.h"

Sensors::Sensors(void)
{
	//int s[SENSORS_NUMBER][DISTANCES]   = {{1958, 805, 480, 369, 324, 303, 300},
	//						 {2745, 683, 380, 280, 228, 184, 173},
	//						 {3634, 907, 425, 301, 251, 215, 197},
	//						 {2028, 824, 733, 642, 610, 591, 582},
	//						 {1875, 789, 565, 480, 444, 417, 403},
	//						 {2921, 1415, 1092, 977, 924, 893, 877},
	//						 {3730, 980, 477, 326, 261, 224, 204},
	//						 {1972, 902, 647, 555, 515, 492, 479}};
	//int s[SENSORS_NUMBER][DISTANCES]   =  {{2211,676,306,34,20,15,11},
	//									{2211,676,306,34,20,15,11},
	//									{2211,676,306,34,20,15,11},
	//									{2211,676,306,34,20,15,11},
	//									{2211,676,306,34,20,15,11},
	//									{2211,676,306,34,20,15,11},
	//									{2211,676,306,34,20,15,11},
	//									{2211,676,306,34,20,15,11}};

	int s[SENSORS_NUMBER][DISTANCES]   =  {{2500,1600,700,400,250,190,100},
										{2500,1600,700,400,250,190,100},
										{2500,1600,700,400,250,190,100},
										{2500,1600,700,400,250,190,100},
										{2500,1600,700,400,250,190,100},
										{2500,1600,700,400,250,190,100},
										{2500,1600,700,400,250,190,100},
										{2500,1600,700,400,250,190,100}};
										

	//double v[SENSORS_NUMBER][DISTANCES] = {{19.69,12.39,13.04,12.70,13.19,15.22,12.34},
	//									{9.06,2.66,3.63,3.51,3.6,3.96,3.57},
	//									{1.5,2.62,4.38,2.45,4.7,4.75,4.28},
	//									{3.34,3.09,3.46,4.46,4.07,4.12,3.32},
	//									{3.66,3.44,2.8,3.3,4.47,3.74,3.36},
	//									{6.91,4.75,4.69,6.06,5.22,6.35,6.21},
	//									{2.59,5.33,5.75,6.17,7.38,5.72,6.83},
	//									{6.02,3.47,5.06,6.23,6.54,6.7,6.37}};
	
	double v[SENSORS_NUMBER][DISTANCES] = {{6.58,5.83,3.6,2,1.58,1.3,1},
										{6.58,5.83,3.6,2,1.58,1.3,1},
										{6.58,5.83,3.6,2,1.58,1.3,1},
										{6.58,5.83,3.6,2,1.58,1.3,1},
										{6.58,5.83,3.6,2,1.58,1.3,1},
										{6.58,5.83,3.6,2,1.58,1.3,1},
										{6.58,5.83,3.6,2,1.58,1.3,1},
										{6.58,5.83,3.6,2,1.58,1.3,1}};

	for(int i=0;i<SENSORS_NUMBER;i++)
		for(int j=0;j<DISTANCES;j++)
			sensor_model_mean[i][j] = s[i][j];

	for(int i=0;i<SENSORS_NUMBER;i++)
		for(int j=0;j<DISTANCES;j++)
			sensor_model_std[i][j] = v[i][j];


}



void Sensors:: print_distance_sensors(double *sensors_value){
	printf("sensors distance to wall:  ");
	for(int i=0;i<8;i++){
		printf(" %d ",distance_to_sensor(i,sensors_value[i]));

	}
	printf("\n");
}

int** Sensors:: distance_all_sensors(double *sensors_value){
	int** result = new int*[SENSORS_NUMBER];
	for(int i=0;i<SENSORS_NUMBER;i++){
		result[i] = new int[2];
		result[i][0] = distance_to_sensor(i,sensors_value[i]);
		result[i][1] = normal_dist(sensors_value[i],result[0][i],i);
	}
	return result;
}

int Sensors:: distance_to_sensor(int sensor_number,double value){

	int l=INFINIT_DISTANCE; //last sensor is less value
	double dl= DBL_MAX; // distance to l
	int b=INFINIT_DISTANCE; //last sensor is biger than value
	double db= DBL_MAX; // distance to b

	for(int j=0;j<DISTANCES;j++){
		if(sensor_model_mean[sensor_number][j]< value){

			b = j;
			db = abs(value - sensor_model_mean[sensor_number][b]);

			if(j!=0){
				l=j-1;
				dl = abs(value - sensor_model_mean[sensor_number][l]);

			}

			break;
		}

	}
	if(l==INFINIT_DISTANCE && b==INFINIT_DISTANCE){// for very little values

		b=DISTANCES-1;
		db= abs(value - sensor_model_mean[sensor_number][b]);

	}


	if(l!=INFINIT_DISTANCE && b!=INFINIT_DISTANCE){

		return dl<db?l+1:b+1;

	}else{
		if(l==INFINIT_DISTANCE){

			if(dl<MAX_DISTANCE){
				return l+1;
			}
			else
				return INFINIT_DISTANCE;
		}else{
			if (b==INFINIT_DISTANCE){

				if(db<MAX_DISTANCE)
					return b+1;
				else
					return INFINIT_DISTANCE;

			}
		}
	}

}

int Sensors:: normal_dist(int sensor_val,int distance,int sensor_number){

	double sigma = sensor_model_std[sensor_number][distance-1];
	double var = pow(sigma,2);
	int mean = sensor_model_mean[sensor_number][distance-1];
	double mean_dist = (double)pow((sensor_val-mean),2);
	double p1 = exp(-mean_dist/2.0*var);
	double p2 = (sigma*sqrt(2*PI));
	double p = p1/p2;

	return floor(p*100);

}