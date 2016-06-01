#pragma once
#ifndef SENSORS_GAURD
#define SENSORS_GAURD

#include<limits.h>
#include<math.h>
#include<iostream>
#include <float.h>

#define SENSORS_NUM 8
#define DISTANCES 7
#define MAX_DISTANCE 300
#define NOT_IN_RANGE -1

class Sensors
{
public:
	int sensor_model[SENSORS_NUM][DISTANCES]; 
	
	Sensors(void);
	int distance_to_sensor(int sensor_number,double value);
	void print_distance_sensors(double *sensors_value);
	int* distance_all_sensors(double *sensors_value);
};

#endif