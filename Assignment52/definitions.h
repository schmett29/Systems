/*
David Schmetterling
Section 02
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>

typedef struct sensor{
	int ISRN;
	int ID;
	int temp;
	struct sensor *next;
}sensor_t;

int LLsize;
int sensorCount;
sensor_t *head;
int cyclecount;

pthread_cond_t self;
pthread_mutex_t SENSORS;
pthread_mutex_t CALC;

void sensor(sensor_t *theSensor);
void calc_temp(sensor_t *head);
void addIt(sensor_t *theSensor);
void resetLL(sensor_t *head);
void test(sensor_t *head);
sensor_t * createSensor(int theTemp, int id);
sensor_t * insertSensorIntoLinkedList(sensor_t * head, sensor_t * theSensor);
void Controller();

/*
void calculateAndAdd(sensor_t *theSensor);
void printTempsAndAvg(sensor_t *head);
void resetLL(sensor_t *head);
*/
