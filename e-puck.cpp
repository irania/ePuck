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
#include "AllParticles.h"
#include "Sensors.h"
#include "Particle.h"
#include "Odometry.h"




#define TIME_STEP 64
#define PARTICLE_SCALE 5

using namespace std;

int height;
int width;
int scale;
bool** map;
Odometry epuck_odometry;
AllParticles allParticles;
Sensors sens;


int counter = 50;




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


/*******particle filter*******/
void particle_filter(){

	allParticles = *(new AllParticles());
	vector<Particle> particles = allParticles.generate_uniform_samples(map,height,width,PARTICLE_SCALE);
    //allParticles.print_particles();



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
	//epuck_odometry = *(new Odometry());
	/* main loop */
	while (wb_robot_step(TIME_STEP) != -1){
		/* get sensors values */
		for (i = 0; i < 8; i++) {
			sensors_value[i] = wb_distance_sensor_get_value(distance_sensor[i]);
		}
		const double *a = wb_accelerometer_get_values(accelerometer);
		

		/* compute odometry and speed values*/
		epuck_odometry.compute_odometry();
		for (i = 0; i < 2; i++) {
			speed[i] = 0.0;
			for (j = 0; j < 8; j++) {
				speed[i] += braitenberg_coefficients[j][i] * (1.0 - (sensors_value[j] / RANGE));
			}
		}

		/* ADOLPH TEAM CODES*/
		epuck_odometry.compute_location();	
		epuck_odometry.print_location();
		sens.print_distance_sensors(sensors_value);


		printf("sensors value:  ");
		for(int i=0;i<8;i++){
			printf(" %f ",sensors_value[i]);

		}
		printf("\n");


		/* set speed values */
		wb_differential_wheels_set_speed(speed[0], speed[1]);
		allParticles.move_particles(epuck_odometry.delta_x,epuck_odometry.delta_y,epuck_odometry.delta_teta);
		counter--;
		if(counter==0)
			break;
		
	}
	allParticles.write_to_file();
	wb_differential_wheels_set_speed(0, 0);
	wb_robot_cleanup();

	return 0;
}
