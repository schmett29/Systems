/*
David Schmetterling
Section 02
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stock.h"

stock_t * newStock(char *name, float closingSharePrice, float openingSharePrice, int numberOfShares){
	stock_t *S = (stock_t *)malloc(sizeof(stock_t));
	int thename;
  	S->stockSymbol = (char *) malloc(sizeof(char)*thename+1);
  	strcpy(S->stockSymbol, name);
	S->closingSharePrice = closingSharePrice;
	S->openingSharePrice = openingSharePrice;
	S->numberOfShares = numberOfShares;
	S->getPrice = getPrice;
	S->getTotalDollarAmount = getTotalDollarAmount;
	S->getPercentChange = getPercentChange;
	S->toString = toString;
  	return S;
}

float getPrice(void * S){
	stock_t *stock = (stock_t *) S;
	return stock->closingSharePrice;
}

float getTotalDollarAmount(void * S){
	stock_t *stock = (stock_t *) S;
	return stock->closingSharePrice * (float) stock->numberOfShares;
}

float getPercentChange(void * S){
	stock_t *stock = (stock_t *) S;
	return (stock->closingSharePrice - stock->openingSharePrice) / stock->openingSharePrice;
}
void toString(void * S){
	stock_t *stock = (stock_t *) S;
	printf("Symbol: %s\tClosing: %.4f\tOpening: %.4f\tPctChange: %.4f\n",
		stock->stockSymbol, stock->closingSharePrice, stock->openingSharePrice, stock->getPercentChange(stock));
}