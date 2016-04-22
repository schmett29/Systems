/*
David Schmetterling
Section 02
*/

#include "definitions.h"

void Controller(){
  sensorCount = 0;
  head = NULL;
  LLsize = 0;
  cyclecount = 1;
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
  // enter 10 temperatures associated with this thread
  for (i=1;i<11;i++) {
    if(pthread_mutex_lock(&SENSORS)) {
      perror("pthread_mutex_lock");
      exit(1);
    }
    addIt(theSensor);
    if(LLsize == 10){
      calc_temp(head);
      printf("temp calculated\n");
      resetLL(head);
      puts("LL Reset");
      pthread_cond_broadcast(&self);
      
    }
  }
  return;
}

void addIt(sensor_t *theSensor){
    printf("Adding sensor %d\n",theSensor->ID);
    
    srand(theSensor->ISRN);
    theSensor->temp = rand()%100;
    printf("The random temp is %d\n", theSensor->temp);
    head = insertSensorIntoLinkedList(head, theSensor);
    LLsize++;
    printf("LLsize: %d\n", LLsize);
    while(LLsize != 10){
      pthread_cond_wait(&self, &SENSORS);
    }
    pthread_mutex_unlock(&SENSORS);
    return;
}

void calc_temp(sensor_t *head) {
  int sum=0;
  sensor_t *temp;
  temp = head;
  while(temp != NULL){
    sum = sum + temp->temp;
    printf("the sum so far is: %d\n",sum );
    temp = temp->next;
  }
  fprintf(stdout,"Avg for Cycle #%d = %d\n",cyclecount,(sum/10));
  return;
  //totalsum = totalsum + sum;
//fprintf(stdout,"Avg for All Sensors = %d\n",(totalsum/100));
}

void resetLL(sensor_t *head){
  head = NULL;
  LLsize = 0;
  puts("Going to next cycle");
  cyclecount++;
}

sensor_t * insertSensorIntoLinkedList(sensor_t * head, sensor_t * theSensor){
  //insert new Sting at the end of list
  sensor_t *q;
  if (head == NULL){
    //head = theSensor;
    return theSensor;
  }
  q = head;
  while (q->next != NULL){
    q=q->next;
  }
  q->next = theSensor;
  printf("sensor has been added with an random number id of %d and an ID of %d\n", theSensor->ISRN, theSensor->ID);
  return head;
}
