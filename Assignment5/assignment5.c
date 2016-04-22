/*
David Schmetterling
Section 02
*/

#include "definitions.h"

int main(int argc,char *argv[]){
	// LinkedList = NULL;
	int *tid;
	int i, j;
	int total_num_read=0;

	if(argc < 2 ) {
    	printf("USAGE: smk # of times agents runs\n");
    	exit(1);
  	}
  	i = atoi(argv[1]);
  	pthread_t sens[i];

 	// create the conditional variable
 	pthread_cond_init(&self, NULL);
  
  	// Create THE MONITOR MUTEX
  	if (pthread_mutex_init(&LL, NULL)) {
  		perror("pthread_mutex_init");
   	 	exit(1);
 	 }

	/*
	//Create an agent thread
  	if((times = (int *)malloc(sizeof(int))) == NULL) {
    	//I am using malloc as a way to make sure that each * thread uses different memory
    	perror("malloc");
    	exit(1);
  	}
  	*times = atoi(argv[1]);
  	if (pthread_create(&(ag), NULL, (void *)agent, times ) != 0) {
   		perror("pthread_create");
    	exit(1);
  	}
  	*/

	/* create sensor threads */
	for(j=0;j<10;j++) {
		if((tid = (int *)malloc(sizeof(int))) == NULL) {
			perror("malloc");
			exit(1);
		}
		*tid = i; /* use tid to keep track of which thread is running */
		fprintf(stdout,"creating sensors\n");
		if (pthread_create(&(sens[i]), NULL, (void *)sensor, tid) != 0) {
			fprintf(stdout,"failing here %d\n",i);
		    perror("pthread_create");
		    exit(1);
		}
		fprintf(stdout,"created sensor %d\n",i);
		}

	// kickoff calculator
	if(pthread_create(&(calc), NULL, (void *)calc_temp, NULL) != 0) {
  		fprintf(stdout,"failing here too!");
  		perror("pthread_create");
  		exit(1);
	}

	/* wait for calculator to finish */
	pthread_join(calc, NULL);
	fprintf(stdout,"Calculator has finished.\n");

	// exit program now that calc is done 
	exit(0);
 }