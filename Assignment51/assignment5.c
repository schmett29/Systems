/*
David Schmetterling
Section 02
*/

#include "definitions.h"

// initialize
// x amount of threads --> create threads
// call sensor
// get rand temp add to list 10 times, wait if its not in the list (untill its not in the list)
// wait till size == number of sensors

int main(int argc,char *argv[]){
	int i, j;

	if(argc < 2 ) {
    	printf("USAGE: smk # of times agents runs\n");
    	exit(1);
  	}
  	i = atoi(argv[1]);
  	pthread_t sens[i];
  	pthread_t calc;
  	srand(time(NULL));

 	// create the conditional variable
 	pthread_cond_init(&self, NULL);
	pthread_mutex_init(&SENSORS, NULL);
	/* create locks */
	if (pthread_mutex_init(&SENSORS, NULL)) {
 		perror("pthread_mutex_init");
  		exit(1);
	}

	if (pthread_mutex_init(&CALC, NULL)) {
  		perror("pthread_mutex_init");
  		exit(1);
	}

	//actually create lock on calculator so it doesn't go
   	// before the sensors complete
	if (pthread_mutex_lock(&CALC)) {
  		perror("pthread_mutex_lock");
  		exit(1);
	}

	//initializes LL + contains variables to play with
	Controller();

	/* create sensor threads */
	for(j=0;j<i;j++) {
		//create node with an integer seed for the random number and an ID number
		fprintf(stdout,"creating sensor node\n");
		sensor_t *theSensor = createSensor(rand()%100,j);
		printf("sensor has been added with an random number id of %d and an ID of %d\n", theSensor->ISRN, theSensor->ID);
		
		//create thread to add to LL
		if(pthread_create(&(sens[j]), NULL, (void *)sensor, theSensor)){
			fprintf(stdout,"failing here %d\n",j);
    		perror("pthread_create");
    		exit(1);
		}
		fprintf(stdout,"created sensor %d\n",j);
	}

	puts("starting calculator");
	// kickoff calculator
	if(pthread_create(&(calc), NULL, (void *)calc_temp, NULL)) {
  		fprintf(stdout,"failing here too!");
  		perror("pthread_create");
  		exit(1);
	}

	// wait for calculator to finish
	pthread_join(calc, NULL);
	fprintf(stdout,"Calculator has finished.\n");

	//printf("Sensor count: %d\n", i);
	puts("All done, bye!");
	// exit program now that calc is done 
	exit(0);
 }