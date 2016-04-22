/*
David Schmetterling
Section 02
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct sensorContainer{

}sensorContainer_t;


pthread_cond_t self;
pthread_t ag;

int temps[10][10];

pthread_mutex_t LL;
pthread_mutex_t CALC;

void sensor(int * id);
