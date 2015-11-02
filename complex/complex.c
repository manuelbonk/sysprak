#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

void foo(){
	printf("Diese Methode wurde in complex.h deklariert und in complex.c definiert.\n");
	}

int main (int argc, char *argv[]){
	complex a,b;
	a.re=1;
	a.im=2;
	b.re=4;
	b.im=3;
	addCom(a,b);
	subCom(a,b);
	mulCom(a,b);
	divCom(a,b);
	foo();
	return 0;
}
