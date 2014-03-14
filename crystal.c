#include <stdio.h>
#include <stdlib.h>

#define SIZEX 40
#define SIZEY 20
#define STEP 1


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
	// Create a new particle
	particle.x = rand()%SIZEX;
	particle.y = rand()%SIZEY;
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
	printf("particle at x:%d y:%d %d",particle.x,particle.y,touch());
}

void main(){

	// Place initial particle
	m[SIZEX/2][SIZEY/2] = 1;

	// Randomize
	time_t t;
 	srand((unsigned) time(&t));

	create();	

	while(1){
		// Plot
		plot(particle);
		
		if(touch()){
			solidify();
		}else{
			randomWalk();
		}

		if(!isValid()){
			create();
		}


		char trash;

		//scanf("%c",&trash);
	}
	
	
}
