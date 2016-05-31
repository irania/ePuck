#include <webots/robot.h>
#include <webots/differential_wheels.h>
#include <webots/distance_sensor.h>
#include <webots/light_sensor.h>
#include <webots/camera.h>
#include <webots/accelerometer.h>
#include <stdio.h>
#include <exception>
#include <Windows.h>
#include <vector>
#include "Particle.h"
#include "Odometry.h"



#define TIME_STEP 64
#define WALL 1

using namespace std;

int height;
int width;
int scale;
int particle_number=1000;
int particle_scale =5;
bool** map;
Odometry epuck_odometry;
int counter = 100;


static void odo(){
		double l = wb_differential_wheels_get_left_encoder();
	double r = wb_differential_wheels_get_right_encoder();
	double dl = l / ENCODER_RESOLUTION * WHEEL_RADIUS; // distance covered by left wheel in meter
	double dr = r / ENCODER_RESOLUTION * WHEEL_RADIUS; // distance covered by right wheel in meter
	double  da = (dr - dl) / AXLE_LENGTH; // delta orientation
	printf("estimated distance covered by left wheel: %g m.\n",dl);
	printf("estimated distance covered by right yasaman: %g m.\n",dr);
	printf("estimated change of orientation: %g rad.\n",da);
}

/****read environment size****/
void read_env_size(){

	char file_name[25]="env.txt";
	FILE* file = fopen (file_name, "r");

	fscanf (file, "%d", &height);   
	fscanf (file, "%d", &width);
	fscanf (file, "%d", &scale); 

	fclose (file);

}

/****read map****/
void read_map(){

	char file_name[25]="map.txt";
	int i;
	int j;
	bool** mat= new bool*[height];
	for(i=0;i<height;++i)
		mat[i]=new bool[width];


	FILE *file;
	file=fopen(file_name, "r");

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++) 
		{
			//Use lf format specifier, %c is for character
			if (!fscanf(file, "%d", &mat[i][j])) 
				break;
			//printf("%d",mat[i][j]);

		}
		//printf("\n");

	}
	fclose(file);
	map = mat;

}

vector<Particle> generate_uniform_samples(){

	//particle_number how much?
	vector<Particle> v;

	int i,j,x,y;

	for (i=0;i<height;i=i+particle_scale){

		for(j=0;j<width;j=j+particle_scale){

            x = j;
		    y = i;
	        while(map[y][x]==WALL){
				y=y+1;
				if(y>=height){
					y=0;
					x=x+1;
				}
				if(x>=width){
					x=0;
				}

			}
			
			Particle* p = new Particle(x,y,1/particle_number,0);
			

			
			v.push_back(*p); 

		}
	}

	particle_number = v.size();
	return v;

}

void print_particles(vector<Particle> particles){
	try{
	int i;
	for(i=0;i<particles.size();i++){

		printf( "particle %d: [%d,%d] w=%f\n",i, particles[i].x,
			particles[i].y,particles[i].weight);

	}
	}catch(...){}

}

/*******particle filter*******/
void particle_filter(){

	 vector<Particle> particles = generate_uniform_samples();
     //print_particles(particles);



}


int main(int argc, char *argv[]) {

	/* define variables */
	WbDeviceTag distance_sensor[8];
	int i,j;
	double speed[2];
	double sensors_value[8];
	double braitenberg_coefficients[8][2] =
	{ {150, -35}, {100, -15}, {80, -10}, {-10, -10},
	{-10, -10}, {-10, 80}, {-30, 100}, {-20, 150} };

	/* initialize Webots */
	wb_robot_init();

	/* get and enable devices */
	WbDeviceTag accelerometer = wb_robot_get_device("accelerometer");
	wb_accelerometer_enable(accelerometer,TIME_STEP*4);
	wb_differential_wheels_enable_encoders(TIME_STEP*4);


	for (i = 0; i < 8; i++) {
		char device_name[4];

		/* get distance sensors */
		sprintf(device_name, "ps%d", i);
		distance_sensor[i] = wb_robot_get_device(device_name);
		wb_distance_sensor_enable(distance_sensor[i],TIME_STEP*4);
	}


	read_env_size();
	read_map();
	particle_filter();
	epuck_odometry = *(new Odometry());
	/* main loop */
	for(;counter>0; counter--) {
		/* get sensors values */
		for (i = 0; i < 8; i++) {
			sensors_value[i] = wb_distance_sensor_get_value(distance_sensor[i]);
		}
		const double *a = wb_accelerometer_get_values(accelerometer);
		

		/* compute odometry and speed values*/
		//epuck_odometry.compute_odometry();
		odo();
		for (i = 0; i < 2; i++) {
			speed[i] = 0.0;
			for (j = 0; j < 8; j++) {
				speed[i] += braitenberg_coefficients[j][i] * (1.0 - (sensors_value[j] / RANGE));
			}
		}

		/* set speed values */
		//epuck_odometry.print_location();
		wb_differential_wheels_set_speed(speed[0], speed[1]);
		
	}

	wb_robot_cleanup();

	return 0;
}
