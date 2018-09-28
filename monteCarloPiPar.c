/*
 * monteCarloPiPar.c
 *
 *  Created on: 25/09/2018
 *      Author: sd2018
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

int globalCounter=0;
pthread_mutex_t lock= PTHREAD_MUTEX_INITIALIZER;

void resPerThread(void *arg){
	double x,y;
	int pointsThread= *((int *)arg);
	/* Intializes random number generator */
	 srand((unsigned) time(NULL));


	for(int i=0; i<pointsThread; i++){
		x= (double)rand()/(double)RAND_MAX ;
		y=(double)rand()/(double)RAND_MAX ;
		if ((pow(x, 2) + pow(y, 2))<=1){
			pthread_mutex_lock(&lock);
				globalCounter++;
				printf("id: %ld -points: %i\n", (long int)pthread_self(), globalCounter);
			pthread_mutex_unlock(&lock);
		}
	}
}

int main (int argc, char **argv) {

	int totalPoints, pointsPerThread, numThreads;

	totalPoints= atoi(argv[1]); //ler como inteiro
	numThreads= atoi(argv[2]);
	pointsPerThread= totalPoints/numThreads;
	pthread_t threadIDs[numThreads];

	for(int i=0; i<numThreads; i++){
		pthread_create(&threadIDs[i], NULL, (void*)&resPerThread, (void*)&pointsPerThread);
	}

	for(int i=0; i<numThreads; i++){
		pthread_join(threadIDs[i], NULL);
	}


	printf("Total number of points = %i\n", totalPoints);
	printf("Points within Circle = %i\n", globalCounter);
	printf("Pi estimation: = %f\n", 4 * (double)globalCounter / (double)totalPoints);

	return 0;
}



