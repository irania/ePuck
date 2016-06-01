#pragma once
#include<limits.h>
#include<math.h>

#define SENSORS_NUM 8
#define DISTANCES 7
#define MAX_DISTANCE 300
#define NOT_IN_RANGE -1

class Sensors
{
public:
	int sensor_model[SENSORS_NUM][DISTANCES]; 
	
	Sensors(void);
	~Sensors(void);
	int distance_to_sensor(int sensor_number,int value);
};

