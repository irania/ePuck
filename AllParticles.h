#pragma once
#ifndef ALLPARTICLES_GAURD
#define ALLPARTICLES_GAURD

#include "Particle.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <float.h>


#define WALL 1
#define FREE 0
#define DISTANCES_NUMBER

using namespace std;

class AllParticles
{
public:
	vector<Particle> particles;
	int particles_number;
	int scale;//TODO meghdar dehi
	bool** map;
	int height;
	int width;


	AllParticles(void);
	void move_particles(double delta_x,double delta_y,double delta_teta);
	vector<Particle> generate_uniform_samples(bool** map,int height,int width,int particle_scale);
	void print_particles();
	void write_to_file();
	void sensors_distance();
	void resample();
	double random(double fmin, double fmax);
	void updat_all_weights();
	void updat_all_weights(int **sensors_distance);
};

#endif