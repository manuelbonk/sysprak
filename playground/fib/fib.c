#include <stdio.h>
#include <stdlib.h>

int rfib (int n){
	if(n==0 || n==1){
		return n;
	 }
	else if (n>1){
		return n+rfib(n-1);
	}
	else {
		return -1;
	}
}

int ifib (int n){
	if (n < 0){
		return -1;
	}
	if (n == 0 || n == 1){
		return n;
	}
	int prevprev=0;
	int prev=1;
	int result;
	for (int i=2;i<=n;i++){
		result=prevprev+prev;
		prevprev=prev;
		prev=result;
	}
	return result;
}

void pifib(int *n){
	n[0]=0;
	n[1]=1;
	for (int i=2;i<=10;i++){
		n[i]=n[i-2]+n[i-1];
	}
}

int main(int argc, char *argv[]){
	int i = 10;
	int *ip = calloc(i,sizeof(int));
	printf(" rfib(%d)=<%d>\n",i,rfib(i));
	printf(" ifib(%d)=<%d>\n",i,ifib(i));
	pifib(ip);
	printf("pifib(%d)=<%d>\n",i,ip[1]);






	return 0;
}
