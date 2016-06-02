#include "AllParticles.h"


AllParticles::AllParticles(void){
	scale=2;
	
}



//***********************move particles***********************
void AllParticles::move_particles(double delta_x,double delta_y,double delta_teta){
	int d_x = (int)(delta_x*scale*100);
	int d_y = (int)(delta_y*scale*100);
	printf( "diff  [%d,%d] w=%f\n", d_x,d_y);
	for(int i=0;i<particles_number;i++){
		particles[i].y -= d_y;
		particles[i].x -= d_x;
		particles[i].orientation += delta_teta;

		if(particles[i].x>=width || particles[i].x<0 ){
			particles[i].weight = - DBL_MAX;
		}else
			if(particles[i].y>=height || particles[i].y<0 ){
				particles[i].weight = - DBL_MAX;
			}else
				if(map[particles[i].y][particles[i].x]==1)
					particles[i].weight = - DBL_MAX;


	}


	
}



//***********************generate particles first time***********************
vector<Particle> AllParticles::generate_uniform_samples(bool** map_,int height_,int width_,int particle_scale){

	//particle_number how much?

	int i,j,x,y;
	map = map_;
	height= height_;
	width = width_;

	particles_number=1000;
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
			Particle p = *(new Particle(x,y,(double)1/particles_number,0));
			

			
			particles.push_back(p);


		}
	}
	particles_number = particles.size();
	return particles;

}



//***********************Print Particles***********************
void AllParticles::print_particles(){
	try{
	int i;
	for(i=0;i<particles.size();i++){

		printf( "particle %d: [%d,%d] w=%f\n",i, particles[i].x,
			particles[i].y,particles[i].weight);

	}
	}catch(...){}

}



//***********************Print Particles to file***********************
void AllParticles::write_to_file(){
  
  ofstream myfile ("particlesinfo.txt");
  if (myfile.is_open())
  {
	  for(int i=0;i<particles_number;i++){
		  myfile << particles[i].x<<" " << particles[i].y<<" "<<particles[i].weight<<" "<<particles[i].orientation<<"\n";	
	  }
	  myfile.close();
  }
  else cout << "Unable to open file";

}


void AllParticles::sensors_distance(){

	for(int i=0;i<particles_number;i++){
		//int sens_dist[][DISTANCES_NUMBER] = particles[i].sensors_distance(map);
	}

}