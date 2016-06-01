#include "Odometry.h"


void Odometry::compute_odometry() {
	pdl=dl;
	pdr=dr;
	pda=da;
	double l = wb_differential_wheels_get_left_encoder();
	double r = wb_differential_wheels_get_right_encoder();
	dl = l / ENCODER_RESOLUTION * WHEEL_RADIUS; // distance covered by left wheel in meter
	dr = r / ENCODER_RESOLUTION * WHEEL_RADIUS; // distance covered by right wheel in meter
	da = (dr - dl) / AXLE_LENGTH; // delta orientation
	printf("estimated distance covered by left wheel: %g m.\n",dl);
	printf("estimated distance covered by right yasaman: %g m.\n",dr);
	printf("estimated change of orientation: %g rad.\n",da);
}

void Odometry::compute_location(){
	double delta_l = dl - pdl;
	double delta_r = dr - pdr;
	printf("diff: [%f , %f , %f]\n",x,y,teta);
	delta_teta = (delta_r - delta_l)/AXLE_LENGTH;
	double delta_d = (delta_l+delta_r)/2;
	delta_y = delta_d*cos(da+(delta_teta)/2);
	delta_x = delta_d*sin(da+(delta_teta)/2);

	x = x-delta_x;
	y= y-delta_y;
	teta = teta+delta_teta;
}

void Odometry::print_location(){
	printf("i am in: [%f , %f , %f]\n",x,y,teta);
}