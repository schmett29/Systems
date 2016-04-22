/*
David Schmetterling
Section 02
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20

typedef  struct stock{
    char * stockSymbol;
    float closingSharePrice;
    float openingSharePrice;
    int numberOfShares;
    float (* getPrice) (void * S);
    float (* getTotalDollarAmount)(void * S);
    float (* getPercentChange)(void * S);
    char * (* toString)( void * S);
}stock_t;