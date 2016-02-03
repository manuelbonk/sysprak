#include <stdio.h>
#include <stdlib.h>
#include "matrixBib.h"

int main (int argc, char *argv[]){

	matrix nein= initMatrixRand(3,3);
	prettyPrint(nein);
	matrix doch= initMatrixRand(3,3);
	prettyPrint(doch);
	matrix oh = multMatrix(nein,doch);
	prettyPrint(oh);
//	matrix lol = initMatrixZero(10,10);
	return 0;
}
