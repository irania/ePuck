#include "Sensors.h"

Sensors::Sensors(void)
{
	//int s[SENSORS_NUM][DISTANCES]   = {{1958, 805, 480, 369, 324, 303, 300},
	//						 {2745, 683, 380, 280, 228, 184, 173},
	//						 {3634, 907, 425, 301, 251, 215, 197},
	//						 {2028, 824, 733, 642, 610, 591, 582},
	//						 {1875, 789, 565, 480, 444, 417, 403},
	//						 {2921, 1415, 1092, 977, 924, 893, 877},
	//						 {3730, 980, 477, 326, 261, 224, 204},
	//						 {1972, 902, 647, 555, 515, 492, 479}};
	int s[SENSORS_NUM][DISTANCES]   = {{2211,676,306,34,20,15,11},
	{2211,676,306,34,20,15,11},
	{2211,676,306,34,20,15,11},
	{2211,676,306,34,20,15,11},
	{2211,676,306,34,20,15,11},
	{2211,676,306,34,20,15,11},
	{2211,676,306,34,20,15,11},
	{2211,676,306,34,20,15,11}};
	for(int i=0;i<SENSORS_NUM;i++)
		for(int j=0;j<DISTANCES;j++)
			sensor_model[i][j] = s[i][j];


}



void Sensors:: print_distance_sensors(double *sensors_value){
	printf("sensors distance to wall:  ");
	for(int i=0;i<8;i++){
		printf(" %d ",distance_to_sensor(i,sensors_value[i]));

	}
	printf("\n");
}

int* Sensors:: distance_all_sensors(double *sensors_value){
	int result[SENSORS_NUM];
	for(int i=0;i<SENSORS_NUM;i++){
		result[i] = distance_to_sensor(i,sensors_value[i]);

	}
	return result;
}

int Sensors:: distance_to_sensor(int sensor_number,double value){

	int l=NOT_IN_RANGE; //last sensor is less value
	double dl= DBL_MAX; // distance to l
	int b=NOT_IN_RANGE; //last sensor is biger than value
	double db= DBL_MAX; // distance to b

	for(int j=0;j<DISTANCES;j++){
		if(sensor_model[sensor_number][j]< value){

			b = j;
			db = abs(value - sensor_model[sensor_number][b]);

			if(j!=0){
				l=j-1;
				dl = abs(value - sensor_model[sensor_number][l]);

			}

			break;
		}

	}
	if(l==NOT_IN_RANGE && b==NOT_IN_RANGE){// for very little values

		b=DISTANCES-1;
		db= abs(value - sensor_model[sensor_number][b]);

	}


	if(l!=NOT_IN_RANGE && b!=NOT_IN_RANGE){

		return dl<db?l+1:b+1;

	}else{
		if(l==NOT_IN_RANGE){

			if(dl<MAX_DISTANCE){
				return l+1;
			}
			else
				return NOT_IN_RANGE;
		}else{
			if (b==NOT_IN_RANGE){

				if(db<MAX_DISTANCE)
					return b+1;
				else
					return NOT_IN_RANGE;

			}
		}
	}

}