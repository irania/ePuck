#include <webots/differential_wheels.h>
#include <iostream>
#include <math.h>

#define WHEEL_RADIUS 0.0205
#define AXLE_LENGTH 0.052
#define ENCODER_RESOLUTION 159.23
#define RANGE (1024 / 2)

class Odometry{
	public:
		double dl;
		double dr;
		double da;
		double pdl;
		double pdr;
		double pda;
		double x;
		double y;
		double teta;
	 
		Odometry::Odometry(){
		dl=0;dr=0;da=0;
		x=0;y=0;teta=0;
		}
		void compute_odometry();
		void compute_location();
		void print_location();
};