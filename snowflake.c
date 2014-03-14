#include <stdio.h>
#include <stdlib.h>

#define SIZEX 	500
#define SIZEY 	250
#define STEP 	4

#define FRAME_SKIP 500000

#define CREATE_FROM_EDGE

typedef struct{
	int x,y;
} point;

int m[SIZEX][SIZEY];
point particle;

void plot(point particle){
	printf("\033[2J\033[1;1H");

	int i,j;
	for(i=0;i<SIZEY;i++){
		for(j=0;j<SIZEX;j++){
			if(m[j][i]){
				printf("#");
			}else if((particle.x==j) & (particle.y==i)){
				printf("*");
			}else
				printf(" ");
		}
		printf("\n");
	}
}

void create(){
#ifndef CREATE_FROM_EDGE
	// Create a new particle
	particle.x = rand()%SIZEX;
	particle.y = rand()%SIZEY;
#else
	// Create a new particle at the boarder
	particle.x = (rand()%2)*(SIZEX-1);
	particle.y = (rand()%2)*(SIZEY-1);
#endif
}

int isValid(){
	return 	(particle.x<SIZEX)&(particle.x>=0)&
		(particle.y<SIZEY)&(particle.y>=0);
}

int touch(){
	int t;
	
	t = m[particle.x+0][particle.y+0];
	if(particle.x < SIZEX-1)
		t|= m[particle.x+1][particle.y+0];
	if(particle.y < SIZEY-1)
		t|= m[particle.x+0][particle.y+1];
	if(particle.x > 0)
		t|= m[particle.x-1][particle.y+0];
	if(particle.y > 0)
		t|= m[particle.x+0][particle.y-1];
	return 	t;
}

void solidify(){
	m[particle.x][particle.y] = 1;
	particle.x = -1;
	particle.y = -1;
}

int getStep(){
	int step;
	step = rand()%(STEP*2+1); // +1 to accont for zero, *2 for direction
	return step-STEP;
}

void randomWalk(){
	particle.x += getStep();
	particle.y += getStep();
	//printf("particle at x:%d y:%d %d",particle.x,particle.y,touch());
}

int isFilled(){
	int i,j;
	for(i=0;i<SIZEY;i++){
		if(m[0][i])
			return 1;
		if(m[SIZEX-1][i])
			return 1;
	}
	for(j=0;j<SIZEX;j++){	
		if(m[j][0])
			return 1;
		if(m[j][SIZEY-1])
			return 1;
	}
	return 0;
}

void main(){

	// Place initial particle
	m[SIZEX/2][SIZEY/2] = 1;

	// Randomize
	time_t t;
 	srand((unsigned) time(&t));

	create();	

	int frame;
	long count=0;
	while(!isFilled()){
		// Plot
		if(frame++>=FRAME_SKIP){
			frame = 0;
			plot(particle);
		}
		
		if(touch()){
			solidify();
		}else{
			randomWalk();
		}

		if(!isValid()){
			create();
		}
		
		count++;
	}

	plot(particle);
	printf("Finished after %ld iterations \n",count);

}
