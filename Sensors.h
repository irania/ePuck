#pragma once
#ifndef SENSORS_GAURD
#define SENSORS_GAURD

#include<limits.h>
#include<math.h>
#include<iostream>
#include <float.h>
#include "Global.h"


#define MAX_DISTANCE 300
#define DISTANCES 7
#define PI 3.14159


class Sensors
{
public:
	
	double sensor_model_std[SENSORS_NUMBER][DISTANCES]; 
	int sensor_model_mean[SENSORS_NUMBER][DISTANCES]; 
	
	Sensors(void);
	int distance_to_sensor(int sensor_number,double value);
	void print_distance_sensors(double *sensors_value);
	int** distance_all_sensors(double *sensors_value);
	int normal_dist(int sensors_value,int distance,int sensor_number);
};

#endif