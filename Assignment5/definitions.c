/*
David Schmetterling
Section 02
*/

#include "definitions.h"

void sensor(int *id) {
	int i=0;
	if(pthread_mutex_lock(&LL)) {
    	perror("pthread_mutex_lock");
    	exit(1);
  	}

  	//pthread_mutex_lock(&SENSORS);
 
  	/* enter 10 temperatures associated with this thread */
  	for (i=0;i<10;i++) {
    	&temps[*id][i] = rand()%110;
    	&total_num_read++;
  	}
  
  	pthread_mutex_unlock(&SENSORS);

  	if(total_num_read == 100){
    	pthread_mutex_unlock(&CALC);
  	}

} /* end sensor */

void calc_temp() {
	int i,j;
	int sum=0,totalsum=0;
	if(pthread_mutex_lock(&CALC)) {
  		perror("pthread_mutex_lock");
  		exit(1);
	}

	for(i=0;i<10;i++) { /* loop for threads */
  		for(j=0;j<10;j++) { /* loops for temps per thread */
			sum = sum + temps[i][j];
  		}
  		fprintf(stdout,"Avg for Sensor %d = %d\n",i,(sum/10));
  		totalsum = totalsum + sum;
	}
	fprintf(stdout,"Avg for All Sensors = %d\n",(totalsum/100));
}
