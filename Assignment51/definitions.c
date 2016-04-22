/*
David Schmetterling
Section 02
*/

#include "definitions.h"

void Controller(){
  sensorCount = 0;
  head = NULL;
  LLsize = 0;
  //totalsum = 0;
}

sensor_t * createSensor(int ISRN, int ID){
  sensor_t *temp;
  temp = malloc(sizeof(sensor_t));
  temp->ISRN = ISRN;
  temp->ID = ID;
  temp->temp = 0;
  temp->next = NULL;
  return temp;
}

void sensor(sensor_t *theSensor) {
  int i = 0;
  printf("I am sensor %d\n",theSensor->ID);
  if(pthread_mutex_lock(&SENSORS)) {
    perror("pthread_mutex_lock");
    exit(1);
  }

  //pthread_mutex_lock(&SENSORS);
 
  /* enter 10 temperatures associated with this thread */
  for (i=0;i<10;i++) {
    srand(theSensor->ISRN);
    theSensor->temp = rand()%100;
    insertSensorIntoLinkedList(head, theSensor);
    LLsize++;
  }
  
  pthread_mutex_unlock(&SENSORS);

  if(LLsize == 10)
    pthread_mutex_unlock(&CALC);

	/*
  int i=0;
  int temp;
  printf("I am sensor %d\n",theSensor->ID);
  srand(theSensor->ISRN);
  // enter 10 temperatures associated with this thread
  while(i<10){
    // this will lock mutex
    printf("sensor %d is about to calculate\n",theSensor->ID);
    calculateAndAdd(theSensor);

    printTempsAndAvg(head);
    resetLL(head);
  }
  i++;
  */
}

void calc_temp() {
  int i,j;
  int sum=0;
  sensor_t *temp;

  if(pthread_mutex_lock(&CALC)) {
    perror("pthread_mutex_lock");
    exit(1);
  }

  for(temp = head; temp->next !=NULL; temp = temp->next){
    sum = sum + temp->temp;
  }
  fprintf(stdout,"Avg for Sensor %d = %d\n",i,(sum/10));
  //totalsum = totalsum + sum;
//fprintf(stdout,"Avg for All Sensors = %d\n",(totalsum/100));
}





/*
void calculateAndAdd(sensor_t *theSensor){
  printf("sensor %d is trying to access LL\n",theSensor->ID);
  pthread_mutex_lock(&lock);
  insertSensorIntoLinkedList(head, theSensor);
  ++LLsize;
  while( LLsize != 10){
      pthread_cond_wait(&self, &lock);  //blocks on cv self, and frees the lock
  }
  pthread_mutex_unlock(&lock);
  return;
}

void printTempsAndAvg(sensor_t *head){

}

void resetLL(sensor_t *head){
  head = NULL;
}
*/


sensor_t * insertSensorIntoLinkedList(sensor_t * head, sensor_t * theSensor){
  //insert new Sting at the end of list
  sensor_t *q;
  if (head == NULL){
    head = theSensor;
    return head;
  }
  q = head;
  while (q->next != NULL){
    q=q->next;
  }
  q->next = theSensor;
  printf("sensor has been added with an random number id of %d and an ID of %d\n", theSensor->ISRN, theSensor->ID);
  return head;
}

/*
void calc_temp() {
	int i,j;
	int sum=0,totalsum=0;
	if(pthread_mutex_lock(&CALC)) {
  		perror("pthread_mutex_lock");
  		exit(1);
	}

	for(i=0;i<10;i++) { // loop for threads
  		for(j=0;j<10;j++) { // loops for temps per thread
			sum = sum + temps[i][j];
  		}
  		fprintf(stdout,"Avg for Sensor %d = %d\n",i,(sum/10));
  		totalsum = totalsum + sum;
	}
	fprintf(stdout,"Avg for All Sensors = %d\n",(totalsum/100));
}
*/
